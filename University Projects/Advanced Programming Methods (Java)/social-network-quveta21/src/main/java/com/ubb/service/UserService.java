package com.ubb.service;
import com.ubb.domain.*;
import com.ubb.exceptions.*;
import com.ubb.relations.Card;
import com.ubb.relations.Friendship;
import com.ubb.repository.*;
import com.ubb.validation.DuckValidator;
import com.ubb.validation.PersoanaValidator;

import java.sql.SQLException;
import java.util.*;

public class UserService {
    private final UserDBRepository repo;
    private final FriendshipDBRepository friendshipRepo;
    private final CardDBRepository cardRepo;
    private final EventDBRepository eventRepo;
    private final PersoanaValidator persoanaValidator;
    private final DuckValidator duckValidator;

    public UserService(UserDBRepository repo, FriendshipDBRepository friendshipRepo, CardDBRepository cardRepo, EventDBRepository eventRepo) throws SQLException {
        this.repo = repo;
        this.friendshipRepo = friendshipRepo;
        this.cardRepo = cardRepo;
        this.eventRepo = eventRepo;
        this.persoanaValidator = new PersoanaValidator();
        this.duckValidator = new DuckValidator();
    }

    public List<User> getAllUsers() {
        if (repo.getAll().isEmpty())
            throw new NoUsersException();
        return repo.getAll();
    }

    public List<Friendship> getAllFriendships() {
        if (friendshipRepo.getAll().isEmpty())
            throw new RepositoryException("!! Nu Exista Prietenii !!");
        return friendshipRepo.getAll();
    }

    public List<Card<?>> getAllCarduri(){
        if(cardRepo.getAll().isEmpty())
            throw new RepositoryException("!! Nu Exista Carduri !!");
        return cardRepo.getAll();
    }

    public List<Event> getAllEvents() {
        if(eventRepo.getAll().isEmpty())
            throw new RepositoryException("!! Nu Exista Event-uri !!");
        return eventRepo.getAll();
    }

    public void addPersoana(String username, String email, String password,
                            String nume, String prenume, String dataNasterii, String ocupatie) {
        // NU RESPECTA INTEGRITATEA DATELOR DACA STERGEM ELEMENTE DAR MOMENTAN E OK
        int id = repo.getAll().size() + 1;
        Persoana p = new Persoana((long) id, username, email, password, nume, prenume, dataNasterii, ocupatie);
        persoanaValidator.validate(p);
        if (repo.findByUsername(username) != null)
            throw new DuplicateException("!! User " + username + " Exista Deja !!");
        repo.add(p);
    }

    public void addDuck(String username, String email, String password,
                        TipRata tipRata, double viteza, double rezistenta) {
        if (tipRata == null)
            throw new ValidatorException("!! Tip Rata invalid !!");

        int id = repo.getAll().size() + 1;
        Duck d;
        switch(tipRata) {
            case FLYING:
                d = new FlyingDuck((long) id, username, email, password, tipRata, viteza, rezistenta);
                break;
            case SWIMMING:
                d = new SwimmingDuck((long) id, username, email, password, tipRata, viteza, rezistenta);
                break;
            case FLYING_AND_SWIMMING:
                d = new FlyingSwimmingDuck((long) id, username, email, password, tipRata, viteza, rezistenta);
                break;
            default:
                throw new ValidatorException("!! Tip Rata invalid !!");
        }
        duckValidator.validate(d);
        if (repo.findByUsername(username) != null)
            throw new DuplicateException("!! User " +  username + " Exista Deja !!");
        repo.add(d);
    }

    public void removeUser(String username) {
        var user = repo.findByUsername(username);
        if(user != null) {
            // stergem toate prieteniile aferente user-ului
            friendshipRepo.getAll()
                            .removeIf(f -> username.equals(f.getFriend1().getUsername())
                            || username.equals(f.getFriend2().getUsername()));
            //il dezabonam de la toate event-urile la care participa
            for (var event : eventRepo.getAll()) {
                event.getSubscribers().removeIf(obs ->
                        (obs instanceof User u) && u.getUsername().equals(username));
            }
            repo.remove(user);
        } else {
            throw new UserNotFoundException(username);
        }
    }

    public void addFriendship(String username1, String username2) {
        var user1 = repo.findByUsername(username1);
        var user2 = repo.findByUsername(username2);
        if(user1 != null && user2 != null) {
            if(user1.equals(user2))
                throw new ValidatorException("!! User " + username1 + " Nu Poate Fi Prieten Cu El/Ea Insusi/Insasi !!");
            Friendship friendship = new Friendship(user1, user2);
            if (friendshipRepo.getAll().contains(friendship)) {
                throw new DuplicateException("!! Prietenia Dintre " + username1 +
                        " si " + username2 + " Exista Deja !!");
            }
            friendshipRepo.add(friendship);
        } else if(user1 == null) {
            throw new UserNotFoundException(username1);
        } else {
            throw new UserNotFoundException(username2);
        }
    }

    public void removeFriendship(String username1, String username2) {
        var user1 = repo.findByUsername(username1);
        var user2 = repo.findByUsername(username2);
        if(user1 != null && user2 != null) {
            Friendship friendship = new Friendship(user1, user2);
            if (!friendshipRepo.getAll().contains(friendship)) {
                throw new RepositoryException("!! Prietenia Dintre " + username1 +
                        " si " + username2 + " Nu Exista !!");
            }
            friendshipRepo.remove(friendship);
        } else if(user1 == null) {
            throw new UserNotFoundException(username1);
        } else {
            throw new UserNotFoundException(username2);
        }
    }

    public void dfs(User u, Map<User, List<User>> adj, Set<User> visited) {
        visited.add(u);
        for (User v : adj.get(u))
            if(!visited.contains(v))
                dfs(v, adj, visited);
    }

    public void dfsCollect(User u, Map<User, List<User>> adj, Set<User> visited, List<User> road) {
        visited.add(u);
        road.add(u);
        for (User v : adj.get(u))
            if(!visited.contains(v))
                dfsCollect(v, adj, visited, road);
    }

    public int bfsMaxDistance(User start, Map<User, List<User>> adj, List<User> community) {
        Map<User, Integer> dist = new HashMap<>();
        Queue<User> q = new LinkedList<>();
        dist.put(start, 0);
        q.offer(start);

        while(!q.isEmpty()) {
            var current = q.poll();
            for (User v : adj.get(current)) {
                if (community.contains(v) && !dist.containsKey(v)) {
                    dist.put(v, dist.get(current) + 1);
                    q.offer(v);
                }
            }
        }
        return dist.values().stream().max(Integer::compareTo).orElse(0);
    }

    private int getDiameter(List<User> community, Map<User, List<User>> adj) {
        int maxDist = 0;
        for (User u : community)
            maxDist = Math.max(maxDist, bfsMaxDistance(u, adj, community));
        return maxDist;
    }

    public Map<User, List<User>> buildAdjacencyList(List<User> users, List<Friendship> friendships) {
        Map<User, List<User>> adj = new HashMap<>();    // lista de adiacenta

        // construim lista de adiacenta
        for (User u : users)
            adj.put(u, new ArrayList<>());
        for (Friendship f : friendships) {
            adj.get(f.getFriend1()).add(f.getFriend2());
            adj.get(f.getFriend2()).add(f.getFriend1());
        }
        return adj;
    }

    public int getNumberOfCommunities() {
        List<User> users = repo.getAll();
        List<Friendship> friendships = friendshipRepo.getAll();
        Map<User, List<User>> adj = buildAdjacencyList(users, friendships);

        // numarul de componente conexe = numarul de parcurgeri complete cu dfs
        Set<User> visited = new HashSet<>();
        int count = 0;
        for (User u : users) {
            if(!visited.contains(u)) {
                dfs(u, adj, visited);
                count++;
            }
        }
        if(count == 0)
            throw new MyException("!! Nu Exista Comunitati !!");
        return count;
    }

    public List<User> getMostSociableCommunity() {
        List<User> users = repo.getAll();
        List<Friendship> friendships = friendshipRepo.getAll();
        Map<User, List<User>> adj = buildAdjacencyList(users, friendships);

        // numarul de componente conexe = numarul de parcurgeri complete cu dfs
        Set<User> visited = new HashSet<>();
        List<List<User>> communities = new ArrayList<>();
        int count = 0;

        for (User u : users) {
            // adaugam fiecare comunitate diferita
            if(!visited.contains(u)) {
                List<User> component = new ArrayList<>();
                dfsCollect(u, adj, visited, component);
                communities.add(component);
                count++;
            }
        }
        if(count == 0)
            throw new MyException("!! Nu Exista Comunitati !!");

        List<User> mostSociable = null;
        int maxDiameter = -1;

        for(List<User> community : communities) {
            int diameter = getDiameter(community, adj);
            if(diameter > maxDiameter) {
                maxDiameter = diameter;
                mostSociable = community;
            }
        }

        return mostSociable;
    }

    public void addCard(Card<?> card) {
        if(cardRepo.findByNume(card.getNumeCard()) != null)
            throw new RepositoryException("!! Cardul Exista Deja !!");
        cardRepo.add(card);
    }

    public void removeCard(String numeCard) {
        var card = cardRepo.findByNume(numeCard);
        if(card == null)
            throw new RepositoryException("!! Nu Exista Comunitati !!");
        cardRepo.remove(card);
    }

    @SuppressWarnings("unchecked")
    public void addCardMember(String numeCard, String username) {
        var card = cardRepo.findByNume(numeCard);
        var user = repo.findByUsername(username);
        if(card == null)
            throw new RepositoryException("!! Nu Exista Cardul !!");
        if(user == null)
            throw new UserNotFoundException(username);
        if (!(user instanceof Duck duck))
            throw new ValidatorException("!! Userul nu este o rata !!");
        if (!duck.getTip().equals(card.getTip()))
            throw new ValidatorException("!! Rata nu e potrivita cardului !!");
        if(duck.getCard() != null)
            throw new ValidatorException("!! Rata are deja un card !!");
        cardRepo.addMembru(card, duck);
    }

    @SuppressWarnings("unchecked")
    public void removeCardMember(String numeCard, String username) {
        var card = cardRepo.findByNume(numeCard);
        var user = repo.findByUsername(username);
        if(card == null)
            throw new RepositoryException("!! Nu Exista Cardul !!");
        if(user == null)
            throw new UserNotFoundException(username);
        if (!(user instanceof Duck duck))
            throw new ValidatorException("!! Userul nu este o rata !!");
        if(duck.getCard() == null)
            throw new ValidatorException("!! Rata nu are niciun card !!");
        cardRepo.removeMembru(card, duck);
    }

    public Duck[] extractSwimmingDucks() {
        return repo.getAll().stream()
                .filter(u -> u instanceof Duck duck && duck.getTip() == TipRata.SWIMMING)
                .map(u -> (Duck) u)
                .toArray(Duck[]::new);
    }

    public void createRaceEvent(Duck[] rate, Culoar[] culoare) {
        //int eventId = eventRepo.getAll().size() + 1;
        RaceEvent race = new RaceEvent(0, rate, culoare);
        for(Duck duck : rate) {
            race.subscribe(duck);
        }
        eventRepo.add(race);
    }

    public Solution startRaceEvent(int id) {
        RaceEvent race = (RaceEvent) findEventById(id);
        //resetam ratele de fiecare data
        Duck[] rate = extractSwimmingDucks();

        race.setRate(rate);
        Solution sol = race.findOptimalSolution();
        //notificam doar ratele care participa la solutia cursei!!!
        if(sol.getRate() != null)
            for(Duck duck : sol.getRate()) {
                if(!race.getSubscribers().contains(duck))
                    race.subscribe(duck);
            }
        var notifications = notifySubscribers(id);
        if(!notifications.isEmpty())
            eventRepo.loadNotifications(notifications);
        return sol;
    }

    public Event findEventById(int id) {
        if(id == -1)
            throw new ValidatorException("!! Nu Exista Event-ul !!");
        var event = eventRepo.findByEventId(id);
        if(event == null)
            throw new ValidatorException("!! Nu Exista Event-ul !!");
        return event;
    }

    public List<String> notifySubscribers(int id) {
        var event = eventRepo.findByEventId(id);
        if(event == null)
            throw new ValidatorException("!! Nu Exista Event-ul !!");
        return event.notifySubscribers("Incepe event-ul " + id + "!!");
    }

    public void removeRaceEvent(int id) {
        var event = eventRepo.findByEventId(id);
        if(event == null)
            throw new ValidatorException("!! Nu Exista Event-ul !!");
        eventRepo.remove(event);
    }
}

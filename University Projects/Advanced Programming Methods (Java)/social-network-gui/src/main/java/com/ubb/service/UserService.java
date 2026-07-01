package com.ubb.service;
import com.ubb.chatting.ChatBoxController;
import com.ubb.chatting.Message;
import com.ubb.chatting.Observable;
import com.ubb.chatting.Observer;
import com.ubb.domain.*;
import com.ubb.domain.EventObservable;
import com.ubb.domain.EventObserver;
import com.ubb.exceptions.*;
import com.ubb.relations.Card;
import com.ubb.relations.FriendRequest;
import com.ubb.relations.Friendship;
import com.ubb.repository.*;
import com.ubb.util.paging.Page;
import com.ubb.util.paging.Pageable;
import com.ubb.validation.DuckValidator;
import com.ubb.validation.PersoanaValidator;
import org.mindrot.jbcrypt.BCrypt;

import java.util.*;
import java.util.stream.Collectors;

public class UserService implements Observable {
    private final UserDBRepository repo;
    private final FriendshipDBRepository friendshipRepo;
    private final CardDBRepository cardRepo;
    private final EventDBRepository eventRepo;
    private final MessageDBRepository messageRepo;
    private final FriendRequestDBRepository friendRequestRepo;

    private final PersoanaValidator persoanaValidator;
    private final DuckValidator duckValidator;

    private final List<Observer> subscribers;

    // OBSERVABLE
    @Override
    public void subscribe(Observer o) {
        subscribers.add(o);
    }

    @Override
    public void unsubscribe(Observer o) {
        subscribers.remove(o);
    }

    @Override
    public void notifySubscribers() {
        for (Observer o : subscribers) {
            o.update();
        }
    }

    public void notifyTyping(String typer, String target, boolean typing) {
        for (Observer o : subscribers) {
            if (o instanceof ChatBoxController chat) {
                var sender = chat.getSender();  // ionel
                var receiver = chat.getReceiver(); // marc
                if (typer.equals(receiver) && target.equals(sender)) {
                    if (typing) chat.updateTyping(typer, true);
                    else chat.updateTyping("", false);
                }
            }
        }
    }

    public void notifyNotifications(String username) {
        for (Observer o : subscribers) {
            if (o instanceof ChatBoxController chat) {
                var currentUser = chat.getSender();
                if (username.equals(currentUser)) {
                    int notifs = 0;
                    for (FriendRequest f : friendRequestRepo.getAll())
                        if (f.getToUser().equals(currentUser) && f.getStatus().equals("pending")) {
                            notifs += 1;
                        }
                    chat.updateNotifications(notifs);
                }
            }
        }
    }

    public UserService(UserDBRepository repo, FriendshipDBRepository friendshipRepo, CardDBRepository cardRepo, EventDBRepository eventRepo, MessageDBRepository messageRepo, FriendRequestDBRepository friendRequestRepo) {
        this.repo = repo;
        this.friendshipRepo = friendshipRepo;
        this.cardRepo = cardRepo;
        this.eventRepo = eventRepo;
        this.messageRepo = messageRepo;
        this.friendRequestRepo = friendRequestRepo;
        this.persoanaValidator = new PersoanaValidator();
        this.duckValidator = new DuckValidator();
        this.subscribers = new ArrayList<>();
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

    public List<Message> getAllMessages() {
        if(messageRepo.getAll().isEmpty())
            throw new RepositoryException("!! Nu Exista Mesaje !!");
        return messageRepo.getAll();
    }

    public List<FriendRequest> getAllFriendRequests(String username) {
        return friendRequestRepo.getAll().stream()
                .filter(f -> f.getToUser().equals(username))
                .collect(Collectors.toList());
    }

    public String encryptPassword(String password) {
        String salt = BCrypt.gensalt();
        return BCrypt.hashpw(password, salt);
    }

    public void addPersoana(String username, String email, String password,
                            String nume, String prenume, String dataNasterii, String ocupatie) {
        int id = repo.getAll().size() + 1;
        String hashedPassword = encryptPassword(password);
        Persoana p = new Persoana((long) id, username, email, hashedPassword, nume, prenume, dataNasterii, ocupatie);
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
        String hashedPassword = encryptPassword(password);
        Duck d;
        switch(tipRata) {
            case FLYING:
                d = new FlyingDuck((long) id, username, email, hashedPassword, tipRata, viteza, rezistenta);
                break;
            case SWIMMING:
                d = new SwimmingDuck((long) id, username, email, hashedPassword, tipRata, viteza, rezistenta);
                break;
            case FLYING_AND_SWIMMING:
                d = new FlyingSwimmingDuck((long) id, username, email, hashedPassword, tipRata, viteza, rezistenta);
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

    public User findUserByUsername(String username) {
        var user = repo.findByUsername(username);
        if(user == null)
            throw new UserNotFoundException(username);
        return user;
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

    public Page<User> findAllOnPage(Pageable pageable, List<User> elements) {
        return repo.findAllOnPage(pageable, elements);
    }

    public Page<Friendship> findAllFriendshipsOnPage(Pageable pageable, List<Friendship> elements) {
        return friendshipRepo.findAllOnPage(pageable, elements);
    }

    public void userLogin(String username, String password) {
        var user = repo.findByUsername(username);
        if(user == null)
            throw new UserNotFoundException(username);
        var loginStatus = user.login(password);
        if(!loginStatus)
            throw new ValidatorException("!! Parola Incorecta !!");
    }

    public void userLogout(String username) {
        var user = repo.findByUsername(username);
        if(user == null)
            throw new UserNotFoundException(username);
        var logoutStatus = user.logout();
        if(!logoutStatus)
            throw new ValidatorException("!! User-ul Nu E Logat !!");
    }

    public Message findMessageById(long id) {
        var message = messageRepo.findById(id);
        if(message == null)
            throw new RepositoryException("!! Nu S-a Gasit Mesajul !!");
        return message;
    }

    public void addMessage(Message message) {
        messageRepo.add(message);
    }

    public void addFriendRequest(FriendRequest friendRequest) {
        String from_user = friendRequest.getFromUser();
        String to_user = friendRequest.getToUser();
        for (Friendship f : friendshipRepo.getAll()) {
            if (f.getFriend1().getUsername().equals(from_user) && f.getFriend2().getUsername().equals(to_user)
            || f.getFriend1().getUsername().equals(to_user) && f.getFriend2().getUsername().equals(from_user)) {
                throw new DuplicateException("!! Sunteti Deja Prieteni !!");
            }
        }
        for (FriendRequest f : friendRequestRepo.getAll()) {
            if (f.getFromUser().equals(from_user) && f.getToUser().equals(to_user) && f.getStatus().equals("pending")) {
                throw new RepositoryException("!! Ati Trimis Deja Cererea !!");
            }
        }

        friendRequestRepo.add(friendRequest);
    }

    public void manageFriendRequest(FriendRequest friendRequest, String newStatus) {
        switch (newStatus) {
            case "approved":
                friendRequestRepo.update(friendRequest, newStatus);
                this.addFriendship(friendRequest.getFromUser(), friendRequest.getToUser());
                break;
            case "rejected":
                friendRequestRepo.update(friendRequest, newStatus);
                break;
            default:
                System.out.println("Nu prea are cum sa ajunga aici...");
        }
    }
}

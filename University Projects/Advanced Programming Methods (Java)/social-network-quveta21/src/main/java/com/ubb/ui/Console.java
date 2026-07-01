package com.ubb.ui;

import com.ubb.domain.*;
import com.ubb.exceptions.*;
import com.ubb.relations.*;
import com.ubb.service.UserService;
import com.ubb.validation.Validator;

import java.io.IOException;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Console {
    private final UserService service;
    private final Scanner input = new Scanner(System.in);

    public Console(UserService service) {
        this.service = service;
    }

    public void menu() {
        System.out.println("Alegeti optiunea:");
        System.out.println("---------------------");
        System.out.println("1. Adauga User");
        System.out.println("2. Sterge User");
        System.out.println("3. Vezi Toti Userii");
        System.out.println("4. Adauga Prietenie");
        System.out.println("5. Sterge Prietenie");
        System.out.println("6. Vezi Toate Prieteniile");
        System.out.println("7. Vezi Numarul Comunitatilor");
        System.out.println("8. Vezi Cea Mai Sociabila Comunitate");
        System.out.println("9. Adauga Card");
        System.out.println("10. Sterge Card");
        System.out.println("11. Vezi Toate Cardurile");
        System.out.println("12. Adauga Membru In Card");
        System.out.println("13. Sterge Membru Din Card");
        System.out.println("14. Creeaza Race Event");
        System.out.println("15. Vezi Toate Race Event");
        System.out.println("16. Start Race Event");
        System.out.println("17. Sterge Race Event");
        System.out.println("0. Exit");
        System.out.println("---------------------");
    }

    public void addUserUI() {
        try{
            System.out.print("Tip User (Persoana / Duck): ");
            String tipUser = input.nextLine();

            System.out.print("Username: ");
            String username = input.nextLine();
            System.out.print("Email: ");
            String email = input.nextLine();
            System.out.print("Password: ");
            String password = input.nextLine();

            switch (tipUser) {
                case "Persoana": {
                    System.out.print("Nume: ");
                    String nume = input.nextLine();
                    System.out.print("Prenume: ");
                    String prenume = input.nextLine();
                    System.out.print("Data nasterii: ");
                    String dataNasterii = input.nextLine();
                    System.out.print("Ocupatie: ");
                    String ocupatie = input.nextLine();
                    service.addPersoana(username, email, password, nume, prenume, dataNasterii, ocupatie);
                    break;
                }
                case "Duck": {
                    System.out.print("Tip Rata (FLYING / SWIMMING / FLYING_AND_SWIMMING): ");
                    String tipRataString = input.nextLine();
                    double viteza = -1, rezistenta = -1;
                    System.out.print("Viteza: ");
                    String vitezaStr = input.nextLine();
                    try {
                        viteza = Double.parseDouble(vitezaStr);
                    } catch (NumberFormatException e) {
                        // viteza ramane -1
                    }
                    System.out.print("Rezistenta: ");
                    String rezistentaStr = input.nextLine();
                    try {
                        rezistenta = Double.parseDouble(rezistentaStr);
                    } catch (NumberFormatException e) {
                        // rezistenta ramane -1
                    }
                    TipRata tipRata;
                    try {
                        tipRata = TipRata.valueOf(tipRataString.toUpperCase());
                    } catch (IllegalArgumentException e) {
                        tipRata = null;
                    }
                    service.addDuck(username, email, password, tipRata, viteza, rezistenta);
                    break;
                }
                default:
                    throw new UIException("!! Tip User invalid !!\n");
            }
        } catch (ValidatorException | UIException | DuplicateException e) {
            System.out.println(e.getMessage());
        }
    }

    public void showUsers() {
        try{
            var users = service.getAllUsers();
            System.out.println("Toti Userii Inregistrati:");
            for (User user : users) {
                System.out.println(user);
            }
        }
        catch(NoUsersException | NullPointerException e){
            System.out.println(e.getMessage());
        }

    }

    public void removeUserUI() {
        try{
            System.out.print("Username: ");
            String username = input.nextLine();
            service.removeUser(username);
        }
        catch(UserNotFoundException e){
            System.out.println(e.getMessage());
        }
    }

    public void addFriendshipUI() {
        try {
            System.out.print("Username 1: ");
            String username1 = input.nextLine();
            System.out.print("Username 2: ");
            String username2 = input.nextLine();
            if("".equals(username1) || "".equals(username2))
                throw new UIException("!! Username Nu Poate Fi Vid !!");
            service.addFriendship(username1, username2);
        } catch (UserNotFoundException | ValidatorException | DuplicateException | UIException e) {
            System.out.println(e.getMessage());
        }
    }

    public void removeFriendshipUI() {
        try {
            System.out.print("Username 1: ");
            String username1 = input.nextLine();
            System.out.print("Username 2: ");
            String username2 = input.nextLine();
            if("".equals(username1) || "".equals(username2))
                throw new UIException("!! Username Nu Poate Fi Vid !!");
            service.removeFriendship(username1, username2);
        } catch (RepositoryException | UIException e) {
            System.out.println(e.getMessage());
        }
    }

    public void showFriendships() {
        try{
            var friendships = service.getAllFriendships();
            System.out.println("Toate Prieteniile Inregistrate:");
            for (Friendship f : friendships) {
                System.out.println(f);
            }
        } catch(RepositoryException e){
            System.out.println(e.getMessage());
        }
    }

    public void showNumberOfCommunities() {
        try {
            System.out.print("Numarul De Comunitati: " + service.getNumberOfCommunities() + "\n");
        } catch(MyException e){
            System.out.println(e.getMessage());
        }
    }

    public void showMostSociableCommunity() {
        try {
            var mostSociable = service.getMostSociableCommunity();
            mostSociable.forEach(u -> System.out.println(" - " + u.getUsername()));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
    }

    public void addCardUI() {
        try{
            System.out.print("Scop card(SwimMasters/SkyFlyers/SkySwimmers): ");
            String scopCard = input.nextLine().toUpperCase();
            System.out.print("Nume card: ");
            String numeCard = input.nextLine();
            Card<?> card = switch (scopCard) {
                case "SWIMMASTERS" -> new SwimMasters(numeCard);
                case "SKYFLYERS" -> new SkyFlyers(numeCard);
                case "SKYSWIMMERS" -> new SkySwimmers(numeCard);
                default -> throw new UIException("!! Scop Pentru Card Invalid !!");
            };
            service.addCard(card);
        } catch(UIException | RepositoryException e){
            System.out.println(e.getMessage());
        }
    }

    public void removeCardUI() {
        try{
            System.out.print("Nume card: ");
            String numeCard = input.nextLine();
            service.removeCard(numeCard);
        } catch(RepositoryException e){
            System.out.println(e.getMessage());
        }
    }

    public void showCarduri() {
        try{
            var carduri = service.getAllCarduri();
            System.out.println("Toti Cardurile Inregistrate:");
            for (Card<?> card : carduri) {
                System.out.println(card);
            }
        }
        catch(RepositoryException e){
            System.out.println(e.getMessage());
        }
    }

    public void addCardMemberUI() {
        try{
            System.out.print("Nume card: ");
            String numeCard = input.nextLine();
            System.out.print("Username: ");
            String username = input.nextLine();
            service.addCardMember(numeCard, username);
        } catch(RepositoryException | ValidatorException e){
            System.out.println(e.getMessage());
        }
    }

    public void removeCardMemberUI() {
        try {
            System.out.print("Nume card: ");
            String numeCard = input.nextLine();
            System.out.print("Username: ");
            String username = input.nextLine();
            service.removeCardMember(numeCard, username);
        } catch(RepositoryException | ValidatorException e){
            System.out.println(e.getMessage());
        }
    }

    public Culoar[] readCuloare(int m) {
        System.out.print("Balize: ");
        String[] line = input.nextLine().split(" ");
        if(line.length != m)
            throw new UIException("!! Trebuie introduse " + m + " balize !!");
        Culoar[] culoare = new Culoar[m];
        for(int i = 0; i < m; i++) {
            culoare[i] = new Culoar(i+1, Double.parseDouble(line[i]));
        }
        return culoare;
    }

    public void createRaceEventUI() {
        try {
            int m = -1;
            System.out.print("Nr. culoare: ");
            String numberStr = input.nextLine();
            try {
                m = Integer.parseInt(numberStr);
            } catch (NumberFormatException e) {
            }
            Culoar[] culoare = readCuloare(m);
            Duck[] rate = service.extractSwimmingDucks();
            service.createRaceEvent(rate, culoare);
        } catch (UIException e) {
            System.out.println(e.getMessage());
        }
    }

    public void startRaceEvent() {
        try {
            int id = -1;
            System.out.print("Id event: ");
            String numberStr = input.nextLine();
            try {
                id = Integer.parseInt(numberStr);
            } catch (NumberFormatException e) {}
            Solution sol = service.startRaceEvent(id);
            System.out.println(sol);
        } catch(ValidatorException e) {
            System.out.println(e.getMessage());
        }
    }

    public void showRaceEvents() {
        try{
            var raceEvents = service.getAllEvents();
            System.out.println("Toate Event-urile Inregistrate:");
            for (Event raceEvent : raceEvents) {
                System.out.println(raceEvent);
            }
        } catch(RepositoryException e){
            System.out.println(e.getMessage());
        }
    }


    public void removeRaceEventUI() {
        try{
            int id = -1;
            System.out.print("Id event: ");
            String numberStr = input.nextLine();
            try {
                id = Integer.parseInt(numberStr);
            } catch (NumberFormatException e) {}
            service.removeRaceEvent(id);
        } catch(ValidatorException e) {
            System.out.println(e.getMessage());
        }
    }

    public void run() {
        menu();
        String choice;
        while (true) {
            System.out.print(">> ");
            choice = input.nextLine();
            switch (choice) {
                case "1":
                    addUserUI();
                    break;
                case "2":
                    removeUserUI();
                    break;
                case "3":
                    showUsers();
                    break;
                case "4":
                    addFriendshipUI();
                    break;
                case "5":
                    removeFriendshipUI();
                    break;
                case "6":
                    showFriendships();
                    break;
                case "7":
                    showNumberOfCommunities();
                    break;
                case "8":
                    showMostSociableCommunity();
                    break;
                case "9":
                    addCardUI();
                    break;
                case "10":
                    removeCardUI();
                    break;
                case "11":
                    showCarduri();
                    break;
                case "12":
                    addCardMemberUI();
                    break;
                case "13":
                    removeCardMemberUI();
                    break;
                case "14":
                    createRaceEventUI();
                    break;
                case "15":
                    showRaceEvents();
                    break;
                case "16":
                    startRaceEvent();
                    break;
                case "17":
                    removeRaceEventUI();
                    break;
                case "0":
                    return;
                default:
                    System.out.println("Optiune invalida");
            }
        }
    }
}

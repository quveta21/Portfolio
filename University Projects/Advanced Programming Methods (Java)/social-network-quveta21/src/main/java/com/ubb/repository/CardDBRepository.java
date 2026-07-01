package com.ubb.repository;

import com.ubb.database.DBConnection;
import com.ubb.domain.Duck;
import com.ubb.exceptions.RepositoryException;
import com.ubb.relations.Card;
import com.ubb.relations.SkyFlyers;
import com.ubb.relations.SkySwimmers;
import com.ubb.relations.SwimMasters;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class CardDBRepository extends InMemoryRepository<Card<? extends Duck>> {
    // necesara referinta la userRepo pentru a extrage userii cu username-ul din DB
    // Card_Membri in DB tine (nume_card, username)
    private final UserDBRepository userRepo;

    public CardDBRepository(UserDBRepository userRepo) {
        super();
        this.userRepo = userRepo;
        load();
    }

    @SuppressWarnings("unchecked")
    public void load() {
        try (Connection connection = DBConnection.getConnection()) {
            String cardQuery = "SELECT * FROM Carduri";
            PreparedStatement statement = connection.prepareStatement(cardQuery);
            ResultSet result = statement.executeQuery();
            while(result.next()) {
                String nume_card = result.getString("nume_card");
                String tip_rata_string = result.getString("tip_rata");
                Card card;
                switch(tip_rata_string) {
                    case "FLYING":
                        card = new SkyFlyers(nume_card);
                        loadMembers(card);
                        super.add(card);
                        break;
                    case "SWIMMING":
                        card = new SwimMasters(nume_card);
                        loadMembers(card);
                        super.add(card);
                        break;
                    case "FLYING_AND_SWIMMING":
                        card = new SkySwimmers(nume_card);
                        loadMembers(card);
                        super.add(card);
                        break;
                    default:
                        throw new SQLException("!! Tip Card invalid !!");
                }
            }
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la load din DB (carduri): " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    public void loadMembers(Card<? extends Duck>  card){
        try (Connection connection = DBConnection.getConnection()) {
            String cardQuery = "SELECT * FROM Card_Membri WHERE nume_card = ?";
            PreparedStatement statement = connection.prepareStatement(cardQuery);
            statement.setString(1, card.getNumeCard());
            ResultSet result = statement.executeQuery();
            while(result.next()){
                String username = result.getString("username");
                var user = userRepo.findByUsername(username);
                if(!(user instanceof Duck duck))
                    throw new SQLException("!! Membru In Card Invalid !!");
                ((Card<Duck>) card).addMembru(duck);
            }

        } catch(SQLException e) {
            throw new RepositoryException("Eroare la load din DB (carduri): " + e.getMessage());
        }
    }

    @Override
    public void add(Card<? extends Duck> card) {
        try (Connection connection = DBConnection.getConnection()) {
            String cardQuery = "INSERT INTO Carduri (nume_card, tip_rata) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(cardQuery);
            statement.setString(1, card.getNumeCard());
            statement.setString(2, card.getTip().toString());
            statement.executeUpdate();
            super.add(card);
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la add in DB (carduri): " + e.getMessage());
        }
    }

    @Override
    public void remove(Card<? extends Duck> card) {
        try (Connection connection = DBConnection.getConnection()) {
            String cardQuery = "DELETE FROM Carduri WHERE nume_card = ?";
            PreparedStatement statement = connection.prepareStatement(cardQuery);
            statement.setString(1, card.getNumeCard());
            statement.executeUpdate();
            super.remove(card);
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la remove din DB (carduri): " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    public void addMembru(Card<? extends Duck> card, Duck duck) {
        try (Connection connection = DBConnection.getConnection()) {
            String membruQuery = "INSERT INTO Card_Membri (nume_card, username) VALUES (?, ?)";
            PreparedStatement membriStatement = connection.prepareStatement(membruQuery);
            membriStatement.setString(1, card.getNumeCard());
            membriStatement.setString(2, duck.getUsername());
            membriStatement.executeUpdate();
            ((Card<Duck>) card).addMembru(duck);
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la add membru in DB (carduri): " + e.getMessage());
        }
    }

    @SuppressWarnings("unchecked")
    public void removeMembru(Card<? extends Duck> card, Duck duck) {
        try (Connection connection = DBConnection.getConnection()) {
            String membruQuery = "DELETE FROM Card_Membri WHERE nume_card = ? AND username = ?";
            PreparedStatement membriStatement = connection.prepareStatement(membruQuery);
            membriStatement.setString(1, card.getNumeCard());
            membriStatement.setString(2, duck.getUsername());
            membriStatement.executeUpdate();
            ((Card<Duck>) card).removeMembru(duck);
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la remove membru din DB (carduri): " + e.getMessage());
        }
    }

    public Card<? extends Duck> findByNume(String numeCard) {
        return getAll().stream()
                .filter(card -> card.getNumeCard().equals(numeCard))
                .findFirst()
                .orElse(null);
    }
}

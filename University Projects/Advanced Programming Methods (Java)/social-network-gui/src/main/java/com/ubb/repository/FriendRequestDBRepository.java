package com.ubb.repository;

import com.ubb.database.DBConnection;
import com.ubb.exceptions.RepositoryException;
import com.ubb.relations.FriendRequest;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class FriendRequestDBRepository extends InMemoryRepository<FriendRequest> {
    public FriendRequestDBRepository() throws SQLException {
        super();
        load();
    }

    public void load() throws SQLException {
        try (Connection connection = DBConnection.getConnection()) {
            String query = "SELECT * FROM FriendRequests";
            PreparedStatement statement = connection.prepareStatement(query);
            ResultSet result = statement.executeQuery();
            while (result.next()) {
                String from_user = result.getString("from_user");
                String to_user = result.getString("to_user");
                String status = result.getString("status");
                FriendRequest fr = new FriendRequest(from_user, to_user, status);
                super.add(fr);
            }
        } catch (SQLException e) {
            throw new RepositoryException("Eroare la load din DB (friend requests): " + e.getMessage());
        }
    }

    @Override
    public void add(FriendRequest fr) {
        try (Connection connection = DBConnection.getConnection()) {
            String query = "INSERT INTO FriendRequests (from_user, to_user, status) VALUES (?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, fr.getFromUser());
            statement.setString(2, fr.getToUser());
            statement.setString(3, fr.getStatus());
            statement.executeUpdate();
            super.add(fr);

        } catch (SQLException e) {
            throw new RepositoryException("Eroare la add in DB (friend requests): " + e.getMessage());
        }
    }

    @Override
    public void remove(FriendRequest fr) {
        try (Connection connection = DBConnection.getConnection()) {
            String query = "DELETE FROM FriendRequests WHERE from_user = ? AND to_user = ?";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, fr.getFromUser());
            statement.setString(2, fr.getToUser());
            statement.executeUpdate();
            super.remove(fr);

        } catch (SQLException e) {
            throw new RepositoryException("Eroare la remove din DB (friend requests): " + e.getMessage());
        }
    }

    public void update(FriendRequest fr, String newStatus) {
        try (Connection connection = DBConnection.getConnection()) {
            String query = "UPDATE FriendRequests SET status = ? WHERE (from_user = ? AND to_user = ?) " +
                    "OR (from_user = ? AND to_user = ?)";
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, newStatus);
            statement.setString(2, fr.getFromUser());
            statement.setString(3, fr.getToUser());
            statement.setString(4, fr.getToUser());
            statement.setString(5, fr.getFromUser());
            statement.executeUpdate();

            // updatam atat cererea initiala, cat si cererea venita de la celalalt user
            // ex. marc -> calina, calina -> marc
            for (FriendRequest f : super.getAll()) {
                if (f.getFromUser().equals(fr.getFromUser()) && f.getToUser().equals(fr.getToUser())
                || f.getFromUser().equals(fr.getToUser()) &&  f.getToUser().equals(fr.getFromUser())) {
                    f.setStatus(newStatus);
                    break;
                }
            }

        } catch (SQLException e) {
            throw new RepositoryException("Eroare la update in DB (friend requests): " + e.getMessage());
        }
    }
}

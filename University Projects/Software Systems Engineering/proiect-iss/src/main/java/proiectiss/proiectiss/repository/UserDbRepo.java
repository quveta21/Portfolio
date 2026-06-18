package proiectiss.proiectiss.repository;

import proiectiss.proiectiss.database.DBConnection;
import proiectiss.proiectiss.domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UserDbRepo implements Repository<String, User> {
    public User findBy(String username, String password) {
        String query = "SELECT id, username, password FROM users WHERE username = ? AND password = ?";

        try (Connection con = DBConnection.getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {

            ps.setString(1, username);
            ps.setString(2, password);

            try (ResultSet rs = ps.executeQuery()) { // Aici se executa acel SELECT SQL din diagrama
                if (rs.next()) {
                    return new User(
                            rs.getString("id"),
                            rs.getString("username"),
                            rs.getString("password")
                    );
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void save(User entity) {

    }

    @Override
    public User findById(String id) {
        return null;
    }

    @Override
    public Iterable<User> findAll() {
        return null;
    }

    @Override
    public void delete(String id) {

    }

    @Override
    public void update(User entity) {

    }
}

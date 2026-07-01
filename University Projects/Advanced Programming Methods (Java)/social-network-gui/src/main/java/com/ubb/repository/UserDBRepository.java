package com.ubb.repository;

import com.ubb.database.DBConnection;
import com.ubb.domain.*;
import com.ubb.exceptions.RepositoryException;
import com.ubb.util.paging.Page;
import com.ubb.util.paging.Pageable;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.mindrot.jbcrypt.BCrypt;

public class UserDBRepository extends InMemoryRepository<User> implements PagingRepository<User> {
    public UserDBRepository() throws SQLException {
        super();
        //encryptAllPasswords();
        load();
    }

    public void load() throws SQLException {
        try (Connection connection = DBConnection.getConnection()) {
            String userQuery = "SELECT * FROM USERS";
            PreparedStatement statement = connection.prepareStatement(userQuery);
            ResultSet result = statement.executeQuery();
            while(result.next()) {
                long id = result.getLong("id");
                String username = result.getString("username");
                String email = result.getString("email");
                String password = result.getString("password");
                String tip_user = result.getString("tip_user");
                switch (tip_user) {
                    case "Persoana":
                        String nume = result.getString("nume");
                        String prenume = result.getString("prenume");
                        String data_nasterii = result.getString("data_nasterii");
                        String ocupatie = result.getString("ocupatie");
                        Persoana p = new Persoana(id, username, email, password,
                                nume, prenume, data_nasterii, ocupatie);
                        super.add(p);
                        break;
                    case "Duck":
                        String tip_rata_string = result.getString("tip_rata");
                        TipRata tip_rata = TipRata.valueOf(tip_rata_string.toUpperCase());
                        double viteza = result.getDouble("viteza");
                        double rezistenta = result.getDouble("rezistenta");
                        long id_card = result.getLong("id_card");
                        Duck d;
                        switch (tip_rata) {
                            case FLYING:
                                d = new FlyingDuck(id, username, email, password, tip_rata, viteza, rezistenta);
                                super.add(d);
                                break;
                            case SWIMMING:
                                d = new SwimmingDuck(id, username, email, password, tip_rata, viteza, rezistenta);
                                super.add(d);
                                break;
                            case FLYING_AND_SWIMMING:
                                d = new FlyingSwimmingDuck(id, username, email, password, tip_rata, viteza, rezistenta);
                                super.add(d);
                                break;
                            default:
                                throw new SQLException("!! Tip Rata invalid !!");
                        }
                        break;
                    default:
                        throw new SQLException("!! Tip User invalid !!");
                }
            }
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la load din DB (users): " + e.getMessage());
        }
    }

    @Override
    public void add(User user) {
        if(user instanceof Persoana p) {
            savePersoana(p);
        } else if(user instanceof Duck d) {
            saveDuck(d);
        } else
            throw new RepositoryException("!! Tip User Invalid !!");
        super.add(user);
    }

    @Override
    public void remove(User user) {
        try(Connection connection = DBConnection.getConnection()){
            String sql = "DELETE FROM Users WHERE username=?";
            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setString(1, user.getUsername());
            statement.executeUpdate();
        }catch(SQLException e){
            throw new RepositoryException("Eroare la stergerea user-ului: " + e.getMessage());
        }
        super.remove(user);
    }

    public void savePersoana(Persoana p) {
        try(Connection connection = DBConnection.getConnection()){
            String insertSql = "INSERT INTO Users (username, email, password, tip_user, nume, prenume, data_nasterii, ocupatie) " +
                    "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(insertSql);
            statement.setString(1, p.getUsername());
            statement.setString(2, p.getEmail());
            statement.setString(3, p.getPassword());
            statement.setString(4, "Persoana");
            statement.setString(5, p.getNume());
            statement.setString(6, p.getPrenume());
            statement.setString(7, p.getDataNasterii());
            statement.setString(8, p.getOcupatie());
            statement.executeUpdate();
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la salvarea persoanei: " + e.getMessage());
        }
    }

    public void saveDuck(Duck d){
        try(Connection connection = DBConnection.getConnection()){
            String insertSql = "INSERT INTO Users (username, email, password, tip_user, tip_rata, viteza, rezistenta) " +
                    "VALUES (?, ?, ?, ?, ?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(insertSql);
            statement.setString(1, d.getUsername());
            statement.setString(2, d.getEmail());
            statement.setString(3, d.getPassword());
            statement.setString(4, "Duck");
            statement.setString(5, d.getTip().toString());
            statement.setDouble(6, d.getViteza());
            statement.setDouble(7, d.getRezistenta());
            statement.executeUpdate();
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la salvarea ratei: " + e.getMessage());
        }
    }

    public User findByUsername(String username) {
        return super.getAll().stream()
                .filter(user -> user.getUsername().equals(username))
                .findFirst()
                .orElse(null);
    }

    @Override
    public Page<User> findAllOnPage(Pageable pageable, List<User> elements) {
        int pageNumber = pageable.getPageNumber();
        int pageSize = pageable.getPageSize();

        //List<User> all = this.getAll();
        int total = elements.size();

        int startIndex = pageNumber * pageSize;
        int endIndex = Math.min(startIndex + pageSize, total);

        if(startIndex >= total)     //daca am depasit numarul de useri
            return null;

        List<User> usersOnPage = elements.subList(startIndex, endIndex);
        return new Page<>(usersOnPage, usersOnPage.size());
    }

    // folosit doar odata sa criptez parolele deja existente in DB
    public void encryptAllPasswords() {
        String selectQuery = "SELECT id, password FROM Users";
        String updateQuery = "UPDATE Users SET password = ? WHERE id = ?";

        try (Connection connection = DBConnection.getConnection();
             PreparedStatement selectStatement = connection.prepareStatement(selectQuery);
             PreparedStatement updateStatement = connection.prepareStatement(updateQuery)) {

            ResultSet result = selectStatement.executeQuery();

            while (result.next()) {
                long id = result.getLong("id");
                String currentPassword = result.getString("password");

                // Verificare de siguranta: Daca parola incepe deja cu $2a$, e probabil deja hashuita cu BCrypt
                // Hashuim doar daca e text simplu
                if (currentPassword != null && !currentPassword.startsWith("$2a$")) {

                    // 1. Generam hash-ul
                    String hashedPassword = BCrypt.hashpw(currentPassword, BCrypt.gensalt());

                    // 2. Pregatim update-ul pentru acest user specific
                    updateStatement.setString(1, hashedPassword);
                    updateStatement.setLong(2, id);

                    // 3. Executam update-ul
                    updateStatement.executeUpdate();

                    System.out.println("Parola actualizata pentru userul cu ID: " + id);
                }
            }

        } catch (SQLException e) {
            throw new RepositoryException("Eroare la criptarea parolelor: " + e.getMessage());
        }
    }
}

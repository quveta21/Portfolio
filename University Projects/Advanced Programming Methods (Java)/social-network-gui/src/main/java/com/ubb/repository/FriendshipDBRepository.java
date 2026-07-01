package com.ubb.repository;

import com.ubb.database.DBConnection;
import com.ubb.domain.User;
import com.ubb.exceptions.RepositoryException;
import com.ubb.relations.Friendship;
import com.ubb.util.paging.Page;
import com.ubb.util.paging.Pageable;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

public class FriendshipDBRepository extends InMemoryRepository<Friendship> implements PagingRepository<Friendship> {
    // necesara referinta la userRepo pentru a extrage userii cu username-ul din DB
    // Friendships in DB tine (username1, username2)
    private final UserDBRepository userRepo;

    public FriendshipDBRepository(UserDBRepository userRepo) throws SQLException {
        super();
        this.userRepo = userRepo;
        load();
    }

    public void load() throws SQLException {
        try (Connection connection = DBConnection.getConnection()) {
            String friendshipQuery = "SELECT * FROM Friendships";
            PreparedStatement statement = connection.prepareStatement(friendshipQuery);
            ResultSet result = statement.executeQuery();
            while(result.next()) {
                String username1 = result.getString("username1");
                String username2 = result.getString("username2");
                var user1 = userRepo.findByUsername(username1);
                var user2 = userRepo.findByUsername(username2);
                Friendship f = new Friendship(user1, user2);
                super.add(f);
            }
        } catch(SQLException e) {
            throw new RepositoryException("Eroare la load din DB (friendship): " + e.getMessage());
        }
    }

    @Override
    public void add(Friendship f){
        try(Connection connection = DBConnection.getConnection()){
            String insertQuery = "INSERT INTO Friendships (username1, username2) VALUES (?, ?)";
            PreparedStatement statement = connection.prepareStatement(insertQuery);
            statement.setString(1, f.getFriend1().getUsername());
            statement.setString(2, f.getFriend2().getUsername());
            statement.executeUpdate();
            super.add(f);

        }catch(SQLException e){
            throw new RepositoryException("Eroare la adaugarea prieteniei: " + e.getMessage());
        }
    }

    @Override
    public void remove(Friendship f){
        try(Connection connection = DBConnection.getConnection()){
            String deleteQuery = "DELETE FROM Friendships WHERE (username1 = ? AND username2 = ?)" +
                    " OR (username1 = ? AND username2 = ?)";
            PreparedStatement statement = connection.prepareStatement(deleteQuery);
            statement.setString(1, f.getFriend1().getUsername());
            statement.setString(2, f.getFriend2().getUsername());
            statement.setString(3, f.getFriend2().getUsername());
            statement.setString(4, f.getFriend1().getUsername());
            statement.executeUpdate();
            super.remove(f);

        }catch(SQLException e){
            throw new RepositoryException("Eroare la stergerea prieteniei: " + e.getMessage());
        }
    }

    @Override
    public Page<Friendship> findAllOnPage(Pageable pageable, List<Friendship> elements) {
        int pageNumber = pageable.getPageNumber();
        int pageSize = pageable.getPageSize();

        int total = elements.size();

        int startIndex = pageNumber * pageSize;
        int endIndex = Math.min(startIndex + pageSize, total);

        if(startIndex >= total)     //daca am depasit numarul de obiecte
            return null;

        List<Friendship> friendshipsOnPage = elements.subList(startIndex, endIndex);
        return new Page<>(friendshipsOnPage, friendshipsOnPage.size());
    }
}

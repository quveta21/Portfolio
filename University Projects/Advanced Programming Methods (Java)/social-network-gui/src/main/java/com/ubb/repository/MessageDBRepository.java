package com.ubb.repository;

import com.ubb.chatting.Message;
import com.ubb.database.DBConnection;
import com.ubb.exceptions.RepositoryException;

import java.sql.*;
import java.time.LocalDateTime;

public class MessageDBRepository extends InMemoryRepository<Message> {

    private final UserDBRepository userRepo;

    public MessageDBRepository(UserDBRepository userRepo) {
        super();
        this.userRepo = userRepo;
        load();
    }

    public void load() {
        try(Connection connection = DBConnection.getConnection()) {
            String query = "SELECT * FROM Messages";
            PreparedStatement statement = connection.prepareStatement(query);
            ResultSet resultSet = statement.executeQuery();
            while(resultSet.next()) {
                long id = resultSet.getLong("id");
                String user_from = resultSet.getString("user_from");
                String user_to = resultSet.getString("user_to");
                String message_text = resultSet.getString("message_text");
                LocalDateTime date = resultSet.getTimestamp("message_date").toLocalDateTime();
                long reply_id = resultSet.getLong("reply_id");
                boolean hasReply = !resultSet.wasNull();

                var userFrom = userRepo.findByUsername(user_from);
                var userTo = userRepo.findByUsername(user_to);
                Message message = new Message(id, userFrom, userTo, message_text, date);
                if(hasReply) {
                    var replyMessage = this.findById(reply_id);
                    message.setReplyTo(replyMessage);
                }

                super.add(message);
            }
        } catch(SQLException ex) {
            throw new RepositoryException("Eroare la load din DB (Messages): " + ex.getMessage());
        }
    }

    @Override
    public void add(Message m) {
        try(Connection connection = DBConnection.getConnection()) {
            String query = "INSERT INTO Messages (user_from, user_to, message_text, message_date, reply_id) " +
                    "VALUES (?, ?, ?, ?, ?)";
            PreparedStatement statement = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, m.getSender().getUsername());
            statement.setString(2, m.getReceiver().getUsername());
            statement.setString(3, m.getMessage());
            statement.setTimestamp(4, Timestamp.valueOf(m.getDate()));
            if(m.getReplyTo() != null) statement.setLong(5, m.getReplyTo().getId());
            else statement.setNull(5, Types.BIGINT);

            statement.executeUpdate();

            try (ResultSet generatedKeys = statement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    long actualId = generatedKeys.getLong(1);
                    m.setId(actualId);
                }
            }

            System.out.println("New message id: " + m.getId() + "\n");

            super.add(m);
        } catch(SQLException ex){
            throw new RepositoryException("Eroare la add in DB (Messages): " + ex.getMessage());
        }
    }

    @Override
    public void remove(Message m) {

    }

    public Message findById(long id) {
        return super.getAll().stream()
                .filter(m -> m.getId() == id)
                .findFirst()
                .orElse(null);
    }
}

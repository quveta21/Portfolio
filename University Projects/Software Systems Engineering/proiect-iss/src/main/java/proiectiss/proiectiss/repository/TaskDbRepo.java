package proiectiss.proiectiss.repository;

import proiectiss.proiectiss.database.DBConnection;
import proiectiss.proiectiss.domain.Task;
import proiectiss.proiectiss.domain.TaskPriority;
import proiectiss.proiectiss.domain.TaskTimeLabel;
import proiectiss.proiectiss.domain.User;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class TaskDbRepo implements Repository<String, Task> {

    public void save(Task task) {
        String query = "INSERT INTO tasks (id, title, description, priority, timeLabel, userId) VALUES (?, ?, ?, ?, ?, ?)";

        try (Connection con = DBConnection.getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {

            ps.setString(1, task.getID());
            ps.setString(2, task.getTitle());
            ps.setString(3, task.getDescription());
            ps.setString(4, task.getPriority());  // Salveaza string-ul din Enum
            ps.setString(5, task.getTimeLabel()); // Salveaza string-ul din Enum
            ps.setString(6, task.getUser().getID());

            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Eroare la salvarea task-ului in baza de date.");
        }
    }

    @Override
    public Task findById(String s) {
        return null;
    }

    public List<Task> findAll() {
        List<Task> tasks = new ArrayList<>();
//        String query = "SELECT id, title, description, priority, timeLabel FROM tasks";
//
//        try (Connection con = DBConnection.getConnection();
//             PreparedStatement ps = con.prepareStatement(query);
//             ResultSet rs = ps.executeQuery()) {
//
//            while (rs.next()) {
//                Task task = new Task(
//                        rs.getString("id"),
//                        rs.getString("title"),
//                        rs.getString("description"),
//                        TaskPriority.valueOf(rs.getString("priority")),
//                        TaskTimeLabel.valueOf(rs.getString("timeLabel"))
//                );
//                tasks.add(task);
//            }
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
        return tasks;
    }

    public List<Task> findAllByUser(User user) {
        List<Task> tasks = new ArrayList<>();
        String query = "SELECT id, title, description, priority, timeLabel FROM tasks WHERE userId = ?";

        try (Connection con = DBConnection.getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {

            ps.setString(1, user.getID());

            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    Task task = new Task(
                            rs.getString("id"),
                            rs.getString("title"),
                            rs.getString("description"),
                            TaskPriority.valueOf(rs.getString("priority")),
                            TaskTimeLabel.valueOf(rs.getString("timeLabel")),
                            user
                    );
                    tasks.add(task);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return tasks;
    }

    @Override
    public void delete(String taskId) {
        String query = "DELETE FROM tasks WHERE id = ?";

        try (Connection con = DBConnection.getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {

            ps.setString(1, taskId);
            ps.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Eroare la ștergerea task-ului.");
        }
    }

    @Override
    public void update(Task task) {
        String query = "UPDATE tasks SET title = ?, description = ?, priority = ?, timeLabel = ? WHERE id = ?";

        try (Connection con = DBConnection.getConnection();
             PreparedStatement ps = con.prepareStatement(query)) {

            ps.setString(1, task.getTitle());
            ps.setString(2, task.getDescription());
            ps.setString(3, task.getPriority());
            ps.setString(4, task.getTimeLabel());
            ps.setString(5, task.getID()); // Identificam task-ul dupa ID

            ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException("Eroare la actualizarea task-ului.");
        }
    }
}
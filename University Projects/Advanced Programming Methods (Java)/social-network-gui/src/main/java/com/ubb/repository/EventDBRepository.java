package com.ubb.repository;

import com.ubb.database.DBConnection;
import com.ubb.domain.*;
import com.ubb.exceptions.RepositoryException;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class EventDBRepository extends InMemoryRepository<Event> {

    private final UserDBRepository userRepo;

    public EventDBRepository(UserDBRepository userRepo) throws SQLException {
        super();
        this.userRepo = userRepo;
        load();
    }


    public void load() throws SQLException {
        try (Connection connection = DBConnection.getConnection()) {

            String sql = "SELECT * FROM Events";
            PreparedStatement st = connection.prepareStatement(sql);
            ResultSet rs = st.executeQuery();

            while (rs.next()) {
                int eventId = rs.getInt("id");
                //String type = rs.getString("type");

                List<User> subscribers = loadSubscribers(connection, eventId);

                Duck[] rate = loadRaceDucks(connection, eventId);
                Culoar[] culoare = loadRaceCuloare(connection, eventId);

                RaceEvent race = new RaceEvent(eventId, rate, culoare);

                subscribers.forEach(race::subscribe);

                super.add(race);
            }

        } catch (SQLException e) {
            throw new RepositoryException("Eroare load Events: " + e.getMessage());
        }
    }

    private List<User> loadSubscribers(Connection c, int eventId) throws SQLException {
        List<User> list = new ArrayList<>();

        String sql = "SELECT username FROM Event_Subscribers WHERE event_id=?";
        PreparedStatement st = c.prepareStatement(sql);
        st.setInt(1, eventId);
        ResultSet rs = st.executeQuery();

        while (rs.next())
            list.add(userRepo.findByUsername(rs.getString("username")));

        return list;
    }

    private Duck[] loadRaceDucks(Connection c, int eventId) throws SQLException {
        List<Duck> list = new ArrayList<>();

        String sql = "SELECT username FROM RaceEvent_Ducks WHERE event_id=?";
        PreparedStatement st = c.prepareStatement(sql);
        st.setInt(1, eventId);
        ResultSet rs = st.executeQuery();

        while (rs.next()) {
            User u = userRepo.findByUsername(rs.getString("username"));
            if (u instanceof Duck d) list.add(d);
        }

        return list.toArray(new Duck[0]);
    }

    private Culoar[] loadRaceCuloare(Connection c, int eventId) throws SQLException {
        List<Culoar> list = new ArrayList<>();

        String sql = """
                SELECT Culoare.id, Culoare.id_in_race, Culoare.baliza
                FROM RaceEvent_Culoare RC
                JOIN Culoare ON RC.culoar_id = Culoare.id
                WHERE RC.event_id=?
                ORDER BY Culoare.id_in_race
                """;

        PreparedStatement st = c.prepareStatement(sql);
        st.setInt(1, eventId);
        ResultSet rs = st.executeQuery();

        while (rs.next()) {
            int index = rs.getInt("id_in_race");
            double baliza = rs.getDouble("baliza");
            list.add(new Culoar(index, baliza));
        }

        return list.toArray(new Culoar[0]);
    }

    public void loadNotifications(List<String> notifications) {
        try(Connection connection = DBConnection.getConnection()){
            String sql = "INSERT INTO Notifications (message) VALUES (?)";
            PreparedStatement st = connection.prepareStatement(sql);
            for (String notification : notifications) {
                st.setString(1, notification);
                st.executeUpdate();
            }
        } catch(SQLException e){
            throw new RepositoryException("Eroare la load notifications in DB: " +  e.getMessage());
        }
    }


    @Override
    public void add(Event e) {
        try (Connection c = DBConnection.getConnection()) {

            String insertEvent = "INSERT INTO Events(type) VALUES(?) RETURNING id";
            PreparedStatement st = c.prepareStatement(insertEvent);
            st.setString(1, "RACE");
            ResultSet rs = st.executeQuery();
            rs.next();

            int eventId = rs.getInt(1);
            e.setEventId(eventId);

            addSubscribers(c, e);

            // if RaceEvent => add specific data
            if (e instanceof RaceEvent race) {
                insertRaceEvent(c, race);
            }

            super.add(e);

        } catch (SQLException ex) {
            throw new RepositoryException("Eroare la adaugarea Event-ului in DB: " + ex.getMessage());
        }
    }

    private void addSubscribers(Connection c, Event e) throws SQLException {
        String sql = "INSERT INTO Event_Subscribers(event_id, username) VALUES(?, ?)";
        PreparedStatement st = c.prepareStatement(sql);
        for (EventObserver u : e.getSubscribers()) {
            st.setInt(1, e.getEventId());
            st.setString(2, ((User) u).getUsername());
            st.executeUpdate();
        }
    }

    private void insertRaceEvent(Connection c, RaceEvent r) throws SQLException {

        String sql = "INSERT INTO RaceEvents(event_id) VALUES(?)";
        PreparedStatement st = c.prepareStatement(sql);
        st.setInt(1, r.getEventId());
        st.executeUpdate();

        String sqlDucks = "INSERT INTO RaceEvent_Ducks(event_id, username) VALUES(?, ?)";
        PreparedStatement stD = c.prepareStatement(sqlDucks);
        for (Duck d : r.getRate()) {
            stD.setInt(1, r.getEventId());
            stD.setString(2, d.getUsername());
            stD.executeUpdate();
        }

        for (Culoar c2 : r.getCuloare()) {

            // insert culoar
            String insertC = "INSERT INTO Culoare(id_in_race, baliza) VALUES(?, ?) RETURNING id";
            PreparedStatement stC = c.prepareStatement(insertC);
            stC.setInt(1, c2.getId());
            stC.setDouble(2, c2.getBaliza());
            ResultSet rsC = stC.executeQuery();
            rsC.next();
            int culoarId = rsC.getInt(1);

            // link to race
            String link = "INSERT INTO RaceEvent_Culoare(event_id, culoar_id) VALUES(?, ?)";
            PreparedStatement stLink = c.prepareStatement(link);
            stLink.setInt(1, r.getEventId());
            stLink.setInt(2, culoarId);
            stLink.executeUpdate();
        }
    }

    @Override
    public void remove(Event e) {
        try (Connection c = DBConnection.getConnection()) {

            // stergem culoarele
            String selectCuloare = """
            SELECT culoar_id FROM RaceEvent_Culoare
            WHERE event_id=?
            """;

            PreparedStatement stSel = c.prepareStatement(selectCuloare);
            stSel.setInt(1, e.getEventId());
            ResultSet rs = stSel.executeQuery();

            List<Integer> culoareIds = new ArrayList<>();
            while (rs.next()) {
                culoareIds.add(rs.getInt("culoar_id"));
            }

            // sterg culoarele din tabelul Culoare
            String deleteCuloare = "DELETE FROM Culoare WHERE id=?";
            PreparedStatement stDelC = c.prepareStatement(deleteCuloare);

            for (int id : culoareIds) {
                stDelC.setInt(1, id);
                stDelC.executeUpdate();
            }

            // delete event
            String deleteEvent = "DELETE FROM Events WHERE id=?";
            PreparedStatement st = c.prepareStatement(deleteEvent);
            st.setInt(1, e.getEventId());
            st.executeUpdate();

            super.remove(e);

        } catch (SQLException ex) {
            throw new RepositoryException("Eroare la stergerea Event-ului in DB: " + ex.getMessage());
        }
    }

    public Event findByEventId(int eventId) {
        return getAll().stream()
                .filter(event -> event.getEventId() == eventId)
                .findFirst()
                .orElse(null);
    }
}

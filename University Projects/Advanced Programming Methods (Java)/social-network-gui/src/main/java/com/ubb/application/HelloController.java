package com.ubb.application;

import com.ubb.repository.*;
import javafx.fxml.FXML;
import com.ubb.domain.Duck;
import com.ubb.domain.Persoana;
import com.ubb.domain.TipRata;
import com.ubb.domain.User;
import com.ubb.exceptions.*;
import com.ubb.relations.Friendship;
import com.ubb.service.UserService;
import com.ubb.util.paging.Page;
import com.ubb.util.paging.Pageable;
import javafx.application.Application;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.BiFunction;
import java.util.function.Supplier;

public class HelloController {

    @FXML private ComboBox<String> comboBox;
    @FXML private TableView<User> userTable;
    @FXML private Button addUserButton, removeUserButton;
    @FXML private Button backButton, nextButton;
    @FXML private Label pageLabel, statusLabel;

    private UserService service;
    private List<User> currentFilteredList;
    private AtomicInteger currentPage = new AtomicInteger(0);
    private final int pageSize = 5;

    @FXML
    public void initialize() throws SQLException {
        setupService();
        setupTable();
        setupFilters();
        setupButtons();
        reloadTable();
    }

    private void setupService() throws SQLException {
        var repo = new UserDBRepository();
        var friendshipRepo = new FriendshipDBRepository(repo);
        var cardRepo = new CardDBRepository(repo);
        var eventRepo = new EventDBRepository(repo);
        var messageRepo = new MessageDBRepository(repo);
        var friendRequestRepo = new FriendRequestDBRepository();
        service = new UserService(repo, friendshipRepo, cardRepo, eventRepo, messageRepo, friendRequestRepo);

        currentFilteredList = new ArrayList<>(service.getAllUsers());
    }

    private void setupTable() {
        TableColumn<User, String> col = new TableColumn<>("Username");
        col.setCellValueFactory(new PropertyValueFactory<>("username"));
        userTable.getColumns().add(col);
    }

    private void setupFilters() {
        comboBox.getItems().addAll("All","Persoana","Duck","FlyingDuck","SwimmingDuck","FlyingAndSwimmingDuck");
        comboBox.getSelectionModel().select("All");

        comboBox.valueProperty().addListener((obs, oldV, newV) -> {
            applyFilter(newV);
            currentPage.set(0);
            reloadTable();
        });
    }

    private void applyFilter(String filter) {
        var all = service.getAllUsers();

        currentFilteredList =
                switch (filter) {
                    case "Persoana" -> all.stream().filter(u -> u instanceof Persoana).toList();
                    case "Duck" -> all.stream().filter(u -> u instanceof Duck).toList();
                    case "FlyingDuck" -> all.stream()
                            .filter(u -> u instanceof Duck d && d.getTip() == TipRata.FLYING).toList();
                    case "SwimmingDuck" -> all.stream()
                            .filter(u -> u instanceof Duck d && d.getTip() == TipRata.SWIMMING).toList();
                    case "FlyingAndSwimmingDuck" -> all.stream()
                            .filter(u -> u instanceof Duck d && d.getTip() == TipRata.FLYING_AND_SWIMMING).toList();
                    default -> all;
                };
    }

    private void setupButtons() {
        backButton.setOnAction(e -> {
            if (currentPage.get() > 0) {
                currentPage.decrementAndGet();
                reloadTable();
            }
        });

        nextButton.setOnAction(e -> {
            currentPage.incrementAndGet();
            var page = service.findAllOnPage(new Pageable(currentPage.get(), pageSize), currentFilteredList);
            if (page == null || !page.getElementsOnPage().iterator().hasNext()) {
                currentPage.decrementAndGet();
            }
            reloadTable();
        });

        addUserButton.setOnAction(e -> {
            service.addPersoana("test","mail","pass","nume","pren","2001-01-01","job");
            applyFilter(comboBox.getValue());
            reloadTable();
            statusLabel.setText("User added!");
        });

        removeUserButton.setOnAction(e -> {
            var user = userTable.getSelectionModel().getSelectedItem();
            if (user != null) {
                service.removeUser(user.getUsername());
                applyFilter(comboBox.getValue());
                reloadTable();
                statusLabel.setText("User removed!");
            }
        });
    }

    private void reloadTable() {
        Page<User> page = service.findAllOnPage(new Pageable(currentPage.get(), pageSize), currentFilteredList);
        if (page == null) return;

        userTable.setItems(FXCollections.observableArrayList((User) page.getElementsOnPage()));

        int totalPages = (int) Math.max(1, Math.ceil((double) currentFilteredList.size() / pageSize));
        pageLabel.setText("Page " + (currentPage.get() + 1) + "/" + totalPages);
    }
}


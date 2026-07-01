package com.ubb.application;

import com.ubb.chatting.ChatBoxController;
import com.ubb.domain.Duck;
import com.ubb.domain.Persoana;
import com.ubb.domain.TipRata;
import com.ubb.domain.User;
import com.ubb.exceptions.*;
import com.ubb.relations.Friendship;
import com.ubb.repository.*;
import com.ubb.service.UserService;
import com.ubb.util.paging.Page;
import com.ubb.util.paging.Pageable;
import javafx.application.Application;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
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

public class HelloApplication extends Application {

    private UserService service;

    private String currentUser;     // username-ul

    private AtomicInteger currentPage = new AtomicInteger(0);
    private AtomicInteger currentFriendshipPage = new AtomicInteger(0);
    private final int pageSize = 5;     // cati useri pe o pagina
    private List<User> currentFilteredList;     // lista curenta de useri filtrati
    private String currentFilter;
    @FXML private Label pageLabel = new Label();

    private VBox comboAndButtonsBox;
    @FXML private TableView<User> tableView;
    @FXML private TableColumn<User, String> usernameColumn;
    @FXML private TableView<Friendship> tableViewFriendships;
    @FXML private ComboBox<String> comboBox;
    @FXML private Label communityNumberLabel;
    @FXML private Label mostSociableCommunity;

    @FXML private Button btnAddUser;
    @FXML private Button btnRemoveUser;
    @FXML private Button btnFriendships;
    @FXML private Button btnBack;
    @FXML private Button btnNext;

    @FXML private Button btnChat;

    @Override
    public void start(Stage stage) throws SQLException, IOException {

        var repo = new UserDBRepository();
        var friendshipRepo = new FriendshipDBRepository(repo);
        var cardRepo = new CardDBRepository(repo);
        var eventRepo = new EventDBRepository(repo);
        var messageRepo = new MessageDBRepository(repo);
        var friendRequestRepo = new FriendRequestDBRepository();
        this.service = new UserService(repo, friendshipRepo, cardRepo, eventRepo, messageRepo, friendRequestRepo);

        FXMLLoader loader = new FXMLLoader(HelloApplication.class.getResource("/com/ubb/hello-view.fxml"));
        loader.setController(this);

        Scene scene = new Scene(loader.load(), 900, 750);
        stage.setTitle("DuckSocialNetwork");
        stage.setScene(scene);
        stage.show();

        // initializam logica DUPA ce s-a incarcat interfata
        initializeLogic();
    }

    private void initializeLogic() {
        // setare lista initiala
        currentFilteredList = new ArrayList<>(service.getAllUsers());

        // configurare comboBox
        comboBox.getItems().setAll("All", "Persoana", "Duck", "FlyingDuck", "SwimmingDuck", "FlyingAndSwimmingDuck");
        comboBox.getSelectionModel().select("All"); // default
        setupComboBoxFiltering(comboBox);

        // configurare tabel
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        // incarcam prima pagina
        loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel, service::findAllOnPage);

        // configurare statistici
        updateCommunityStats(communityNumberLabel, mostSociableCommunity);

        // configurare actiuni butoane (Event Handlers)
        btnAddUser.setOnAction(e -> addUserManagementStage(1));
        btnRemoveUser.setOnAction(e -> addUserManagementStage(0));
        btnFriendships.setOnAction(e -> friendshipManagementStage());

        // configurare butoane paginare (Logic mutat aici din addPaginationButtons)
        btnBack.setOnAction(e -> {
            if (currentPage.get() > 0){
                currentPage.decrementAndGet();
                loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel, service::findAllOnPage);
            }
        });

        btnNext.setOnAction(e -> {
            currentPage.incrementAndGet();
            var testPage = service.findAllOnPage(new Pageable(currentPage.get(), pageSize), currentFilteredList);
            if (testPage == null || !testPage.getElementsOnPage().iterator().hasNext()) {
                currentPage.decrementAndGet(); // Revenim daca pagina e goala
            }
            // Reincarcam pagina (fie cea noua, fie cea veche daca next a esuat)
            loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel, service::findAllOnPage);
        });

        // configurare chatbox
        btnChat.setOnAction(e -> {
            try {
                var chatBox = new ChatBoxController(service);
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }
        });
    }

    private <T> void loadPage(TableView<T> tableView, List<T> elementsList, AtomicInteger currentPage, int pageSize, Label pageLabel, BiFunction<Pageable, List<T>, Page<T>> paginator) {
        Page<T> page = paginator.apply(new Pageable(currentPage.get(), pageSize), elementsList);
        if(page == null) return;

        ObservableList<T> list = FXCollections.observableArrayList();
        page.getElementsOnPage().forEach(list::add);

        int totalPages = (int)Math.ceil((double)elementsList.size() / pageSize);
        if(totalPages == 0) totalPages = 1;

        pageLabel.setText("Page " + (currentPage.get() + 1) + " / " + totalPages);
        tableView.setItems(list);
    }

    public void updateCommunityStats(Label communityNumberLabel, Label mostSociableCommunity) {
        communityNumberLabel.setText(showCommunitiesNumber());
        mostSociableCommunity.setText(showMostSociableCommunity());
    }

    public String showCommunitiesNumber() {
        String res = "";
        try {
            res += "Number of communities: " + service.getNumberOfCommunities();
        } catch (MyException e) {
            res += e.getMessage();
        }
        return res;
    }

    public String showMostSociableCommunity() {
        String res = "";
        try{
            var community = service.getMostSociableCommunity();
            for(User u : community){
                res += u.getUsername() + "\n";
            }
        } catch(MyException ex) {}
        return res;
    }

    public void addUserManagementStage(int dummy) {
        Stage stage = new Stage();
        VBox  root = new VBox(5);
        switch(dummy) {
            case 0:
                userManagementRemove(root);
                break;
            case 1:
                userManagementAdd(root);
                break;
            default:
                break;
        }
        Scene scene;
        if(dummy == 1) {
            scene = new Scene(root, 320, 370);
        } else {
            scene = new Scene(root, 320, 90);
        }
        stage.setTitle("User Management");
        stage.setScene(scene);
        stage.show();
    }

    public void userManagementRemove(Pane root) {
        var removeLabel = new Label("Remove User:");

        var usernameField = new TextField();
        usernameField.setPromptText("Username");
        usernameField.setFocusTraversable(false);
        usernameField.setAlignment(Pos.CENTER);

        var removeButton = new Button("Remove");
        removeButton.setAlignment(Pos.CENTER);

        var successLabel = new Label();
        successLabel.setStyle("-fx-text-fill: black; -fx-font-size: 12;");
        var errorLabel = new Label();
        errorLabel.setStyle("-fx-text-fill: red; -fx-font-size: 12;");

        removeButton.setOnAction(e -> {
            try {
                successLabel.setText("");
                errorLabel.setText("");
                service.removeUser(usernameField.getText());
                usernameField.setText("");
                successLabel.setText("User successfully removed!");

                setupCurrentFilteredList(currentFilter);
                loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel,
                        service::findAllOnPage);
                updateCommunityStats(communityNumberLabel, mostSociableCommunity);
            } catch(UserNotFoundException ex){
                errorLabel.setText(ex.getMessage());
            }
        });


        root.getChildren().addAll(removeLabel, usernameField, removeButton, successLabel, errorLabel);
    }

    public void userManagementAdd(Pane root) {
        var userLabel =  new Label("User Type:");
        var comboBox = new ComboBox<String>();
        comboBox.getItems().setAll(
                "Persoana",
                "Duck"
        );
        var fields = new VBox(5);

        // aici tratam erorile de validare
        var successLabel = new Label();
        successLabel.setStyle("-fx-text-fill: black; -fx-font-size: 12;");
        var errorLabel = new Label();
        errorLabel.setStyle("-fx-text-fill: red; -fx-font-size: 12;");

        comboBox.getSelectionModel().selectedItemProperty().addListener((observableValue, oldValue, newValue) -> {
            fields.getChildren().clear();
            errorLabel.setText("");

            var usernameField = new TextField();
            usernameField.setPromptText("Username");
            var emailField = new TextField();
            emailField.setPromptText("Email");
            var passwordField = new PasswordField();
            passwordField.setPromptText("Password");

            fields.getChildren().addAll(usernameField, emailField, passwordField);

            var addButton = new Button("Add");

            switch(newValue) {
                case "Persoana":
                    var numeField  = new TextField();
                    numeField.setPromptText("Nume");
                    var prenumeField =  new TextField();
                    prenumeField.setPromptText("Prenume");
                    var dataNasteriiField = new TextField();
                    dataNasteriiField.setPromptText("Data Nasterii");
                    var ocupatieField = new TextField();
                    ocupatieField.setPromptText("Ocupatie");

                    addPersoanaEvent(addButton, successLabel, errorLabel, usernameField, emailField, passwordField,
                            numeField, prenumeField, dataNasteriiField, ocupatieField);
                    fields.getChildren().addAll(numeField, prenumeField, dataNasteriiField, ocupatieField);
                    break;
                case "Duck":
                    var tipRataField =  new TextField();
                    tipRataField.setPromptText("Tip Rata");
                    var vitezaField = new TextField();
                    vitezaField.setPromptText("Viteza");
                    var rezistentaField = new TextField();
                    rezistentaField.setPromptText("Rezistenta");

                    addDuckEvent(addButton, successLabel, errorLabel, usernameField, emailField, passwordField,
                            tipRataField, vitezaField, rezistentaField);
                    fields.getChildren().addAll(tipRataField, vitezaField, rezistentaField);
                    break;
            }

            fields.getChildren().addAll(addButton, successLabel, errorLabel);

        });

        root.getChildren().addAll(userLabel, comboBox, fields);
    }

    public void addPersoanaEvent(Button addButton, Label successLabel, Label errorLabel, TextField username, TextField email, TextField password,
                                 TextField nume, TextField prenume, TextField dataNasterii, TextField ocupatie) {
        addButton.setOnAction(e -> {
            try {
                successLabel.setText("");
                errorLabel.setText("");
                service.addPersoana(
                        username.getText(),
                        email.getText(),
                        password.getText(),
                        nume.getText(),
                        prenume.getText(),
                        dataNasterii.getText(),
                        ocupatie.getText()
                );
                username.setText("");
                email.setText("");
                password.setText("");
                nume.setText("");
                prenume.setText("");
                dataNasterii.setText("");
                ocupatie.setText("");
                successLabel.setText("User successfully added!");

                setupCurrentFilteredList(currentFilter);
                loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel,
                        service::findAllOnPage);
                updateCommunityStats(communityNumberLabel, mostSociableCommunity);
            } catch (ValidatorException ex) {
                errorLabel.setText(ex.getMessage());
            }
        });
    }

    public void addDuckEvent(Button addButton, Label successLabel, Label errorLabel, TextField username, TextField email, TextField password,
                             TextField tipRataField, TextField vitezaField, TextField rezistentaField) {

        addButton.setOnAction(e -> {
            try {
                successLabel.setText("");
                errorLabel.setText("");
                double viteza = -1, rezistenta = -1;
                try {
                    viteza = Double.parseDouble(vitezaField.getText());
                } catch (NumberFormatException ex) {
                    // viteza ramane -1
                }
                try {
                    rezistenta = Double.parseDouble(rezistentaField.getText());
                } catch (NumberFormatException ex) {
                    // rezistenta ramane -1
                }
                TipRata tipRata;
                try {
                    tipRata = TipRata.valueOf(tipRataField.getText().toUpperCase());
                } catch (IllegalArgumentException ex) {
                    tipRata = null;
                }

                service.addDuck(
                        username.getText(),
                        email.getText(),
                        password.getText(),
                        tipRata,
                        viteza,
                        rezistenta
                );
                username.setText("");
                email.setText("");
                password.setText("");
                tipRataField.setText("");
                vitezaField.setText("");
                rezistentaField.setText("");
                successLabel.setText("User successfully added!");

                setupCurrentFilteredList(currentFilter);
                loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel,
                        service::findAllOnPage);
                updateCommunityStats(communityNumberLabel, mostSociableCommunity);
            } catch (ValidatorException ex) {
                errorLabel.setText(ex.getMessage());
            }
        });
    }

    public void friendshipManagementStage() {
        Stage stage = new Stage();
        HBox  root = new HBox(5);

        addFriendshipsTabelView(root);
        addFriendshipsFunctionalitiesButtons(root);

        Scene scene = new Scene(root, 500, 300);
        stage.setTitle("Friendships Management");
        stage.setScene(scene);
        stage.show();
    }

    public void addFriendshipsTabelView(Pane root) {
        VBox vbox = new  VBox(5);
        Label pageLabel = new Label();
        tableViewFriendships = new TableView<>();

        TableColumn<Friendship, String> user1Col = new TableColumn<>("user1");
        TableColumn<Friendship, String> user2Col = new TableColumn<>("user2");

        user1Col.setCellValueFactory(cell ->
                new SimpleStringProperty(cell.getValue().getFriend1().getUsername()));
        user2Col.setCellValueFactory(cell ->
                new SimpleStringProperty(cell.getValue().getFriend2().getUsername()));
        tableViewFriendships.getColumns().addAll(user1Col, user2Col);

        loadPage(tableViewFriendships, service.getAllFriendships(), currentFriendshipPage, pageSize, pageLabel,
                service::findAllFriendshipsOnPage);

        vbox.getChildren().addAll(tableViewFriendships, pageLabel);
        addPaginationButtons(vbox, tableViewFriendships, () -> service.getAllFriendships(),  currentFriendshipPage, pageSize, pageLabel,
                service::findAllFriendshipsOnPage);

        root.getChildren().add(vbox);
    }

    public void addFriendshipsFunctionalitiesButtons(Pane root) {
        VBox vbox = new VBox(5);
        TextField friend1Field = new TextField();
        TextField friend2Field = new TextField();

        Button addButton = new Button("Add Friendship");
        Button removeButton = new Button("Remove Friendship");

        var successLabel = new Label();
        successLabel.setStyle("-fx-text-fill: black; -fx-font-size: 12;");
        var errorLabel = new Label();
        errorLabel.setStyle("-fx-text-fill: red; -fx-font-size: 12;");

        addButton.setOnAction(e -> {
            try {
                successLabel.setText("");
                errorLabel.setText("");
                service.addFriendship(friend1Field.getText(), friend2Field.getText());
                friend1Field.setText("");
                friend2Field.setText("");
                successLabel.setText("Friendship successfully added!");

                loadPage(tableViewFriendships, service.getAllFriendships(), currentFriendshipPage, pageSize, pageLabel,
                        service::findAllFriendshipsOnPage);
                updateCommunityStats(communityNumberLabel, mostSociableCommunity);
            } catch (ValidatorException | DuplicateException | UserNotFoundException ex) {
                errorLabel.setText(ex.getMessage());
            }
        });

        removeButton.setOnAction(e -> {
            try {
                successLabel.setText("");
                errorLabel.setText("");
                service.removeFriendship(friend1Field.getText(), friend2Field.getText());
                friend1Field.setText("");
                friend2Field.setText("");
                successLabel.setText("Friendship successfully removed!");

                loadPage(tableViewFriendships, service.getAllFriendships(), currentFriendshipPage, pageSize, pageLabel,
                        service::findAllFriendshipsOnPage);
                updateCommunityStats(communityNumberLabel, mostSociableCommunity);
            } catch (RepositoryException ex) {
                errorLabel.setText(ex.getMessage());
            }
        });

        vbox.getChildren().addAll(friend1Field, friend2Field, addButton, removeButton, successLabel, errorLabel);
        root.getChildren().add(vbox);
    }

    private <T> void addPaginationButtons(VBox root, TableView<T> tableView, Supplier<List<T>> elementsSupplier, AtomicInteger currentPage, int pageSize, Label pageLabel, BiFunction<Pageable, List<T>, Page<T>> paginator) {

        HBox hbox = new HBox(10);
        hbox.setAlignment(Pos.CENTER);

        Button back = new Button("<< Back");
        Button next = new Button("Next >>");

        back.setOnAction(e -> {
            if (currentPage.get() > 0){
                currentPage.decrementAndGet();
                loadPage(tableView, elementsSupplier.get(), currentPage, pageSize, pageLabel,
                        paginator);
            }
        });

        next.setOnAction(e -> {
            currentPage.incrementAndGet();
            var testPage = paginator.apply(new Pageable(currentPage.get(), pageSize), elementsSupplier.get());
            if (testPage == null || !testPage.getElementsOnPage().iterator().hasNext()) {
                currentPage.decrementAndGet();
                loadPage(tableView, elementsSupplier.get(), currentPage, pageSize, pageLabel, paginator);
            } else {
                loadPage(tableView, elementsSupplier.get(), currentPage, pageSize, pageLabel, paginator);
            }
        });

        hbox.getChildren().addAll(back, next);
        root.getChildren().add(hbox);
    }

    public void setupComboBoxFiltering(ComboBox<String> comboBox) {

        currentFilter = "All";

        //reset pagina la filtrare
        comboBox.getSelectionModel().selectedItemProperty().addListener((observableValue, oldValue, newValue) -> {
            setupCurrentFilteredList(newValue);

            currentPage.set(0);    //reset pagina la fiecare filtrare
            loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel,
                    service::findAllOnPage);
        });
    }

    public void setupCurrentFilteredList(String filter) {

        var all = service.getAllUsers();
        currentFilter = filter;

        if(filter.equals("All")){
            currentFilteredList = all;
        }
        if(filter.equals("Persoana")){
            currentFilteredList = all.stream()
                    .filter(user -> user instanceof Persoana)
                    .toList();
        }
        else if(filter.equals("Duck")){
            currentFilteredList = all.stream()
                    .filter(user -> user instanceof Duck)
                    .toList();
        }
        else if(filter.trim().equals("FlyingDuck")){
            currentFilteredList = all.stream()
                    .filter(user -> user instanceof Duck d && d.getTip() == TipRata.FLYING)
                    .toList();
        }
        else if(filter.trim().equals("SwimmingDuck")){
            currentFilteredList = all.stream()
                    .filter(user -> user instanceof Duck d && d.getTip() == TipRata.SWIMMING)
                    .toList();
        }
        else if(filter.trim().equals("FlyingAndSwimmingDuck")){
            currentFilteredList = all.stream()
                    .filter(user -> user instanceof Duck d && d.getTip() == TipRata.FLYING_AND_SWIMMING)
                    .toList();
        }
    }


    // VECHIUL START():
//            HBox root = new HBox(5);  // spacing = 5
//        root.setPadding(new Insets(40));
//        root.setAlignment(Pos.BASELINE_CENTER);
//
//        var repo = new UserDBRepository();
//        var friendshipRepo = new FriendshipDBRepository(repo);
//        var cardRepo = new CardDBRepository(repo);
//        var eventRepo = new EventDBRepository(repo);
//        this.service = new UserService(repo, friendshipRepo, cardRepo, eventRepo);
//
//        currentFilteredList = new ArrayList<>(service.getAllUsers());
//        comboAndButtonsBox = new VBox(5);
//        root.getChildren().add(comboAndButtonsBox);     // partea din stanga cu comboBox si butoanele de add/remove
//        addComboBox(comboAndButtonsBox);
//        addFunctionalitiesButtons(comboAndButtonsBox);
//        addUserTableView(root);
//        setupComboBoxFiltering(comboBox);
//        Scene scene = new Scene(root, 800, 600);
//        stage.setTitle("DuckSocialNetwork");
//        stage.setScene(scene);
//        stage.show();

    // COD VECHI (replaced by initializeLogic()):
//    public void addComboBox(Pane root) {
//        comboBox = new ComboBox<>();
//        comboBox.getItems().setAll(
//                "All",
//                "Persoana",
//                "Duck",
//                "   FlyingDuck",
//                "   SwimmingDuck",
//                "   FlyingAndSwimmingDuck"
//        );
//        comboBox.getSelectionModel().clearSelection();
//
//        root.getChildren().add(comboBox);
//    }
//
//    public void addFunctionalitiesButtons(Pane root) {
//        var userLabel = new Label("Manage users:");
//        var addUserButton = new Button("Add User");
//        var removeUserButton = new Button("Remove User");
//
//        var friendshipLabel = new Label("Manage Friendships:");
//        var friendshipButton = new Button("See Friendships");
//
//        var communityLabel = new Label("Communities:");
//        communityNumberLabel = new Label();
//        mostSociableCommunity = new Label();
//        updateCommunityStats(communityNumberLabel, mostSociableCommunity);
//
//        addUserButton.setOnAction(e -> {
//            addUserManagementStage(1);
//        });
//
//        removeUserButton.setOnAction(e -> {
//            addUserManagementStage(0);
//        });
//
//        friendshipButton.setOnAction(e -> {
//            friendshipManagementStage();
//        });
//
//        root.getChildren().addAll(userLabel,  addUserButton, removeUserButton,
//                friendshipLabel, friendshipButton, communityLabel, communityNumberLabel, mostSociableCommunity);
//    }
//    public TableView<User> addUserTableView(Pane root) {
//        VBox vbox = new VBox(5);
//        tableView = new TableView<>();
//
//        TableColumn<User, String> nameCol = new TableColumn<>("username");
//        tableView.getColumns().addAll(nameCol);
//        loadPage(tableView, currentFilteredList, currentPage, pageSize, pageLabel,
//                service::findAllOnPage);
//
//        vbox.getChildren().add(tableView);
//        nameCol.setCellValueFactory(new PropertyValueFactory<User, String>("username"));
//        addPaginationButtons(vbox, tableView,  () -> currentFilteredList, currentPage, pageSize, pageLabel,
//                service::findAllOnPage);
//        vbox.getChildren().add(pageLabel);
//
//        root.getChildren().add(vbox);
//
//        return tableView;
//    }
}

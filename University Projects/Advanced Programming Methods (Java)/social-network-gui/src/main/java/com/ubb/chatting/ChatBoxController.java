package com.ubb.chatting;

import com.ubb.application.HelloApplication;
import com.ubb.domain.User;
import com.ubb.exceptions.DuplicateException;
import com.ubb.exceptions.RepositoryException;
import com.ubb.exceptions.UserNotFoundException;
import com.ubb.exceptions.ValidatorException;
import com.ubb.relations.FriendRequest;
import com.ubb.service.UserService;
import javafx.animation.PauseTransition;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ChatBoxController implements Observer {

    private UserService service;

    private Stage stage;

    private String currentUser;
    @FXML private Label currentUserLabel;

    @FXML private Button btnLogin;
    @FXML private Button btnLogout;

    // messages
    @FXML private ScrollPane scrollPane;
    @FXML private Button btnSend;
    @FXML private ComboBox<String> comboUserSelector;
    @FXML private VBox messagesContainer;
    @FXML private TextArea messageInput;
    private Message currentReplyMessage = null;
    @FXML private HBox replyPreviewPanel;
    @FXML private Label replyPreviewLabel;
    @FXML private Button btnCancelReply;

    // typing...
    @FXML private Label typingLabel;
    private boolean isTyping = false;
    private PauseTransition typingTimer;

    // friend request + notifications
    @FXML private Button btnNotifications;
    @FXML private Button btnAddFriend;

    // OBSERVER
    @Override
    public void update() {
        loadConversation();
    }

    public void updateTyping(String username, boolean typing) {
        if(!typing) {
            typingLabel.setVisible(false);
        } else {
            typingLabel.setText(username + " is typing...");
            typingLabel.setVisible(true);
        }
    }

    public void updateNotifications(int notifications) {
        btnNotifications.setText("Notifications: " + notifications);
    }

    public ChatBoxController(UserService service) throws IOException {
        this.service = service;
        service.subscribe(this);
        createChatBox();
    }

    public String getSender() {
        return currentUser;
    }

    public String getReceiver() {
        return comboUserSelector.getValue();
    }

    public void createChatBox() throws IOException {
        FXMLLoader loader = new FXMLLoader(HelloApplication.class.getResource("/com/ubb/chat-view.fxml"));
        loader.setController(this);
        Scene scene = new Scene(loader.load(), 700, 500);

        initializeChatLogic();

        stage = new Stage();
        stage.setTitle("Duck Chat - " + (currentUser != null ? currentUser : "Guest"));
        stage.setScene(scene);
        stage.show();
    }

    private void initializeChatLogic() {
        // configurare butoane login/logout
        currentUserLabel.setText("Current user: Guest");
        currentUser = null;

        // initial logout-ul e disabled pt guest
        btnLogout.setDisable(true);
        btnLogin.setOnAction(e -> addLoginStage());
        btnLogout.setOnAction(e -> userLogout());

        loadChatComboBox(currentUser);

        comboUserSelector.getSelectionModel()
                .selectedItemProperty().addListener((observableValue, oldValue, newValue) -> {
                    if(currentUser == null) {
                        messagesContainer.getChildren().clear();
                        btnAddFriend.setText("Select a user first!");
                    }
                    else {
                        loadConversation();
                        btnAddFriend.setVisible(true);
                        btnAddFriend.setManaged(true);
                        btnAddFriend.setText("Add " + newValue + " as Friend!");
                    }
                });

        // autoscroll pana la cel mai recent mesaj
        messagesContainer.heightProperty().addListener((observable, oldValue, newValue) -> {
            scrollPane.setVvalue(1.0);
        });

        // ascundem panoul de reply la inceput
        replyPreviewPanel.setVisible(false);
        replyPreviewPanel.setManaged(false);

        // anularea reply-ului
        btnCancelReply.setOnAction(e -> {
            this.currentReplyMessage = null;
            replyPreviewPanel.setVisible(false);
            replyPreviewPanel.setManaged(false);
        });

        btnSend.setOnAction(e -> sendMessage());

        // adaugam un timer ca dupa 1.5 secunde de inactivitate, sa se considere ca "nu mai scrie"
        typingTimer = new PauseTransition(Duration.seconds(1.5));
        typingTimer.setOnFinished(e -> {
            isTyping = false;
            if (currentUser != null)
                service.notifyTyping(currentUser, comboUserSelector.getValue(), false);
        });

        // adaugam un listener pe text area pt "is typing..."
        messageInput.textProperty().addListener((obs, oldText, newText) -> {
            // daca se opreste din scris
            if(newText.isEmpty()) {
                typingTimer.stop();
                if(isTyping) {
                    isTyping = false;
                    service.notifyTyping(currentUser, comboUserSelector.getValue(), false);
                }
                return;
            }

            // daca utilizatorul scrie, resetam timer-ul
            typingTimer.playFromStart();

            if (!isTyping) {
                isTyping = true;
                service.notifyTyping(currentUser, comboUserSelector.getValue(), true);
            }
        });

        // ascundem partea de friend request initial pentru Guest
        setupFriendRequestButtons(false);

        // trimiterea cererii de prietenie
        btnAddFriend.setOnAction(e -> {
            try {
                String from_user = currentUser;
                String to_user = comboUserSelector.getValue();
                if (from_user == null || to_user == null) return;

                FriendRequest friendRequest = new FriendRequest(from_user, to_user, "pending");
                service.addFriendRequest(friendRequest);

                btnAddFriend.setText("Request sent!");

                service.notifyNotifications(to_user);

            } catch (RepositoryException ex) {
                btnAddFriend.setText(ex.getMessage());
            }
        });


        btnNotifications.setOnAction(e -> {
           setupNotificationsStage();
        });
    }

    public void setupNotificationsStage() {
        Stage stage = new Stage();
        HBox  root = new HBox(5);

        addNotificationsTabelView(root);

        Scene scene = new Scene(root, 250, 300);
        stage.setTitle("Notifications Management");
        stage.setScene(scene);
        stage.show();
    }

    public void addNotificationsTabelView(Pane root) {
        VBox vbox = new VBox(5);
        TableView<FriendRequest> tableView = new TableView<>();

        TableColumn<FriendRequest, String> fromCol = new TableColumn<>("From");
        TableColumn<FriendRequest, String> toCol = new TableColumn<>("To");
        TableColumn<FriendRequest, String> statusCol = new TableColumn<>("Status");

        fromCol.setCellValueFactory(cell ->
                new SimpleStringProperty(cell.getValue().getFromUser()));
        toCol.setCellValueFactory(cell ->
                new SimpleStringProperty(cell.getValue().getToUser()));
        statusCol.setCellValueFactory(cell ->
                new SimpleStringProperty(cell.getValue().getStatus()));
        tableView.getColumns().addAll(fromCol, toCol, statusCol);

        loadNotificationsTableView(tableView);

        HBox hbox =  new HBox(5);
        hbox.alignmentProperty().set(Pos.CENTER);
        Button accept = new Button("Accept");
        Button reject = new Button("Reject");

        accept.setOnAction(e -> {
            try {
                var friendRequest = tableView.getSelectionModel().getSelectedItem();
                if (friendRequest == null || !friendRequest.getStatus().equals("pending")) return;

                service.manageFriendRequest(friendRequest, "approved");
                //loadNotificationsTableView(tableView);
                friendRequest.setStatus("approved");
                tableView.refresh();
                service.notifyNotifications(currentUser);

            } catch (RepositoryException | ValidatorException ex) {
                throw new RuntimeException(ex);
            }
        });

        reject.setOnAction(e -> {
            try {
                var friendRequest = tableView.getSelectionModel().getSelectedItem();
                if (friendRequest == null || !friendRequest.getStatus().equals("pending")) return;

                service.manageFriendRequest(friendRequest, "rejected");
                //loadNotificationsTableView(tableView);
                friendRequest.setStatus("rejected");
                tableView.refresh();
                service.notifyNotifications(currentUser);

            } catch (RepositoryException ex) {
                throw new RuntimeException(ex);
            }
        });

        hbox.getChildren().addAll(accept, reject);
        vbox.getChildren().addAll(tableView, hbox);

        root.getChildren().add(vbox);
    }

    public void loadNotificationsTableView(TableView<FriendRequest> tableView) {
        ObservableList<FriendRequest> list = FXCollections.observableArrayList();
        list.addAll(service.getAllFriendRequests(currentUser));
        tableView.setItems(list);
    }

    private void loadChatComboBox(String currentUser) {
        if(currentUser != null){    //ca guest nu poti da mesaje
            comboUserSelector.getItems().setAll(service.getAllUsers().stream()
                    .map(User::getUsername)
                    .filter(username -> !username.equals(currentUser))
                    .toArray(String[]::new));
        }
        else{
            comboUserSelector.getItems().clear();
        }
    }


    public void sendMessage() {
        String textToSend = messageInput.getText();
        String selectedUser = comboUserSelector.getValue();

        if(textToSend.isEmpty() || selectedUser.isEmpty()){ return; }


        var sender = service.findUserByUsername(currentUser);
        var receiver = service.findUserByUsername(comboUserSelector.getValue());
        if(sender == null || receiver == null){ return; }

        // id 0 e un dummy, baza de date il va ignora si va genera id-ul potrivit datorita BIGSERIAL
        Message m = new Message(0, sender, receiver, textToSend, LocalDateTime.now());

        // daca mesajul e un reply la alt mesaj
        if(currentReplyMessage != null)
            m.setReplyTo(currentReplyMessage);

        try {
            service.addMessage(m);
            loadSenderMessageBubble(m);

            messageInput.clear();
            currentReplyMessage = null;
            replyPreviewPanel.setVisible(false);
            replyPreviewPanel.setManaged(false);

            // observer pattern
            service.notifySubscribers();
        } catch (RepositoryException e) {
            throw new RuntimeException(e);
        }
    }

    public void replyLoadSetup(VBox messageBubble, Message m) {
        String replyText = "Replying to: " + m.getReplyTo().getSender().getUsername();
        Label replyLabel = new Label(replyText);
        replyLabel.setStyle("-fx-text-fill: #ffffff; -fx-font-size: 10px; -fx-font-style: italic;");

        Label replyContentLabel = new Label(m.getReplyTo().getMessage());
        //replyContentLabel.setStyle("-fx-text-fill: #bdc3c7; -fx-font-size: 10px;");
        replyContentLabel.setStyle("-fx-text-fill: #e8e5e5; -fx-font-size: 10px;");
        replyContentLabel.setMaxWidth(300);

        // Le punem intr-un container mic cu o bara verticala
        VBox replyContainer = new VBox(replyLabel, replyContentLabel);
        replyContainer.setStyle("-fx-border-color: #bdc3c7; -fx-border-width: 0 0 0 2; -fx-padding: 0 0 0 5;");

        messageBubble.getChildren().add(replyContainer);
    }

    public void replyItemSetup(MenuItem replyItem,  Message m) {
        replyItem.setOnAction(e -> {
            currentReplyMessage = m;

            // updatam panoul vizual
            String sender = m.getSender().getUsername();
            String previewText = m.getMessage().length() > 20
                    ? m.getMessage().substring(0, 20) + "..."   // in caz ca e prea lung mesajul
                    : m.getMessage();
            replyPreviewLabel.setText(sender + ": " + previewText);

            replyPreviewPanel.setVisible(true);
            replyPreviewPanel.setManaged(true);

            // sa putem scrie direct dupa ce am selectat reply
            messageInput.requestFocus();
        });
    }

    public void loadSenderMessageBubble(Message m) {
        // stilizarea labelului mesajului
        Label textLabel = new Label(m.getMessage());
        textLabel.setWrapText(true);
        textLabel.setMaxWidth(350); // mesajul sa nu fie cat tot ecranul
        textLabel.setStyle("-fx-text-fill: #ffffff; -fx-font-size: 13px; -fx-font-weight: bold;");

        // label pentru data/ora (mic, sub text)
        Label dateLabel = new Label(m.getDate().format(DateTimeFormatter.ofPattern("dd MMM yy HH:mm")));
        dateLabel.setStyle("-fx-text-fill: #d8e9ea; -fx-font-size: 9px;");
        dateLabel.setAlignment(Pos.BOTTOM_RIGHT);

        VBox messageBubble = new VBox(5); // spatiu intre text si data
        if (m.getReplyTo() != null) {
            replyLoadSetup(messageBubble, m);
        }
        messageBubble.getChildren().addAll(textLabel, dateLabel);

        // stilizare bubble
        // Coltul dreapta-jos e ascutit (0) pentru a indica "speech bubble"
        messageBubble.setStyle("-fx-background-color: #d2a600; " +
                "-fx-background-radius: 15 15 0 15; " +
                "-fx-padding: 10 15 10 15; " +
                "-fx-effect: dropshadow(three-pass-box, rgba(0,0,0,0.1), 5, 0, 0, 1);");

        // container HBox pentru aliniere (mesajele mele -> dreapta)
        HBox rowContainer = new HBox();
        rowContainer.setAlignment(Pos.CENTER_RIGHT); // Aliniere la dreapta
        rowContainer.setPadding(new Insets(5, 0, 5, 0)); // Spatiu intre mesaje
        rowContainer.getChildren().add(messageBubble);

        // adaugam logica de reply la acest mesaj
        ContextMenu contextMenu = new ContextMenu();
        MenuItem replyItem = new MenuItem("Reply");
        replyItemSetup(replyItem, m);

        contextMenu.getItems().add(replyItem);
        messageBubble.setOnContextMenuRequested(e ->
                contextMenu.show(messageBubble, e.getScreenX(), e.getScreenY())
        );

        messagesContainer.getChildren().add(rowContainer);
    }

    public void loadReceiverMessageBubble(Message m) {
        Label textLabel = new Label(m.getMessage());
        textLabel.setWrapText(true);
        textLabel.setMaxWidth(350);
        textLabel.setStyle("-fx-text-fill: #ffffff; -fx-font-size: 13px; -fx-font-weight: bold;");

        Label dateLabel = new Label(m.getDate().format(DateTimeFormatter.ofPattern("dd MMM yy HH:mm")));
        dateLabel.setStyle("-fx-text-fill: #d8e9ea; -fx-font-size: 9px;");
        dateLabel.setAlignment(Pos.BOTTOM_RIGHT);

        VBox messageBubble = new VBox(5);
        if(m.getReplyTo() != null) {
            replyLoadSetup(messageBubble, m);
        }
        messageBubble.getChildren().addAll(textLabel, dateLabel);

        messageBubble.setStyle("-fx-background-color: #2c3e50; " +
                "-fx-background-radius: 15 15 15 0; " +
                "-fx-padding: 10 15 10 15; " +
                "-fx-effect: dropshadow(three-pass-box, rgba(0,0,0,0.1), 5, 0, 0, 1);");

        HBox rowContainer = new HBox();
        rowContainer.setAlignment(Pos.CENTER_LEFT);
        rowContainer.setPadding(new Insets(5, 0, 5, 0));
        rowContainer.getChildren().add(messageBubble);

        // adaugam logica de reply la acest mesaj (click dreapta)
        ContextMenu contextMenu = new ContextMenu();
        MenuItem replyItem = new MenuItem("Reply");
        replyItemSetup(replyItem, m);

        contextMenu.getItems().add(replyItem);
        messageBubble.setOnContextMenuRequested(e ->
                contextMenu.show(messageBubble, e.getScreenX(), e.getScreenY())
        );

        messagesContainer.getChildren().add(rowContainer);
    }

    public void loadConversation() {
        messagesContainer.getChildren().clear();

        // incarca conversatia din perspectiva user-ului logat
        String sender = currentUser;
        String receiver = comboUserSelector.getValue();

        for(Message m : service.getAllMessages()){
            if(sender.equals(m.getSender().getUsername()) && receiver.equals(m.getReceiver().getUsername()))
                loadSenderMessageBubble(m);
            if(sender.equals(m.getReceiver().getUsername()) && receiver.equals(m.getSender().getUsername()))
                loadReceiverMessageBubble(m);
        }
    }

    public void addLoginStage() {
        Stage stage = new Stage();
        VBox root = new VBox(5);
        var usernameField = new TextField();
        usernameField.setPromptText("Username");
        usernameField.setFocusTraversable(false);

        var passwordField = new PasswordField();
        passwordField.setPromptText("Password");
        passwordField.setFocusTraversable(false);

        var successLabel = new Label();
        successLabel.setStyle("-fx-text-fill: black; -fx-font-size: 12;");
        var errorLabel = new Label();
        errorLabel.setStyle("-fx-text-fill: red; -fx-font-size: 12;");

        var loginButton = new Button("        Login        ");
        loginButton.setOnAction(e -> userLogin(usernameField, passwordField, successLabel, errorLabel));

        root.getChildren().addAll(usernameField, passwordField, loginButton,  successLabel, errorLabel);
        Scene scene = new Scene(root, 320, 150);
        stage.setScene(scene);
        stage.show();
    }

    public void userLogin(TextField usernameField, TextField passwordField,
                          Label successLabel, Label errorLabel) {
        try{
            successLabel.setText("");
            errorLabel.setText("");
            var username = usernameField.getText();
            var password = passwordField.getText();
            service.userLogin(username, password);

            btnLogout.setDisable(false);
            currentUserLabel.setText("Current user: " + username);
            currentUser = username;
            successLabel.setText("Login Successful");
            loadChatComboBox(currentUser);
            setupFriendRequestButtons(true);
            stage.setTitle("Duck Chat - " + currentUser);
        } catch(UserNotFoundException | ValidatorException ex) {
            errorLabel.setText(ex.getMessage());
        }
    }

    public void userLogout() {
        try {
            service.userLogout(currentUser);

            currentUserLabel.setText("Current user: Guest");
            currentUser = null;
            btnLogout.setDisable(true);
            loadChatComboBox(currentUser);
            setupFriendRequestButtons(false);
            stage.setTitle("Duck Chat - Guest");
        } catch(UserNotFoundException | ValidatorException ex) {
            System.out.println(ex.getMessage());
        }
    }

    public void setupFriendRequestButtons(boolean logged) {
        btnNotifications.setVisible(logged);
        btnNotifications.setManaged(logged);
        btnAddFriend.setVisible(logged);
        btnAddFriend.setManaged(logged);

        if(logged) {
            // incarc numarul de notificari pentru fiecare user
            service.notifyNotifications(currentUser);
        }
    }

}

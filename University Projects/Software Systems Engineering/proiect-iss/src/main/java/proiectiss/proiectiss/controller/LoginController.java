package proiectiss.proiectiss.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import proiectiss.proiectiss.TaskManagerApp;
import proiectiss.proiectiss.domain.User;
import proiectiss.proiectiss.repository.TaskDbRepo;
import proiectiss.proiectiss.repository.TaskRepo;
import proiectiss.proiectiss.repository.UserDbRepo;
import proiectiss.proiectiss.repository.UserRepo;
import proiectiss.proiectiss.service.TaskService;

import java.io.IOException;

public class LoginController {

    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private Label errorLabel;

    private UserDbRepo userRepo;

    public LoginController(UserDbRepo userRepo) {
        this.userRepo = userRepo;
    }

    @FXML
    protected void onLoginClick() {
        String username = usernameField.getText();
        String password = passwordField.getText();

        User user = userRepo.findBy(username, password);

        if (user != null) {
            System.out.println("Login reusit pentru: " + user.getUsername());
            openMainWindow(user);
        } else {
            errorLabel.setText("Utilizator sau parola incorecta!");
        }
    }

    private void openMainWindow(User user) {
        try {
            TaskDbRepo taskRepo = new TaskDbRepo();
            TaskService taskService = new TaskService(taskRepo);
            MainController mainController = new MainController(taskService, user);

            FXMLLoader loader = new FXMLLoader(TaskManagerApp.class.getResource("main-view.fxml"));
            loader.setController(mainController);

            Stage stage = (Stage) usernameField.getScene().getWindow();
            stage.setScene(new Scene(loader.load()));
            stage.setTitle("Task Manager - " + user.getUsername());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

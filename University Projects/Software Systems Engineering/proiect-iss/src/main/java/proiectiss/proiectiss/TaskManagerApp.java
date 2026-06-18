package proiectiss.proiectiss;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import proiectiss.proiectiss.controller.LoginController;
import proiectiss.proiectiss.domain.User;
import proiectiss.proiectiss.repository.UserDbRepo;
import proiectiss.proiectiss.repository.UserRepo;

import java.io.IOException;

public class TaskManagerApp extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        UserDbRepo userRepo = new UserDbRepo();

        LoginController loginController = new LoginController(userRepo);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("login.fxml"));
        loader.setController(loginController);

        Scene scene = new Scene(loader.load());
        stage.setTitle("Task Manager - Login");
        stage.setScene(scene);
        stage.show();
    }
}

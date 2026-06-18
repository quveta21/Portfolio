package proiectiss.proiectiss.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import proiectiss.proiectiss.TaskManagerApp;
import proiectiss.proiectiss.domain.Task;
import proiectiss.proiectiss.domain.User;
import proiectiss.proiectiss.service.TaskService;

import java.util.List;
import java.util.stream.Collectors;

public class MainController {

    @FXML private Label welcomeLabel;
    @FXML private TableView<Task> taskTable;
    @FXML private TableColumn<Task, String> colTitle;
    @FXML private TableColumn<Task, String> colDesc;
    @FXML private TableColumn<Task, String> colPriority;
    @FXML private TableColumn<Task, String> colTime;
    @FXML private TextField searchField;
    @FXML private ComboBox<String> filterPriorityCombo;

    private TaskService taskService;
    private User currentUser;
    private ObservableList<Task> taskModel = FXCollections.observableArrayList();

    public MainController(TaskService taskService, User user) {
        this.taskService = taskService;
        this.currentUser = user;
    }

    @FXML
    public void initialize() {
        welcomeLabel.setText("Salut, " + currentUser.getUsername() + "!");

        colTitle.setCellValueFactory(new PropertyValueFactory<>("title"));
        colDesc.setCellValueFactory(new PropertyValueFactory<>("description"));
        colPriority.setCellValueFactory(new PropertyValueFactory<>("priority"));
        colTime.setCellValueFactory(new PropertyValueFactory<>("timeLabel"));

        filterPriorityCombo.getItems().addAll("Toate", "High", "Medium", "Low");

        refreshTaskList();
    }

    public void refreshTaskList() {
        List<Task> tasks = taskService.getTasksForUser(currentUser);
        taskModel.setAll(tasks);
        taskTable.setItems(taskModel);
    }

    @FXML
    private void onSearch() {
        String query = searchField.getText().toLowerCase();
        List<Task> filtered = taskService.getTasksForUser(currentUser).stream()
                .filter(t -> t.getTitle().toLowerCase().contains(query))
                .collect(Collectors.toList());
        taskModel.setAll(filtered);
    }

    @FXML
    private void onFilter() {
        String selected = filterPriorityCombo.getValue();
        if (selected == null || selected.equals("Toate")) {
            refreshTaskList();
            return;
        }
        List<Task> filtered = taskService.getTasksForUser(currentUser).stream()
                .filter(t -> t.getPriority().equals(selected.toUpperCase()))
                .collect(Collectors.toList());
        taskModel.setAll(filtered);
    }

    private void deschideFormular(Task taskToEdit, String titluFereastra) {
        try {
            TaskFormController formController = new TaskFormController(taskService, currentUser, this::refreshTaskList, taskToEdit);
            FXMLLoader loader = new FXMLLoader(TaskManagerApp.class.getResource("task-form.fxml"));
            loader.setController(formController);

            Stage dialogStage = new Stage();
            dialogStage.setTitle(titluFereastra);
            dialogStage.setScene(new Scene(loader.load()));
            dialogStage.showAndWait();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void arataEroare(String titlu, String mesaj) {
        Alert alert = new Alert(Alert.AlertType.WARNING, mesaj, ButtonType.OK);
        alert.setTitle(titlu);
        alert.showAndWait();
    }

    @FXML
    private void onAddClick() {
        deschideFormular(null, "Adauga Task"); // Trimitem null pentru taskToEdit
    }

    @FXML
    private void onEditClick() {
        Task selected = taskTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            deschideFormular(selected, "Editeaza Task"); // Trimitem task-ul selectat
        } else {
            arataEroare("Eroare", "Te rog selecteaza un task din lista pentru a-l edita.");
        }
    }

    @FXML
    private void onDeleteClick() {
        Task selected = taskTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            // UC-3: Sistemul cere confirmare
            Alert alert = new Alert(Alert.AlertType.CONFIRMATION, "Esti sigur ca vrei sa stergi acest task?", ButtonType.YES, ButtonType.NO);
            alert.setTitle("Confirmare Stergere");
            alert.showAndWait();

            if (alert.getResult() == ButtonType.YES) {
                taskService.deleteTask(selected.getID());
                refreshTaskList();
            }
        } else {
            arataEroare("Eroare", "Te rog selecteaza un task din lista pentru a-l sterge.");
        }
    }

    @FXML
    private void onMarkDoneClick() {
        Task selected = taskTable.getSelectionModel().getSelectedItem();
        if (selected != null) {
            // UC-4: Logica de finalizare (exemplu: stergere sau mutare in alta lista)
            System.out.println("Task finalizat: " + selected.getTitle());
        }
    }
}

package proiectiss.proiectiss.controller;

import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import proiectiss.proiectiss.domain.Task;
import proiectiss.proiectiss.domain.User;
import proiectiss.proiectiss.service.TaskService;

public class TaskFormController {

    @FXML private TextField titleField;
    @FXML private TextArea descField;
    @FXML private ComboBox<String> priorityCombo;
    @FXML private ComboBox<String> timeCombo;
    @FXML private Label errorLabel;

    private TaskService taskService;
    private User currentUser;
    private Runnable onTaskSavedCallback;
    private Task taskToEdit;

    // Injectam Service-ul si actiunea de refresh
    public TaskFormController(TaskService taskService, User currentUser, Runnable onTaskSavedCallback, Task taskToEdit) {
        this.taskService = taskService;
        this.currentUser = currentUser;
        this.onTaskSavedCallback = onTaskSavedCallback;
        this.taskToEdit = taskToEdit;
    }

    @FXML
    public void initialize() {
        priorityCombo.getItems().addAll("Low", "Medium", "High");
        timeCombo.getItems().addAll("Daily", "Weekly", "Monthly", "Yearly");

        // Verificam daca suntem pe modul EDITARE
        if (taskToEdit != null) {
            titleField.setText(taskToEdit.getTitle());
            descField.setText(taskToEdit.getDescription());
            priorityCombo.getSelectionModel().select(taskToEdit.getPriority());
            timeCombo.getSelectionModel().select(taskToEdit.getTimeLabel());
        } else {
            // Suntem pe modul ADAUGARE
            priorityCombo.getSelectionModel().select("Medium");
            timeCombo.getSelectionModel().select("Daily");
        }
    }

    @FXML
    private void onSaveClick() {
        String title = titleField.getText();
        String desc = descField.getText();
        String priority = priorityCombo.getValue().toUpperCase();
        String time = timeCombo.getValue().toUpperCase();

        try {
            if (taskToEdit == null) {
                // Mod ADAUGARE
                taskService.createTask(title, desc, priority, time, currentUser);
            } else {
                // Mod EDITARE (pasam si ID-ul task-ului existent)
                taskService.updateTask(taskToEdit.getID(), title, desc, priority, time, currentUser);
            }

            if (onTaskSavedCallback != null) {
                onTaskSavedCallback.run();
            }
            closeWindow();
        } catch (IllegalArgumentException e) {
            errorLabel.setText(e.getMessage());
        }
    }

    @FXML
    private void onCancelClick() {
        closeWindow();
    }

    private void closeWindow() {
        Stage stage = (Stage) titleField.getScene().getWindow();
        stage.close();
    }
}

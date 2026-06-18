package proiectiss.proiectiss.service;

import proiectiss.proiectiss.domain.Task;
import proiectiss.proiectiss.domain.TaskPriority;
import proiectiss.proiectiss.domain.TaskTimeLabel;
import proiectiss.proiectiss.domain.User;
import proiectiss.proiectiss.repository.TaskDbRepo;
import proiectiss.proiectiss.repository.TaskRepo;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class TaskService {

    private TaskDbRepo taskRepo;

    public TaskService(TaskDbRepo taskRepo) {
        this.taskRepo = taskRepo;
    }

    public void createTask(String title, String description, String priorityStr, String timeLabelStr, User user) {

        if (title == null || title.trim().isEmpty()) {
            throw new IllegalArgumentException("Titlul task-ului nu poate fi gol!");
        }

        TaskPriority priority = TaskPriority.valueOf(priorityStr);
        TaskTimeLabel timeLabel = TaskTimeLabel.valueOf(timeLabelStr);

        Task newTask = new Task(title, description, priority, timeLabel, user);

        taskRepo.save(newTask);
    }

    public void updateTask(String taskId, String title, String description, String priorityStr, String timeLabelStr, User user) {
        if (title == null || title.trim().isEmpty()) {
            throw new IllegalArgumentException("Titlul task-ului nu poate fi gol!");
        }

        TaskPriority priority = TaskPriority.valueOf(priorityStr);
        TaskTimeLabel timeLabel = TaskTimeLabel.valueOf(timeLabelStr);

        // Reconstruim entitatea cu datele noi, dar pastrand vechiul ID
        Task updatedTask = new Task(taskId, title, description, priority, timeLabel, user);
        taskRepo.update(updatedTask);
    }

    public void deleteTask(String taskId) {
        taskRepo.delete(taskId);
    }

    public List<Task> getTasksForUser(User user) {
        return taskRepo.findAllByUser(user);
    }
}

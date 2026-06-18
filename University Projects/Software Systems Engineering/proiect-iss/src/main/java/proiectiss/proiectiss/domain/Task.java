package proiectiss.proiectiss.domain;
import java.util.UUID;

public class Task extends Entity<String> {
    private String title;
    private String description;
    private TaskPriority priority;
    private TaskTimeLabel timeLabel;
    private User user;

    // Constructor pentru task deja existent
    public Task(String id, String title, String description, TaskPriority priority, TaskTimeLabel timeLabel, User user) {
        super(id);
        this.title = title;
        this.description = description;
        this.priority = priority;
        this.timeLabel = timeLabel;
        this.user = user;
    }

    // Constructor pentru task nou
    public Task(String title, String description, TaskPriority priority, TaskTimeLabel timeLabel, User user) {
        super(UUID.randomUUID().toString());
        this.title = title;
        this.description = description;
        this.priority = priority;
        this.timeLabel = timeLabel;
        this.user = user;
    }

    public String getTitle() { return title; }
    public String getDescription() { return description; }
    public String getPriority() { return priority != null ? priority.name() : ""; }
    public String getTimeLabel() { return timeLabel != null ? timeLabel.name() : ""; }
    public User getUser() { return user; }
}

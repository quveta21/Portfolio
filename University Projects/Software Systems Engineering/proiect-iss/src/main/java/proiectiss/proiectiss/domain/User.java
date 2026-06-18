package proiectiss.proiectiss.domain;
import java.util.UUID;

public class User extends Entity<String> {
    private String username;
    private String password;

    // Constructor pentru user deja existent
    public User(String id, String username, String password) {
        super(id);
        this.username = username;
        this.password = password;
    }

    // Constructor pentru user nou
    public User(String username, String password) {
        super(UUID.randomUUID().toString());
        this.username = username;
        this.password = password;
    }

    public String getUsername() { return username; }
    public String getPassword() { return password; }
}

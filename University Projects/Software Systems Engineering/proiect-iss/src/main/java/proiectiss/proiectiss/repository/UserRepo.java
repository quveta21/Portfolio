package proiectiss.proiectiss.repository;

import proiectiss.proiectiss.domain.User;

public class UserRepo extends MemoryRepository<String, User> {

    public User findBy(String username, String password) {
        for (User user : entities.values()) {
            if (user.getUsername().equals(username) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }
}

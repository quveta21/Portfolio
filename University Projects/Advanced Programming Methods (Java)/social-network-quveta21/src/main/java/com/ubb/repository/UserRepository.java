package com.ubb.repository;

import com.ubb.domain.User;

import java.util.ArrayList;
import java.util.List;

public class UserRepository extends InMemoryRepository<User> {
    //private List<User> users;

    public UserRepository() {
        super();
    }

    public User findByUsername(String username) {
        return getAll().stream()
                .filter(user -> user.getUsername().equals(username))
                .findFirst()
                .orElse(null);
    }
}

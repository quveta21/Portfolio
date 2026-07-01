package com.ubb.domain;

import org.mindrot.jbcrypt.BCrypt;

import java.util.Objects;

public abstract class User implements EventObserver {
    private long id;
    private String username;
    private String email;
    private String password;
    private boolean loggedIn;

    public User(long id, String username, String email, String password) {
        this.id = id;
        this.username = username;
        this.email = email;
        this.password = password;
    }

    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return id == user.id && Objects.equals(username, user.username);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, username);
    }

    @Override
    public String update(String message) {
        String notification = getUsername() + " a fost notificat: " + message;
        System.out.println(getUsername() + " a fost notificat: " + message);
        return notification;
    }

    public long getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public boolean login(String password) {
        loggedIn = BCrypt.checkpw(password, this.password);
        return loggedIn;
    }

    public boolean logout() {
        if (!loggedIn)
            return false;
        loggedIn = false;
        return true;
    }
}

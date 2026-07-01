package com.ubb.domain;

import java.util.Objects;

public abstract class User implements Observer {
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

    public boolean isLoggedIn() {
        return loggedIn;
    }

    public boolean login() {
        if  (username == null || password == null) {
            return false;
        }
        loggedIn = true;
        return true;
    }

    public boolean logout() {
        loggedIn = false;
        return true;
    }
}

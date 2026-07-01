package com.ubb.relations;

import com.ubb.domain.User;

import java.util.Objects;

public class Friendship {
    private final User friend1;
    private final User friend2;
    public Friendship(User friend1, User friend2) {
        this.friend1 = friend1;
        this.friend2 = friend2;
    }

    public User getFriend1() {
        return friend1;
    }

    public User getFriend2() {
        return friend2;
    }

    // asigura relatia bidirectionala
    @Override
    public boolean equals(Object o) {
        if (o == null || getClass() != o.getClass()) return false;
        Friendship that = (Friendship) o;
        return Objects.equals(friend1, that.friend1) && Objects.equals(friend2, that.friend2)
                ||  Objects.equals(friend1, that.friend2) && Objects.equals(friend2, that.friend1);
    }

    @Override
    public int hashCode() {
        return Objects.hash(friend1, friend2);
    }

    @Override
    public String toString() {
        return friend1.getUsername() + " si " +  friend2.getUsername() + " sunt prieteni";
    }
}

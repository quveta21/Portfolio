package com.ubb.exceptions;

public class UserNotFoundException extends RepositoryException {

    public UserNotFoundException(String username) {
        super("!! User-ul " + username + " nu a fost gasit !!");
    }
}

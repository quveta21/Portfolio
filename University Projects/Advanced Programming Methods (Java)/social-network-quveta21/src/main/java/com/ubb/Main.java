package com.ubb;

import com.ubb.repository.*;
import com.ubb.service.UserService;
import com.ubb.ui.Console;

import java.sql.SQLException;

public class Main {
    public static void main(String[] args) throws SQLException {
        var repo = new UserDBRepository();
        var friendshipRepo = new FriendshipDBRepository(repo);
        var cardRepo = new CardDBRepository(repo);
        var eventRepo = new EventDBRepository(repo);
        var service = new UserService(repo, friendshipRepo, cardRepo, eventRepo);
        var ui = new Console(service);
        ui.run();
    }
}
package com.ubb.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBConnection {
    private static final String url="jdbc:postgresql://localhost:5432/DuckSocialNetwork";
    private static final String user = "postgres";
    private static final String password = "1234";

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(url, user, password);
    }
}

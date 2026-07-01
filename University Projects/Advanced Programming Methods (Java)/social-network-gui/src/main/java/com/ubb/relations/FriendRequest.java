package com.ubb.relations;

public class FriendRequest {
    private String from_user;
    private String to_user;
    private String status;

    public FriendRequest(String from_user, String to_user, String status) {
        this.from_user = from_user;
        this.to_user = to_user;
        this.status = status;
    }

    public String getFromUser() {
        return from_user;
    }

    public String getToUser() {
        return to_user;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String newStatus) {status = newStatus;}
}

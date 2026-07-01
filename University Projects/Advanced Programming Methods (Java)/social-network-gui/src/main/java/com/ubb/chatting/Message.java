package com.ubb.chatting;

import com.ubb.domain.User;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class Message {
    private long id;
    private User from;
    private User to;
    private String message;
    private LocalDateTime date;
    private Message replyTo;

    public Message(long id, User from, User to, String message, LocalDateTime date) {
        this.id = id;
        this.from = from;
        this.to = to;
        this.message = message;
        //this.date = LocalDateTime.parse(LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm")));
        this.date = date;
        this.replyTo = null;
    }

    public long getId() {
        return id;
    }

    public User getSender() {
        return from;
    }

    public User getReceiver() {
        return to;
    }

    public String getMessage() {
        return message;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public Message getReplyTo() {
        return replyTo;
    }

    public void setReplyTo(Message replyTo) {
        this.replyTo = replyTo;
    }

    public void setId(long id) {this.id = id;}
}

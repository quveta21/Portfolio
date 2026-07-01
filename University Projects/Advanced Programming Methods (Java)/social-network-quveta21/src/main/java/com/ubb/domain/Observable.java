package com.ubb.domain;


import java.util.List;

public interface Observable {
    void subscribe(Observer o);
    void unsubscribe(Observer o);
    List<String> notifySubscribers(String message);
}
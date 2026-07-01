package com.ubb.domain;


import java.util.List;

public interface EventObservable {
    void subscribe(EventObserver o);
    void unsubscribe(EventObserver o);
    List<String> notifySubscribers(String message);
}
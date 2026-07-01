package com.ubb.domain;

import java.util.*;

public class Event implements Observable {
    int eventId;
    private final List<Observer> subscribers;

    public Event(int eventId) {
        this.eventId = eventId;
        subscribers = new ArrayList<>();
    }

    public int getEventId() {
        return eventId;
    }

    public void setEventId(int eventId) {
        this.eventId = eventId;
    }

    public List<Observer> getSubscribers() {
        return subscribers;
    }

    @Override
    public void subscribe(Observer o) {
        subscribers.add(o);
    }

    @Override
    public void unsubscribe(Observer o) {
        subscribers.remove(o);
    }

    @Override
    public List<String> notifySubscribers(String message) {
        List<String> allNotifications = new ArrayList<>();
        for (Observer o : subscribers) {
            allNotifications.add(o.update(message));
        }
        return allNotifications;
    }

    @Override
    public String toString() {
        return "Event " + eventId;
    }

}

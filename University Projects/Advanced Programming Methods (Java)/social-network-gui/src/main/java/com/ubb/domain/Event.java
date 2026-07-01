package com.ubb.domain;

import java.util.ArrayList;
import java.util.List;

public class Event implements EventObservable {
    int eventId;
    private final List<EventObserver> subscribers;

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

    public List<EventObserver> getSubscribers() {
        return subscribers;
    }

    @Override
    public void subscribe(EventObserver o) {
        subscribers.add(o);
    }

    @Override
    public void unsubscribe(EventObserver o) {
        subscribers.remove(o);
    }

    @Override
    public List<String> notifySubscribers(String message) {
        List<String> allNotifications = new ArrayList<>();
        for (EventObserver o : subscribers) {
            allNotifications.add(o.update(message));
        }
        return allNotifications;
    }

    @Override
    public String toString() {
        return "Event " + eventId;
    }

}

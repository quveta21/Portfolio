package com.ubb.repository;

import com.ubb.domain.Event;

public class EventRepository extends InMemoryRepository<Event> {
    public EventRepository() {
        super();
    }

    public Event findByEventId(int eventId) {
        return getAll().stream()
                .filter(event -> event.getEventId() == eventId)
                .findFirst()
                .orElse(null);
    }
}

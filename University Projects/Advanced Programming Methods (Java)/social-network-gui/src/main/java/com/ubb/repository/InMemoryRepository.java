package com.ubb.repository;

import java.util.ArrayList;
import java.util.List;

public abstract class InMemoryRepository<E> implements Repository<E> {
    private final List<E> entities;

    public InMemoryRepository() {
        this.entities = new ArrayList<>();
    }

    @Override
    public List<E> getAll() {
        return entities;
    }

    @Override
    public void add(E e) {
        entities.add(e);
    }

    @Override
    public void remove(E e) {
        entities.remove(e);
    }
}

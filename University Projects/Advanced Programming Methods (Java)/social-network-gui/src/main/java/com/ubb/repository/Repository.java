package com.ubb.repository;

import java.util.List;

public interface Repository<E> {
    List<E> getAll();
    void add(E e);
    void remove(E e);
}

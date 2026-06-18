package proiectiss.proiectiss.repository;

import proiectiss.proiectiss.domain.Entity;

public interface Repository<ID, E extends Entity<ID>> {
    void save(E entity);
    E findById(ID id);
    Iterable<E> findAll();
    void delete(ID id);
    void update(E entity);
}

package proiectiss.proiectiss.repository;

import proiectiss.proiectiss.domain.Entity;

import java.util.HashMap;
import java.util.Map;

public class MemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    protected Map<ID, E> entities = new HashMap<>();

    @Override
    public void save(E entity) {
        if (entity == null || entity.getID() == null) {
            throw new IllegalArgumentException("Entitatea sau ID-ul e null!");
        }
        entities.put(entity.getID(), entity);
    }

    @Override
    public E findById(ID id) {
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public void delete(ID id) {
        entities.remove(id);
    }

    @Override
    public void update(E entity) {
        if (entities.containsKey(entity.getID())) {
            entities.put(entity.getID(), entity);
        } else {
            throw new IllegalArgumentException("Entitatea nu exista in memorie.");
        }
    }
}

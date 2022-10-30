package repository.memory;

import domain.Entity;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    Map<ID, E> entities;

    public InMemoryRepository() {
        entities = new HashMap<>();
    }

    @Override
    public E find(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }
        if(entities.containsKey(id)) {
            return entities.get(id);
        }
        throw new InexistentEntityException(id + " does not exist!");
    }

    public void add(E entity) {
        if(entity == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }
        if(entities.containsKey(entity.getId())) {
            throw  new ExistentEntityException(entity.getId() + " already exists!");
        }
        entities.put(entity.getId(), entity);
    }

    public void remove(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }
        if(!entities.containsKey(id)) {
            throw  new InexistentEntityException(id + " does not exist!");
        }
        entities.remove(id);
    }

    public Iterable<E> getAll() {
        return entities.values();
    }

    public void clear() {
        entities.clear();
    }
}

package repository.memory;

import domain.Entity;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.util.HashMap;
import java.util.Map;

/**
 * Class for modelling a repository with persistence in memory
 * @param <ID> - generic type
 * @param <E> - generic type
 */
public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    Map<ID, E> entities;

    /**
     * Constructor for the repository
     */
    public InMemoryRepository() {
        entities = new HashMap<>();
    }

    /**
     * Method that returns the entity with the given ID
     * @param id ID - the id of the entity to be returned
     *           id must not be null
     * @return E
     * @exception IllegalArgumentException if id is null
     * @exception InexistentEntityException if there is no entity with the given id
     */
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

    /**
     * Method that adds an entity to the repo
     * @param entity E - the entity that needs to be added
     * @exception ExistentEntityException if the entity is already in the repo
     */
    public void add(E entity) {
        if(entity == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }
        if(entities.containsKey(entity.getId())) {
            throw  new ExistentEntityException(entity.getId() + " already exists!");
        }
        entities.put(entity.getId(), entity);
    }

    /**
     * Method that removes an entity from repo
     * @param id ID - the id of the entity that needs to be removes
     * @exception IllegalArgumentException if id is null
     * @exception InexistentEntityException if there is no entity with the given id
     */
    public void remove(ID id) {
        if(id == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }
        if(!entities.containsKey(id)) {
            throw  new InexistentEntityException(id + " does not exist!");
        }
        entities.remove(id);
    }

    /**
     * Method that modifies an entity in the repo
     * @param entity entity that will replace the one with the same id
     * @exception IllegalArgumentException if id is null
     * @throws InexistentEntityException if there is no entity that has the same id as the given entity
     */
    public void modify(E entity) {
        if(entity == null) {
            throw new IllegalArgumentException("Id must be not null!");
        }
        if(!entities.containsKey(entity.getId())) {
            throw  new InexistentEntityException(entity.getId() + " does not exist!");
        }
        entities.replace(entity.getId(), entity);
    }

    /**
     * Method that returns an iterable object of all entities from the repo
     * @return a iterable object with all entities from the repository
     */
    public Iterable<E> getAll() {
        return entities.values();
    }

    /**
     * Method that returns the map of the objects
     * @return a map object with all entities from the repository
     */
    public Map<ID, E> getMap() {
        return entities;
    }

    /**
     * Method that clears the repo
     */
    public void clear() {
        entities.clear();
    }
}

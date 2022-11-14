package repository;

import domain.Entity;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.util.Map;

/**
 * CRUD operations repository interface
 * @param <ID> - type E must have an attribute of type ID
 * @param <E> -  type of entities saved in repository
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Returns the entity that has the given id
     * @param id ID - the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     * @throws IllegalArgumentException if the id is null.
     * @throws InexistentEntityException if there is no entity with the given id
     */
    E find(ID id) throws IllegalArgumentException;

    /**
     * Returns all entities in the repository
     * @return - an iterable object that contains all entities
     */
    Iterable<E> getAll();

    /**
     * Method that returns the map of the objects
     * @return a map object with all entities from the repository
     */
    public Map<ID, E> getMap();

    /**
     * Adds an entity in the repo
     * @param entity E - the entity that needs to be added
     * @throws ExistentEntityException if there is already an entity that has the same id with the give one
     */
    void add(E entity);

    /**
     * Adds an entity in the repo
     * @param id ID - the id of the entity that needs to be removes
     * @throws InexistentEntityException if there is no entity that has the given id
     */
    void remove(ID id);

    /**
     * Method that modifies an entity in the repo
     * @param entity entity that will replace the one with the same id
     * @throws InexistentEntityException if there is no entity that has the same id as the given entity
     */
    void modify(E entity);

    /**
     * Clears the repository's data
     */
    void clear();
}

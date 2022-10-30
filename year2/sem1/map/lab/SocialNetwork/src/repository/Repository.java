package repository;

import domain.Entity;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

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
    E find(ID id) throws IllegalArgumentException, InexistentEntityException;

    /**
     * Returns all entities
     * @return Iterable<E>
     */
    Iterable<E> getAll();

    /**
     * Adds an entity in the repo
     * @param entity E - the entity that needs to be added
     * @throws ExistentEntityException if there is already an entity that has the same id with the give one
     */
    void add(E entity) throws ExistentEntityException;

    /**
     * Adds an entity in the repo
     * @param id ID - the id of the entity that needs to be removes
     * @throws ExistentEntityException if there is no entity that has the given id
     */
    void remove(ID id) throws InexistentEntityException;

    /**
     * Clears the repository's data
     */
    void clear();
}

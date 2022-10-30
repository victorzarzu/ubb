package repository;

import domain.Entity;

/**
 * CRUD operations repository interface
 * @param <ID> - type E must have an attribute of type ID
 * @param <E> -  type of entities saved in repository
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     *
     * @param id ID - the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     * @throws IllegalArgumentException if the id is null.
     */
    E find(ID id) throws IllegalArgumentException;

    /**
     * Returns all entities
     * @return Iterable<E>
     */
    Iterable<E> getAll();

    void add(E entity);
}

package ToySocialNetwork.repository;

import ToySocialNetwork.exceptions.repository.ExistentEntityException;
import ToySocialNetwork.exceptions.repository.InexistentEntityException;

/**
 * Interface for a repository of objects
 * @param <E> social network entity
 */
public interface Repository<E> {
    /**
     * Method that adds an entity in the repository
     * @param entity E
     * @throws ExistentEntityException if the entity already exists in the repository
     */
    public void add(E entity) throws ExistentEntityException;

    /**
     * Method that removes an entity in the repository
     * @param entity E
     * @throws InexistentEntityException if the entity does not exist in the repository
     */
    public void remove(E entity) throws InexistentEntityException;

    /**
     * Method that removes all entities from the repository
     */
    public void clear();
}

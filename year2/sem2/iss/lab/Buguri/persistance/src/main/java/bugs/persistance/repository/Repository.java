package bugs.persistance.repository;

import bugs.model.Identifiable;
import bugs.persistance.repository.exceptions.RepositoryException;

public interface Repository<ID, E extends Identifiable<ID>> {

    /**
     * Method to find an entity in the repository by id.
     * @param id the id of the entity
     * @return the entity with the given id
     * @throws RepositoryException if the entity with the given id does not exist
     */
    E findById(ID id);

    /**
     * Method to get all entities from the repository.
     * @return a list of all entities
     */
    Iterable<E> findAll();

    /**
     * Method to add an entity to the repository.
     * @param entity the entity to be added
     * @return a list of all entities
     * @throws RepositoryException if the entity already exists
     */
    void add(E entity);

    /**
     * Method to remove an entity from the repository.
     * @param entity the entity to be removed
     * @throws RepositoryException if the entity does not exist
     */
    void remove(E entity);

    /**
     * Method to get all entities from the repository.
     * @return a list of all entities
     * @throws RepositoryException if the entity does not exist
     */
    void modify(E entity);
}

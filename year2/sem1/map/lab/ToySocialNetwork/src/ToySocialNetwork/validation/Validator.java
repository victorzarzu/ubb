package ToySocialNetwork.validation;

import ToySocialNetwork.exceptions.validation.ValidationException;

/**
 * Interface for validators in the social media app
 * @param <E> Social media entity
 */
public interface Validator<E> {
    /**
     * Method that validates the given entity
     * @param entity E
     * @throws ValidationException with the according messages if the entity is not a valid one
     */
    void validate(E entity) throws ValidationException;
}

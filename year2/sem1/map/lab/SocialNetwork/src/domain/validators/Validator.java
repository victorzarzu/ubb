package domain.validators;

/**
 * Interface for a generic validator
 * @param <E>
 */
public interface Validator<E> {
    void validate(E entity) throws ValidationException;
}

package bugs.utils.validators;

public interface Validator<E> {
    public void validate(E entity);
}
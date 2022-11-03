package domain.validators;

/**
 * Exception to be thrown when it exists a validation problem with the entities of the domain
 */
public class ValidationException extends RuntimeException {
    public ValidationException() {
    }

    public ValidationException(String message) {
        super(message);
    }

    public ValidationException(String message, Throwable cause) {
        super(message, cause);
    }

    public ValidationException(Throwable cause) {
        super(cause);
    }

    public ValidationException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}

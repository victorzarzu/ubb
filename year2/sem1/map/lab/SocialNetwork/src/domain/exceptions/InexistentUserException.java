package domain.exceptions;

import repository.exceptions.ExistentEntityException;

public class InexistentUserException extends ExistentEntityException {
    public InexistentUserException() {
    }

    public InexistentUserException(String message) {
        super(message);
    }

    public InexistentUserException(String message, Throwable cause) {
        super(message, cause);
    }

    public InexistentUserException(Throwable cause) {
        super(cause);
    }

    public InexistentUserException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}

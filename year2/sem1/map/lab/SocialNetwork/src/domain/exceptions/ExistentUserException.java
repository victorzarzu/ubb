package domain.exceptions;

import repository.exceptions.ExistentEntityException;

public class ExistentUserException extends ExistentEntityException {
    public ExistentUserException() {
    }

    public ExistentUserException(String message) {
        super(message);
    }

    public ExistentUserException(String message, Throwable cause) {
        super(message, cause);
    }

    public ExistentUserException(Throwable cause) {
        super(cause);
    }

    public ExistentUserException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}

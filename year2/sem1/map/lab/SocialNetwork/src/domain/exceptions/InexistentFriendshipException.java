package domain.exceptions;

import repository.exceptions.ExistentEntityException;

public class InexistentFriendshipException extends ExistentEntityException {
    public InexistentFriendshipException() {
    }

    public InexistentFriendshipException(String message) {
        super(message);
    }

    public InexistentFriendshipException(String message, Throwable cause) {
        super(message, cause);
    }

    public InexistentFriendshipException(Throwable cause) {
        super(cause);
    }

    public InexistentFriendshipException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}

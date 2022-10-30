package domain.exceptions;

import repository.exceptions.ExistentEntityException;

public class ExistentFriendshipException extends ExistentEntityException {
    public ExistentFriendshipException() {
    }

    public ExistentFriendshipException(String message) {
        super(message);
    }

    public ExistentFriendshipException(String message, Throwable cause) {
        super(message, cause);
    }

    public ExistentFriendshipException(Throwable cause) {
        super(cause);
    }

    public ExistentFriendshipException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}

package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class ExistentFriendshipException extends ExistentEntityException {
    public ExistentFriendshipException(String errorMessage) {
        super(errorMessage);
    }
}

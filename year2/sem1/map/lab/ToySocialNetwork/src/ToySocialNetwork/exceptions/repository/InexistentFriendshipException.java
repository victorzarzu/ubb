package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class InexistentFriendshipException extends InexistentEntityException {
    public InexistentFriendshipException(String errorMessage) {
        super(errorMessage);
    }
}

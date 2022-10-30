package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class ExistingFriendshipException extends MultiMessageException {
    public ExistingFriendshipException(List<String> errorMessages) {
        super(errorMessages);
    }
}

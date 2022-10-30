package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class ExistentUserException extends ExistentEntityException {
    public ExistentUserException(String errorMessage) {
        super(errorMessage);
    }
}

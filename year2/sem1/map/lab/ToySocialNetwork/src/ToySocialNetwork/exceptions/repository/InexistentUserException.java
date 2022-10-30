package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class InexistentUserException extends InexistentEntityException {
    public InexistentUserException(String errorMessage) {
        super(errorMessage);
    }
}

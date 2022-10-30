package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class InexistentEntityException extends Exception {
    public InexistentEntityException(String errorMessage) {
        super(errorMessage);
    }
}

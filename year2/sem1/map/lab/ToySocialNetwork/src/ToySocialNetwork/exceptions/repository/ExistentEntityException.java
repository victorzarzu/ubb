package ToySocialNetwork.exceptions.repository;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class ExistentEntityException extends Exception {
    public ExistentEntityException(String errorMessage) {
        super(errorMessage);
    }
}

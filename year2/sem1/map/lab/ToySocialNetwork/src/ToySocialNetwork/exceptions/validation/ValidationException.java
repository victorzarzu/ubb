package ToySocialNetwork.exceptions.validation;

import ToySocialNetwork.exceptions.MultiMessageException;

import java.util.List;

public class ValidationException extends MultiMessageException {
    public ValidationException(List<String> errorMessages) {
        super(errorMessages);
    }
}
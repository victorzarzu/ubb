package ToySocialNetwork.exceptions.domain;

import ToySocialNetwork.exceptions.validation.*;

import java.util.List;

public class UserValidationException extends ValidationException {
    public UserValidationException(List<String> errorMessages) {
        super(errorMessages);
    }
}

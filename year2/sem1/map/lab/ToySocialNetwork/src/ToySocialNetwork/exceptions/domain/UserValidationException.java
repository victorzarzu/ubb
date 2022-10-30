package ToySocialNetwork.exceptions;

import java.util.List;

public class UserValidationException extends MultiMessageException {
    public UserValidationException(List<String> errorMessages) {
        super(errorMessages);
    }
}

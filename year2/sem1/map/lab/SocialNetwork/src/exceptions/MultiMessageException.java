package exceptions;

import java.util.List;

public class MultiMessageException extends Exception {
    private List<String> errorMessages;

    public MultiMessageException(List<String> messages) {
        this.errorMessages = messages;
    }

    @Override
    public String getMessage() {
        String errorMessage = "";
        for(String message : errorMessages) {
            errorMessage += message + "\n";
        }
        return errorMessage;
    }
}

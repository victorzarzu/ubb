package bugs.utils.validators;

import bugs.model.Bug;

import java.time.LocalDateTime;

public class BugValidator implements Validator<Bug> {
    @Override
    public void validate(Bug bug) {
        String errorMessages = "";
        if(bug.getName() == "") {
            errorMessages += "Invalid name!\n";
        }
        if(bug.getDescription() == "") {
            errorMessages += "Invalid description!\n";
        }
        if(bug.getStatus() == null) {
            errorMessages += "Invalid status!\n";
        }
        if(bug.getDate() == null || bug.getDate().isAfter(LocalDateTime.now())) {
            errorMessages += "Invalid date!\n";
        }
        if(bug.getPriority() == null) {
            errorMessages += "Invalid priority!\n";
        }

        if(errorMessages.length() > 0) {
            throw new ValidationException(errorMessages);
        }
    }
}

package bugs.utils.validators;

import bugs.model.Comment;

public class CommentValidator implements Validator<Comment> {

    @Override
    public void validate(Comment entity) {
        String errorMessages = "";
        if(entity.getText() == "") {
            errorMessages += "Invalid text!\n";
        }
        if(entity.getDate() == null) {
            errorMessages += "Invalid date!\n";
        }
        if(entity.getEmployee() == null) {
            errorMessages += "Invalid employee!\n";
        }

        if(errorMessages.length() > 0) {
            throw new ValidationException(errorMessages);
        }
    }
}

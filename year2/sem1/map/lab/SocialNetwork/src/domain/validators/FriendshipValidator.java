package domain.validators;

import domain.Friendship;

import java.time.LocalDateTime;
public class FriendshipValidator implements Validator<Friendship> {

    /**
     * Method that validates a friendship
     * @param friendship Friendship - the friendship to be validated
     * @throws ValidationException with the errors if the friendship is not valid
     */
    public void validate(Friendship friendship) {
        String errorMessage = "";
        if(friendship.getId().size() == 1) {
            errorMessage += friendship.getFirstUsername() + " cannot be friend to itself!\n";
        }
        if(friendship.getFriendshipDate().isAfter(LocalDateTime.now().plusSeconds(5))) {
            errorMessage += "Friendship date cannot be in the future!";
        }
        if(errorMessage.length() > 0) {
            throw new ValidationException(errorMessage);
        }
    }
}

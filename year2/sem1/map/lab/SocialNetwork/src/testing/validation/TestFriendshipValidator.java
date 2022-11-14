package testing.validation;

import domain.Friendship;
import domain.User;
import domain.validators.FriendshipValidator;
import domain.validators.UserValidator;
import domain.validators.ValidationException;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class TestFriendshipValidator {

    @Test
    @DisplayName("Testing friendship validator on good user")
    public void testFriendshipValidatorOnGoodUser() throws ValidationException {
        FriendshipValidator validator = new FriendshipValidator();
        Friendship friendship = new Friendship("eu", "tu");
        validator.validate(friendship);
    }

    @Test
    @DisplayName("Testing friendship validator on bad user")
    public void testFriendshipValidatorOnBadUser() {
        FriendshipValidator validator = new FriendshipValidator();
        Friendship friendship = new Friendship("eu", "eu");

        try {
            validator.validate(friendship);
        } catch (ValidationException exception) {
            assertEquals(exception.getMessage(), "eu cannot be friend to itself!");
        }
    }
}

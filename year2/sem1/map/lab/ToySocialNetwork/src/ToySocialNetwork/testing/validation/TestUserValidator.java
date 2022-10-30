package ToySocialNetwork.testing.validation;

import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.domain.UserValidationException;
import ToySocialNetwork.validation.domain.UserValidator;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class TestUserValidator {

    @Test
    @DisplayName("Testing user validator on good user")
    public void testUserValidatorOnGoodUser() throws UserValidationException {
        UserValidator validator = new UserValidator();
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        validator.validate(user);
    }

    @Test
    @DisplayName("Testing user validator on bad user")
    public void testUserValidatorOnBadUser() {
        UserValidator validator = new UserValidator();
        User user = new User("vi", "ceva", "victorzarzugmail.com", "Vic4tor", "Zarzu", "Man");
        try {
            validator.validate(user);
        } catch (UserValidationException exception) {
            assertEquals(exception.getMessage(), "Too short username! Minimum 4 characters!\nInvalid email!\nInvalid first name!\n");
        }
        user.setPassword("");
        user.setGender("ww");
        try {
            validator.validate(user);
            assertTrue(false);
        } catch (UserValidationException exception) {
            assertEquals(exception.getMessage(), "Too short username! Minimum 4 characters!\nInvalid password!\nInvalid email!\nInvalid first name!\nInvalid gender!\n");
        }
    }
}

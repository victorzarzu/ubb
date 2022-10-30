package ToySocialNetwork.validation.domain;

import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.domain.UserValidationException;
import ToySocialNetwork.validation.Validator;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * Validator for users
 */
public class UserValidator implements Validator<User> {

    /**
     * Method that verifies if the given string is a name
     * @param name String
     * @return true if the string is a name and false otherwise
     */
    private boolean isNameValid(String name) {
        if(!Character.isUpperCase(name.charAt(0))) {
            return false;
        }
        for(int i = 1;i < name.length();++i) {
            if(Character.isUpperCase(name.charAt(i)) || !Character.isAlphabetic(name.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    /**
     * Method that verifies if a string is an username
     * @param username String
     * @return List<String> that contains the messages with validation errors for the given username
     */
    private List<String> validateUsername(String username) {
        List<String> errorMessages = new LinkedList<>();
        if(username == "") {
            errorMessages.add("Invalid username!");
        }
        else if(username.length() <= 3) {
            errorMessages.add("Too short username! Minimum 4 characters!");
        }
        return errorMessages;
    }

    /**
     * Method that verifies if a string is a password
     * @param password String
     * @return List<String> that contains the messages with validation errors for the given password
     */
    private List<String> validatePassword(String password) {
        List<String> errorMessages = new LinkedList<>();
        if(password == "") {
            errorMessages.add("Invalid password!");
        }
        else if(password.length() <= 3) {
            errorMessages.add("Too short password! Minimum 4 characters!");
        }
        return errorMessages;
    }

    /**
     * Method that verifies if a given string is an email
     * @param email String
     * @return true if the string is an email and false otherwise
     */
    private boolean isEmailValid(String email) {
        int index;
        for(index = 0;index < email.length() && email.charAt(index) != '@';++index);
        if(index >= email.length() - 1) {
            return false;
        }
        for(;index < email.length() && email.charAt(index) != '.';++index);
        if(index >= email.length() - 1) {
            return false;
        }
        return true;
    }

    /**
     * Method that verifies if a given string is a gender
     * @param gender String
     * @return true if the string is a gender and false otherwise
     */
    private boolean isGenderValid(String gender) {
        List<String> genders = Arrays.asList("Man", "Woman");
        return genders.contains(gender);
    }

    /**
     * Method that validates an user
     * @param user User
     * @throws UserValidationException only if the user is not valid and contains all the bad things about the user
     */
    public void validate(User user) throws UserValidationException {
        List<String> errorMessages = new LinkedList<String>();

        errorMessages.addAll(this.validateUsername(user.getUsername()));
        errorMessages.addAll(this.validatePassword(user.getPassword()));
        if(!isEmailValid(user.getEmail())) {
            errorMessages.add("Invalid email!");
        }
        if(!isNameValid(user.getFirstName())) {
            errorMessages.add("Invalid first name!");
        }
        if(!isNameValid(user.getLastName())) {
            errorMessages.add("Invalid last name!");
        }
        if(!isGenderValid(user.getGender())) {
            errorMessages.add("Invalid gender!");
        }

        if(errorMessages.size() > 0) {
            throw new UserValidationException(errorMessages);
        }
    }
}

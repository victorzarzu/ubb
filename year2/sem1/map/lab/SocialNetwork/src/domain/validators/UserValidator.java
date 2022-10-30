package domain.validators;

import domain.User;
import domain.User;
import domain.validators.Validator;

import java.awt.*;
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
     * @throws ValidationException only if the user is not valid and contains all the bad things about the user
     */
    public void validate(User user) throws ValidationException {
        String errorMessages = "";

        Iterable<String> usernameErrors = this.validateUsername(user.getId());
        for(String message : usernameErrors) {
            errorMessages += message + "\n";
        }

        Iterable<String> passwordErrors = this.validatePassword(user.getPassword());
        for(String message : passwordErrors) {
            errorMessages += message + "\n";
        }
        if(!isEmailValid(user.getEmail())) {
            errorMessages += "Invalid email!\n";
        }
        if(!isNameValid(user.getFirstName())) {
            errorMessages += "Invalid first name!\n";
        }
        if(!isNameValid(user.getLastName())) {
            errorMessages += "Invalid last name!\n";
        }
        if(!isGenderValid(user.getGender())) {
            errorMessages += "Invalid gender!\n";
        }

        if(errorMessages.length() > 0) {
            throw new ValidationException(errorMessages);
        }
    }
}
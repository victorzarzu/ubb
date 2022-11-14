package domain;


import java.util.Objects;
import java.util.UUID;

/**
 * Class the models an user in a social network
 */
public class User extends Entity<String> {

    private static final UUID serialVersionUID = UUID.randomUUID();
    private String password;
    private String email;
    private String firstName;
    private String lastName;
    private String gender;


    /**
     * Constructor for creating an user
     * @param id String
     * @param password String
     * @param email String
     * @param firstName String
     * @param lastName String
     * @param gender String
     */
    public User(String id, String password, String email, String firstName, String lastName, String gender) {
        super(id);
        this.password = password;
        this.email = email;
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
    }

    /**
     * Method that returns the password of a user
     * @return String
     */
    public String getPassword() {
        return password;
    }

    /**
     * Method that returns the email of a user
     * @return String
     */
    public String getEmail() {
        return email;
    }

    /**
     * Function that returns the first name of a user
     * @return String
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Function that returns the last name of a user
     * @return String
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Function that returns the gender of a user
     * @return String
     */
    public String getGender() {
        return gender;
    }

    /**
     * Function that sets the password of a user
     * @param password String
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * Method that sets the email of a user
     * @param email String
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Method that sets the first name of a user
     * @param firstName String
     */
    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    /**
     * Method that sets the second name of a user
     * @param lastName String
     */
    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    /**
     * Method that sets the gender of a user
     * @param gender String
     */
    public void setGender(String gender) {
        this.gender = gender;
    }


    /**
     * Method that returns a printable form of the user
     * @return String
     */
    @Override
    public String toString() {
        return "Username: " + this.getId() + " | Email : " + this.email + " | First name: "
                + this.firstName + " | Last name: " + this.lastName + " | Gender: " + this.gender;
    }
}

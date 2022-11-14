package repository.file;

import domain.User;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.util.List;

public class UserFileRepository extends AbstractFileRepository<String, User> {

    /**
     * Contructor for creating a repository with persistence in file
     * @param filename - the path where the data is stored
     */
    public UserFileRepository(String filename) {
        super(filename);
    }

    /**
     * Method that converts a string into a user based on a list of String attributes
     * @param atributes the atributes of the returned entity
     * @return User - the converted user
     */
    @Override
    public User extractEntity(List<String> atributes) {
        User user = new User(atributes.get(0), atributes.get(1), atributes.get(2), atributes.get(3), atributes.get(4), atributes.get(5));
        return user;
    }

    /**
     * Method that converts a user to the storable form
     * @param user E - the entity to be converted to string
     * @return String - the conversion of the user into String
     */
    @Override
    protected String entityEntityToString(User user) {
        return user.getId() + ";" + user.getPassword() + ";"  + user.getEmail() + ";" + user.getFirstName() + ";" +
                user.getLastName() + ";" + user.getGender() + "\n";
    }
}

package ToySocialNetwork.repository;

import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;

import java.util.HashMap;
import java.util.Map;

public class UserRepository implements Repository<User> {

    Map<String, User> users;

    public UserRepository() {
        users = new HashMap<>();
    }

    /**
     * Method that adds a user to the repository
     * @param user User
     * @throws ExistentUserException if the user already exists
     */
    @Override
    public void add(User user) throws ExistentUserException {
        if(users.containsKey(user.getUsername())) {
            throw new ExistentUserException(user.getUsername() + " already exists!");
        }
        users.put(user.getUsername(), user);
    }

    @Override
    /**
     * Method that removes a user from the repository
     * @param user User
     * @throws InexistentUserException if the user does not exist
     */
    public void remove(User user) throws InexistentUserException {
        if(!users.containsKey(user.getUsername())) {
            throw new InexistentUserException(user.getUsername() + " does not exist!");
        }
        users.remove(user.getUsername());
    }

    @Override
    /**
     * Method that removes all users from the repository
     */
    public void clear() {
        users.clear();
    }

    /**
     * Method that returns the user with the given username
     * @param username String
     * @return User
     * @throws InexistentUserException if there is not user with the given username
     */
    public User findUser(String username) throws InexistentUserException {
        if(users.containsKey(username)) {
            return users.get(username);
        }
        throw new InexistentUserException(username + " does not exist!");
    }
}

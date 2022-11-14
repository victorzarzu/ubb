package repository.database;

import domain.User;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.sql.*;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class UserDbRepository implements Repository<String, User> {

    private String url;
    private String username;
    private String password;

    /**
     * Constructor for creating a user repository with persistence in database
     * @param url the url of the database
     * @param username the username for connecting to the database
     * @param password the password for connecting to the database
     */
    public UserDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * Method that extract a user from a ResultSet
     * @param resultSet the result set of the query
     * @return the extracted user
     * @throws SQLException if there is some error with extracting the date from result set
     */
    private User getUserFromResultSet(ResultSet resultSet) throws SQLException{
        String username = resultSet.getString("username");
        String password = resultSet.getString("password");
        String email = resultSet.getString("email");
        String firstName = resultSet.getString("first_name");
        String lastName = resultSet.getString("last_name");
        String gender = resultSet.getString("gender");

        return new User(username, password, email, firstName, lastName, gender);
    }

    /**
     * Method that verifies if a user is in the repo
     * @param username the username of the searched user
     * @return true if the user exists and false otherwise
     */
    private boolean exists(String username) {
        String sql = "SELECT * FROM Users WHERE username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();

            if(resultSet.next()) {
                return true;
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return false;
    }

    /**
     * Method that returns the searched user
     * @param username - the username of the user to be returned
     *           username must not be null
     * @return the searched username
     * @throws IllegalArgumentException if the username is null
     * @throws InexistentEntityException if there is no user with the given username
     */
    @Override
    public User find(String username) throws IllegalArgumentException, InexistentEntityException {
        if(username == null) {
            throw new IllegalArgumentException("Username must be not null!");
        }

        String sql = "SELECT * FROM Users WHERE username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, username);
            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next()) {
                throw new InexistentEntityException(username + " does not exist!");
            } else {
                return getUserFromResultSet(resultSet);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return null;
    }

    /**
     * Method that returns an iterable object with all the users
     * @return an iterable object with users
     */
    @Override
    public Iterable<User> getAll() {
        Set<User> users = new HashSet<>();
        String sql = "SELECT * FROM Users";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery()) {

            while(resultSet.next()) {
                User user = getUserFromResultSet(resultSet);
                users.add(user);
            }
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return users;
    }

    /**
     * Method that returns a map with the users and their usernames as keys
     * @return a map with usernames and users
     */
    @Override
    public Map<String, User> getMap() {
        Map<String, User> users = new HashMap<>();
        String sql = "SELECT * FROM Users";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery()) {

            while(resultSet.next()) {
                User user = getUserFromResultSet(resultSet);
                users.put(user.getId(), user);
            }
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return users;
    }

    /**
     * Method that adds a user to the repository
     * @param user User - the user to be added
     */
    @Override
    public void add(User user) {
        if(exists(user.getId())) {
            throw new ExistentEntityException(user.getId() + " already exists!");
        }
        String sql = "INSERT INTO Users VALUES(?, ?, ?, ?, ?, ?)";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)){
            statement.setString(1, user.getId());
            statement.setString(2, user.getPassword());
            statement.setString(3, user.getEmail());
            statement.setString(4, user.getFirstName());
            statement.setString(5, user.getLastName());
            statement.setString(6, user.getGender());

            statement.executeUpdate();
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    /**
     * Method that removes a user with the given username
     * @param username String - the username of the searched user
     * @throws InexistentEntityException if there is not user with the given username
     */
    @Override
    public void remove(String username) throws InexistentEntityException {
        if(!exists(username)) {
            throw new InexistentEntityException(username + " does not exist!");
        }
        String sql = "DELETE FROM Users WHERE username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)){
            statement.setString(1, username);

            statement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }


    /**
     * Method that modifies a user in the repository
     * @param user User - the new user data of the user with the same username of the given one
     * @throws InexistentEntityException if there is no user with the same username as the given one
     */
    @Override
    public void modify(User user) {
        if(!exists(user.getId())) {
            throw new InexistentEntityException(user.getId() + " does not exist!");
        }
        String sql = "UPDATE Users SET password = ?, email = ?, first_name = ?, last_name = ?, gender = ? WHERE username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)){
            statement.setString(6, user.getId());
            statement.setString(1, user.getPassword());
            statement.setString(2, user.getEmail());
            statement.setString(3, user.getFirstName());
            statement.setString(4, user.getLastName());
            statement.setString(5, user.getGender());

            statement.executeUpdate();
        }catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    /**
     * Method that clears the repository
     */
    @Override
    public void clear() {
        String sql = "DELETE FROM Users";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ) {
            statement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }
}

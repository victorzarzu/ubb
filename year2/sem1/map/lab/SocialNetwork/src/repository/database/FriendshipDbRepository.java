package repository.database;

import constants.DateTime;
import domain.Friendship;
import domain.exceptions.ExistentFriendshipException;
import domain.exceptions.InexistentFriendshipException;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.*;

import static constants.DateTime.DATATIME_FORMATTER;

public class FriendshipDbRepository implements Repository<Set<String>, Friendship> {
    private String url;
    private String username;
    private String password;

    /**
     * Constructor for creating a friendship repository with persistence in database
     * @param url the url of the database
     * @param username the username for connecting to the database
     * @param password the password for connecting to the database
     */
    public FriendshipDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    /**
     * Method that verifies if a friendship with the given usernames is in the repository
     * @param usernames Set<String> - the usernames of the friendship
     * @return true if the searched friendship exists and false otherwise
     */
    private boolean exists(Set<String> usernames) {
        List<String> usersList = new ArrayList<>(usernames);
        String firstUsername = usersList.get(0);
        String secondUsername = usersList.get(1);
        String sql = "SELECT * FROM Friendships WHERE first_username = ? AND second_username = ?";


        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, firstUsername);
            statement.setString(2, secondUsername);

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
     * Method that returns the friendship with the given usernames
     * @param usernames Set<String> - the usernames of the friendship
     * @return the searched friendship
     * @throws IllegalArgumentException if the usernames is null
     * @throws InexistentEntityException if there is no friendship with the given usernames
     */
    @Override
    public Friendship find(Set<String> usernames) throws IllegalArgumentException {
        if(usernames == null) {
            throw new IllegalArgumentException("Usernames must be not null!");
        }

        List<String> usersList = new ArrayList<>(usernames);
        String firstUsername = usersList.get(0);
        String secondUsername = usersList.get(1);
        String sql = "SELECT date FROM Friendships WHERE first_username = ? AND second_username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, firstUsername);
            statement.setString(2, secondUsername);
            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next()) {
                throw new InexistentEntityException("Friendship between " + firstUsername + " and " + secondUsername + " does not exist!");
            }
            LocalDateTime friendshipDate = resultSet.getTimestamp("date").toLocalDateTime();
            Friendship friendship = new Friendship(firstUsername, secondUsername, friendshipDate);

            return friendship;
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    /**
     * Method that returns an iterable object with all friendships
     * @return an iterable object with friendship
     */
    @Override
    public Iterable<Friendship> getAll() {
        Set<Friendship> friendshipsSet = new HashSet<>();
        String sql = "SELECT * FROM Friendships";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery()) {

            while(resultSet.next()) {
                String firstUsername = resultSet.getString("first_username");
                String secondUsername = resultSet.getString("second_username");
                LocalDateTime friendshipDate = resultSet.getTimestamp("date").toLocalDateTime();

                Friendship friendship = new Friendship(firstUsername, secondUsername, friendshipDate);
                friendshipsSet.add(friendship);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return friendshipsSet;
    }

    /**
     * Method that returns a map with the friendships and their usernames as keys
     * @return a mep with the usernames and friendships
     */
    @Override
    public Map<Set<String>, Friendship> getMap() {
        Map<Set<String>, Friendship> friendshipsMap = new HashMap<>();
        String sql = "SELECT * FROM Friendships";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery()) {

            while(resultSet.next()) {
                String firstUsername = resultSet.getString("first_username");
                String secondUsername = resultSet.getString("second_username");
                LocalDateTime friendshipDate = resultSet.getTimestamp("date").toLocalDateTime();

                Friendship friendship = new Friendship(firstUsername, secondUsername, friendshipDate);
                friendshipsMap.put(friendship.getId(), friendship);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return friendshipsMap;
    }

    /**
     * Method that adds a friendship to the repository
     * @param friendship Friendship - the friendship to be added
     * @throws ExistentFriendshipException if there is already a friendship between the users of the given frienship
     */
    @Override
    public void add(Friendship friendship) {
        if(exists(friendship.getId())) {
            throw new ExistentFriendshipException("Friendship between " + friendship.getFirstUsername() + " and " + friendship.getSecondUsername() + " already exists!");
        }

        String sql = "INSERT INTO friendships(first_username, second_username, date) VALUES(?, ?, ?)";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, friendship.getFirstUsername());
            statement.setString(2, friendship.getSecondUsername());
            statement.setTimestamp(3, Timestamp.valueOf(friendship.getFriendshipDate()));

            statement.executeUpdate();

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    /**
     * Method the removes the friendship with the given usernames
     * @param usernames Set<String> - the usernames of the friendship to be deleted
     * @throws InexistentFriendshipException - if there is not friendship with the given usernames
     */
    @Override
    public void remove(Set<String> usernames) {
        List<String> usersList = new ArrayList<>(usernames);
        String firstUsername = usersList.get(0);
        String secondUsername = usersList.get(1);

        if(!exists(usernames)) {
            throw new InexistentFriendshipException("Friendship between " + firstUsername + " and " + secondUsername + " does not exist!");
        }

        String sql = "DELETE FROM friendships WHERE first_username = ? AND second_username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setString(1, firstUsername);
            statement.setString(2, secondUsername);

            statement.executeUpdate();

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    /**
     * Method the modifies a friendship from the repository
     * @param friendship Friendship - the friendship with the usernames equal with the usernames of the friendship to be modified
     */
    @Override
    public void modify(Friendship friendship) {
        if(!exists(friendship.getId())) {
            throw new InexistentFriendshipException("Friendship between " + friendship.getFirstUsername() + " and " + friendship.getSecondUsername() + " does not exist!");
        }

        String sql = "UPDATE friendships SET date = ? WHERE first_username = ? AND second_username = ?";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setTimestamp(1, Timestamp.valueOf(friendship.getFriendshipDate()));
            statement.setString(2, friendship.getFirstUsername());
            statement.setString(3, friendship.getSecondUsername());

            statement.executeUpdate();

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    /**
     * Method that clears the repository
     */
    @Override
    public void clear() {
        String sql = "DELETE FROM friendships";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.executeUpdate();

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
    }

    /**
     * Method that deletes all the friendship of a user
     * @param username String - the username of the user of which friendship to be deleted
     */
    public void deleteUserFriendships(String username) {
        for(Friendship friendship : this.getAll()) {
            if(friendship.getId().contains(username)) {
                this.remove(friendship.getId());
            }
        }
    }
}

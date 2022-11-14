package domain;

import java.lang.reflect.Array;
import java.time.LocalDateTime;
import java.util.*;

public class Friendship extends Entity<Set<String>> {
    private static final UUID serialVersionUID = UUID.randomUUID();
    private LocalDateTime friendshipDate;

    /**
     * Method for constructing a friendship
     * @param username1 usersame of one user
     * @param username2 username of the second user
     */
    public Friendship(String username1, String username2) {
        super(new TreeSet<>(Arrays.asList(username1, username2)));
        this.friendshipDate = LocalDateTime.now();
    }

    /**
     * Method for constructing a friendship
     * @param username1 usersame of one user
     * @param username2 username of the second user
     * @param friendshipDate date of the friendship
     */
    public Friendship(String username1, String username2, LocalDateTime friendshipDate) {
        super(new TreeSet<>(Arrays.asList(username1, username2)));
        this.friendshipDate = friendshipDate;
    }

    /**
     * Method that returns the date of the friendship
     * @return the date from which the users are friends
     */
    public LocalDateTime getFriendshipDate() {
        return friendshipDate;
    }

    /**
     * Method that changes the date of the friendship
     * @param friendshipDate the new date of the friendship
     */
    public void setFriendshipDate(LocalDateTime friendshipDate) {
        this.friendshipDate = friendshipDate;
    }

    /**
     * Method that returns the first username of the friendship
     * @return String
     */
    public String getFirstUsername() {
        List<String> usersList = new ArrayList<>(this.getId());
        return usersList.get(0);
    }

    /**
     * Method that returns the first username of the friendship
     * @return String
     */
    public String getSecondUsername() {
        List<String> usersList = new ArrayList<>(this.getId());
        return usersList.get(1);
    }


    @Override
    public String toString() {
        List<String> usersList = new ArrayList<>(this.getId());
        return "Friendship between " + this.getFirstUsername() + " and " + this.getSecondUsername();
    }
}

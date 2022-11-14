package testing.repository;

import config.Config;
import domain.Friendship;
import domain.User;
import domain.exceptions.InexistentFriendshipException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.Repository;
import repository.database.FriendshipDbRepository;
import repository.database.UserDbRepository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;

import java.time.LocalDateTime;
import java.time.Month;
import java.util.Arrays;
import java.util.HashSet;

import static org.junit.jupiter.api.Assertions.*;

public class TestFriendshipDbRepository {

    private static FriendshipDbRepository repository = new FriendshipDbRepository(Config.getProperties().getProperty("databaseTestUrl"),
            Config.getProperties().getProperty("username"), Config.getProperties().getProperty("password"));
    private static Repository<String, User> userRepository = new UserDbRepository(Config.getProperties().getProperty("databaseTestUrl"),
            Config.getProperties().getProperty("username"), Config.getProperties().getProperty("password"));


    @BeforeEach
    public void init() {
        userRepository.clear();
        repository.clear();

        userRepository.add(new User("eu", "da", "da", "da", "da", "da"));
        userRepository.add(new User("tu", "da", "da", "da", "da", "da"));
        userRepository.add(new User("el", "da", "da", "da", "da", "da"));
        userRepository.add(new User("ea", "da", "da", "da", "da", "da"));
    }

    @Test
    @DisplayName("Test add user repository")
    public void testAdd() throws Exception {
        Friendship friendship = new Friendship("eu", "tu");

        repository.add(friendship);
        try{
            repository.add(friendship);
            fail();
        } catch (ExistentEntityException exception) {
            assertEquals(exception.getMessage(), "Friendship between eu and tu already exists!");
        }
    }

    @Test
    @DisplayName("Test remove user repository")
    public void testRemove() throws Exception {
        Friendship friendship = new Friendship("eu", "tu");
        repository.add(friendship);
        repository.remove(friendship.getId());

        try{
            repository.remove(friendship.getId());
            fail();
        } catch (InexistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "Friendship between eu and tu does not exist!");
        }
    }

    @Test
    @DisplayName("Test clear user repository")
    public void testClear() throws Exception {
        Friendship friendship1 = new Friendship("eu", "tu");
        Friendship friendship2 = new Friendship("el", "ea");

        repository.add(friendship1);
        repository.add(friendship2);

        repository.clear();

        try{
            repository.remove(friendship1.getId());
            fail();
        } catch (InexistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "Friendship between eu and tu does not exist!");
        }

        try{
            repository.remove(friendship2.getId());
            fail();
        } catch (InexistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "Friendship between ea and el does not exist!");
        }
    }

    @Test
    @DisplayName("Test find friendship by usernames repository")
    public void testFindFriendship() {
        Friendship friendship = new Friendship("eu", "tu");
        repository.add(friendship);

        Friendship foundUser = repository.find(new HashSet<>(Arrays.asList("eu", "tu")));
        assertEquals(foundUser.getFriendshipDate().getMinute(), LocalDateTime.now().getMinute());

        try{
            repository.find(new HashSet<>(Arrays.asList("el", "ea")));
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "Friendship between el and ea does not exist!");
        }
    }

    @Test
    @DisplayName("Test modify friendship repository")
    public void testModify() {
        Friendship friendship = new Friendship("eu", "tu");
        repository.add(friendship);

        Friendship friendshipNew = new Friendship("eu", "tu", LocalDateTime.of(2050, Month.APRIL, 29, 20, 15, 14));
        repository.modify(friendshipNew);
        Friendship friendshipFound = repository.find(new HashSet<>(Arrays.asList("eu", "tu")));
        assertEquals(friendshipFound.getFriendshipDate().getYear(), 2050);

        Friendship friendshipInexistent = new Friendship("el", "ea");

        try{
            repository.remove(friendshipInexistent.getId());
            fail();
        } catch (InexistentFriendshipException exception) {
            assertEquals(exception.getMessage(), "Friendship between ea and el does not exist!");
        }
    }

    @Test
    @DisplayName("Test delete user friendship repository")
    public void testDeleteUserFriendship() {
        Friendship friendship = new Friendship("eu", "tu");
        repository.add(friendship);
        repository.deleteUserFriendships("eu");

        assertEquals(repository.getMap().size(), 0);
    }
}

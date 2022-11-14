package testing.repository;

import domain.Friendship;
import domain.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.memory.InMemoryRepository;

import java.time.LocalDateTime;
import java.time.Month;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

public class TestFriendshipRepository {

    private static Repository<Set<String>, Friendship> repository = new InMemoryRepository<>();

    @BeforeEach
    public void init() {
        repository.clear();
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
            assertEquals(exception.getMessage(), "[eu, tu] already exists!");
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
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "[eu, tu] does not exist!");
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
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "[eu, tu] does not exist!");
        }

        try{
            repository.remove(friendship2.getId());
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "[ea, el] does not exist!");
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
            assertEquals(exception.getMessage(), "[el, ea] does not exist!");
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
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "[ea, el] does not exist!");
        }
    }
}

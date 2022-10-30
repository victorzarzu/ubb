package testing.repository;

import domain.User;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.Repository;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.memory.InMemoryRepository;

import static org.junit.jupiter.api.Assertions.*;

public class TestUserRepository {

    private static Repository<String, User> repository = new InMemoryRepository<>();

    @BeforeEach
    public void init() {
        repository.clear();
    }

    @Test
    @DisplayName("Test add user repository")
    public void testAdd() throws Exception {
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");

        repository.add(user);
        try{
            repository.add(user);
            fail();
        } catch (ExistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu already exists!");
        }
    }

    @Test
    @DisplayName("Test remove user repository")
    public void testRemove() throws Exception {
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        repository.add(user);
        repository.remove(user.getId());

        try{
            repository.remove(user.getId());
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }
    }

    @Test
    @DisplayName("Test clear user repository")
    public void testClear() throws Exception {
        User user1 = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        User user2 = new User("andrei.ol", "ceva", "andrei.ol@gmail.com", "Andrei", "Ol", "Man");

        repository.add(user1);
        repository.add(user2);

        repository.clear();

        try{
            repository.remove(user1.getId());
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "victor.zarzu does not exist!");
        }

        try{
            repository.remove(user2.getId());
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }
    }

    @Test
    @DisplayName("Test find user by username repository")
    public void testFindUser() throws Exception {
        User user = new User("victor.zarzu", "ceva", "victorzarzu@gmail.com", "Victor", "Zarzu", "Man");
        repository.add(user);

        User foundUser = repository.find("victor.zarzu");
        assertEquals(foundUser.getId(), "victor.zarzu");
        assertEquals(foundUser.getPassword(), "ceva");
        assertEquals(foundUser.getEmail(), "victorzarzu@gmail.com");
        assertEquals(foundUser.getFirstName(), "Victor");
        assertEquals(foundUser.getLastName(), "Zarzu");
        assertEquals(foundUser.getGender(), "Man");

        try{
            repository.find("andrei.ol");
            fail();
        } catch (InexistentEntityException exception) {
            assertEquals(exception.getMessage(), "andrei.ol does not exist!");
        }
    }
}

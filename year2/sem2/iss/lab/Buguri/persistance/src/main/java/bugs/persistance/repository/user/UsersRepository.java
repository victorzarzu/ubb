package bugs.persistance.repository.user;

import bugs.model.Admin;
import bugs.model.Programmer;
import bugs.model.Tester;
import bugs.model.User;
import org.springframework.stereotype.Repository;

import javax.transaction.Transactional;

@org.springframework.stereotype.Repository
@Transactional
public interface UsersRepository extends bugs.persistance.repository.Repository<Integer, User> {
    @Transactional
    public User findByUsernamePassword(String username, String password);

    @Transactional
    public Iterable<Tester> getAllTesters();

    @Transactional
    public Iterable<Admin> getAllAdmins();

    @Transactional
    public Iterable<Programmer> getAllProgrammers();
}

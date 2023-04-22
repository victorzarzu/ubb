package bugs.services;

import bugs.model.Bug;
import bugs.model.User;
import org.springframework.transaction.annotation.Transactional;

@Transactional
public interface BugsService {

    @Transactional
    public User login(String username, String password);

    @Transactional
    public Iterable<Bug> getAllBugs();

    @Transactional
    public void deleteBug(Bug bug);
}

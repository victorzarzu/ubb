package bugs.services;

import bugs.model.*;
import org.springframework.transaction.annotation.Transactional;

@Transactional
public interface BugsService extends BugsObservable {

    @Transactional
    public User login(String username, String password);

    @Transactional
    public Iterable<Bug> getAllBugs();
    @Transactional
    public Iterable<Programmer> getAllProgrammers();

    @Transactional
    public Bug findBug(Integer id);

    @Transactional
    public void addBug(Bug bug);
    @Transactional
    public void deleteBug(Bug bug);

    @Transactional
    public void modifyBug(Bug bug);

    @Transactional
    public void addComment(Bug bug, Comment comment);

    @Transactional
    public void modifyBugStatus(Bug bug, BugStatus status);
}

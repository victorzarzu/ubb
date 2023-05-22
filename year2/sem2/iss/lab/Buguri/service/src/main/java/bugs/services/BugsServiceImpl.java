package bugs.services;

import bugs.model.*;
import bugs.persistance.repository.bug.BugsRepository;
import bugs.persistance.repository.exceptions.NonexistentEntityException;
import bugs.persistance.repository.user.UsersRepository;
import bugs.utils.validators.BugValidator;
import bugs.utils.validators.CommentValidator;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@Transactional
public class BugsServiceImpl extends ConcreteBugsObservable implements BugsService {

    private UsersRepository usersRepository;
    private BugsRepository bugsRepository;
    private BugValidator bugValidator;
    private CommentValidator commentValidator;

    public BugsServiceImpl() {}

    public BugsServiceImpl(UsersRepository usersRepository, BugsRepository bugsRepository,
                           BugValidator bugValidator, CommentValidator commentValidator) {
        this.usersRepository = usersRepository;
        this.bugsRepository = bugsRepository;
        this.bugValidator = bugValidator;
        this.commentValidator = commentValidator;
    }

    public void setUsersRepository(UsersRepository usersRepository) {
        this.usersRepository = usersRepository;
    }

    public void setBugsRepository(BugsRepository bugsRepository) {
        this.bugsRepository = bugsRepository;
    }

    public void setBugValidator(BugValidator bugValidator) {
        this.bugValidator = bugValidator;
    }

    public void setCommentValidator(CommentValidator commentValidator) {
        this.commentValidator = commentValidator;
    }

    @Transactional
    public User login(String username, String password) {
        User user;
        try{
            user = this.usersRepository.findByUsernamePassword(username, password);
        }catch (NonexistentEntityException e) {
            throw new BugsException(e.getMessage());
        }
        return user;
    }

    @Transactional
    public Iterable<Bug> getAllBugs() {
        return this.bugsRepository.findAll();
    }

    @Transactional
    public Iterable<Programmer> getAllProgrammers() {
        return this.usersRepository.getAllProgrammers();
    }

    @Transactional
    public void addBug(Bug bug) {
        this.bugValidator.validate(bug);
        try {
            this.bugsRepository.add(bug);
        } catch (Exception e) {
            throw new BugsException(e.getMessage());
        }
        notifyObserversBugAdded(bug);
    }

    @Transactional
    public void deleteBug(Bug bug) {
        try {
            this.bugsRepository.remove(bug);
        } catch (Exception e) {
            throw new BugsException(e.getMessage());
        }
        this.notifyObserversBugDeleted(bug);
    }

    @Transactional
    public void modifyBug(Bug bug) {
        this.bugValidator.validate(bug);

        try {
            this.bugsRepository.modify(bug);
        } catch (Exception e) {
            throw new BugsException("Bug name error!");
        }
        this.notifyObserversBugModified(bug);
    }

    @Transactional
    public void addComment(Bug bug, Comment comment) {
        commentValidator.validate(comment);
        bug.addComment(comment);
        this.bugsRepository.modify(bug);
        bug = this.findBug(bug.getId());
        this.notifyObserversBugModified(bug);
    }

    @Transactional
    public void modifyBugStatus(Bug bug, BugStatus status) {
        bug.setStatus(status);
        this.bugsRepository.modify(bug);
        this.notifyObserversBugModified(bug);
    }

    @Override
    public Bug findBug(Integer id) {
        return this.bugsRepository.findById(id);
    }
}

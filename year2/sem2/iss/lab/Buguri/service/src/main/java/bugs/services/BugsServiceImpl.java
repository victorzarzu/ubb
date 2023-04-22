package bugs.services;

import bugs.model.Bug;
import bugs.model.User;
import bugs.persistance.repository.admin.AdminsRepository;
import bugs.persistance.repository.bug.BugsRepository;
import bugs.persistance.repository.programmer.ProgrammersRepository;
import bugs.persistance.repository.tester.TestersRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.HashSet;
import java.util.Set;

@Service
@Transactional
public class BugsServiceImpl implements BugsService {

    private ProgrammersRepository programmersRepository;
    private AdminsRepository adminsRepository;
    private TestersRepository testersRepository;
    private BugsRepository bugsRepository;

    public BugsServiceImpl() {}

    public BugsServiceImpl(ProgrammersRepository programmersRepository, AdminsRepository adminsRepository,
                           TestersRepository testersRepository, BugsRepository bugsRepository) {
        this.programmersRepository = programmersRepository;
        this.adminsRepository = adminsRepository;
        this.testersRepository = testersRepository;
        this.bugsRepository = bugsRepository;
    }

    public void setProgrammersRepository(ProgrammersRepository programmersRepository) {
        this.programmersRepository = programmersRepository;
    }

    public void setAdminsRepository(AdminsRepository adminsRepository) {
        this.adminsRepository = adminsRepository;
    }

    public void setTestersRepository(TestersRepository testersRepository) {
        this.testersRepository = testersRepository;
    }

    public void setBugsRepository(BugsRepository bugsRepository) {
        this.bugsRepository = bugsRepository;
    }

    @Transactional
    public User login(String username, String password) {
        User user = this.programmersRepository.findByUsernamePassword(username, password);
        if(user == null) {
            user = this.adminsRepository.findByUsernamePassword(username, password);
        }
        if(user == null) {
            user = this.testersRepository.findByUsernamePassword(username, password);
        }
        if(user == null) {
            throw new BugsException("Invalid credentials!");
        }
        return user;
    }

    @Transactional
    public Iterable<Bug> getAllBugs() {
        return this.bugsRepository.findAll();
    }

    @Transactional
    public void deleteBug(Bug bug) {
        this.bugsRepository.remove(bug);
    }
}

package bugs.persistance.repository.programmer;

import bugs.model.Programmer;
import bugs.model.Tester;
import bugs.persistance.dao.programmer.ProgrammerDAO;
import bugs.persistance.dao.tester.TesterDAO;
import bugs.persistance.repository.tester.TestersRepository;
import org.hibernate.cfg.NotYetImplementedException;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
@Transactional
public class ProgrammersDbRepository implements ProgrammersRepository {
    private ProgrammerDAO programmerDAO;

    public void setProgrammerDAO(ProgrammerDAO programmerDAO) {
        this.programmerDAO = programmerDAO;
    }

    @Override
    @Transactional
    public void add(Programmer programmer) {
        this.programmerDAO.save(programmer);
    }

    @Override
    @Transactional
    public void remove(Programmer programmer) {
        this.programmerDAO.delete(programmer);
    }

    @Override
    @Transactional
    public void modify(Programmer programmer) {
        throw new NotYetImplementedException();
    }

    @Override
    @Transactional
    public Iterable<Programmer> findAll() {
        return this.programmerDAO.getAll();
    }

    @Override
    @Transactional
    public Programmer findByUsernamePassword(String username, String password) {
        return this.programmerDAO.findByUsernameAndPassword(username, password);
    }
}
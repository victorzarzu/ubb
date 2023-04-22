package bugs.persistance.repository.tester;

import bugs.model.Tester;
import bugs.persistance.dao.tester.TesterDAO;
import org.hibernate.cfg.NotYetImplementedException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
@Transactional
public class TestersDbRepository implements TestersRepository {
    private TesterDAO testerDAO;

    public void setTesterDAO(TesterDAO testerDAO) {
        this.testerDAO = testerDAO;
    }

    @Override
    @Transactional
    public void add(Tester tester) {
        this.testerDAO.save(tester);
    }

    @Override
    @Transactional
    public void remove(Tester tester) {
        this.testerDAO.delete(tester);
    }

    @Override
    @Transactional
    public void modify(Tester tester) {
        throw new NotYetImplementedException();
    }

    @Override
    @Transactional
    public Iterable<Tester> findAll() {
        return this.testerDAO.getAll();
    }

    @Override
    public Tester findByUsernamePassword(String username, String password) {
        return this.testerDAO.findByUsernameAndPassword(username, password);
    }
}

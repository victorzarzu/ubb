package bugs.persistance.repository.bug;

import bugs.model.Bug;
import bugs.persistance.dao.bug.BugDAO;
import org.hibernate.cfg.NotYetImplementedException;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

@Repository
@Transactional
public class BugsDbRepository implements BugsRepository {
    private BugDAO bugDAO;

    public void setBugDAO(BugDAO bugDAO) {
        this.bugDAO = bugDAO;
    }

    @Override
    @Transactional
    public void add(Bug bug) {
        this.bugDAO.save(bug);
    }

    @Override
    @Transactional
    public void remove(Bug bug) {
        this.bugDAO.delete(bug);
    }

    @Override
    @Transactional
    public void modify(Bug bug) {
        throw new NotYetImplementedException();
    }

    @Override
    @Transactional
    public Iterable<Bug> findAll() {
        return this.bugDAO.getAll();
    }
}

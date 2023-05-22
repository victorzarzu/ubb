package bugs.persistance.repository.bug;

import bugs.model.Bug;
import bugs.model.Programmer;
import bugs.persistance.repository.exceptions.ExistentEntityException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.NotYetImplementedException;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Repository
@Transactional
public class BugsDbRepository implements BugsRepository {
    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void add(Bug bug) {
        try {
            Session session = this.sessionFactory.openSession();
            Transaction transaction = session.beginTransaction();
            session.persist(bug);
            transaction.commit();
            session.close();
        } catch (Exception e) {
            throw new ExistentEntityException("Bug with this name already exists");
        }
    }

    @Override
    public void remove(Bug bug) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.delete(bug);
        transaction.commit();
        session.close();
    }

    @Override
    public void modify(Bug bug) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.merge(bug);
        transaction.commit();
        session.close();
    }

    @SuppressWarnings("unchecked")
    @Override
    public List<Bug> findAll() {
        Session session = this.sessionFactory.openSession();
        List<Bug> bugs = session.createQuery("from Bug", Bug.class).list();
        session.close();
        return bugs;
    }

    @Override
    public Bug findById(Integer id) {
        Session session = this.sessionFactory.openSession();
        Bug bug = session.get(Bug.class, id);
        session.close();
        return bug;
    }
}

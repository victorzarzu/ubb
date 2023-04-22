package bugs.persistance.dao.bug;

import bugs.model.Bug;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.List;

public class BugDAOImpl implements BugDAO {
    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void save(Bug bug) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.persist(bug);
        transaction.commit();
        session.close();
    }

    @Override
    public void delete(Bug bug) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.remove(bug);
        transaction.commit();
        session.close();
    }

    @Override
    public void update(Bug bug) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.merge(bug);
        transaction.commit();
        session.close();
    }

    @SuppressWarnings("unchecked")
    @Override
    public List<Bug> getAll() {
        Session session = this.sessionFactory.openSession();
        List<Bug> bugs = session.createQuery("from Bug", Bug.class).list();
        session.close();
        return bugs;
    }
}

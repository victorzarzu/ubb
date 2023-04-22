package bugs.persistance.dao.programmer;

import bugs.model.Programmer;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.List;

public class ProgrammerDAOImpl implements ProgrammerDAO {
    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void save(Programmer programmer) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.persist(programmer);
        transaction.commit();
        session.close();
    }

    @Override
    public void delete(Programmer programmer) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.remove(programmer);
        transaction.commit();
        session.close();
    }

    @Override
    public void update(Programmer programmer) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.merge(programmer);
        transaction.commit();
        session.close();
    }

    @Override
    public Programmer findByUsernameAndPassword(String username, String password) {
        Session session = this.sessionFactory.openSession();
        List<Programmer> users = session
                .createQuery("from Programmer p where p.username = :username and p.password = :password", Programmer.class)
                .setParameter("username", username)
                .setParameter("password", password)
                .getResultList();
        session.close();
        return users.isEmpty() ? null : users.get(0);
    }

    @SuppressWarnings("unchecked")
    @Override
    public List<Programmer> getAll() {
        Session session = this.sessionFactory.openSession();
        List<Programmer> programmers = session.createQuery("from Programmer", Programmer.class).list();
        session.close();
        return programmers;
    }
}

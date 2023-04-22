package bugs.persistance.dao.admin;

import bugs.model.Admin;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.List;

public class AdminDAOImpl implements AdminDAO {
    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void save(Admin admin) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.persist(admin);
        transaction.commit();
        session.close();
    }

    @Override
    public void delete(Admin admin) {
        Session session = this.sessionFactory.openSession();
        Transaction transaction = session.beginTransaction();
        session.remove(admin);
        transaction.commit();
        session.close();
    }

    @SuppressWarnings("unchecked")
    @Override
    public Iterable<Admin> getAll() {
        Session session = this.sessionFactory.openSession();
        List<Admin> admins = session.createQuery("from Admin", Admin.class).list();
        session.close();
        return admins;
    }

    @Override
    public Admin findByUsernameAndPassword(String username, String password) {
        Session session = this.sessionFactory.openSession();
        List<Admin> users = session
                .createQuery("from Admin a where a.username = :username and a.password = :password", Admin.class)
                .setParameter("username", username)
                .setParameter("password", password)
                .getResultList();
        session.close();
        return users.isEmpty() ? null : users.get(0);
    }
}

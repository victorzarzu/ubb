package bugs.persistance.dao.tester;

import bugs.model.Tester;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import javax.transaction.Transactional;
import java.util.List;

@Repository
@Transactional
public class TesterDAOImpl implements TesterDAO {

    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    @Transactional
    public void save(Tester tester) {
        Session session = sessionFactory.getCurrentSession();
        session.persist(tester);
    }

    @Override
    @Transactional
    public void delete(Tester tester) {
        Session session = sessionFactory.getCurrentSession();
        session.remove(tester);
    }

    @Override
    @Transactional
    public void update(Tester tester) {
        Session session = sessionFactory.getCurrentSession();
        session.merge(tester);
    }

    @Override
    @Transactional
    public Tester findByUsernameAndPassword(String username, String password) {
        Session session = sessionFactory.getCurrentSession();
        List<Tester> users = session
                .createQuery("from Tester t where t.username = :username and t.password = :password", Tester.class)
                .setParameter("username", username)
                .setParameter("password", password)
                .getResultList();
        return users.isEmpty() ? null : users.get(0);
    }

    @SuppressWarnings("unchecked")
    @Override
    @Transactional
    public List<Tester> getAll() {
        Session session = sessionFactory.getCurrentSession();
        return session.createQuery("from Tester", Tester.class).list();
    }
}
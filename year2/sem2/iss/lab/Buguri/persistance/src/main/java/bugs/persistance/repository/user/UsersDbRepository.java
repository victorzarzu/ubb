package bugs.persistance.repository.user;

import bugs.model.Admin;
import bugs.model.Programmer;
import bugs.model.Tester;
import bugs.model.User;
import bugs.persistance.repository.exceptions.NonexistentEntityException;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Repository
@Transactional
public class UsersDbRepository implements UsersRepository {
    private SessionFactory sessionFactory;

    public void setSessionFactory(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    @javax.transaction.Transactional
    public void add(User user) {
        Session session = sessionFactory.getCurrentSession();
        session.persist(user);
    }

    @Override
    @javax.transaction.Transactional
    public void remove(User user) {
        Session session = sessionFactory.getCurrentSession();
        session.remove(user);
    }

    @Override
    @javax.transaction.Transactional
    public void modify(User user) {
        Session session = sessionFactory.getCurrentSession();
        session.merge(user);
    }

    @Override
    @javax.transaction.Transactional
    public User findByUsernamePassword(String username, String password) {
        Session session = sessionFactory.getCurrentSession();
        List<User> users = session
                .createQuery("from User u where u.username = :username and u.password = :password", User.class)
                .setParameter("username", username)
                .setParameter("password", password)
                .getResultList();
        if(users.isEmpty()) {
            throw new NonexistentEntityException("Invalid credentials!");
        }
        return users.get(0);
    }

    @SuppressWarnings("unchecked")
    @Override
    @javax.transaction.Transactional
    public List<User> findAll() {
        Session session = sessionFactory.getCurrentSession();
        return session.createQuery("from User", User.class).list();
    }

    @Override
    @Transactional
    public Iterable<Tester> getAllTesters() {
        Session session = sessionFactory.getCurrentSession();
        return session.createQuery("from Tester", Tester.class).list();
    }

    @Override
    public Iterable<Admin> getAllAdmins() {
        Session session = sessionFactory.getCurrentSession();
        return session.createQuery("from Admin", Admin.class).list();
    }

    @Override
    public Iterable<Programmer> getAllProgrammers() {
        Session session = sessionFactory.getCurrentSession();
        return session.createQuery("from Programmer", Programmer.class).list();
    }

    @Override
    public User findById(Integer integer) {
        return null;
    }
}

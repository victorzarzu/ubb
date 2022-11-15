package repository;

import domain.User;

import javax.xml.transform.Result;
import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class UserDbRepository implements Repository<Long, User> {
    private String url;
    private String username;
    private String password;

    public UserDbRepository(String url, String username, String password) {
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public User findOne(Long aLong) {
        return null;
    }

    @Override
    public Iterable<User> findAll() {
        Set<User> userSet = new HashSet<>();
        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement("select * from users");
            ResultSet resultSet = preparedStatement.executeQuery()) {

            while(resultSet.next()) {
                Long id = resultSet.getLong("id");
                String first_name = resultSet.getString("first_name");
                String last_name = resultSet.getString("last_name");

                User user = new User(first_name, last_name);
                user.setId(id);
                userSet.add(user);
            }

        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return userSet;
    }

    @Override
    public User save(User user) {
        String sql = "insert into users(first_name, last_name) values(?, ?)";

        try(Connection connection = DriverManager.getConnection(this.url, this.username, this.password);
            PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, user.getFirst_name());
            preparedStatement.setString(2, user.getLast_name());
            preparedStatement.executeUpdate();
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }

        return null;
    }

    @Override
    public User delete(Long aLong) {
        return null;
    }

    @Override
    public User update(User entity) {
        return null;
    }
}

import domain.User;
import repository.UserDbRepository;

public class Main {
    public static void main(String[] args) {
        String url = "jdbc:postgresql://localhost:5432/academic";
        UserDbRepository userDbRepository = new UserDbRepository(url, "postgres", "admin");

        User user = new User("ccc", "bbb");
        userDbRepository.save(user);

        userDbRepository.findAll().forEach(System.out::println);
    }
}
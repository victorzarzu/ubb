import config.Config;
import domain.Friendship;
import domain.User;
import domain.validators.FriendshipValidator;
import domain.validators.UserValidator;
import repository.Repository;
import repository.database.FriendshipDbRepository;
import repository.database.UserDbRepository;
import service.NetworkService;
import ui.console.ConsoleUI;

import java.util.Set;

public class Main {
    public static void main(String[] args) {
        Repository<String, User> userRepository = new UserDbRepository(Config.getProperties().getProperty("databaseUrl"),
                Config.getProperties().getProperty("username"), Config.getProperties().getProperty("password"));
        Repository<Set<String>, Friendship> friendshipRepository = new FriendshipDbRepository(Config.getProperties().getProperty("databaseUrl"),
                Config.getProperties().getProperty("username"), Config.getProperties().getProperty("password"));

        UserValidator userValidator = new UserValidator();
        FriendshipValidator friendshipValidator = new FriendshipValidator();
        NetworkService userService = new NetworkService(userRepository, userValidator, friendshipRepository, friendshipValidator);
        ConsoleUI console = new ConsoleUI(userService);

        console.present();
    }
}
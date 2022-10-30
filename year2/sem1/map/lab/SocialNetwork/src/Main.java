import config.Config;
import domain.User;
import domain.validators.UserValidator;
import repository.Repository;
import repository.file.FileAllNetwork;
import repository.file.UserFileRepository;
import repository.memory.InMemoryAllNetwork;
import service.UserService;
import ui.ConsoleUI;

public class Main {
    public static void main(String[] args) {
        Repository<String, User> userRepository = new UserFileRepository(Config.getProperties().getProperty("usersStorage"));
        UserValidator userValidator = new UserValidator();
        FileAllNetwork network = new FileAllNetwork(Config.getProperties().getProperty("usersStorage"),
                Config.getProperties().getProperty("friendshipsStorage"));
        UserService userService = new UserService(userRepository, userValidator, network);
        ConsoleUI console = new ConsoleUI(userService);

        console.present();
    }
}
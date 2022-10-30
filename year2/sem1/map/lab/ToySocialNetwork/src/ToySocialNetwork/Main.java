package ToySocialNetwork;

import ToySocialNetwork.presentation.Console;
import ToySocialNetwork.repository.AllNetwork;
import ToySocialNetwork.repository.UserRepository;
import ToySocialNetwork.service.UserService;
import ToySocialNetwork.validation.domain.UserValidator;

public class Main {
    public static void main(String[] args) {
        UserRepository userRepository = new UserRepository();
        UserValidator userValidator = new UserValidator();
        AllNetwork network = new AllNetwork();
        UserService userService = new UserService(userRepository, userValidator, network);
        Console console = new Console(userService);

        console.run();
    }
}
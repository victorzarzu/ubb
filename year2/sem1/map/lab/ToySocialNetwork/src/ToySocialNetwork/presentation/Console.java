package ToySocialNetwork.presentation;

import ToySocialNetwork.domain.User;
import ToySocialNetwork.exceptions.repository.ExistentFriendshipException;
import ToySocialNetwork.exceptions.repository.ExistentUserException;
import ToySocialNetwork.exceptions.repository.InexistentFriendshipException;
import ToySocialNetwork.exceptions.repository.InexistentUserException;
import ToySocialNetwork.exceptions.validation.ValidationException;
import ToySocialNetwork.service.UserService;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Console implements Presenter {
    String username;
    private UserService userService;
    private BufferedReader bufferedReader;

    public Console(UserService userService) {
        this.userService = userService;
        username = null;
        bufferedReader = new BufferedReader(new InputStreamReader(System.in));
    }

    private static class ConsoleLogged implements Presenter {
        private User currentUser;
        private UserService userService;
        private BufferedReader bufferedReader;

        public ConsoleLogged(User currentUser, UserService userService) {
            this.currentUser = currentUser;
            this.userService = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("1 - Add friend");
            System.out.println("2 - Remove friend");
            System.out.println("3 - Delete account");
            System.out.println("4 - Exit");
        }

        private void addFriend() throws InexistentUserException, ExistentFriendshipException {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }
            this.userService.addFriendship(currentUser.getUsername(), username);
        }

        private void removeFriend() throws InexistentUserException, InexistentFriendshipException {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }
            this.userService.removeFriendShip(currentUser.getUsername(), username);
        }

        private void deleteAccount() throws InexistentUserException {
            this.userService.removeUser(currentUser.getUsername());
        }

        @Override
        public void run() {
            while (true) {
                printMenu();
                String command;
                try {
                    command = bufferedReader.readLine();
                } catch (IOException exception) {
                    System.out.println("Error reading the command");
                    continue;
                }
                try {
                    switch (command) {
                        case "1":
                            addFriend();
                            break;
                        case "2":
                            removeFriend();
                            break;
                        case "3":
                            deleteAccount();
                        case "4":
                            return;
                    }
                } catch (InexistentUserException inexistentUserException) {
                    System.out.println(inexistentUserException.getMessage());
                } catch (ExistentFriendshipException existentFriendshipException) {
                    System.out.println(existentFriendshipException.getMessage());
                } catch (InexistentFriendshipException inexistentFriendshipException) {
                    System.out.println(inexistentFriendshipException.getMessage());
                }
            }

        }
    }

    private static class ConsoleUnlogged implements Presenter {
        private UserService userService;
        private BufferedReader bufferedReader;

        public ConsoleUnlogged(UserService userService) {
            this.userService = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("1 - Add user");
            System.out.println("2 - Number of communities");
            System.out.println("3 - Most social community1");
            System.out.println("4 - Log in");
            System.out.println("5 - Exit");
        }

        private void addUser() throws ExistentUserException, ValidationException {
            String username;
            String password;
            String email;
            String firstName;
            String lastName;
            String gender;
            try {
                System.out.print("Username: ");
                username = bufferedReader.readLine();
                System.out.print("Password: ");
                password = bufferedReader.readLine();
                System.out.print("Email: ");
                email = bufferedReader.readLine();
                System.out.print("First name: ");
                firstName = bufferedReader.readLine();
                System.out.print("Last name: ");
                lastName = bufferedReader.readLine();
                System.out.print("Gender: ");
                gender = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the data");
                return;
            }
            userService.addUser(username, password, email, firstName, lastName, gender);
        }

        private void numberOfCommunities() {
            System.out.println("Number of communities is equal with " + userService.numberOfCommunities());
        }

        private void mostSocialCommunity() {
            System.out.println(userService.mostSocialCommunity());
        }

        private void logIn() {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }

            User user;
            try {
                user = userService.findUser(username);
            } catch (InexistentUserException inexistentUserException) {
                System.out.println(inexistentUserException.getMessage());
                return;
            }
            ConsoleLogged consoleLogged = new ConsoleLogged(user, this.userService);
            consoleLogged.run();
        }

        @Override
        public void run() {
            while (true) {
                printMenu();
                String command;
                try {
                    command = bufferedReader.readLine();
                } catch (IOException exception) {
                    System.out.println("Error reading the command");
                    continue;
                }
                try {
                    switch (command) {
                        case "1":
                            addUser();
                            break;
                        case "2":
                            numberOfCommunities();
                            break;
                        case "3":
                            mostSocialCommunity();
                            break;
                        case "4":
                            logIn();
                            break;
                        case "5":
                            return;
                        default:
                            System.out.println("Unknown command!");
                    }
                } catch (ExistentUserException existentUserException) {
                    System.out.println(existentUserException.getMessage());
                } catch (ValidationException validationException) {
                    System.out.println(validationException.getMessage());
                }
            }
        }
    }

    @Override
    public void run() {
        ConsoleUnlogged consoleUnlogged = new ConsoleUnlogged(this.userService);
        consoleUnlogged.run();
    }
}

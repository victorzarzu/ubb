package ui.console;

import domain.Friendship;
import domain.User;
import domain.exceptions.ExistentUserException;
import domain.validators.ValidationException;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import service.NetworkService;
import ui.UI;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.time.LocalDateTime;
import java.time.format.DateTimeParseException;

import static constants.DateTime.DATATIME_FORMATTER;

public class ConsoleUI implements UI {
    String username;
    private NetworkService service;
    private BufferedReader bufferedReader;

    public ConsoleUI(NetworkService userService) {
        this.service = userService;
        username = null;
        bufferedReader = new BufferedReader(new InputStreamReader(System.in));
    }

    private static class ConsoleLogged implements UI {
        private User currentUser;
        private NetworkService service;
        private BufferedReader bufferedReader;

        public ConsoleLogged(User currentUser, NetworkService userService) {
            this.currentUser = currentUser;
            this.service = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("1 - Add friend");
            System.out.println("2 - Remove friend");
            System.out.println("3 - Modify friendship date");
            System.out.println("4 - Modify user data");
            System.out.println("5 - Delete account");
            System.out.println("6 - Exit");
        }

        private void addFriend() {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }
            this.service.addFriendship(currentUser.getId(), username);
        }

        private void removeFriend() {
            String username;

            System.out.print("Username: ");
            try {
                username = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }
            this.service.removeFriendship(currentUser.getId(), username);
        }

        private void modifyFriendshipDate() {
            String username;
            LocalDateTime newDate;

            try {
                System.out.print("Username: ");
                username = bufferedReader.readLine();
                System.out.print("New date: ");
                newDate = LocalDateTime.parse(bufferedReader.readLine(), DATATIME_FORMATTER);
            } catch (IOException exception) {
                System.out.println("Error reading the username");
                return;
            }catch (DateTimeParseException dateTimeParseException) {
                System.out.println("Incorrect date fromat");
                return;
            }

            this.service.modifyFriendshipDate(currentUser.getId(), username, newDate);
        }

        private void modifyData() {
            String newPassword;
            String newEmail;
            String newFirstName;
            String newLastName;
            String newGender;
            try {
                System.out.print("New password: ");
                newPassword = bufferedReader.readLine();
                System.out.print("New email: ");
                newEmail = bufferedReader.readLine();
                System.out.print("New first name: ");
                newFirstName = bufferedReader.readLine();
                System.out.print("New last name: ");
                newLastName = bufferedReader.readLine();
                System.out.print("New gender: ");
                newGender = bufferedReader.readLine();
            } catch (IOException exception) {
                System.out.println("Error reading the data");
                return;
            }
            service.modifyUser(this.currentUser.getId(), newPassword, newEmail, newFirstName,
                    newLastName, newGender);
        }

        private void deleteAccount() {
            this.service.removeUser(currentUser.getId());
        }

        @Override
        public void present() {
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
                            modifyFriendshipDate();
                            break;
                        case "4":
                            modifyData();
                            break;
                        case "5":
                            deleteAccount();
                        case "6":
                            return;
                        default:
                            System.out.println("Unknown command!");
                    }
                } catch (InexistentEntityException inexistentEntityException) {
                    System.out.println(inexistentEntityException.getMessage());
                } catch (ExistentEntityException existentEntityException) {
                    System.out.println(existentEntityException.getMessage());
                } catch (ValidationException validationException) {
                    System.out.println(validationException.getMessage());
                }
            }

        }
    }

    private static class ConsoleUnlogged implements UI {
        private NetworkService service;
        private BufferedReader bufferedReader;

        public ConsoleUnlogged(NetworkService userService) {
            this.service = userService;
            bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        }
        private void printMenu() {
            System.out.println("1 - List all users");
            System.out.println("2 - List all friendships");
            System.out.println("3 - Add user");
            System.out.println("4 - Number of communities");
            System.out.println("5 - Most social community");
            System.out.println("6 - Log in");
            System.out.println("7 - Exit");
        }

        private void listAllUsers() {
            Iterable<User> allUsers = this.service.getAllUsers();
            for(User user : allUsers) {
                System.out.println(user);
            }
            System.out.println();
        }

        private void listAllFriendships() {
            Iterable<Friendship> allFriendships = this.service.getAllFriendships();
            for(Friendship friendship : allFriendships) {
                System.out.println(friendship);
            }
            System.out.println();
        }

        private void addUser() {
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
            service.addUser(username, password, email, firstName, lastName, gender);
        }

        private void numberOfCommunities() {
            System.out.println("Number of communities is equal with " + service.numberOfCommunities());
        }

        private void mostSocialCommunity() {
            System.out.println(service.mostSocialCommunity());
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
                user = service.findUser(username);
            } catch (InexistentEntityException inexistentEntityException) {
                System.out.println(inexistentEntityException.getMessage());
                return;
            }
            ConsoleLogged consoleLogged = new ConsoleLogged(user, this.service);
            consoleLogged.present();
        }

        @Override
        public void present() {
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
                            listAllUsers();
                            break;
                        case "2":
                            listAllFriendships();
                            break;
                        case "3":
                            addUser();
                            break;
                        case "4":
                            numberOfCommunities();
                            break;
                        case "5":
                            mostSocialCommunity();
                            break;
                        case "6":
                            logIn();
                            break;
                        case "7":
                            return;
                        default:
                            System.out.println("Unknown command!");
                    }
                } catch (ExistentEntityException existentEntityException) {
                    System.out.println(existentEntityException.getMessage());
                } catch (ValidationException validationException) {
                    System.out.println(validationException.getMessage());
                }
            }
        }
    }

    @Override
    public void present() {
        ConsoleUnlogged consoleUnlogged = new ConsoleUnlogged(this.service);
        consoleUnlogged.present();
    }
}

package repository.file;

import domain.Network;
import domain.User;
import repository.exceptions.ExistentEntityException;
import repository.exceptions.InexistentEntityException;
import repository.memory.InMemoryAllNetwork;

import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class FileAllNetwork extends InMemoryAllNetwork {
    String usersFilename;
    String friendshipsFilename;

    /**
     * Contructor for creating a network with persistence in file
     * @param usersFilename the file where the users are stored
     * @param friendshipsFilename the file where the friendships are stored
     */
    public FileAllNetwork(String usersFilename, String friendshipsFilename) {
        this.usersFilename = usersFilename;
        this.friendshipsFilename = friendshipsFilename;
        loadData();
    }

    /**
     * Method that loads the users and friendships for the network
     */
    private void loadData() {
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(this.usersFilename))) {
            String line;
            while((line = bufferedReader.readLine()) != null) {
                List<String> users = Arrays.asList(line.split(";"));
                this.addUser(new User(users.get(0), users.get(1), users.get(2), users.get(3), users.get(4), users.get(5)));
            }
        }
        catch (FileNotFoundException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        }
        catch (IOException ioException) {
            ioException.printStackTrace();
        }
        try(BufferedReader bufferedReader = new BufferedReader(new FileReader(this.friendshipsFilename))) {
            String line;
            while((line = bufferedReader.readLine()) != null) {
                List<String> users = Arrays.asList(line.split(";"));
                super.addFriendship(new User(users.get(0), "", "", "", "", ""),
                        new User(users.get(1), "", "", "", "", ""));
            }
        }
        catch (FileNotFoundException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        }
        catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    /**
     * Method that writes the friendships in file
     */
    private void writeData() {
        try(BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.friendshipsFilename))) {
            Network network = new Network();
            for(User user : this.network.getMap().keySet()) {
                network.addUser(user);
            }

            for(Map.Entry<User, Set<User>> entry : this.network.getMap().entrySet()) {
                for(User user : entry.getValue()) {
                    if(!network.areFriends(entry.getKey(), user)) {
                        String written = entry.getKey().getId() + ";" + user.getId() + "\n";
                        bufferedWriter.write(written);
                        network.addFriendship(entry.getKey(), user);
                    }
                }
            }
        } catch (FileNotFoundException fileNotFoundException) {
            fileNotFoundException.printStackTrace();
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    /**
     * Method that adds a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws InexistentEntityException if at least one of the user does not exist in the network
     * @throws ExistentEntityException if there is already a friendship between the users
     */
    public void addFriendship(User user1, User user2) {
        super.addFriendship(user1, user2);
        this.writeData();
    }

    /**
     * Method that removes a friendship in the network
     * @param user1 User
     * @param user2 User
     * @throws InexistentEntityException if at least one of the user does not exist in the network
     * @throws InexistentEntityException if there is not friendship between the users with the given usernames
     */
    public void removeFriendsShip(User user1, User user2) {
        super.removeFriendsShip(user1, user2);
        this.writeData();
    }
}

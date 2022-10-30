package repository.file;

import domain.User;
import repository.memory.InMemoryAllNetwork;

import java.io.*;
import java.util.Arrays;
import java.util.List;

public class FileAllNetwork extends InMemoryAllNetwork {
    String usersFilename;
    String friendshipsFilename;

    public FileAllNetwork(String usersFilename, String friendshipsFilename) {
        this.usersFilename = usersFilename;
        this.friendshipsFilename = friendshipsFilename;
        loadData();
    }

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
                this.addFriendship(new User(users.get(0), "", "", "", "", ""),
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
}

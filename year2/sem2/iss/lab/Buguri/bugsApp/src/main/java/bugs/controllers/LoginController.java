package bugs.controllers;

import bugs.StartApp;
import bugs.model.Admin;
import bugs.model.Programmer;
import bugs.model.Tester;
import bugs.model.User;
import bugs.services.BugsException;
import bugs.services.BugsObserver;
import bugs.services.BugsService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.util.HashSet;
import java.util.Set;

public class LoginController {
    private BugsService bugsService;

    @FXML
    TextField usernameField;
    @FXML
    TextField passwordField;

    Set<BugsObserver> observers = new HashSet<>();

    public void setBugsService(BugsService bugsService) {
        this.bugsService = bugsService;
    }

    private void openTesterWindow(Tester tester) {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("tester-view.fxml"));
            Parent root = (Parent) loader.load();
            TesterController testerController = loader.getController();
            testerController.setBugsService(bugsService);
            testerController.setTester(tester);

            observers.add(testerController);

            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setTitle(tester.getName());
            stage.setScene(scene);
            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void openProgrammerWindow(Programmer programmer) {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("programmer-view.fxml"));
            Parent root = (Parent) loader.load();
            ProgrammerController programmerController = loader.getController();
            programmerController.setBugsService(bugsService);
            programmerController.setProgrammer(programmer);

            observers.add(programmerController);

            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setTitle(programmer.getName());
            stage.setScene(scene);
            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void openAdminWindow(Admin admin) {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("admin-view.fxml"));
            Parent root = (Parent) loader.load();
            AdminController adminController = loader.getController();
            adminController.setBugsService(bugsService);
            adminController.setAdmin(admin);

            observers.add(adminController);

            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setTitle(admin.getName());
            stage.setScene(scene);
            stage.show();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void openUserWindow(User user) {
        if(user instanceof Tester) {
            openTesterWindow((Tester)user);
        } else if(user instanceof Programmer) {
            openProgrammerWindow((Programmer)user);
        } else if(user instanceof Admin) {
            openAdminWindow((Admin)user);
        }
        else {
            throw new BugsException("User type not recognized! " + user.getClass());
        }
    }

    public void loginPressed(ActionEvent actionEvent) {
        String username = usernameField.getText();
        String password = passwordField.getText();

        User user = bugsService.login(username, password);
        openUserWindow(user);
    }
}

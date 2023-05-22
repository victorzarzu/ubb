package bugs;

import bugs.controllers.LoginController;
import bugs.model.Admin;
import bugs.persistance.repository.user.UsersDbRepository;
import bugs.persistance.repository.user.UsersRepository;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import bugs.services.BugsService;

import java.io.IOException;

public class StartApp extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("bugsConfig.xml");

        BugsService bugsService = context.getBean(BugsService.class);

        FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("login-view.fxml"));
        Parent loginView = (Parent)loader.load();
        LoginController loginController = loader.getController();
        loginController.setBugsService(bugsService);

        Scene scene = new Scene(loginView);
        stage.setTitle("Bugs");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
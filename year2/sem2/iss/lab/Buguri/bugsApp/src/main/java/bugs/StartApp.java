package bugs;

import bugs.controllers.LoginController;
import bugs.persistance.repository.tester.TestersRepository;
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

        TestersRepository testersRepository = context.getBean(TestersRepository.class);
        BugsService bugsService = context.getBean(BugsService.class);

        //Login
        FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("login.fxml"));
        Parent root = (Parent)loader.load();
        LoginController loginController = loader.getController();
        loginController.setBugsService(bugsService);

        Scene scene = new Scene(root);
        stage.setTitle("Bugs");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}
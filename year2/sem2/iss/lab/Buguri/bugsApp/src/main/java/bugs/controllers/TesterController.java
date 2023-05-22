package bugs.controllers;

import bugs.StartApp;
import bugs.model.Bug;
import bugs.model.BugStatus;
import bugs.model.Comment;
import bugs.model.Tester;
import bugs.services.BugsException;
import bugs.services.BugsObserver;
import bugs.services.BugsService;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

public class TesterController extends Controller implements BugsObserver {
    private Tester currentTester;

    private Map<BugStatus, Color> statusColorMap = new HashMap<>() {{
        put(BugStatus.OPEN, Color.ORANGE);
        put(BugStatus.SOLVED, Color.GREEN);
        put(BugStatus.REOPENED, Color.YELLOW);
        put(BugStatus.STOPPED, Color.RED);
        put(BugStatus.RETURNED, Color.CADETBLUE);
    }};

    @FXML
    private TableView testerBugsTableView;
    @FXML
    private TableColumn testerBugsStatusColumn;
    @FXML
    private TableView bugsTableView;
    @FXML
    private TableColumn bugsStatusColumn;
    @FXML
    private Button modifyButton;
    @FXML
    private Button viewButton;
    @FXML
    private Button deleteButton;
    private ObservableList<Bug> testerBugsModel = FXCollections.observableArrayList();
    private ObservableList<Bug> bugsModel = FXCollections.observableArrayList();
    private Bug selectedBug = null;
    private Stage addBugView = new Stage();
    private Stage modifyBugView = new Stage();
    private ModifyBugController modifyBugController;
        private Stage viewBugStage = new Stage();
    private ViewBugController viewBugController;

    public void setTester(Tester tester) {
        this.currentTester = tester;

        initComponents();
    }

    @Override
    protected void initComponents() {

        initTesterBugsTableView();
        initBugsTableView();

        initAddWindow();
        initModifyWindow();
        initViewBugWindow();
    }

    private void initAddWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("modify-bug-view.fxml"));
            Parent addBugView = (Parent) loader.load();
            ModifyBugController addBugController = loader.getController();
            addBugController.setBugsService(bugsService);
            addBugController.setTester(currentTester);
            addBugController.convertToAdd();

            Scene scene = new Scene(addBugView);
            this.addBugView.setTitle("Add a bug");
            this.addBugView.setScene(scene);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void initModifyWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("modify-bug-view.fxml"));
            Parent modifyBugView = (Parent) loader.load();
            modifyBugController = loader.getController();
            modifyBugController.setBugsService(bugsService);
            modifyBugController.setTester(currentTester);

            Scene scene = new Scene(modifyBugView);
            this.modifyBugView.setTitle("Modify a bug");
            this.modifyBugView.setScene(scene);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void initViewBugWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("view-bug-view.fxml"));
            Parent viewBugView = (Parent) loader.load();
            viewBugController = loader.getController();
            viewBugController.setBugsService(bugsService);
            viewBugController.setEmployee(currentTester);

            Scene scene = new Scene(viewBugView);
            viewBugStage.setTitle("View bug");
            viewBugStage.setScene(scene);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void UpdateButtonsStates() {
        if(selectedBug.getTester().equals(currentTester)) {
            deleteButton.setDisable(false);
            modifyButton.setDisable(false);
            viewButton.setDisable(false);
        } else {
            deleteButton.setDisable(true);
            modifyButton.setDisable(true);
            viewButton.setDisable(false);
        }
    }

    public void initTesterBugsTableView() {
        testerBugsTableView.setItems(testerBugsModel);
        testerBugsModel.setAll(currentTester.getBugs());

        testerBugsTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                selectedBug = (Bug) newSelection;
                System.out.println(selectedBug);
                UpdateButtonsStates();
            }
        });

        Callback<TableColumn<Bug, String>, TableCell<Bug, String>> statusFactory =
                new Callback<TableColumn<Bug, String>, TableCell<Bug, String>>() {
                    @Override
                    public TableCell call(final TableColumn<Bug, String> param) {
                        final TableCell<Bug, String> cell = new TableCell<Bug, String>() {

                            @Override
                            public void updateItem(String item, boolean empty) {
                                super.updateItem(item, empty);
                                if (empty) {
                                    setGraphic(null);
                                    setText(null);
                                } else {
                                    Bug bug = getTableView().getItems().get(getIndex());
                                    setText(bug.getStatus().toString());
                                    setTextFill(statusColorMap.get(bug.getStatus()));
                                }
                            }
                        };
                        return cell;
                    }
                };

        testerBugsStatusColumn.setCellFactory(statusFactory);
    }

    public void initBugsTableView() {
        bugsTableView.setItems(bugsModel);
        List<Bug> bugs = (List<Bug>)bugsService.getAllBugs();
        bugs.removeAll(currentTester.getBugs());
        bugsModel.setAll(bugs);

        bugsTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                selectedBug = (Bug) newSelection;
                UpdateButtonsStates();
            }
        });

        Callback<TableColumn<Bug, String>, TableCell<Bug, String>> statusFactory =
                new Callback<TableColumn<Bug, String>, TableCell<Bug, String>>() {
                    @Override
                    public TableCell call(final TableColumn<Bug, String> param) {
                        final TableCell<Bug, String> cell = new TableCell<Bug, String>() {

                            @Override
                            public void updateItem(String item, boolean empty) {
                                super.updateItem(item, empty);
                                if (empty) {
                                    setGraphic(null);
                                    setText(null);
                                } else {
                                    Bug bug = getTableView().getItems().get(getIndex());
                                    System.out.println(bug.getStatus());
                                    setText(bug.getStatus().toString());
                                    setTextFill(statusColorMap.get(bug.getStatus()));
                                }
                            }
                        };
                        return cell;
                    }
                };

        bugsStatusColumn.setCellFactory(statusFactory);
    }

    public void deletePressed() {
        if (selectedBug != null) {
            try{
                System.out.println(selectedBug);
                bugsService.deleteBug(selectedBug);
            } catch (BugsException e) {
                MessageAlert.showErrorMessage(null, e.getMessage());
            }
        }
    }

    @Override
    public void bugAdded(Bug bug) {
        if(bug.getTester().equals(currentTester)) {
            this.currentTester.addBug(bug);
            testerBugsModel.add(bug);
        } else {
            bugsModel.add(bug);
        }
        this.modifyButton.setDisable(true);
        this.deleteButton.setDisable(true);
    }

    @Override
    public void bugDeleted(Bug bug) {
        if(bug.getTester().equals(currentTester)) {
            testerBugsModel.remove(bug);
            this.currentTester.removeBug(bug);
        } else {
            bugsModel.remove(bug);
        }
        this.modifyButton.setDisable(true);
        this.deleteButton.setDisable(true);
    }

    @Override
    public void bugModified(Bug bug) {
        if(bug.getTester().equals(currentTester)) {
            this.currentTester.removeBug(bug);
            this.currentTester.addBug(bug);

            this.testerBugsModel.setAll(this.currentTester.getBugs());

        } else {
            this.bugsModel.remove(bug);
            this.bugsModel.add(bug);
        }
        this.modifyButton.setDisable(true);
        this.deleteButton.setDisable(true);
    }

    public void addPressed() {
        addBugView.show();
    }

    public void modifyPressed() {
        if(selectedBug != null) {
            modifyBugController.setBug(selectedBug);
            modifyBugView.show();
        }
    }

    public void viewPressed() {
        if(selectedBug != null) {
            viewBugController.setBug(selectedBug);
            viewBugStage.show();
        }
    }
}

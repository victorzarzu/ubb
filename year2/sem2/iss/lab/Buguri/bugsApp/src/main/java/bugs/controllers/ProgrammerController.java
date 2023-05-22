package bugs.controllers;

import bugs.StartApp;
import bugs.model.Bug;
import bugs.model.BugStatus;
import bugs.model.Programmer;
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
import java.util.*;
import java.util.stream.Collectors;

public class ProgrammerController extends Controller implements BugsObserver {
    private Programmer currentProgrammer;

    private Map<BugStatus, Color> statusColorMap = new HashMap<>() {{
        put(BugStatus.OPEN, Color.ORANGE);
        put(BugStatus.SOLVED, Color.GREEN);
        put(BugStatus.REOPENED, Color.YELLOW);
        put(BugStatus.STOPPED, Color.RED);
        put(BugStatus.RETURNED, Color.CADETBLUE);
    }};

    private ViewBugController viewBugController;
    private Stage viewBugStage = new Stage();
    private ModifyStatusBugController modifyStatusBugController;
    private Stage modifyBugStatusStage = new Stage();

    @FXML
    private TableView<Bug> assignedBugsTableView;
    private ObservableList<Bug> assignedBugsModel = FXCollections.observableList(new ArrayList<>());
    @FXML
    private TableView<Bug> bugsTableView;
    private ObservableList<Bug> bugsModel = FXCollections.observableList(new ArrayList<>());

    @FXML
    private Button viewButton;
    @FXML
    private Button modifyButton;

    @FXML
    private TableColumn testerBugsStatusColumn;
    @FXML
    private TableColumn bugsStatusColumn;

    private Bug selectedBug;

    public void setProgrammer(Programmer programmer) {
        this.currentProgrammer = programmer;

        initComponents();
    }

    @Override
    protected void initComponents() {
        initBugsTableView();
        initAssignedBugsTableView();

        initModifyStatusBugWindow();
        initViewBugWindow();
    }

    private void initAssignedBugsTableView() {
        assignedBugsTableView.setItems(assignedBugsModel);
        List<Bug> programmerBugs = this.currentProgrammer.getAssignedBugs().stream()
                .filter(bug -> bug.getStatus() == BugStatus.OPEN || bug.getStatus() == BugStatus.REOPENED).toList();
        assignedBugsModel.setAll(programmerBugs);

        assignedBugsTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
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

    private void initBugsTableView() {
        bugsTableView.setItems(bugsModel);
        List<Bug> bugs = ((List<Bug>)bugsService.getAllBugs()).stream()
                .filter(bug -> bug.getStatus() == BugStatus.OPEN || bug.getStatus() == BugStatus.REOPENED)
                .collect(Collectors.toCollection(ArrayList::new));
        bugs.removeAll(this.currentProgrammer.getAssignedBugs());
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

    private void initViewBugWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("view-bug-view.fxml"));
            Parent viewBugView = (Parent) loader.load();
            viewBugController = loader.getController();
            viewBugController.setBugsService(bugsService);
            viewBugController.setEmployee(this.currentProgrammer);

            Scene scene = new Scene(viewBugView);
            viewBugStage.setTitle("View bug");
            viewBugStage.setScene(scene);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }

    private void initModifyStatusBugWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(StartApp.class.getResource("modify-status-bug-view.fxml"));
            Parent viewBugView = (Parent) loader.load();
            modifyStatusBugController = loader.getController();
            modifyStatusBugController.setBugsService(bugsService);
            modifyStatusBugController.setProgrammer(this.currentProgrammer);

            Scene scene = new Scene(viewBugView);
            modifyBugStatusStage.setTitle("Modify bug");
            modifyBugStatusStage.setScene(scene);
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
    }


    @Override
    public void bugAdded(Bug bug) {
        if(bug.getProgrammer() != null && bug.getProgrammer().equals(this.currentProgrammer)) {
            if(bug.getStatus() == BugStatus.OPEN || bug.getStatus() == BugStatus.REOPENED) {
                assignedBugsModel.add(bug);
            }
        } else {
            if(bug.getStatus() == BugStatus.OPEN || bug.getStatus() == BugStatus.REOPENED) {
                bugsModel.add(bug);
            }
        }
    }

    @Override
    public void bugDeleted(Bug bug) {
        if(bug.getProgrammer() != null && bug.getProgrammer().equals(this.currentProgrammer)) {
            assignedBugsModel.remove(bug);
        } else {
            bugsModel.remove(bug);
        }
    }

    @Override
    public void bugModified(Bug bug) {
        if(bug.getProgrammer() != null && bug.getProgrammer().equals(this.currentProgrammer)) {
            currentProgrammer.removeAssignedBug(bug);
            currentProgrammer.addAssignedBug(bug);
            assignedBugsModel.remove(bug);
            if(bug.getStatus() == BugStatus.OPEN || bug.getStatus() == BugStatus.REOPENED) {
                assignedBugsModel.add(bug);
            } else {
                viewButton.setDisable(true);
                modifyButton.setDisable(true);
            }
            initAssignedBugsTableView();
        } else {
            bugsModel.remove(bug);
            if(bug.getStatus() == BugStatus.OPEN || bug.getStatus() == BugStatus.REOPENED) {
                bugsModel.add(bug);
            } else {
                viewButton.setDisable(true);
                modifyButton.setDisable(true);
            }
            initBugsTableView();
        }
    }

    private void UpdateButtonsStates() {
        if(selectedBug.getProgrammer().equals(currentProgrammer)) {
            modifyButton.setDisable(false);
            viewButton.setDisable(false);
        } else {
            viewButton.setDisable(false);
            modifyButton.setDisable(true);
        }
    }

    public void modifyBugStatusPressed() {
        if(selectedBug != null) {
            modifyStatusBugController.setBug(selectedBug);
            modifyBugStatusStage.show();
        }
    }

    public void viewPressed(ActionEvent actionEvent) {
        if(selectedBug != null) {
            viewBugController.setBug(selectedBug);
            viewBugStage.show();
        }
    }
}

package bugs.controllers;

import bugs.model.Bug;
import bugs.model.Tester;
import bugs.services.BugsObserver;
import bugs.services.BugsService;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;

import java.util.List;

public class TesterController implements BugsObserver {
    private BugsService bugsService;
    private Tester tester;

    @FXML
    TableView testerBugsTableView;
    @FXML
    TableView bugsTableView;
    ObservableList<Bug> testerBugsModel = FXCollections.observableArrayList();
    ObservableList<Bug> bugsModel = FXCollections.observableArrayList();

    Bug bugSelected = null;

    public void setBugsService(BugsService bugsService) {
        this.bugsService = bugsService;
    }

    public void setTester(Tester tester) {
        this.tester = tester;

        initComponents();
    }

    void initComponents() {
        initTesterBugsTableView();
        initBugsTableView();
    }

    void initTesterBugsTableView() {
        testerBugsTableView.setItems(testerBugsModel);
        testerBugsModel.setAll(tester.getBugs());

        testerBugsTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                bugSelected = (Bug) newSelection;
            }
        });
    }

    void initBugsTableView() {
        bugsTableView.setItems(bugsModel);
        List<Bug> bugs = (List<Bug>)bugsService.getAllBugs();
        bugs.removeAll(tester.getBugs());
        bugsModel.setAll(bugs);

        bugsTableView.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                bugSelected = (Bug) newSelection;
            }
        });
    }

    public void deletePressed(ActionEvent actionEvent) {
        if (bugSelected != null) {
            bugsService.deleteBug(bugSelected);
        }
    }

    @Override
    public void bugAdded(Bug bug) {
        if(bug.getTester().equals(tester)) {
            testerBugsModel.add(bug);
        } else {
            bugsModel.add(bug);
        }
    }
}

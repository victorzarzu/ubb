package bugs.controllers;

import bugs.model.*;
import bugs.services.BugsException;
import bugs.utils.validators.ValidationException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.util.StringConverter;

import java.time.LocalDateTime;
import java.util.List;

public class ModifyBugController extends Controller {
    private Tester currentTester;
    private Bug bug;

    boolean isAdd = false;

    @FXML
    private TextField nameField;
    @FXML
    private TextArea descriptionField;
    @FXML
    private ComboBox priorityCombo;
    @FXML
    private ComboBox statusCombo;
    @FXML
    private ComboBox programmerCombo;
    @FXML
    private Button modifyButton;

    private ObservableList<Programmer> programmersModel = FXCollections.observableArrayList();

    public void setTester(Tester tester) {
        this.currentTester = tester;

        initComponents();
    }

    public void setBug(Bug bug) {
        this.bug = bug;

        nameField.setText(bug.getName());
        descriptionField.setText(bug.getDescription());
        priorityCombo.getSelectionModel().select(bug.getPriority());
        statusCombo.getSelectionModel().select(bug.getStatus());
        programmerCombo.getSelectionModel().select(bug.getProgrammer());
    }

    @Override
    protected void initComponents() {
        initProgrammersCombo();
        initPriorityCombo();
        initStatusCombo();
    }

    private void initProgrammersCombo() {
        programmersModel.setAll((List)bugsService.getAllProgrammers());
        programmerCombo.setItems(programmersModel);
        programmerCombo.getSelectionModel().selectFirst();

        programmerCombo.setConverter(new StringConverter<Programmer>() {
            @Override
            public String toString(Programmer programmer) {
                return programmer.getUsername();
            }

            @Override
            public Programmer fromString(String string) {
                return null;
            }
        });
    }

    private void initPriorityCombo() {
        Object[] possiblePriorities = BugPriority.NORMAL.getDeclaringClass().getEnumConstants();
        priorityCombo.getItems().addAll(possiblePriorities);
        priorityCombo.getSelectionModel().selectFirst();
    }

    private void initStatusCombo() {
        Object[] possibleStatuses = BugStatus.OPEN.getDeclaringClass().getEnumConstants();
        statusCombo.getItems().addAll(possibleStatuses);
        statusCombo.getSelectionModel().selectFirst();
    }

    public void convertToAdd() {
        modifyButton.setText("Add");

        this.statusCombo.setDisable(true);
        isAdd = true;
    }

    private Bug createBugWithData() {
        String name = nameField.getText();
        String description = descriptionField.getText();
        BugPriority priority = (BugPriority) priorityCombo.getSelectionModel().getSelectedItem();
        Programmer programmer = (Programmer) programmerCombo.getSelectionModel().getSelectedItem();
        BugStatus status = (BugStatus) statusCombo.getSelectionModel().getSelectedItem();

        Bug bug = new Bug(name, description, status, LocalDateTime.now(), priority, currentTester, programmer);
        return bug;
    }

    private Bug modifyBugWithData(Bug bug) {
        String name = nameField.getText();
        String description = descriptionField.getText();
        BugPriority priority = (BugPriority) priorityCombo.getSelectionModel().getSelectedItem();
        Programmer programmer = (Programmer) programmerCombo.getSelectionModel().getSelectedItem();
        BugStatus status = (BugStatus) statusCombo.getSelectionModel().getSelectedItem();

        bug.setName(name);
        bug.setDescription(description);
        bug.setPriority(priority);
        bug.setProgrammer(programmer);
        bug.setStatus(status);

        return bug;
    }

    private void addBug(ActionEvent ae) {
        Bug bug = createBugWithData();

        try{
            bugsService.addBug(bug);
            this.currentTester.addBug(bug);

            nameField.clear();
            descriptionField.clear();
            priorityCombo.getSelectionModel().selectFirst();
            programmerCombo.getSelectionModel().selectFirst();
            statusCombo.getSelectionModel().selectFirst();

            ((Node)ae.getSource()).getScene().getWindow().hide();
        } catch (ValidationException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        } catch (BugsException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    private void modifyBug(ActionEvent ae) {
        Bug bug = modifyBugWithData(this.bug);

        try{
            bugsService.modifyBug(bug);
            this.currentTester.removeBug(bug);
            this.currentTester.addBug(bug);
            ((Node)ae.getSource()).getScene().getWindow().hide();
        } catch (ValidationException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        } catch (BugsException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

    public void modifyPressed(ActionEvent ae) {
        if(isAdd) {
            addBug(ae);
        } else {
            modifyBug(ae);
        }
    }
}

package bugs.controllers;

import bugs.model.*;
import bugs.services.BugsObserver;
import bugs.services.BugsService;
import bugs.utils.validators.ValidationException;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.*;

import java.time.LocalDateTime;

public class ModifyStatusBugController extends Controller {
    private Bug bug;
    private Programmer programmer;

    @FXML
    private TextField nameField;
    @FXML
    private TextArea descriptionArea;
    @FXML
    private DatePicker datePicker;
    @FXML
    private TextField priorityField;
    @FXML
    private TextArea commentArea;
    @FXML
    private ComboBox<BugStatus> statusCombo;
    @FXML
    private Button modifyButton;

    public void setBug(Bug bug) {
        this.bug = bug;

        nameField.setText(bug.getName());
        descriptionArea.setText(bug.getDescription());
        priorityField.setText(bug.getPriority().toString());
        datePicker.setValue(bug.getDate().toLocalDate());
        statusCombo.setValue(bug.getStatus());
    }

    public void setProgrammer(Programmer programmer) {
        this.programmer = programmer;

        this.initComponents();
    }

    @Override
    protected void initComponents() {
        statusCombo.getItems().addAll(BugStatus.values());
        statusCombo.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                if(newSelection != bug.getStatus()) {
                    modifyButton.setDisable(false);
                }
            }
        });
    }

    public void modifyPressed(ActionEvent actionEvent) {
        try {
            BugStatus status = statusCombo.getValue();
            Comment comment = new Comment(commentArea.getText(), LocalDateTime.now(), programmer);
            bugsService.addComment(bug, comment);
            bugsService.modifyBugStatus(bug, status);

            ((Node) actionEvent.getSource()).getScene().getWindow().hide();
        } catch (ValidationException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }
}

package bugs.controllers;

import bugs.model.Bug;
import bugs.model.Comment;
import bugs.model.Employee;
import bugs.services.BugsService;
import bugs.utils.validators.ValidationException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.*;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ViewBugController extends Controller {
    private Bug bug;
    private Employee employee;

    @FXML
    private TextField nameField;
    @FXML
    private TextArea descriptionArea;
    @FXML
    private TextField priorityField;
    @FXML
    private TextField statusField;
    @FXML
    private TextField programmerField;
    @FXML
    private DatePicker datePicker;
    @FXML
    private ListView commentsList;
    @FXML
    private TextArea commentArea;
    @FXML
    private Button addCommentButton;

    ObservableList<Comment> commentsModel = FXCollections.observableArrayList();

    public void setBug(Bug bug) {
        this.bug = bug;

        nameField.setText(bug.getName());
        descriptionArea.setText(bug.getDescription());
        priorityField.setText(bug.getPriority().toString());
        statusField.setText(bug.getStatus().toString());
        programmerField.setText(bug.getProgrammer().getUsername());
        datePicker.setValue(bug.getDate().toLocalDate());

        initComponents();
    }

    public void setEmployee(Employee employee) {
        this.employee = employee;
    }


    @Override
    protected void initComponents() {
        initComments();

        commentArea.textProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                if(!newSelection.isEmpty()) {
                    addCommentButton.setDisable(false);
                } else {
                    addCommentButton.setDisable(true);
                }
            }
        });
    }

    private void initComments() {
        commentsModel.setAll(bug.getComments());
        commentsList.setCellFactory(list -> new ListCell<Comment>() {
            @Override
            protected void updateItem(Comment comment, boolean empty) {
                super.updateItem(comment, empty);
                if (empty || comment == null) {
                    setText(null);
                } else {
                    setText(comment.getEmployee().getUsername() + " - " + comment.getDate().format(DateTimeFormatter.ISO_DATE_TIME) + ": " + comment.getText());
                }
            }
        });
        commentsList.setItems(commentsModel);
    }

    public void addCommentPressed(ActionEvent actionEvent) {
        String commentText = commentArea.getText();
        Comment comment = new Comment(commentText, LocalDateTime.now(), employee);

        commentArea.clear();

        try {
            bugsService.addComment(bug, comment);
            ((Node)actionEvent.getSource()).getScene().getWindow().hide();
        } catch (ValidationException validationException) {
            MessageAlert.showErrorMessage(null, validationException.getMessage());
        }
    }
}

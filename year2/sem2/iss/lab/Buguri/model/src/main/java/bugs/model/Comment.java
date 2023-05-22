package bugs.model;

import javax.persistence.*;
import java.time.LocalDateTime;

@Entity
@Table(name="comments")
public class Comment extends Identifiable<Integer> {
    private String text;
    private LocalDateTime date;

    @ManyToOne
    @JoinColumn(name="employee_id", nullable=false)
    private Employee employee;

    public Comment() {}

    public Comment(Integer id, String text, LocalDateTime date) {
        super(id);
        this.text = text;
        this.date = date;
    }

    public Comment(String text, LocalDateTime date, Employee employee) {
        super(0);
        this.text = text;
        this.date = date;
        this.employee = employee;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public Employee getEmployee() {
        return employee;
    }

    public void setEmployee(Employee employee) {
        this.employee = employee;
    }

    @Override
    public String toString() {
        return "Comment{" +
                "id=" + this.getId().toString() + '\'' +
                "text='" + text + '\'' +
                ", date=" + date +
                ", employee=" + employee +
                '}';
    }
}

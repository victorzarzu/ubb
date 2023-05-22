package bugs.model;

import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name="bugs")
public class Bug extends Identifiable<Integer> {
    private String name;
    private String description;
    private BugStatus status;
    private LocalDateTime date;
    private BugPriority priority;
    @OneToMany(cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    private Set<Comment> comments = new HashSet<>();
    @ManyToOne
    @JoinColumn(name="tester_id")
    private Tester tester;

    @ManyToOne
    @JoinColumn(name = "programmer_id")
    private Programmer programmer;

    public Bug() {};

    public Bug(String name, String description, BugStatus status, LocalDateTime date, BugPriority priority, Tester tester, Programmer programmer) {
        this.name = name;
        this.description = description;
        this.status = status;
        this.date = date;
        this.priority = priority;
        this.tester = tester;
        this.programmer = programmer;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public BugStatus getStatus() {
        return status;
    }

    public void setStatus(BugStatus status) {
        this.status = status;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public BugPriority getPriority() {
        return priority;
    }

    public void setPriority(BugPriority priority) {
        this.priority = priority;
    }

    public Set<Comment> getComments() {
        return comments;
    }

    public void setComments(Set<Comment> comments) {
        this.comments = comments;
    }

    public void addComment(Comment comment) {
        comments.add(comment);
    }

    public Tester getTester() {
        return tester;
    }

    public void setTester(Tester tester) {
        this.tester = tester;
    }

    public String getProgrammerUsername() {
        return this.programmer.getUsername();
    }

    public Programmer getProgrammer() {
        return programmer;
    }

    public void setProgrammer(Programmer programmer) {
        this.programmer = programmer;
    }

    @Override
    public String toString() {
        return "Bug{" +
                "id=" + getId() + " " +
                "name='" + name + '\'' +
                ", description='" + description + '\'' +
                ", status=" + status +
                ", date=" + date +
                ", priority=" + priority +
                ", comments=" + comments +
                ", tester=" + tester +
                ", programmer=" + programmer +
                '}';
    }
}

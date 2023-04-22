package bugs.model;

import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name="bugs")
public class Bug extends Identifiable<Integer>{
    private String name;
    private String description;
    private BugStatus status;
    private LocalDateTime date;
    private BugPriority priority;
    @OneToMany(mappedBy = "bug", cascade = CascadeType.ALL)
    private Set<Comment> comments = new HashSet<>();
    @ManyToOne
    @JoinColumn(name="tester_id")
    private Tester tester;

    @ManyToOne
    @JoinColumn(name = "programmer_id")
    private Programmer programmer;

    public Bug() {}

    public Bug(Integer id, String name, String description, BugStatus status, LocalDateTime date, BugPriority priority, Set<Comment> comments, Programmer programmer) {
        super(id);
        this.name = name;
        this.description = description;
        this.status = status;
        this.date = date;
        this.priority = priority;
        this.comments = comments;
        this.programmer = programmer;
    }

    public Bug(Integer id, String name, String description, BugStatus status, LocalDateTime date, BugPriority priority, Programmer programmer) {
        super(id);
        this.name = name;
        this.description = description;
        this.status = status;
        this.date = date;
        this.priority = priority;
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
        comment.setBug(this);
    }

    public void removeComment(Comment comment) {
        comments.remove(comment);
        comment.setBug(null);
    }

    public Tester getTester() {
        return tester;
    }

    public void setTester(Tester tester) {
        this.tester = tester;
    }

    public Programmer getProgrammer() {
        return programmer;
    }

    public String getProgrammerUsername() {
        return programmer.getUsername();
    }

    public void setProgrammer(Programmer programmer) {
        this.programmer = programmer;
    }
}

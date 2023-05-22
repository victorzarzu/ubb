package bugs.model;

import javax.persistence.*;
import java.util.Set;

@Entity
@Table(name="programmers")
@PrimaryKeyJoinColumn(name="id", referencedColumnName="id")
@DiscriminatorValue("programmer")
public class Programmer extends Employee {

    @OneToMany(mappedBy = "programmer", cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    private Set<Bug> assignedBugs;

    public Set<Bug> getAssignedBugs() {
        return assignedBugs;
    }

    public void setAssignedBugs(Set<Bug> assignedBugs) {
        this.assignedBugs = assignedBugs;
    }

    public void addAssignedBug(Bug bug) {
        this.assignedBugs.add(bug);
    }

    public void removeAssignedBug(Bug bug) {
        this.assignedBugs.remove(bug);
    }

    //    public Employee(Integer id, String name, String username, String password) {
//        super(id, name, username, password);
//    }
}
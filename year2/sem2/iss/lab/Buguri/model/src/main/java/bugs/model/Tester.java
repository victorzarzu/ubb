package bugs.model;

import org.springframework.transaction.annotation.Transactional;

import javax.persistence.*;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name="testers")
@PrimaryKeyJoinColumn(name="id", referencedColumnName="id")
@DiscriminatorValue("tester")
public class Tester extends Employee {

    @OneToMany(mappedBy = "tester", cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    private Set<Bug> bugs = new HashSet<>();

    @Transactional
    public Set<Bug> getBugs() {
        return bugs;
    }

    @Transactional
    public void setBugs(Set<Bug> bugs) {
        this.bugs = bugs;
    }

    public void addBug(Bug bug) {
        bugs.add(bug);
        bug.setTester(this);
    }

    public void removeBug(Bug bug) {
        bugs.remove(bug);
        bug.setTester(null);
    }
}
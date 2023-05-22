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

    public Set<Bug> getBugs() {
        return bugs;
    }

    public void setBugs(Set<Bug> bugs) {
        this.bugs = bugs;
    }

    @Transactional
    public void addBug(Bug bug) {
        bugs.add(bug);
        bug.setTester(this);
    }

    @Transactional
    public void removeBug(Bug bug) {
        bugs.remove(bug);
    }

    @Transactional
    public void modifyBug(Bug bug) {
        // Find the bug to modify based on its id
        Bug existingBug = bugs.stream()
                .filter(b -> b.getId().equals(bug.getId()))
                .findFirst()
                .orElse(null);
        if (existingBug != null) {
            System.out.println("dadadaadaad" + existingBug);
            // Update the bug's properties with the new values
            existingBug.setName(bug.getName());
            existingBug.setDescription(bug.getDescription());
            existingBug.setStatus(bug.getStatus());
            existingBug.setDate(bug.getDate());
            existingBug.setPriority(bug.getPriority());
            existingBug.setProgrammer(bug.getProgrammer());
        }
    }
}
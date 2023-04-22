package bugs.model;

import javax.persistence.DiscriminatorValue;
import javax.persistence.Entity;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;

@Entity
@Table(name="programmers")
@PrimaryKeyJoinColumn(name="id", referencedColumnName="id")
@DiscriminatorValue("programmer")
public class Programmer extends Employee {

//    public Employee(Integer id, String name, String username, String password) {
//        super(id, name, username, password);
//    }
}
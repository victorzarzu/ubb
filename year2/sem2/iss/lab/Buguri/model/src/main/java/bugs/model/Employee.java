package bugs.model;

import javax.persistence.*;

@Entity
@Table(name="employees")
@PrimaryKeyJoinColumn(name="id", referencedColumnName="id")
@DiscriminatorValue("employee")
public class Employee extends User {

//    public Employee(Integer id, String name, String username, String password) {
//        super(id, name, username, password);
//    }
}

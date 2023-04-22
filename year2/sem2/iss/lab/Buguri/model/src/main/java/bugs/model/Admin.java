package bugs.model;

import javax.persistence.DiscriminatorValue;
import javax.persistence.Entity;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Table;

@Entity
@Table(name="admins")
@PrimaryKeyJoinColumn(name="id", referencedColumnName="id")
@DiscriminatorValue("admin")
public class Admin extends User {

}

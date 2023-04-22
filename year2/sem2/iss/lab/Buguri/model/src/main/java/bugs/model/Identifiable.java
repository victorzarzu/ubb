package bugs.model;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;

@MappedSuperclass
public class Identifiable<ID> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private ID id;

    public Identifiable() {}

    /**
     * Default constructor.
     *
     * @param id
     */
    public Identifiable(ID id) {
        this.id = id;
    }

    /**
     * Method to get the id of the entity.
     * @return the id of the entity
     */
    public ID getId() {
        return id;
    }

    /**
     * Method to set the id of the entity.
     * @param id the id of the entity
     */
    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        Identifiable other = (Identifiable) obj;
        if (id == null) {
            if (other.id != null) {
                return false;
            }
        } else if (!id.equals(other.id)) {
            return false;
        }
        return true;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 7;
        result = prime * result + ((id == null) ? 0 : id.hashCode());
        return result;
    }
}

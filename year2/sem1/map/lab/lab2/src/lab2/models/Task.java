package lab2.models;

import java.util.Objects;

public abstract class Task {
    private String taskID;
    private String descriere;

    public Task(final String taskID, final String descriere) {
        this.taskID = taskID;
        this.descriere = descriere;
    }

    public String getTaskID() {
        return taskID;
    }

    public void setTaskID(String taskID) {
        this.taskID = taskID;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public abstract void execute();

    @Override
    public String toString() {
        return "id=" + this.getTaskID() + "descriere=" + this.getDescriere();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this) {
            return true;
        }
        if(!(obj instanceof Task)) {
            return false;
        }

        Task task = (Task)obj;
        return Objects.equals(this.taskID, task.taskID) && Objects.equals(this.descriere, task.descriere);
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.getTaskID(), this.getDescriere());
    }
}

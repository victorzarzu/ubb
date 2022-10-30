package sum3_s.domain;

import java.util.Objects;

public class Student {
    private String nume;
    private float average;

    public Student(String nume, float average) {
        this.nume = nume;
        this.average = average;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.nume, this.average);
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this) {
            return true;
        }
        if(!(obj instanceof Student)) {
            return false;
        }
        Student student = (Student) obj;

        return Objects.equals(this.nume, student.nume) && Float.compare(this.average, student.average) == 0;
    }

    @Override
    public String toString() {
        return "Student{" +
                "nume='" + nume + '\'' +
                ", average=" + average +
                '}';
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public float getAverage() {
        return average;
    }

    public void setAverage(float average) {
        this.average = average;
    }
}

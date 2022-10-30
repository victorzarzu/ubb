package sum3_s;

import sum3_s.domain.Student;

import java.util.Collection;
import java.util.HashSet;

public class TestRunner {
    private static Student[] initStudents() {
        Student s1 = new Student("Dan", 4.5f);
        Student s2 = new Student("Ana", 8.5f);
        Student s3 = new Student("Dan", 4.5f);

        return new Student[]{s1, s2, s3};
    }

    private static void runHashSet() {
        System.out.println("\nHashSet");
        HashSet<Student> hashSet = new HashSet<>();
        Student[] students = initStudents();

        for(Student student : students) {
            hashSet.add(student);
        }

        for(Student student : hashSet) {
            System.out.println(student);
        }
    }

    public static void Run() {
        runHashSet();
    }
}

package lab2.models;

import lab2.logic.factory.SorterFactory;
import lab2.utils.sorter.AbstractSorter;
import lab2.utils.sorter.SortingStrategy;

import java.util.Arrays;

public class SortingTask extends Task {
    private AbstractSorter sorter;
    private int[] array;

    public SortingTask(String taskID, String descriere, SortingStrategy strategy, int[] array) {
        super(taskID, descriere);
        this.sorter = SorterFactory.getInstance().createSorter(strategy);
        this.array = array;
    }

    @Override
    public void execute() {
        sorter.sort(array);
        System.out.println(Arrays.toString(array));
    }

    @Override
    public String toString() {
        return super.toString() + "sortare";
    }
}

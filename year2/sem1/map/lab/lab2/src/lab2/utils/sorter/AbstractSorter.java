package lab2.utils.sorter;

public abstract class AbstractSorter {

    protected static void swap(int[] array, int i, int j)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public abstract int[] sort(int[] array);
}

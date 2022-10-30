package utils.sorter;

public class QuickSorter extends AbstractSorter {

    private static int partition(int[] array, int left, int right) {
        int pivot = array[right];
        int index = left - 1;
        for(int i = left;i < right;++i) {
            if(array[i] < pivot) {
                ++index;
                swap(array, index, i);
            }
        }
        swap(array, index + 1, right);

        return index + 1;
    }

    private static void quickSort(int[] array, int left, int right) {
        if(left < right) {
            int pivot = partition(array, left, right);

            quickSort(array, left, pivot - 1);
            quickSort(array, pivot + 1, right);
        }
    }

    public int[] sort(int[] array) {
        quickSort(array, 0, array.length - 1);
        return array;
    }
}

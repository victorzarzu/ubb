package utils.sorter;

public class BubbleSorter extends AbstractSorter {
    public int[] sort(int[] array) {
        boolean found = false;
        do{
            found = false;
            for(int i = 0;i < array.length - 1;++i) {
                if(array[i] > array[i + 1]) {
                    swap(array, i, i + 1);
                    found = true;
                }
            }

        } while(found);

        return array;
    }
}

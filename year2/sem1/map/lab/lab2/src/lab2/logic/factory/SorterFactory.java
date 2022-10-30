package lab2.logic.factory;

import lab2.utils.sorter.AbstractSorter;
import lab2.utils.sorter.BubbleSorter;
import lab2.utils.sorter.QuickSorter;
import lab2.utils.sorter.SortingStrategy;

public class SorterFactory {

    private static SorterFactory instance = new SorterFactory();
    public AbstractSorter createSorter(SortingStrategy strategy) {
        AbstractSorter sorter;
        if (strategy == SortingStrategy.BUBBLE) {
            sorter = new BubbleSorter();
        }
        sorter = new QuickSorter();
        return sorter;
    }

    public static SorterFactory getInstance() {
       return instance;
    }
}

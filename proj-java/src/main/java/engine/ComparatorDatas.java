package engine;


/**
 * Comparator pela data do Post
 *
 */

import java.util.Comparator;
import java.io.Serializable;
import java.time.LocalDate;

public class ComparatorDatas implements Comparator<LocalDate>, Serializable{
    public int compare(LocalDate d1, LocalDate d2){ 
        if(d1.isBefore(d2)) return -1;
        if(d1.isAfter(d2)) return 1;
        else return 0;
    }
}

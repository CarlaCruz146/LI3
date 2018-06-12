package engine;

 /*
 * Comparator pela Rep do User
 *
 */

import java.util.Comparator;
import java.io.Serializable;
import java.time.LocalDate;

public class ComparatorUserRep implements Comparator<User>, Serializable{
    public int compare(User u1, User u2){
        int s1, s2;
        s1 = u1.getUserRep();
        s2 = u2.getUserRep();	
        if(s1 == s2) return 1;
        if(s1>s2) return -1;
        else return 1;
    }
}
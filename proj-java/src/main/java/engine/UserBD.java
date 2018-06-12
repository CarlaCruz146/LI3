package engine;

/**
 * Classe que contém a implementação da base de dados dos Users
 *
 * @author Grupo 51
 */

import java.util.Map;
import java.util.HashMap;
import java.util.Collection;
import java.util.stream.Collectors;

public class UserBD {

    private HashMap<Long,User> usermap;

    public UserBD(){
        this.usermap = new HashMap<Long,User>();
    }

    public UserBD(HashMap<Integer,User> u){
        HashMap<Integer,User> usermap = new HashMap<>();
        u.entrySet().stream().forEach(entry -> usermap.put(entry.getKey(), entry.getValue().clone()));
    }

    public UserBD(UserBD u){
        usermap = u.getUserMap();
    }

    public void clear(){
        this.usermap.clear();
    }

    public User getUser(long id){
        return this.usermap.get(id);
    }
    
    public void addUser(User u){
        this.usermap.put(u.getUserId(),u.clone());
    }
    
    public HashMap<Long,User> getUserMap(){
        HashMap<Long,User> usermap = new HashMap<>();
        this.usermap.entrySet().stream().forEach(entry -> usermap.put(entry.getKey(), entry.getValue().clone()));
        return usermap;
    }
    
    public UserBD clone(){
        return new UserBD(this);
    }
    
    public boolean equals(Object o){
        if(this==o) return true;
        
        if(o==null || o.getClass() != this.getClass()) return false;
        
        UserBD bd = (UserBD) o;
        return bd.getUserMap().equals(this.usermap);
    }
}
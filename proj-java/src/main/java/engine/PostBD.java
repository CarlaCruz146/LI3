package engine;

/**
 * Classe que contém a implementação da base de dados dos Users
 *
 * @author Grupo 51
 */

import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.ArrayList;
import java.util.Collection;
import java.util.stream.Collectors;
import java.time.LocalDate;
import java.util.Vector;

public class PostBD {

    private HashMap<Long,Post> postmap;
    private TreeMap<LocalDate,ArrayList<Post>> postdatas;
    

    public PostBD(){
        this.postmap = new HashMap<Long,Post>();
        this.postdatas = new TreeMap<LocalDate,ArrayList<Post>>(new ComparatorDatas());
    }

    public PostBD(HashMap<Long,Post> p, TreeMap<LocalDate,ArrayList<Post>> d){
        postmap = new HashMap<Long,Post>();
        p.entrySet().stream().forEach(entry -> postmap.put(entry.getKey(), entry.getValue().clone()));
        postdatas = new TreeMap<LocalDate,ArrayList<Post>>();
        
    }

    public PostBD(PostBD p){
        postmap = p.getPostMap();
        postdatas = p.getPostDatas();
    }

    public void clear(){
        this.postmap.clear();
        this.postdatas.clear();
    }
    
    public void addPost(Post p){
        ArrayList<Post> posts = null;
        this.postmap.put(p.getPostId(),p.clone());
        if(this.postdatas.containsKey(p.getPostDate())){
            this.postdatas.get(p.getPostDate()).add(p.clone());
        }
        else {
            posts = new ArrayList<>();
            posts.add(p.clone());
            this.postdatas.put(p.getPostDate(), posts);
        }
    }
    
    public HashMap<Long,Post> getPostMap(){
        HashMap<Long,Post> postmap = new HashMap<>();
        this.postmap.entrySet().stream().forEach(entry -> postmap.put(entry.getKey(), entry.getValue().clone()));
        return postmap;
    }
    
    public TreeMap<LocalDate,ArrayList<Post>> getPostDatas(){
        TreeMap<LocalDate,ArrayList<Post>> postdatas = new TreeMap<>();
        for(Map.Entry<LocalDate,ArrayList<Post>> a: this.postdatas.entrySet())
            postdatas.put(a.getKey(),a.getValue());
        return postdatas;
    }
    
    public PostBD clone(){
        return new PostBD(this);
    }
    
    
    
    public boolean equals(Object o){
        if(this==o) return true;
        
        if(o==null || o.getClass() != this.getClass()) return false;
        
        PostBD bd = (PostBD) o;
        return (bd.getPostMap().equals(this.postmap) && bd.getPostDatas().equals(this.postdatas));
    }
}
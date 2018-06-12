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

public class TagBD {

    private HashMap<Long,Tag> tagmap;

    public TagBD(){
        this.tagmap = new HashMap<Long,Tag>();
    }

    public TagBD(HashMap<Long,Tag> t){
        HashMap<Long,Tag> tagmap = new HashMap<>();
        t.entrySet().stream().forEach(entry -> tagmap.put(entry.getKey(), entry.getValue().clone()));
    }

    public TagBD(TagBD u){
        tagmap = u.getTagMap();
    }

    public void clear(){
        this.tagmap.clear();
    }
    
    public void addTag(Tag u){
        this.tagmap.put(u.getTagId(),u.clone());
    }
    
    public HashMap<Long,Tag> getTagMap(){
        HashMap<Long,Tag> tagmap = new HashMap<>();
        this.tagmap.entrySet().stream().forEach(entry -> tagmap.put(entry.getKey(), entry.getValue().clone()));
        return tagmap;
    }
    
    public TagBD clone(){
        return new TagBD(this);
    }
    
    public boolean equals(Object o){
        if(this==o) return true;
        
        if(o==null || o.getClass() != this.getClass()) return false;
        
        TagBD bd = (TagBD) o;
        return bd.getTagMap().equals(this.tagmap);
    }
}
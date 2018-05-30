/**
 * Classe que contém a implementação da estrutura geral TCD
 *
 * @author Grupo 51
 */

import java.util.ArrayList;
import java.time.LocalDate;
import java.util.Set;
import java.util.TreeSet;

public class TCD{
    private Set<Post> posts;
    private Set<User> users;
    private Set <Tag> tags;

    /**
     * Construtor vazio
     */
    public TCD(){
        this.posts = new TreeSet<>();
        this.users = new TreeSet<>();
        this.tags = new TreeSet<>();
    }
    /**
     * Contrutor parametizado
     * @param Set<Post> posts
     * @param Set<User> users
     * @param Set<Tag> tags
     */
    public TCD (Set<Post> postsp,Set<User> usersp, Set<Tag> tagsp){
        this.posts = new TreeSet<>();
        postsp.forEach(a->this.posts.add(a));
        
        this.users = new TreeSet<>();
        usersp.forEach(a->this.users.add(a));
        
        this.tags = new TreeSet<>();
        tagsp.forEach(a->this.tags.add(a));
    }

    /**
     * Contrutor por cópia
     * @param TCD TCD
     */
    public TCD(TCD community){
        this.posts = community.getTCDPosts();
        this.users = community.getTCDUsers();
        this.tags = community.getTCDTags();
    }

    /**
     * Devolve o set com todos os posts
     * @return Set<Post>
     */
    public Set<Post> getTCDPosts(){
        return this.posts;
    }

    /**
     * Devolve o set com todos os users
     * @return Set<User>
     */
    public Set<User> getTCDUsers(){
        return this.users;
    }

    /**
     * Devolve o set com todos as tags
     * @return Set<Tag>
     */
    public Set<Tag> getTCDTags(){
        return this.tags;
    }

}
/**
 * Classe que contém a implementação da estrutura dos Users
 *
 * @author Grupo 51
 */

import java.util.ArrayList;
import java.time.LocalDate;

public class User {
    private long id;
    private int reputacao;
    private String nome;
    private String bio;
    private int nposts;
    private ArrayList<Post> uposts;

    /**
     * Construtor vazio
     */
    public User(){
        this.id = -2;
        this.reputacao = 0;
        this.nome = null;
        this.bio = null;
        this.nposts = 0;
        this.uposts = new ArrayList<>();
    }
    
    /**
    * Cria um User.
    *@param   long id do User.
    *@param   int reputação do User.
    *@param   String nome do User.
    *@param   String biografia do User.
    *@param   int número de Posts do User.
    *@param   ArrayList<Post> dos Posts do User.
    *@return  User criado.
    */
    public User(long id, int reputacao, String nome, String bio, int nposts, ArrayList<Post> uposts){
        this.id = id;
        this.reputacao = reputacao;
        this.nome = nome;
        this.bio = bio;
        this.nposts=nposts;
        this.uposts = new ArrayList<>();
        uposts.forEach(a->this.uposts.add(a));
    } 

    /**
     * Construtor por copia
     * @param User posts
     */
    public User(User g){
        this.id = g.getUserId();
        this.reputacao = g.getUserRep();
        this.nome = g.getUserName();
        this.bio = g.mygetUserBio();
        this.nposts = g.getUserNameNPosts();
        this.uposts = g.getUserPosts();
    }

    /**
     * Devolve o ID do user
     * @return long
     */
    public long getUserId(){
        return this.id;
    }

    /**
     * Devolve a reputação do user
     * @return int
     */
    public int getUserRep(){
        return this.reputacao;
    }

    /**
     * Devolve o nome do user
     * @return String
     */
    public String getUserName(){
        return this.nome;
    }

    /**
     * Devolve a bio do user
     * @return String
     */
    public String mygetUserBio(){
        return this.bio;
    }

    /**
     * Devolve o número de posts do user
     * @return int
     */
    public int getUserNameNPosts(){
        return this.nposts;
    }

    /**
     * Devolve os posts do user
     * @return ArrayList<Posts>
     */
    public ArrayList<Post> getUserPosts(){
        return this.uposts;
    }

    /**
    * Verifica a igualdade com outro objecto
    * @param o Objeto
    * @return boolean
    */
    public boolean equals(Object cont){
        if (this == cont) return true;
        if ( (cont == null) || (this.getClass() != cont.getClass()) ) return false;
        User c = (User) cont;
        return (this.id == c.getUserId() && this.nome.equals(c.getUserName()));
    }

    /**
     * Devolve uma cópia da instância
     * @return 
     */
    @Override
    public User clone(){
        return new User(this);
    }
}
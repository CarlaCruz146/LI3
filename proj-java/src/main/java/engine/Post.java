/**
 * Classe que contém a implementação da estrutura dos Posts
 *
 * @author Grupo 51
 */

import java.util.ArrayList;
import java.time.LocalDate;

public class Post{
    private long id;
    private int type;
    private long pid;
    private int score;
    private int vcount;
    private LocalDate date;
    private long owner;
    private int ownerRep;
    private int numcom;
    private int nres;
    private String titulo;
    private ArrayList<String> tag;
    private int ntags;
     /**
     * Construtor vazio
     */
    public Post(){
        this.id = -2;
        this.type = 0;
        this.pid = -2 ;
        this.score = 0;
        this.vcount = 0;
        this.date = null;
        this.owner = 0;
        this.ownerRep = 0;
        this.numcom = 0;
        this.nres = 0;
        this.titulo = null;
        this.tag = new ArrayList<>();
        this.ntags = 0;
    }
     /**
       * Construtor parametrizado
       *@param   long id do Post.
        *@param   int tipo do Post.
        *@param   long parent id do Post.
        *@param   int score do Post.
        *@param   int view count do Post.
        *@param   Date data de criação do Post.
        *@param   long id do User que criou o Post.
        *@param   int reputação do User que criou o Post.
        *@param   int número de comentários do Post.
        *@param   int de respostas do Post.
        *@param   String título do Post.
        *@param   ArrayList<String> array com as tags do Post.
        *@param   int número de tags do Post.
        *@return  Post criado.
     */
    public Post(long id, int type, long pid, int score, int vcount, LocalDate date, long owner, int ownerRep, int numcom, int nres, String titulo, ArrayList<String> tags, int ntags){
        this.id = id;
        this.type = type;
        this.pid = pid;
        this.score = score;
        this.vcount = vcount;
        this.date = date;
        this.owner = owner;
        this.ownerRep = ownerRep;
        this.numcom = numcom;
        this.nres = nres;
        this.titulo = titulo;
        this.tag = new ArrayList<>();
        tags.forEach(a->this.tag.add(a));
        this.ntags = ntags;
    }
    /**
     * Construtor por copia
     * @param Post posts
     */
    public Post(Post g){
        this.id = g.getPostId();
        this.type = g.getPostType();
        this.pid = g.getPid();
        this.score = g.getPostScore();
        this.vcount = g.getPostVCount();
        this.date = g.getPostDate();
        this.owner = g.getPostOwner();
        this.ownerRep = g.getPostOwnerRep();
        this.numcom = g.getPostNumCom();
        this.nres = g.getPostNRes();
        this.titulo = g.getPostTitulo();
        this.tag = g.getPostTags();
        this.ntags = g.getnTags();
    }

    /**
     * Devolve o ID
     * @return long
     */
    public long getPostId(){
        return this.id;
    }
    
    /**
     * Devolve o tipo do Post
     * @return int
     */
    public int getPostType(){
        return this.type;
    }

    /**
     * Devolve o Parent ID 
     * @return long
     */
    public long getPid(){
        return this.pid;
    }

    /**
     * Devolve o score 
     * @return int
     */
    public int getPostScore(){
        return this.score;
    }

    /**
     * Devolve o número de views
     * @return int
     */
    public int getPostVCount(){
        return this.vcount;
    }

    /**
     * Devolve a Data
     * @return LocalDate
     */
    public LocalDate getPostDate(){
        return this.date;
    }

    /**
     * Devolve o ID do owner
     * @return long
     */
    public long getPostOwner(){
        return this.owner;
    }

    /**
     * Devolve a reputação do owner
     * @return int
     */
    public int getPostOwnerRep(){
        return this.ownerRep;
    }

    /**
     * Devolve o número de comentários
     * @return int
     */
    public int getPostNumCom(){
        return this.numcom;
    }

    /**
     * Devolve o número de respostas
     * @return int
     */
    public int getPostNRes(){
        return this.nres;
    }
    
    /**
     * Devolve o título do post
     * @return String
     */
    public String getPostTitulo(){
        return this.titulo;
    }

    /**
     * Devolve as Strings com todas as tags
     * @return ArrayList<String>
     */
    public ArrayList<String> getPostTags(){
        return this.tag;
    }

    /**
     * Devolve o número de tags
     * @return int
     */
    public int getnTags(){
        return this.ntags;
    }

    /**
     * Devolve a tag da posição i
     * @return( String
     */
    public String getTagI(int i){
        ArrayList<String> ptr = new ArrayList<>();
        ptr = getPostTags();
        return ptr.get(i);
    }

    /**
    * Verifica a igualdade com outro objecto
    * @param o Objeto
    * @return boolean
    */
    public boolean equals(Object cont){
        if (this == cont) return true;
        if ( (cont == null) || (this.getClass() != cont.getClass()) ) return false;
        Post c = (Post) cont;
        return (this.id == c.getPostId() && this.type == c.getPostType() && this.pid==c.getPostOwner() && 
                this.owner == c.getPostOwner() && this.titulo.equals(c.getPostTitulo()) && 
                this.date.equals(c.getPostDate()));
      }

    /**
     * Devolve uma cópia da instância
     * @return 
     */
    @Override
    public Post clone(){
        return new Post(this);
    }
}

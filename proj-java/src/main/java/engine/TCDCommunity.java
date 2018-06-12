package engine;

/**
 * Classe que contém a implementação das interrogaçoes
 *
 * @author Grupo 51
 */

import common.MyLog;
import common.Pair;
import li3.TADCommunity;
import org.xml.sax.SAXException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import javax.xml.namespace.QName;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLStreamReader;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.LocalDate;
import java.util.Arrays;
import java.util.Map;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.TreeSet;
import java.util.TreeMap;
import java.util.Collections;
import java.util.Iterator;


public class TCDCommunity implements TADCommunity {
    private TCD com;
    private MyLog qelog;

    /**
     * Construtor de classe
     */
    public TCDCommunity(){
        this.com = new TCD();
        this.qelog = new MyLog("queryengine");
    }
    
    /**
     * Efetua o load das informações contidas nos ficheiros .xml para a estrutura
     * @param String path onde se encontram os ficheiros
     */
    public void load(String dumpPath) {
        try {
        SAXParserFactory xml = SAXParserFactory.newInstance();
        SAXParser saxParser = xml.newSAXParser();
        UserHandler userh = new UserHandler();
        PostHandler posth = new PostHandler();
        TagHandler tagh = new TagHandler();

        saxParser.parse(new File(dumpPath+"Users.xml"), userh);
        saxParser.parse(new File(dumpPath+"Posts.xml"), posth);
        saxParser.parse(new File(dumpPath+"Tags.xml"), tagh);
        
        

        for(User u: userh.getUsers().getUserMap().values())
            this.com.getUsers().addUser(u);

        for(Map.Entry<Integer,ArrayList<Post>> m: posth.getUserPosts().entrySet()){
            this.com.getUsers().getUser(m.getKey()).setUserNPosts(m.getValue().size());
            this.com.getUsers().getUser(m.getKey()).setUserPosts(m.getValue());
        }

        for(Post p: posth.getPosts().getPostMap().values())
            this.com.getPosts().addPost(p);

        for(Tag t: tagh.getTags().getTagMap().values())
            this.com.getTags().addTag(t);
        
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        }
    }

    // Query 1
    public Pair<String,String> infoFromPost(long id) {
        Pair<String,String> par = new Pair<>(null,null);     
        return par;
    }

    // Query 2
/*
    public List<Long> topMostActive(int N) {
    
    }
    */

    // Query 3
    /*
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        
    }
    */
    
    // Query 4
    /*
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
    }
*/
    // Query 5
     /*
    public Pair<String, List<Long>> getUserInfo(long id){
    }
*/

    // Query 6
   /*
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
    }
*/

        // Query 7
    /**
     * Dado um intervalo de tempo arbitrário devolver os id's das N perguntas com mais perguntas.
     * @param long Id do User
     * @param LocalDate data inicial
     * @param LocalDate data final
     * @return List<Long> com short bio do user e o id dos ultimos 10 posts
     */
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        TreeMap<LocalDate,ArrayList<Post>> posts = this.com.getPosts().getPostDatas();
        ArrayList<Post> datepost = null;
        Set<Post> retS = new TreeSet<>(new ComparatorPostNRes());

        while(!begin.equals(end.plusDays(1))){
            datepost = posts.get(begin);
            for(Post p : datepost){
                    retS.add(p);
            }
            begin = begin.plusDays(1);
        }
        List<Long> list = new ArrayList<>();
        List<Post> aux = new ArrayList<>();
        int i = 0;
        for(Post p : retS){
            aux.add(i,p);
            i++;
        }
        for(int j = 0; j < N; j++){
            list.add(j,Long.valueOf(aux.get(j).getPostId()));
        }
        return list;

    }

    // Query 8
    /**
     * Dado uma palavra devolver uma lista com is Id's das N perguntas cujo o titulo contenha
     * @param int N
     * @param String palavra 
     * @return List<Long> com todas as perguntas cujo título contenha a palavra
     */
    public List<Long> containsWord(int N, String word) {
        PostBD posts = com.getPosts();
        Set<Post> postsS = new TreeSet<>(new ComparatorPostDate());
        List<Post> aux = new ArrayList<>();
        List<Long> ret = new ArrayList<Long>();
        System.out.println("oi");
        for(Post p : posts.getPostMap().values()){
            if(p.getPostType() == 1 && p.getPostTitulo().contains(word))
                postsS.add(p);   
        }
        int i = 0;
        for(Post p : postsS){
            aux.add(i,p.clone());
            i++;
        }
        for(i = 0; i < N; i++)
           ret.add(i,aux.get(i).getPostId());

        return ret;
    }

    // Query 9
    /**
    *@brief   Retorna as últimas N perguntas (por ordem cronológica inversa) em que participaram dois utilizadores específicos.
    *@param   long id do user 1.
    *@param   long id do user 2.
    *@param   int N.
    *return   LONG_list ID's das perguntas.
    */
    public List<Long> bothParticipated (int N, long id1, long id2){
        Integer key1 = (int)(long)id1;
        Integer key2 = (int)(long)id2;
        ArrayList<Post> posts1 = new ArrayList<>((this.com.getUsers().getUserMap().get(id1).getUserPosts()));
        ArrayList<Post> posts2 = new ArrayList<>((this.com.getUsers().getUserMap().get(id2).getUserPosts()));

        Set<Integer> aux = new TreeSet<>();
        TreeSet<Post> setaux = new TreeSet<Post>(new ComparatorPostDate());

        for(Post p1 : posts1)
            for(Post p2 : posts2){
                if(p1.getPostType() == 2 && p2.getPostType() == 1 && p2.getPostId() == p1.getPostPid())
                    setaux.add(p2.clone());
                 
                if(p1.getPostType() == 1 && p2.getPostType() == 2 && p2.getPostPid() == p1.getPostId())   
                    setaux.add(p1.clone());

                if(p1.getPostType() == 2 && p2.getPostType() == 2 && p2.getPostPid() == p1.getPostPid()){
                    Post p3 = this.com.getPosts().getPostMap().get(p1.getPostPid());
                    setaux.add(p3.clone());
                }

            }
        List<Long> res = new ArrayList<>();
        Post post = null;

        Iterator<Post> it = setaux.iterator();

        int i = 0;
        while(it.hasNext() && i<N){
            post = it.next();
            post = setaux.first();
            res.add(post.getPostId());
            i++;
        }

        return res;
    }
    
    // Query 10
    /**
     * Dado o id de um post obter a melhor resposta
     * @param long id do post 
     * @return long id da melhor resposta
     */
    public long betterAnswer(long id){
        Map<Long,Post> posts = com.getPosts().getPostMap();
        Set<Post> sposts = new HashSet<>();
        long ret = -1;
        double x, media = 0;
        for(Post p : posts.values())
            if(p.getPostType()==2 && p.getPostPid()==id){
                sposts.add(p);
                
            }
        if(sposts != null){
            for(Post p : sposts){
                x = ((p.getPostScore()*0.65) + (com.getUsers().getUser(p.getPostOwner()).getUserRep()*0.25) + (p.getPostNumCom()*0.1));
                if(x>media){ 
                    media = x;
                    ret = p.getPostId();
                }
            }
        }
        return ret;        
    }

    //Query 11
    /*
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
    
    }
    */

    public void clear(){
        this.com.clear();
    }
    
    
}

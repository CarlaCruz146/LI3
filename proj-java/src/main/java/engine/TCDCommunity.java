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
/*
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
    }
*/
    // Query 8
    /*
    public List<Long> containsWord(int N, String word) {
    }
    */

    // Query 9
   /*
    public List<Long> bothParticipated (int N, long id1, long id2){
    }
    
    */

    // Query 10
    /*
    public long betterAnswer(long id){     
    }
*/

    //Query 11
    /*
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
    
    }
    */

    public void clear(){
        this.com.clear();
    }
    
    
}

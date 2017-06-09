package dcc.daa;

import java.io.*;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

public class Main {

    static String sigma = "abcdefghijklmnopqrstuvwxyz";

    public static void main(String[] args) throws IOException{

        Path inputPath = Paths.get(args[0]);
        File input = new File(inputPath.toString());
        String pattern = args[1];

        /*
        int patternLength = pattern.length();

        int [][] dfaTransitionFunction = getTransitionFunction(pattern);


        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < patternLength+1; j++) {
                System.out.print(dfaTransitionFunction[i][j]+" ");
            }
            System.out.println("\n");
        }
        */

        System.out.println(countAppearances(pattern, input));
    }

    public static int countAppearances(String pattern, File input) throws IOException{
        /*
        * The whole point of this is not running out of memory while reading the file.
        * Tested it with a 1Gb file, worked out fine.
        * */
        BufferedReader reader = new BufferedReader( new InputStreamReader( new FileInputStream(input)));

        int [][] dfa = getTransitionFunction(pattern);
        int state = 0;
        int occurrences = 0;
        int c;
        while((c = reader.read()) != -1) {
            char character = (char) c;
            /*
            * This condition will be used until we decide on a "cleaned" text format.
            * */
            if(sigma.indexOf(character) != -1){
                state = dfa[sigma.indexOf(character)][state];
                if(state == pattern.length()){
                    occurrences++;
                }
            }
        }
        return occurrences;
    }

    /*
    * First assumption made by our model: the alphabet is the english alphabet so no need
    * to use this function to compute it. Decided this because it will take a long time to compute
    * this for large inputs. No time to waste!!
    * */
    public static int distinctSymbolsInPattern(String pattern){
        Set<Character> s = new HashSet<>();
        for (char c: pattern.toCharArray()) {
            s.add(c);
        }
        return s.size();
    }

    public static int[][] getTransitionFunction(String pattern){
        int patternLength = pattern.length();
        int alphabetSize = sigma.length();
        int [][] transitionFunction = new int [alphabetSize][patternLength+1];

        /*
        * Initial conditions:
        * */
        for (int i = 1; i < alphabetSize; i++) {
            transitionFunction[i][0] = 0;
        }

        /*
        * Match transition:
        * */
        int index;
        for (int i = 0; i < patternLength; i++) {
            index = sigma.indexOf(pattern.charAt(i));
            transitionFunction[index][i] = i+1;
        }

        /*
        * We need to set the transitions of accept state.
        * These need to be same as the start state.
        * */
        for (int i = 0; i < alphabetSize; i++) {
            transitionFunction[i][patternLength] = transitionFunction[i][0];
        }


        /*
        * Mismatch transition:
        * */
        int x = 0;
        for (int j = 1; j < patternLength; j++) {
            for (int i = 0; i < alphabetSize; i++) {
                if(sigma.charAt(i) != pattern.charAt(j)){
                    transitionFunction[i][j] = transitionFunction[i][x];
                }
            }
            x = transitionFunction[sigma.indexOf(pattern.charAt(j))][x];
        }

        return transitionFunction;
    }
}

package dcc.daa;

import java.io.IOException;
import java.nio.channels.FileChannel;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

public class Main {

    static String sigma = "abcdefghijklmnopqrstuvwxyz";

    public static void main(String[] args) throws IOException{

        Path inputPath = Paths.get(args[0]);
        FileChannel input = FileChannel.open(inputPath);
        String pattern = args[1];

        int patternLength = pattern.length();

        int [][] dfaTransitionFunction = getTransitionFunction(pattern);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < patternLength; j++) {
                System.out.println(dfaTransitionFunction[i][j]);
            }
            System.out.println("-------------------");
        }
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
        int [][] transitionFunction = new int [alphabetSize][patternLength];

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
        * Mismatch transition:
        * */
        int x = 0;
        for (int j = 1; j < patternLength; j++) {
            for (int i = 0; i < alphabetSize; i++) {
                if(sigma.charAt(i) != pattern.charAt(j)){
                    transitionFunction[i][j] = transitionFunction[i][x];
                    x = transitionFunction[j][x];
                }
            }
        }

        return transitionFunction;
    }
}

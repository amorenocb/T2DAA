package dcc.daa;

import java.io.IOException;
import java.nio.channels.FileChannel;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

public class Main {


    public static void main(String[] args) throws IOException{

        Path inputPath = Paths.get(args[0]);
        FileChannel input = FileChannel.open(inputPath);
        String pattern = args[1];

        int patternLength = pattern.length();

        int [][] dfaTransitionFunction; //= new int[0][patternLength];

        System.out.println(distinctSymbolsInPattern(pattern));

    }

    public static int distinctSymbolsInPattern(String pattern){
        Set<Character> s = new HashSet<>();
        for (char c: pattern.toCharArray()) {
            s.add(c);
        }
        return s.size();
    }

    public static int[][] getTransitionFunction(String pattern){
        int patternLength = pattern.length();
        int distinctSymbols = distinctSymbolsInPattern(pattern);
        int [][] transitionFunction = new int [distinctSymbols][patternLength];

        for (char c: pattern.toCharArray()) {
            
        }
    }
}

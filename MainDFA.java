import java.io.*;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.*;
import java.util.stream.Stream;
import java.nio.file.Files;
import java.util.stream.Collectors;

import Utilities;

import static java.nio.file.StandardOpenOption.APPEND;
import static java.nio.file.StandardOpenOption.CREATE;

public class Main {

    static final String sigma = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ ";
    static Random randomGenerator = new Random();
    static Path resultPath = Paths.get("results.csv");
    static StringBuilder line = new StringBuilder();

    public static void main(String[] args) throws IOException{

        Path inputsFolderPath = Paths.get(args[0]);

        // Here we store the paths to all input files.
        List<Path> inputPaths;
        try (Stream<Path> paths = Files.walk(inputsFolderPath)) {
            inputPaths = paths.filter(Files::isRegularFile).collect(Collectors.toList());
        }

        for (Path aPath: inputPaths) {
            File input = new File(aPath.toString());
            File cleanedInput = textCleaner(input);

            System.out.println("Finished cleaning "+input.getName());

            List<String> testWords = getTestWords(cleanedInput);

            int wc = getWordCount(cleanedInput);

            for (String word: testWords) {
                line.setLength(0);
                line.append(wc);
                line.append(",");
                line.append(word);
                line.append(",");
                line.append(word.length());
                line.append(",");
                int appearances = countAppearances(word,cleanedInput);
                line.append(appearances);
                line.append(System.lineSeparator());
                Files.write(resultPath, line.toString().getBytes(), CREATE, APPEND);
            }
            System.out.println("Finished processing: "+input.getName());

        }


    }

    /*
    * Gets N/100 random words from input for testing.
    * @param File input : File object that contains a text file already pre processed. (See textCleaner)
    * @returns List<String> : Contains the N/100 words obtained at random from input.
    * */
    public static List<String> getTestWords(File input) throws IOException{
        int wordCount = getWordCount(input);
        int sampleSize = (int)Math.ceil(wordCount/100);
        long randomPointerLocation;
        RandomAccessFile raf = new RandomAccessFile(input, "r");
        StringBuilder wordToAdd = new StringBuilder();

        List<String> testWords = new ArrayList<>();
        while (testWords.size() < sampleSize) {
            try {
                wordToAdd.setLength(0);
                randomPointerLocation = Utilities.nextLong(randomGenerator, raf.length());
                raf.seek(randomPointerLocation);
                char c = (char)raf.read();
                if(c != ' '){
                    while (c != ' '){
                        c = (char)raf.read();
                    }

                    c = (char)raf.read();
                    while (c != ' '){
                        if(wordToAdd.length() > 100){
                            continue;
                        }
                        wordToAdd.append(c);
                        c = (char)raf.read();
                    }
                }
                else{
                    while (c == ' '){
                        c = (char)raf.read();
                    }
                    while (c != ' '){
                        if(wordToAdd.length() > 100){
                            continue;
                        }
                        wordToAdd.append(c);
                        c = (char)raf.read();
                    }
                }
                if(wordToAdd.length() > 0 ){
                    testWords.add(wordToAdd.toString());
                }

            }
            catch (EOFException e){
                continue;
            }
        }

        return testWords;

    }

    /*
    * Cleans an input text file. It deletes every non alphabetic character (e.g á) and replaces punctuations
    * with spaces. The same for line/paragraph separators.
    * @param File input : File object that contains a text file to be pre processed.
    * @returns File : File object that contains the cleaned version of the input file.
    * */
    public static File textCleaner(File input) throws IOException{
        Writer writer =
                new BufferedWriter(
                    new OutputStreamWriter(
                        new FileOutputStream(input.getName()+"Cleaned.txt"), "utf-8"));
        Scanner scanner = new Scanner(input);
        while(scanner.hasNextLine()){
            String line = scanner.nextLine();
            for (char c: line.toCharArray()) {
                if (Character.getType(c) == Character.LINE_SEPARATOR){
                    writer.write(" ");
                }
                else if (Character.getType(c) == Character.PARAGRAPH_SEPARATOR){
                    writer.write(" ");
                }
                else if(Character.getType(c) == Character.OTHER_PUNCTUATION){
                    if(c == '\''){
                        continue;
                    }
                    else{
                        writer.write(" ");
                    }

                }
                else if (sigma.indexOf(c) != -1){
                    if (Character.isUpperCase(c)){
                        writer.write(Character.toLowerCase(c));
                    }
                    else {
                        writer.write(c);
                    }
                }


            }
        }
        writer.write(" ");
        scanner.close();
        writer.close();
        File output = new File(input.getName()+"Cleaned.txt");
        return output;
    }

    /*
    * Counts the amount of words in File input. This file has to be previously pre processed by the
    * textCleaner function. Here we define a word as a sequence of characters in sigma with no character
    * space between it.
    * @param File input : File object that contains a text file already pre processed. (See textCleaner)
    * @returns int : word count for input file.
    * */
    public static int getWordCount(File input) throws IOException{
        Scanner scanner = new Scanner(input);
        scanner.useDelimiter(" ");
        int wc = 0;
        while (scanner.hasNext()) {
            String word = scanner.next();
            if(word.length() > 0){
                wc++;
            }
        }
        return wc;
    }

    /*
    * Counts the amount of appearances of the String pattern in the File input. It uses the getTransitionFunction
    * function to construct an DFA and then iterates through the File inputs characters one by one. Passing from one
    * state to another accordingly.
    * @param String pattern : The pattern we search for in File input.
    * @param File input : File object that contains a text file already pre processed. (See textCleaner)
    * */
    public static int countAppearances(String pattern, File input) throws IOException{
        /*
        * The whole point of this is not running out of memory while reading the file.
        * Tested it with a 1Gb file, worked out fine.
        * */
        BufferedReader reader = new BufferedReader( new InputStreamReader( new FileInputStream(input)));

        long currentTime = System.nanoTime();
        int [][] dfa = getTransitionFunction(pattern);
        long execTime = System.nanoTime() - currentTime;
        line.append(execTime);
        line.append(",");

        int state = 0;
        int occurrences = 0;
        int c;
        currentTime = System.nanoTime();
        while((c = reader.read()) != -1) {
            char character = (char) c;
            /*
            * This condition will be used until we decide on a "cleaned" text format.
            * */
            if(character != ' '){
                state = dfa[sigma.indexOf(character)][state];
                if(state == pattern.length()){
                    occurrences++;
                }
            }else{
                state = 0;
            }
        }
        execTime = System.nanoTime() - currentTime;
        line.append(execTime);
        line.append(",");
        return occurrences;
    }

    /*
    * Constructs the transition function for a DFA that is able to search in a text for the
    * String pattern. This corresponds to the Knuth-Morris-Pratt algorithm.
    * @param String pattern : The pattern that the corresponding DFA is going to search for in texts.
    * @returns int [][] : The representation of the transition function of the DFA. Here rows correspond
    * to what the DFA is currently seeing in the text, while the columns represent a character in the pattern.
    * So column j corresponds to the jth character in the pattern.
    * */
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

import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Part1 {
    static String[] patterns;
    static Set<String> patternSet = new HashSet<>();
    static Set<String> validSubstrings = new HashSet<>();
    static Set<String> invalidSubstrings = new HashSet<>();

    private static boolean validPattern(String towel) {
        if(towel.isEmpty()) {
            return true;
        }

        if(validSubstrings.contains(towel)) {
            return true;
        }

        if(invalidSubstrings.contains(towel)) {
            return false;
        }

        for(String pattern : patterns) {
            if(towel.startsWith(pattern)) {
                boolean validPattern = validPattern(towel.substring(pattern.length()));
                if(validPattern) {
                    validSubstrings.add(towel);
                    return true;
                }
                invalidSubstrings.add(towel);
            }
        }
        return false;
    }

    public static void main(String[] args) {
        try {
            File f = new File("C:\\Users\\langd\\OneDrive\\Desktop\\Advent of Code 2024 Day 19\\src\\input.txt");
            Scanner scanner = new Scanner(f);

            // Read in input from input file
            patterns = scanner.nextLine().split(", ");

            scanner.nextLine();
            int validPatterns = 0;
            while(scanner.hasNextLine()) {
                String towel = scanner.nextLine();
                if(validPattern(towel)) {
                    System.out.println(towel);
                    validPatterns++;
                }
            }

            System.out.println("Valid Patterns: " + validPatterns);


        } catch (FileNotFoundException fnfe) {
            System.out.println("Couldn't find input");
        }
    }
}
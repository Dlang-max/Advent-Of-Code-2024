import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;

public class Part2 {
    static String[] patterns;
    static Map<String, Long> waysToBuildSubstrings = new HashMap<>();

    private static long validPatterns(String towel) {
        if(towel.isEmpty()) {
            return 1;
        }

        if(waysToBuildSubstrings.containsKey(towel)) {
            return waysToBuildSubstrings.get(towel);
        }

        long validWays = 0;
        for(String pattern : patterns) {
            if(towel.startsWith(pattern)) {
                validWays += validPatterns(towel.substring(pattern.length()));
            }
        }

        waysToBuildSubstrings.put(towel, validWays);
        return validWays;
    }

    public static void main(String[] args) {
        try {
            File f = new File("./input.txt");
            Scanner scanner = new Scanner(f);

            // Read in input from input file
            patterns = scanner.nextLine().split(", ");

            scanner.nextLine();
            long waysToBuildValidPatterns = 0;
            while(scanner.hasNextLine()) {
                String towel = scanner.nextLine();
                waysToBuildValidPatterns += validPatterns(towel);
            }

            System.out.println("Ways to Build Valid Patterns: " + waysToBuildValidPatterns);


        } catch (FileNotFoundException fnfe) {
            System.out.println("Couldn't find input");
        }
    }
}

import java.util.*;
import java.io.*;


public class Part2 {
    public static final int PRUNE_FACTOR = 16777216;
    public static final int GENERATIONS = 2000;

    static Map<String, Integer> map = new HashMap<>();

    private static void generateSecretNumbers(long initial) {
        List<Integer> secretNumbers = new ArrayList<>();

        long curr = initial;
        secretNumbers.add((int)(curr % 10));
        for(int i = 0; i < GENERATIONS; i++) {
            curr = ((curr << 6) ^ curr) % PRUNE_FACTOR;
            curr = ((curr >> 5) ^ curr) % PRUNE_FACTOR;
            curr = ((curr << 11) ^ curr) % PRUNE_FACTOR;

            secretNumbers.add((int)(curr % 10));
        }

        Map<String, Integer> currMap = getSequenceScores(secretNumbers);
        for(Map.Entry<String, Integer> entry : currMap.entrySet()) {
            String key = entry.getKey();
            map.put(key, map.getOrDefault(key, 0) + entry.getValue());
        }
    }

    private static Map<String, Integer> getSequenceScores(List<Integer> secretNumbers) {
        Map<String, Integer> currMap = new HashMap<>();
        for(int i = 4; i < secretNumbers.size(); i++) {
            int a = secretNumbers.get(i - 4), b = secretNumbers.get(i - 3);
            int c = secretNumbers.get(i - 2), d = secretNumbers.get(i - 1);
            int e = secretNumbers.get(i);

            String key = (b - a) + "_" + (c - b) + "_" + (d - c) + "_" + (e - d);
            if(currMap.containsKey(key)) {
                continue;
            }
            currMap.put(key, e);
        }

        return currMap;
    }

    public static void main(String[] args) {
        try {
            File file = new File("./input.txt");
            Scanner scanner = new Scanner(file);

            while (scanner.hasNextLine()) {
                long initial = Long.parseLong(scanner.nextLine());
                generateSecretNumbers(initial);
            }

            int bananas = Integer.MIN_VALUE;
            for(Map.Entry<String, Integer> entry : map.entrySet()) {
                bananas = Math.max(bananas, entry.getValue());
            }
            System.out.println("Bananas: " + bananas);
        } catch (FileNotFoundException e) {
            System.out.println("File Not Found");
        }
    }
}
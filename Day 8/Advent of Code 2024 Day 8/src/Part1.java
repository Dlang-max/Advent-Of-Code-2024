import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

public class Part1 {
    public static final int ROWS = 50;
    private static final int COLS = 50;

    private static boolean inBounds(int row, int col) {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS;
    }


    public static void main(String[] args) {
        Map<Character, ArrayList<int[]>> map = new HashMap<>();
        Set<String> antinodes = new HashSet<>();

        try {
            File file = new File("./input.txt");
            Scanner scanner = new Scanner(file);

            int row = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                for(int col = 0; col < line.length(); col++) {
                    if (line.charAt(col) != '.') {
                        map.put(line.charAt(col), map.getOrDefault(line.charAt(col), new ArrayList<>()));
                        map.get(line.charAt(col)).add(new int[]{row, col});
                    }
                }
                row++;
            }
            scanner.close();

            for(Map.Entry<Character, ArrayList<int[]>> entry : map.entrySet()) {
                for(int i = 0; i < entry.getValue().size(); i++) {
                    for(int j = 0; j < entry.getValue().size(); j++) {
                        if(i == j) {
                            continue;
                        }

                        int[] antenna1 = entry.getValue().get(i);
                        int[] antenna2 = entry.getValue().get(j);

                        int dRow = antenna2[0] - antenna1[0];
                        int dCol = antenna2[1] - antenna1[1];

                        int antinodeRow = antenna1[0] + 2 * dRow;
                        int antinodeCol = antenna1[1] + 2 * dCol;

                        if(inBounds(antinodeRow, antinodeCol)) {
                            antinodes.add(antinodeRow + ":" + antinodeCol);
                        }
                    }
                }
            }

            System.out.println("Unique Antinodes: " + antinodes.size());


        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
    }
}

import java.util.*;
import java.io.*;
import java.io.FileNotFoundException;

public class Part1 {
    public static final int KEYPADS = 2;
    static Map<String, Long> memo = new HashMap<>();
    static char[][] dirKeypad = {{'#', '^', 'A'}, {'<', 'v', '>'}};
    static char[][] numericKeypad ={{'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'#', '0', 'A'}};

    private static int[] getKeypadPos(char key, char[][] keypad) {
        for(int i = 0; i < keypad.length; i++) {
            for(int j = 0; j < keypad[0].length; j++) {
                if(keypad[i][j] == key) {
                    return new int[]{i, j};
                }
            }
        }
        return new int[]{-1, -1};
    }

    private static List<String> minSequenceBetweenKeys(char k1, char k2, char[][] keypad) {
        List<String> paths = new ArrayList<>();
        int[] k1Pos = getKeypadPos(k1, keypad);
        int[] k2Pos = getKeypadPos(k2, keypad);

        int k1Row = k1Pos[0], k1Col = k1Pos[1];
        int k2Row = k2Pos[0], k2Col = k2Pos[1];
        int dRow = k2Row - k1Row, dCol = k2Col - k1Col;

        StringBuilder rowMoves = new StringBuilder();
        StringBuilder colMoves = new StringBuilder();
        // Get key presses to go dRow
        for(int i = 0; i < Math.abs(dRow); i++) {
            if(dRow > 0) {
                rowMoves.append('v');
            } else {
                rowMoves.append('^');
            }
        }
        // Get Key presses to go dCol
        for(int i = 0; i < Math.abs(dCol); i++) {
            if(dCol > 0) {
                colMoves.append('>');
            } else {
                colMoves.append('<');
            }
        }

        if(dRow == 0 && dCol == 0) {
            paths.add("");
            return paths;
        } else if (dRow == 0) {
            paths.add(colMoves.toString());
            return paths;
        } else if (dCol == 0) {
            paths.add(rowMoves.toString());
            return paths;
        } else if (keypad[k1Row][k2Col] == '#') {
            // To avoid the robot from entering a gap and panicking,
            // perform row moves first and then column moves.
            paths.add(rowMoves.toString() + colMoves.toString());
            return paths;
        } else if (keypad[k2Row][k1Col] == '#') {
            // To avoid the robot from entering a gap and panicking,
            // preform column moves first and then row moves.
            paths.add(colMoves.toString() + rowMoves.toString());
            return paths;
        } else {
            paths.add(rowMoves.toString() + colMoves.toString());
            paths.add(colMoves.toString() + rowMoves.toString());
            return paths;
        }
    }

    // Code: <<<^>>>v --> something like this
    private static long getMoves(String code, int depth) {
        if(depth == 1) {
            return code.length();
        }

        String memoKey = code + ":" + depth;
        if(memo.containsKey(memoKey)) {
            return memo.get(memoKey);
        }

        char[][] keypad = dirKeypad;
        if(code.matches(".*[0-9].*")) {
            keypad = numericKeypad;
        }

        // Always start from the "A" key
        long minMoves = 0;
        code = "A" + code;
        for(int i = 1; i < code.length(); i++) {
            char key1 = code.charAt(i - 1), key2 = code.charAt(i);
            List<String> minPressesPaths = minSequenceBetweenKeys(key1, key2, keypad);

            long currMinMoves = Long.MAX_VALUE;
            for(String path : minPressesPaths) {
                long moves = getMoves(path + "A", depth - 1);
                currMinMoves = Math.min(currMinMoves, moves);
                // Memoize results of getMoves to make computations more efficient
                memo.put(path + "A" + ":" + (depth - 1), moves);
            }
            minMoves += currMinMoves;
        }
        return minMoves;
    }


    public static void main(String[] args) {
        try {
            File file = new File("./input.txt");
            Scanner scanner = new Scanner(file);

            long totalMoves = 0;
            while(scanner.hasNextLine()) {
                String line = scanner.nextLine();
                int numericCode = Integer.parseInt(line.substring(0, 3));

                // 1: Directional keypad we're typing into
                // 2: Directional keypads robots are typing into
                // 1: Numerical keypad robot is typing into
                long moves = getMoves(line, 1 + KEYPADS + 1);
                totalMoves += numericCode * moves;
            }
            System.out.println("Total moves: " + totalMoves);
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }

    }
}

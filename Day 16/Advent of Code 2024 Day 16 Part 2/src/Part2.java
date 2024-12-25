import org.w3c.dom.Node;

import java.util.*;
import java.io.*;



public class Part2 {
    static class PosInfo {
        int[] nodeInfo;
        Set<String> path;

        public PosInfo(int[] nodeInfo) {
            this.nodeInfo = nodeInfo;
            this.path = new HashSet<>();
        }
    }

    public static final int DIRECTIONS = 4;
    public static final int MULTIPLIER = 1000;
    public static final int ROWS = 17;
    public static final int COLS = 17;

    public static Set<String> sittingPositions = new HashSet<>();
    public static char[][] grid = new char[ROWS][COLS];
    public static int sRow, sCol, eRow, eCol;

    public static Map<String, Integer> visited = new HashMap<>();

    private static void dijkstra() {
        int[] dRow = {0, 1, 0, -1};
        int[] dCol = {1, 0, -1, 0};

        // Curr Position : Position that got us here
        PriorityQueue<PosInfo> pq = new PriorityQueue<>((a, b) -> a.nodeInfo[3] - b.nodeInfo[3]);

        PosInfo sPosInfo = new PosInfo(new int[]{sRow, sCol, 0, 0});
        sPosInfo.path.add(sRow + ":" + sCol);
        pq.offer(sPosInfo);

        int lowestScore = Integer.MAX_VALUE;
        while(!pq.isEmpty()) {
            PosInfo curr = pq.poll();
            int row = curr.nodeInfo[0], col = curr.nodeInfo[1], dir = curr.nodeInfo[2], score = curr.nodeInfo[3];
            Set<String> currPath = curr.path;
            if(score > lowestScore) {
                break;
            }

            if(row == eRow && col == eCol) {
                lowestScore = score;
                sittingPositions.addAll(curr.path);
                continue;
            }

            if(!canVisit(row + ":" + col + ":" + dir, score)) {
                continue;
            }

            // Enqueue straight, clockwise turn, and counterclockwise turn
            int[] moves = {-1, 0, 1};
            for(int move : moves) {
                int nDir = (dir + move + DIRECTIONS) % DIRECTIONS;
                int nRow = row + dRow[nDir], nCol = col + dCol[nDir];
                int nScore = score + Math.abs(MULTIPLIER * move) + 1;

                String key = nRow + ":" + nCol + ":" + nDir;
                if(validPos(nRow, nCol) && canVisit(key, nScore)) {
                    PosInfo nPosInfo = new PosInfo(new int[]{nRow, nCol, nDir, nScore});
                    nPosInfo.path.addAll(currPath);
                    nPosInfo.path.add(nRow + ":" + nCol);
                    pq.offer(nPosInfo);
                }
            }
        }
    }

    private static boolean canVisit(String key, int score) {
        if(visited.containsKey(key) && visited.get(key) < score) {
            return false;
        }
        visited.put(key, score);
        return true;
    }

    private static boolean validPos(int row, int col) {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS && grid[row][col] != '#';
    }

    private static void fillGrid() {
        for(String pos : sittingPositions) {
            String[] split = pos.split(":");
            int row = Integer.parseInt(split[0]), col = Integer.parseInt(split[1]);
            grid[row][col] = 'O';
        }

    }

    private static void printGrid() {
        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COLS; j++) {
                System.out.print(grid[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        try {

            File f = new File("./input.txt");
            Scanner scanner = new Scanner(f);

            int row = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                for(int col = 0; col < COLS; col++) {
                    char c = line.charAt(col);
                    grid[row][col] = c;

                    // Get the start and end positions
                    if(c == 'S') {
                        sRow = row;
                        sCol = col;
                    } else if(c == 'E') {
                        eRow = row;
                        eCol = col;
                    }
                }
                row++;
            }
            dijkstra();
            fillGrid();
            printGrid();
            System.out.println("Unique Sitting Positions: " + sittingPositions.size());

        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
    }
}

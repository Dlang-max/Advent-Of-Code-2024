import java.util.*;
import java.io.*;


public class Part1 {
    public static Map<String, Integer> gateValues = new HashMap<>();
    public static List<String[]> queries = new ArrayList<>();

    private static void simulateAdder() {
        Deque<String[]> deque = new ArrayDeque<>();
        // Solve already solvable queries. Add unsolvable ones to a deque.
        for (String[] ios : queries) {
            String in1 = ios[0], in2 = ios[1], out = ios[2], opp = ios[3];
            if (gateValues.containsKey(in1) && gateValues.containsKey(in2)) {
                gateValues.put(out, calculateLogicGateOutput(in1, in2, opp));
            } else {
                deque.addLast(ios);
            }
        }

        // Process unanswered queries
        while(!deque.isEmpty()) {
            String[] query = deque.removeLast();
            if(gateValues.containsKey(query[0]) && gateValues.containsKey(query[1])) {
                calculateLogicGateOutput(query[0], query[1], query[3]);
                gateValues.put(query[2], calculateLogicGateOutput(query[0], query[1], query[3]));
            } else {
                deque.addFirst(query);
            }
        }
    }

    private static int calculateLogicGateOutput(String in1, String in2, String opp) {
        int output = 0;
        switch (opp) {
            case "AND":
                output = gateValues.get(in1) & gateValues.get(in2);
                break;

            case "OR":
                output = gateValues.get(in1) | gateValues.get(in2);
                break;

            case "XOR":
                output = gateValues.get(in1) ^ gateValues.get(in2);
                break;

            default:
                break;
        }
        return output;
    }


    public static void main(String[] args) {
        try {
            File f = new File("./input.txt");
            Scanner scanner = new Scanner(f);

            while(scanner.hasNextLine()) {
                String line  = scanner.nextLine();
                if(line.isEmpty()) {
                    continue;
                }

                if(line.charAt(3) == ':') {
                    String key = line.substring(0, 3);
                    int value = line.charAt(5) - '0';

                    gateValues.put(key, value);
                } else {
                    String[] ios = line.split(" ");
                    String[] query = new String[]{ios[0], ios[2], ios[4], ios[1]};
                    // ios[i] : in1, in2, out, opp
                    queries.add(query);
                }
            }
            long start = System.currentTimeMillis();
            simulateAdder();
            List<String> wires = new ArrayList<>(gateValues.keySet());
            Collections.sort(wires);

            long decimalAnswer = 0;
            for(int i = wires.size() - 1; i >= 0 && wires.get(i).charAt(0) == 'z'; i--) {
                decimalAnswer = (decimalAnswer << 1) | gateValues.get(wires.get(i));
            }

            System.out.println("Decimal Answer: " + decimalAnswer);
        } catch(FileNotFoundException e) {
            System.out.println("File not found");
        }

    }
}

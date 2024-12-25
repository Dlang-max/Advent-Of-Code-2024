import java.lang.reflect.Array;
import java.util.*;
import java.io.*;


public class Part2 {

    // Maps input wires and logic gates to output wires
    public static Map<String, String> inToOut = new HashMap<>();
    // Maps output wires to input wires and logic gates
    public static Map<String, String[]> outToIn = new HashMap<>();


    public static Map<String, Integer> gateValues = new HashMap<>();
    public static List<String[]> queries = new ArrayList<>();
    public static List<String> mismatchedWires = new ArrayList<>();

    private static void findWiringErrors() {
        // Check that all logic gates preceding wires beginning with 'z'
        // have "XOR" logic gates except "z45". Make sure "z45" has a preceding
        // logic gate of "OR"
        for(String wire : outToIn.keySet()) {
            if(wire.charAt(0) == 'z' && !checkXORPrecedesZWire(outToIn.get(wire))) {
                mismatchedWires.add(wire);
            }
        }

        for(String wire : outToIn.keySet()) {
            if(wire.charAt(0) != 'z' && outToIn.get(wire)[0].charAt(0) != 'x' &&
                                        outToIn.get(wire)[1].charAt(0) != 'y' &&
                                        outToIn.get(wire)[2].equals("XOR")) {
                mismatchedWires.add(wire);
            }
        }
        for(String mismatch : mismatchedWires) {
            System.out.println("Mismatched wire: " + mismatch);
        }
    }


    private static boolean checkXORPrecedesZWire(String[] input) {
       return input[2].equals("XOR") && !inToOut.get(Arrays.toString(input)).equals("z45") ||
              input[2].equals("OR") && inToOut.get(Arrays.toString(input)).equals("z45");
    }

    private static void processInputs() {
        Deque<String[]> deque = new ArrayDeque<>();
        for (String[] ios : queries) {
            String in1 = ios[0], in2 = ios[1], opp = ios[2];
            String out = inToOut.get(Arrays.toString(ios));
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
                String opp = query[2];
                calculateLogicGateOutput(query[0], query[1], opp);
                gateValues.put(inToOut.get(Arrays.toString(query)), calculateLogicGateOutput(query[0], query[1], opp));
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

                    // query array : {in1, in2, out, opp}
                    String[] query = {"~", "~", "~"};
                    query[0] = ios[0];
                    query[1] = ios[2];
                    Arrays.sort(query);
                    query[2] = ios[1];

                    String out = ios[4];

                    // Map inputs to outputs and outputs to inputs
                    // String : out
                    inToOut.put(Arrays.toString(query), out);
                    // out : String[]
                    outToIn.put(out, query);


                    queries.add(query);
                }
            }


            findWiringErrors();
            // Result of x + y should equal the result of passing x and y through the adder.
            // After you find mismatched wires, swap them in input.txt and run again. The remaining
            // mismatched gates are located where the result of z ^ adderResult equal 1. Fix the two
            // remaining mismatched gates. Note down the gates we've swapped, sort them, and add commas
            // between each. This is the solution to the problem.
            long x = 24408943247053L;
            long y = 23256441849881L;
            long z = x + y;
            System.out.println("Z: " + z);

            processInputs();
            List<String> wires = new ArrayList<>(gateValues.keySet());
            Collections.sort(wires);

            long adderResult = 0;
            for(int i = wires.size() - 1; i >= 0 && wires.get(i).charAt(0) == 'z'; i--) {
                adderResult = (adderResult << 1) | gateValues.get(wires.get(i));
            }
            System.out.println("Adder result: " + adderResult);

            // 1s in this output represent gates in our adder that are mismatched
            for(int i = 63; i >= 0; i--) {
                System.out.print(((z ^ adderResult) >> i) & 1);
            }
            System.out.println();

        } catch(FileNotFoundException e) {
            System.out.println("File not found");
        }

    }
}

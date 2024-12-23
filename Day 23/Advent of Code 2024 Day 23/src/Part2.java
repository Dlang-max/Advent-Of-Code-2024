import java.util.*;
import java.io.*;

public class Part2 {
    public static Map<String, Set<String>> graph = new HashMap<>();
    public static Set<String> maximumConnectedCliques = new HashSet<>();
    // Bron-Kerbosch Algorithm
    // Code inspired by: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
    private static void getMaximalConnectedClique(Set<String> R, Set<String> P, Set<String> X) {
        // If P and X are the empty Set, take R as a maximal clique and check
        // if it is the largest maximal clique.
        if(P.isEmpty() && X.isEmpty()) {
            if(R.size() > maximumConnectedCliques.size()) {
                maximumConnectedCliques = R;
            }
            return;
        }

        // Chose a pivot from the Union of P and X
        String pivot = "";
        Iterator<String> pIter = P.iterator(), xIter = X.iterator();
        if(pIter.hasNext()) {
            pivot = pIter.next();
        } else {
            pivot = xIter.next();
        }

        Set<String> pCopy = new HashSet<>(P);
        for(String vertex : pCopy) {
            if(graph.containsKey(pivot) && graph.get(pivot).contains(vertex)) {
                continue;
            }

            // The next R Set we use
            Set<String> newR = new HashSet<>(R);
            newR.add(vertex);

            // The next P Set we use
            Set<String> newP = new HashSet<>();
            for(String v : graph.get(vertex)) {
                if(P.contains(v)) {
                    newP.add(v);
                }
            }
            // The next X Set we use
            Set<String> newX = new HashSet<>();
            for(String v : graph.get(vertex)) {
                if(X.contains(v)) {
                    newX.add(v);
                }
            }
            // BronKerboschWithPivot(R U v, P n neighbors(v), X n neighbors(v))
            getMaximalConnectedClique(newR, newP, newX);
            // Remove vertex from P
            P.remove(vertex);
            // Add vertex to X
            X.add(vertex);
        }
    }

    public static void main(String[] args) {
        try {
            File f = new File("C:\\Users\\langd\\OneDrive\\Desktop\\Advent of Code 2024 Day 23\\src\\input.txt");
            Scanner scanner = new Scanner(f);

            while(scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String node1 = line.substring(0,2);
                String node2 = line.substring(3);

                graph.computeIfAbsent(node1, k -> new HashSet<>()).add(node2);
                graph.computeIfAbsent(node2, k -> new HashSet<>()).add(node1);
            }

            long start = System.currentTimeMillis();
            getMaximalConnectedClique(new HashSet<>(), graph.keySet(), new HashSet<>());
            List<String> nodes = new ArrayList<>(maximumConnectedCliques);
            Collections.sort(nodes);
            String password = String.join(",", nodes);
            System.out.println("Password: " + password);
            System.out.println("Time taken: " + (System.currentTimeMillis() - start));
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
    }
}
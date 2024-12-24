import java.util.*;
import java.io.*;

public class Part1 {
    static Map<String, Set<String>> graph = new HashMap<>();
    private static int getTripleConnectedComputers() {
        Set<String> triples = new HashSet<>();
        for(Map.Entry<String, Set<String>> entry : graph.entrySet()) {

            List<String> neighbors = entry.getValue().stream().toList();
            for(int i = 0; i < neighbors.size(); i++) {
                for(int j = i + 1; j < neighbors.size(); j++) {
                    String source = entry.getKey();
                    String neighbor1 = neighbors.get(i);
                    String neighbor2 = neighbors.get(j);

                    if(graph.get(neighbor1).contains(neighbor2) && (source.charAt(0) == 't' ||
                                                                    neighbor1.charAt(0) == 't' ||
                                                                    neighbor2.charAt(0) == 't')) {
                        List<String> nodes = new ArrayList<>();
                        nodes.add(entry.getKey());
                        nodes.add(neighbors.get(i));
                        nodes.add(neighbors.get(j));
                        Collections.sort(nodes);

                        StringBuilder keySB = new StringBuilder();
                        for(String node : nodes) {
                            keySB.append(node);
                        }

                        String key = keySB.toString();
                        if (triples.contains(key)) {
                            continue;
                        }
                        triples.add(key);
                    }
                }
            }
        }

        return triples.size();
    }

    public static void main(String[] args) {
        try {
            File f = new File("./input.txt");
            Scanner scanner = new Scanner(f);

            while(scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String node1 = line.substring(0,2);
                String node2 = line.substring(3);

                graph.computeIfAbsent(node1, k -> new HashSet<>()).add(node2);
                graph.computeIfAbsent(node2, k -> new HashSet<>()).add(node1);
            }

            System.out.println("Triple Connected Components with T: " + getTripleConnectedComputers());
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
        }
    }
}

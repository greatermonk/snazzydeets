#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <utility>
  
// Function to display an Unweighted Graph (using an adjacency list of neighbors)
void displayUnweightedGraph(const std::map<char, std::vector<char>>& graph, const std::string& title) {
    std::cout << "\n=======================================================\n";
    std::cout << "  " << title << " (Unweighted/Undirected)\n";
    std::cout << "=======================================================\n";

    // Iterate through every node (key) in the map
    for (const auto& pair : graph) {
        char node = pair.first;
        const std::vector<char>& neighbors = pair.second;

        // Print the current node
        std::cout << std::setw(3) << node << " --> ";

        // Print the list of its neighbors
        if (neighbors.empty()) {
            std::cout << "(No neighbors)";
        } else {
            for (size_t i = 0; i < neighbors.size(); ++i) {
                std::cout << neighbors[i];
                // Add a separator for all elements except the last one
                if (i < neighbors.size() - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------------------------\n";
}

// Function to display a Weighted, Directed Graph (using an adjacency list of <neighbor, weight> pairs)
void displayWeightedGraph(const std::map<char, std::vector<std::pair<char, int>>>& graph, const std::string& title) {
    std::cout << "\n=======================================================\n";
    std::cout << "  " << title << " (Weighted/Directed)\n";
    std::cout << "=======================================================\n";

    // Iterate through every node (key) in the map
    for (const auto& pair : graph) {
        char source = pair.first;
        const std::vector<std::pair<char, int>>& edges = pair.second;

        // Print the current source node
        std::cout << std::setw(3) << source << " --> ";

        // Print the list of its directed edges (neighbor and weight)
        if (edges.empty()) {
            std::cout << "(No outgoing edges)";
        } else {
            for (size_t i = 0; i < edges.size(); ++i) {
                char target = edges[i].first;
                int weight = edges[i].second;

                // Format: Target(Weight)
                std::cout << target << "(" << weight << ")";

                // Add a separator
                if (i < edges.size() - 1) {
                    std::cout << " -> ";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "-------------------------------------------------------\n";
}


int main() {
    // 1. Unweighted/Undirected Graph (From first ASCII art)
    std::map<char, std::vector<char>> unweighted_graph = {
        {'A', {'B', 'C', 'D'}},
        {'B', {'A', 'D'}},
        {'C', {'A', 'D', 'E'}},
        {'D', {'A', 'B', 'C'}},
        {'E', {'C'}}
    };

    // 2. Weighted, Directed, Cyclic Graph (From second request)
    // Structure: map<SourceNode, vector<pair<TargetNode, Weight>>>
    std::map<char, std::vector<std::pair<char, int>>> weighted_cyclic_graph = {
        {'A', {{'B', 5}, {'D', 1}}},
        {'B', {{'E', 2}}},
        {'C', {{'A', 8}, {'D', 4}}},
        {'D', {{'C', 6}}},
        {'E', {{'D', 3}}}
    };

    // 3. Weighted, Directed Acyclic Graph (DAG) (From second request)
    std::map<char, std::vector<std::pair<char, int>>> weighted_dag = {
        // A -> B(1), A -> C(5), A -> D(3)
        {'A', {{'B', 1}, {'C', 5}, {'D', 3}}},
        // B -> D(2)
        {'B', {{'D', 2}}},
        // C -> D(7)
        {'C', {{'D', 7}}},
        // D has no outgoing edges
        {'D', {}},
        // E -> B(4), E -> D(6)
        {'E', {{'B', 4}, {'D', 6}}}
    };


    // Display all graphs
    displayUnweightedGraph(unweighted_graph, "Unweighted/Undirected Graph");
    displayWeightedGraph(weighted_cyclic_graph, "Weighted, Directed, Cyclic Graph");
    displayWeightedGraph(weighted_dag, "Weighted, Directed Acyclic Graph (DAG)");

    return 0;
}


#include<iostream>
#include "../console_colors/colours.hpp"
#include "graphs.hpp"

using namespace std;
using namespace colors;

int main() {

    // Enable colored output (set to false for no colors)
    bool USE_COLORS = true;
    
    cprint(USE_COLORS, "=== Graph Data Structure Implementation Demo ===\n\n", 
           BRIGHT_WHITE, true);
    
    try {
        // 1. Null Graph with integers
        cprint(USE_COLORS, "1. NULL GRAPH (int)\n", BRIGHT_YELLOW, true);
        NullGraph<int> nullGraph;
        nullGraph.addVertex(1);
        nullGraph.addVertex(2);
        nullGraph.addVertex(3);
        nullGraph.addVertex(4);
        nullGraph.addVertex(5);
        nullGraph.display(USE_COLORS);
        cout << endl;
        
        // 2. Trivial Graph with char
        cprint(USE_COLORS, "2. TRIVIAL GRAPH (char)\n", BRIGHT_YELLOW, true);
        TrivialGraph<char> trivialGraph('A');
        trivialGraph.display(USE_COLORS);
        cout << endl;
        
        // 3. Undirected Graph with integers
        cprint(USE_COLORS, "3. UNDIRECTED GRAPH (int)\n", BRIGHT_YELLOW, true);
        UndirectedGraph<int> undirGraph;
        undirGraph.addEdge(1, 2);
        undirGraph.addEdge(2, 3);
        undirGraph.addEdge(3, 4);
        undirGraph.display(USE_COLORS);
        cout << endl;
        
        // 4. Directed Graph with integers
        cprint(USE_COLORS, "4. DIRECTED GRAPH (int)\n", BRIGHT_YELLOW, true);
        DirectedGraph<int> dirGraph;
        dirGraph.addEdge(1, 2);
        dirGraph.addEdge(2, 3);
        dirGraph.addEdge(2, 4);
        dirGraph.addEdge(3, 4);
        dirGraph.display(USE_COLORS);
        cout << endl;
        
        // 5. Connected Graph with strings
        cprint(USE_COLORS, "5. CONNECTED GRAPH (string)\n", BRIGHT_YELLOW, true);
        ConnectedGraph<string> connGraph;
        connGraph.addEdge("A", "B");
        connGraph.addEdge("B", "C");
        connGraph.addEdge("C", "D");
        connGraph.addEdge("D", "A");
        connGraph.display(USE_COLORS);
        cout << endl;
        
        // 6. Disconnected Graph with integers
        cprint(USE_COLORS, "6. DISCONNECTED GRAPH (int)\n", BRIGHT_YELLOW, true);
        DisconnectedGraph<int> disconnGraph;
        disconnGraph.addEdge(1, 2);
        disconnGraph.addEdge(2, 3);
        disconnGraph.addEdge(4, 5); // Separate component
        disconnGraph.display(USE_COLORS);
        cout << endl;
        
        // 7. Complete Graph with chars
        cprint(USE_COLORS, "7. COMPLETE GRAPH (char)\n", BRIGHT_YELLOW, true);
        CompleteGraph<char> completeGraph;
        completeGraph.addVertex('A');
        completeGraph.addVertex('B');
        completeGraph.addVertex('C');
        completeGraph.addVertex('D');
        completeGraph.display(USE_COLORS);
        cout << endl;
        
        // 8. Cyclic Graph with integers
        cprint(USE_COLORS, "8. CYCLIC GRAPH (int)\n", BRIGHT_YELLOW, true);
        CyclicGraph<int> cyclicGraph;
        cyclicGraph.addEdge(1, 2);
        cyclicGraph.addEdge(2, 3);
        cyclicGraph.addEdge(3, 4);
        cyclicGraph.addEdge(4, 1); // Creates a cycle
        cyclicGraph.display(USE_COLORS);
        cout << endl;
        
        // 9. Directed Acyclic Graph with chars
        cprint(USE_COLORS, "9. DIRECTED ACYCLIC GRAPH (DAG) (char)\n", BRIGHT_YELLOW, true);
        DirectedAcyclicGraph<char> dag;
        dag.addEdge('A', 'B');
        dag.addEdge('A', 'C');
        dag.addEdge('B', 'D');
        dag.addEdge('C', 'D');
        dag.display(USE_COLORS);
        cout << endl;
        
        // 10. Bipartite Graph with integers
        cprint(USE_COLORS, "10. BIPARTITE GRAPH (int)\n", BRIGHT_YELLOW, true);
        BipartiteGraph<int> biGraph;
        biGraph.addEdge(1, 2);
        biGraph.addEdge(1, 4);
        biGraph.addEdge(2, 3);
        biGraph.addEdge(3, 4);
        biGraph.display(USE_COLORS);
        cout << endl;
        
        // 11. Weighted Graph (Undirected) with strings
        cprint(USE_COLORS, "11. WEIGHTED GRAPH (Undirected) (string)\n", BRIGHT_YELLOW, true);
        WeightedGraph<string> weightedGraph(false);
        weightedGraph.addEdge("A", "B", 10);
        weightedGraph.addEdge("B", "C", 20);
        weightedGraph.addEdge("C", "D", 30);
        weightedGraph.addEdge("A", "D", 15);
        weightedGraph.display(USE_COLORS);
        cout << endl;
        
        // 12. Weighted & Directed Graph with chars
        cprint(USE_COLORS, "12. WEIGHTED & DIRECTED GRAPH (char)\n", BRIGHT_YELLOW, true);
        WeightedGraph<char> weightedDirGraph(true);
        weightedDirGraph.addEdge('A', 'B', 1);
        weightedDirGraph.addEdge('A', 'C', 1);
        weightedDirGraph.addEdge('B', 'C', 2);
        weightedDirGraph.addEdge('B', 'D', 2);
        weightedDirGraph.addEdge('C', 'D', 3);
        weightedDirGraph.display(USE_COLORS);
        cout << endl;
        
        // 13. Demonstration with float vertices
        cprint(USE_COLORS, "13. UNDIRECTED GRAPH (float)\n", BRIGHT_YELLOW, true);
        UndirectedGraph<float> floatGraph;
        floatGraph.addEdge(1.5f, 2.3f);
        floatGraph.addEdge(2.3f, 3.7f);
        floatGraph.addEdge(3.7f, 4.2f);
        floatGraph.display(USE_COLORS);
        cout << endl;
        
        // ====================================================================
        // GRAPH PROPERTIES DEMONSTRATION
        // ====================================================================
        
        cout << "\n" << string(70, '=') << endl;
        cprint(USE_COLORS, "GRAPH PROPERTIES DEMONSTRATION\n", BRIGHT_WHITE, true);
        cout << string(70, '=') << endl;
        
        // Example 1: Analyze a social network
        cprint(USE_COLORS, "\n--- Example 1: Social Network Analysis ---\n", 
               BRIGHT_CYAN, true);
        UndirectedGraph<string> social;
        social.addEdge("Alice", "Bob");
        social.addEdge("Bob", "Charlie");
        social.addEdge("Charlie", "David");
        social.addEdge("David", "Alice");
        social.addEdge("Alice", "Eve");
        social.addEdge("Eve", "Frank");
        
        social.display(USE_COLORS);
        social.displayProperties(USE_COLORS);
        
        // Check specific vertex degree
        cprint(USE_COLORS, "Degree of 'Alice': ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(social.getDegree("Alice")), BRIGHT_BLUE);
        cprint(USE_COLORS, " connections\n", BRIGHT_WHITE);
        
        cprint(USE_COLORS, "Degree of 'Frank': ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(social.getDegree("Frank")), BRIGHT_BLUE);
        cprint(USE_COLORS, " connections\n", BRIGHT_WHITE);
        
        // Check distance between vertices
        cprint(USE_COLORS, "Distance between Alice and Frank: ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(social.getDistance("Alice", "Frank")), BRIGHT_GREEN);
        cprint(USE_COLORS, " hops\n", BRIGHT_WHITE);
        
        cprint(USE_COLORS, "Distance between Bob and David: ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(social.getDistance("Bob", "David")), BRIGHT_GREEN);
        cprint(USE_COLORS, " hops\n", BRIGHT_WHITE);
        cout << endl;
        
        // Example 2: Directed graph properties
        cprint(USE_COLORS, "--- Example 2: Web Page Link Analysis ---\n", 
               BRIGHT_CYAN, true);
        DirectedGraph<int> web;
        web.addEdge(1, 2);
        web.addEdge(1, 3);
        web.addEdge(2, 3);
        web.addEdge(3, 4);
        web.addEdge(4, 2);  // Creates a cycle
        
        web.display(USE_COLORS);
        web.displayProperties(USE_COLORS);
        
        cprint(USE_COLORS, "Out-degree of page 1: ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(web.getDegree(1)), BRIGHT_GREEN);
        cprint(USE_COLORS, " outgoing links\n", BRIGHT_WHITE);
        
        cprint(USE_COLORS, "In-degree of page 2: ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(web.getInDegree(2)), BRIGHT_BLUE);
        cprint(USE_COLORS, " incoming links\n", BRIGHT_WHITE);
        
        cprint(USE_COLORS, "In-degree of page 3: ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(web.getInDegree(3)), BRIGHT_BLUE);
        cprint(USE_COLORS, " incoming links\n", BRIGHT_WHITE);
        cout << endl;
        
        // Example 3: Complete graph properties
        cprint(USE_COLORS, "--- Example 3: Complete Graph (Mesh Network) ---\n", 
               BRIGHT_CYAN, true);
        CompleteGraph<char> mesh;
        mesh.addVertex('A');
        mesh.addVertex('B');
        mesh.addVertex('C');
        mesh.addVertex('D');
        
        mesh.display(USE_COLORS);
        mesh.displayProperties(USE_COLORS);
        
        cprint(USE_COLORS, "All vertices in complete graph have degree: ", 
               BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(mesh.getDegree('A')) + "\n", BRIGHT_CYAN);
        
        cprint(USE_COLORS, "Distance between any two vertices: ", BRIGHT_WHITE, true);
        cprint(USE_COLORS, to_string(mesh.getDistance('A', 'D')) + "\n", BRIGHT_GREEN);
        cout << endl;
        
        // Demonstrate error handling with colors
        cprint(USE_COLORS, "--- Example 4: Error Handling Demo ---\n", 
               BRIGHT_CYAN, true);
        try {
            NullGraph<int> nullG;
            nullG.addVertex(1);
            nullG.addEdge(1, 2);  // Should throw error
        } catch (const logic_error& e) {
            cprint(USE_COLORS, "Error: ", RED, true);
            cprint(USE_COLORS, string(e.what()) + "\n", RED);
        }
        cout << endl;
        
        // ====================================================================
        // GRAPH OPERATIONS DEMONSTRATION
        // ====================================================================
        
        cout << "\n" << string(70, '=') << endl;
        cprint(USE_COLORS, "GRAPH OPERATIONS DEMONSTRATION\n", BRIGHT_WHITE, true);
        cout << string(70, '=') << endl;
        
        // Example 1: Delete Vertex Operation
        cprint(USE_COLORS, "\n--- Example 1: Delete Vertex Operation ---\n", 
               BRIGHT_CYAN, true);
        
        UndirectedGraph<int> deleteDemo;
        deleteDemo.addEdge(1, 2);
        deleteDemo.addEdge(2, 3);
        deleteDemo.addEdge(3, 4);
        deleteDemo.addEdge(4, 1);
        deleteDemo.addEdge(2, 4);
        
        cprint(USE_COLORS, "Original Graph:\n", BRIGHT_YELLOW, true);
        deleteDemo.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nDeleting vertex 2...\n", BRIGHT_RED, true);
        bool deleted = deleteDemo.deleteVertex(2);
        
        if (deleted) {
            cprint(USE_COLORS, "✓ Vertex 2 deleted successfully\n", BRIGHT_GREEN);
            cprint(USE_COLORS, "\nGraph after deletion:\n", BRIGHT_YELLOW, true);
            deleteDemo.display(USE_COLORS);
        }
        cout << endl;
        
        // Example 2: Delete Edge Operation
        cprint(USE_COLORS, "--- Example 2: Delete Edge Operation ---\n", 
               BRIGHT_CYAN, true);
        
        DirectedGraph<char> edgeDemo;
        edgeDemo.addEdge('A', 'B');
        edgeDemo.addEdge('B', 'C');
        edgeDemo.addEdge('C', 'D');
        edgeDemo.addEdge('D', 'A');
        
        cprint(USE_COLORS, "Original Graph:\n", BRIGHT_YELLOW, true);
        edgeDemo.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nDeleting edge C -> D...\n", BRIGHT_RED, true);
        bool edgeDeleted = edgeDemo.deleteEdge('C', 'D');
        
        if (edgeDeleted) {
            cprint(USE_COLORS, "✓ Edge deleted successfully\n", BRIGHT_GREEN);
            cprint(USE_COLORS, "\nGraph after edge deletion:\n", BRIGHT_YELLOW, true);
            edgeDemo.display(USE_COLORS);
        }
        cout << endl;
        
        // Example 3: Join Operation (Union of Graphs)
        cprint(USE_COLORS, "--- Example 3: Join Operation (Graph Union) ---\n", 
               BRIGHT_CYAN, true);
        
        UndirectedGraph<string> graph1;
        graph1.addEdge("A", "B");
        graph1.addEdge("B", "C");
        
        UndirectedGraph<string> graph2;
        graph2.addEdge("C", "D");
        graph2.addEdge("D", "E");
        
        cprint(USE_COLORS, "Graph 1:\n", BRIGHT_YELLOW, true);
        graph1.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nGraph 2:\n", BRIGHT_YELLOW, true);
        graph2.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nJoining Graph 1 and Graph 2...\n", BRIGHT_MAGNETA, true);
        graph1.join(graph2);
        
        cprint(USE_COLORS, "\nResult (Graph 1 ∪ Graph 2):\n", BRIGHT_GREEN, true);
        graph1.display(USE_COLORS);
        cout << endl;
        
        // Example 4: Operator+ for Graph Union
        cprint(USE_COLORS, "--- Example 4: Operator+ (Graph Union) ---\n", 
               BRIGHT_CYAN, true);
        
        DirectedGraph<int> g1;
        g1.addEdge(1, 2);
        g1.addEdge(2, 3);
        
        DirectedGraph<int> g2;
        g2.addEdge(3, 4);
        g2.addEdge(4, 5);
        
        cprint(USE_COLORS, "Graph G1:\n", BRIGHT_YELLOW, true);
        g1.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nGraph G2:\n", BRIGHT_YELLOW, true);
        g2.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nComputing G3 = G1 + G2...\n", BRIGHT_MAGNETA, true);
        Graph<int> g3 = g1 + g2;
        
        cprint(USE_COLORS, "\nResult G3:\n", BRIGHT_GREEN, true);
        g3.display(USE_COLORS);
        cout << endl;
        
        // Example 5: Error Handling - Incompatible Graph Join
        cprint(USE_COLORS, "--- Example 5: Join Error Handling ---\n", 
               BRIGHT_CYAN, true);
        
        try {
            DirectedGraph<int> directed;
            directed.addEdge(1, 2);
            
            UndirectedGraph<int> undirected;
            undirected.addEdge(3, 4);
            
            cprint(USE_COLORS, "Attempting to join directed and undirected graphs...\n", 
                   BRIGHT_YELLOW);
            directed.join(undirected);
            
        } catch (const logic_error& e) {
            cprint(USE_COLORS, "✗ Error: ", RED, true);
            cprint(USE_COLORS, string(e.what()) + "\n", RED);
            cprint(USE_COLORS, "  (This is expected behavior)\n", BRIGHT_WHITE);
        }
        cout << endl;
        
        // ====================================================================
        // BFS & DFS TRAVERSAL DEMONSTRATION
        // ====================================================================
        
        cout << "\n" << string(70, '=') << endl;
        cprint(USE_COLORS, "GRAPH TRAVERSAL ALGORITHMS\n", BRIGHT_WHITE, true);
        cout << string(70, '=') << endl;
        
        // Example 1: BFS on Undirected Graph
        cprint(USE_COLORS, "\n--- Example 1: BFS on Undirected Graph ---\n", 
               BRIGHT_CYAN, true);
        
        UndirectedGraph<int> bfsGraph;
        bfsGraph.addEdge(1, 2);
        bfsGraph.addEdge(1, 3);
        bfsGraph.addEdge(2, 4);
        bfsGraph.addEdge(2, 5);
        bfsGraph.addEdge(3, 6);
        bfsGraph.addEdge(3, 7);
        bfsGraph.addEdge(4, 8);
        
        cprint(USE_COLORS, "Graph Structure:\n", BRIGHT_YELLOW, true);
        bfsGraph.display(USE_COLORS);
        
        vector<int> bfsResult = bfsGraph.BFS(1, USE_COLORS);
        
        // Example 2: DFS on Undirected Graph
        cprint(USE_COLORS, "\n--- Example 2: DFS on Undirected Graph ---\n", 
               BRIGHT_CYAN, true);
        
        cprint(USE_COLORS, "Graph Structure (same as above):\n", BRIGHT_YELLOW, true);
        
        vector<int> dfsResult = bfsGraph.DFS(1, USE_COLORS);
        
        // Example 3: BFS on Directed Graph
        cprint(USE_COLORS, "\n--- Example 3: BFS on Directed Graph ---\n", 
               BRIGHT_CYAN, true);
        
        DirectedGraph<char> dirBFS;
        dirBFS.addEdge('A', 'B');
        dirBFS.addEdge('A', 'C');
        dirBFS.addEdge('B', 'D');
        dirBFS.addEdge('B', 'E');
        dirBFS.addEdge('C', 'F');
        dirBFS.addEdge('E', 'F');
        
        cprint(USE_COLORS, "Directed Graph Structure:\n", BRIGHT_YELLOW, true);
        dirBFS.display(USE_COLORS);
        
        vector<char> dirBFSResult = dirBFS.BFS('A', USE_COLORS);
        
        // Example 4: DFS on Directed Graph
        cprint(USE_COLORS, "\n--- Example 4: DFS on Directed Graph ---\n", 
               BRIGHT_CYAN, true);
        
        cprint(USE_COLORS, "Directed Graph Structure (same as above):\n", 
               BRIGHT_YELLOW, true);
        
        vector<char> dirDFSResult = dirBFS.DFS('A', USE_COLORS);
        
        // Example 5: BFS on Disconnected Graph
        cprint(USE_COLORS, "\n--- Example 5: BFS on Disconnected Graph ---\n", 
               BRIGHT_CYAN, true);
        
        DisconnectedGraph<string> disconn;
        disconn.addEdge("A", "B");
        disconn.addEdge("B", "C");
        disconn.addEdge("D", "E");  // Separate component
        disconn.addEdge("F", "G");  // Another component
        
        cprint(USE_COLORS, "Disconnected Graph:\n", BRIGHT_YELLOW, true);
        disconn.display(USE_COLORS);
        
        cprint(USE_COLORS, "\nBFS from 'A' (will only visit connected component):\n", 
               BRIGHT_MAGNETA, true);
        vector<string> disconnBFS = disconn.BFS("A", USE_COLORS);
        
        // Example 6: Comparing BFS and DFS
        cprint(USE_COLORS, "\n--- Example 6: BFS vs DFS Comparison ---\n", 
               BRIGHT_CYAN, true);
        
        UndirectedGraph<int> compareGraph;
        compareGraph.addEdge(1, 2);
        compareGraph.addEdge(1, 3);
        compareGraph.addEdge(2, 4);
        compareGraph.addEdge(2, 5);
        compareGraph.addEdge(3, 6);
        compareGraph.addEdge(4, 7);
        
        cprint(USE_COLORS, "Graph Structure:\n", BRIGHT_YELLOW, true);
        compareGraph.display(USE_COLORS);
        
        cprint(USE_COLORS, "\n┌─ BFS Traversal:\n", BRIGHT_CYAN, true);
        vector<int> bfsComp = compareGraph.BFS(1, USE_COLORS);
        
        cprint(USE_COLORS, "\n┌─ DFS Traversal:\n", BRIGHT_MAGNETA, true);
        vector<int> dfsComp = compareGraph.DFS(1, USE_COLORS);
        
        cprint(USE_COLORS, "\n┌─ Comparison Summary:\n", BRIGHT_WHITE, true);
        cprint(USE_COLORS, "├─ BFS explores level by level (breadth-first)\n", 
               BRIGHT_CYAN);
        cprint(USE_COLORS, "└─ DFS explores as deep as possible (depth-first)\n", 
               BRIGHT_MAGNETA);
        cout << endl;
        
    } catch (const exception& e) {
        cprint(true, "Fatal Error: ", RED, true);
        cprint(true, string(e.what()) + "\n", RED);
    }
    
    cprint(USE_COLORS, "\n=== Demo Complete ===\n", BRIGHT_WHITE, true);
    cprint(USE_COLORS, "Tip: Set USE_COLORS = false to disable colored output\n", 
           BRIGHT_YELLOW);
    
    return 0;
}

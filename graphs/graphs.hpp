#ifndef GRAPHS_HPP
#define GRAPHS_HPP

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include "../console_colors/colours.hpp"
#include<climits>


using namespace std;
using namespace colors;

// ============================================================================
// BASE GRAPH CLASS WITH TEMPLATE SUPPORT
// ============================================================================

/**
 * Base Graph class implementing fundamental graph operations
 * Uses adjacency list representation for efficient storage
 * Template parameter T allows vertices to be of any type (int, char, string, etc.)
 */
template<typename T>
class Graph {
protected:
    int numVertices;
    bool isDirected;
    bool isWeighted;
    map<T, vector<pair<T, int>>> adjList; // vertex -> [(neighbor, weight)]
    set<T> vertices;
    
public:
    /**
     * Constructor: Initializes a graph with given properties
     * @param directed: Boolean indicating if graph is directed
     * @param weighted: Boolean indicating if graph is weighted
     */
    Graph(bool directed = false, bool weighted = false) 
        : numVertices(0), isDirected(directed), isWeighted(weighted) {}
    
    /**
     * Adds a vertex to the graph
     * @param vertex: The vertex to add
     */
    void addVertex(T vertex) {
        if (vertices.find(vertex) == vertices.end()) {
            vertices.insert(vertex);
            adjList[vertex] = vector<pair<T, int>>();
            numVertices++;
        }
    }
    
    /**
     * Adds an edge between two vertices with optional weight
     * @param src: Source vertex
     * @param dest: Destination vertex
     * @param weight: Edge weight (default = 1)
     */
    virtual void addEdge(T src, T dest, int weight = 1) {
        addVertex(src);
        addVertex(dest);
        
        adjList[src].push_back({dest, weight});
        if (!isDirected) {
            adjList[dest].push_back({src, weight});
        }
    }

    /**
     * Deletes a vertex and all edges connected to it
     * @param vertex: The vertex to delete
     * @return True if vertex was deleted, false if vertex didn't exist
     */
    virtual bool deleteVertex(T vertex) {
        if (vertices.find(vertex) == vertices.end()) {
            return false;  // Vertex doesn't exist
        }

        // Remove the vertex from the vertices set
        vertices.erase(vertex);
        numVertices--;

        // Remove the vertex's adjacency list entry
        adjList.erase(vertex);

        // Remove all edges pointing to this vertex from other vertices
        for (auto& _pair : adjList) {
            auto& neighbors = _pair.second;
            neighbors.erase(
                remove_if(neighbors.begin(), neighbors.end(),
                         [vertex](const pair<T, int>& p) {
                             return p.first == vertex;
                         }),
                neighbors.end()
            );
        }

        return true;
    }

    /**
     * Deletes an edge between two vertices
     * @param src: Source vertex
     * @param dest: Destination vertex
     * @return True if edge was deleted, false if edge didn't exist
     */
    bool deleteEdge(T src, T dest) {
        if (vertices.find(src) == vertices.end() ||
            vertices.find(dest) == vertices.end()) {
            return false;
        }

        bool found = false;

        // Remove edge from src to dest
        auto& srcNeighbors = adjList[src];
        auto it = remove_if(srcNeighbors.begin(), srcNeighbors.end(),
                           [dest](const pair<T, int>& p) {
                               return p.first == dest;
                           });
        if (it != srcNeighbors.end()) {
            srcNeighbors.erase(it, srcNeighbors.end());
            found = true;
        }

        // For undirected graphs, also remove dest to src
        if (!isDirected) {
            auto& destNeighbors = adjList[dest];
            auto it2 = remove_if(destNeighbors.begin(), destNeighbors.end(),
                                [src](const pair<T, int>& p) {
                                    return p.first == src;
                                });
            if (it2 != destNeighbors.end()) {
                destNeighbors.erase(it2, destNeighbors.end());
            }
        }

        return found;
    }

    /**
     * Joins another graph with this graph (union operation)
     * @param other: The graph to join with
     * @throws logic_error: If graphs have incompatible types
     */
    void join(const Graph<T>& other) {
        // Check compatibility
        if (this->isDirected != other.isDirected) {
            throw logic_error("Cannot join directed and undirected graphs");
        }
        if (this->isWeighted != other.isWeighted) {
            throw logic_error("Cannot join weighted and unweighted graphs");
        }

        // Add all vertices from other graph
        for (const auto& vertex : other.vertices) {
            addVertex(vertex);
        }

        // Add all edges from other graph
        for (const auto& pair : other.adjList) {
            T src = pair.first;
            for (const auto& neighbor : pair.second) {
                T dest = neighbor.first;
                int weight = neighbor.second;

                // Check if edge already exists to avoid duplicates
                bool exists = false;
                auto it = adjList.find(src);
                if (it != adjList.end()) {
                    for (const auto& existing : it->second) {
                        if (existing.first == dest) {
                            exists = true;
                            break;
                        }
                    }
                }

                if (!exists) {
                    // For undirected graphs, only add if we haven't added reverse
                    if (isDirected || src < dest) {
                        addEdge(src, dest, weight);
                    }
                }
            }
        }
    }

    /**
     * Operator+ overload for graph union
     * @param other: The graph to join with
     * @return New graph containing union of both graphs
     */
    Graph<T> operator+(const Graph<T>& other) const {
        Graph<T> result(this->isDirected, this->isWeighted);

        // Add all vertices and edges from this graph
        for (const auto& vertex : this->vertices) {
            result.addVertex(vertex);
        }
        for (const auto& pair : this->adjList) {
            T src = pair.first;
            for (const auto& neighbor : pair.second) {
                T dest = neighbor.first;
                int weight = neighbor.second;
                if (isDirected || src < dest) {
                    result.addEdge(src, dest, weight);
                }
            }
        }

        // Join with other graph
        result.join(other);

        return result;
    }

    /**
     * Performs Breadth-First Search traversal from a starting vertex
     * @param start: Starting vertex for BFS
     * @param use_colored_output: Enable colored output
     * @return Vector of vertices in BFS order
     */
    vector<T> BFS(T start, bool use_colored_output = false) const {
        if (vertices.find(start) == vertices.end()) {
            throw invalid_argument("Start vertex not found in graph");
        }

        vector<T> traversal;
        set<T> visited;
        queue<T> q;
        map<T, T> parent;  // For path tracking
        map<T, int> level;  // For level tracking

        q.push(start);
        visited.insert(start);
        parent[start] = start;
        level[start] = 0;

        // Print header
        cprint(use_colored_output, "\n╔════════════════════════════════════════╗\n",
               BRIGHT_BLACK, true);
        cprint(use_colored_output, "║   BREADTH-FIRST SEARCH TRAVERSAL       ║\n",
               BRIGHT_BLACK, true);
        cprint(use_colored_output, "╚════════════════════════════════════════╝\n",
               BRIGHT_BLACK, true);

        cprint(use_colored_output, "Starting from vertex: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, start, BRIGHT_BLUE);
        cout << "\n\n";

        int step = 0;
        while (!q.empty()) {
            int levelSize = q.size();

            cprint(use_colored_output, "Level " + to_string(level[q.front()]) + ": ",
                   BRIGHT_YELLOW, true);

            for (int i = 0; i < levelSize; i++) {
                T current = q.front();
                q.pop();
                traversal.push_back(current);

                // Visual representation
                if (i > 0) cprint(use_colored_output, " → ", BRIGHT_WHITE);
                cprint(use_colored_output, "[", BRIGHT_WHITE);
                cprint(use_colored_output, current, BRIGHT_BLUE);
                cprint(use_colored_output, "]", BRIGHT_WHITE);

                // Explore neighbors
                auto it = adjList.find(current);
                if (it != adjList.end()) {
                    for (const auto& neighbor : it->second) {
                        if (visited.find(neighbor.first) == visited.end()) {
                            visited.insert(neighbor.first);
                            parent[neighbor.first] = current;
                            level[neighbor.first] = level[current] + 1;
                            q.push(neighbor.first);
                        }
                    }
                }
            }
            cout << "\n";
        }

        // Print tree structure
        cout << "\n";
        cprint(use_colored_output, "BFS Tree Structure:\n", BRIGHT_GREEN, true);
        cprint(use_colored_output, "───────────────────\n", BRIGHT_GREEN);
        printBFSTree(start, parent, level, use_colored_output);

        // Print summary
        cout << "\n";
        cprint(use_colored_output, "Traversal Order: ", BRIGHT_WHITE, true);
        for (size_t i = 0; i < traversal.size(); i++) {
            if (i > 0) cprint(use_colored_output, " → ", BRIGHT_YELLOW);
            cprint(use_colored_output, traversal[i], BRIGHT_BLUE);
        }
        cout << "\n";

        cprint(use_colored_output, "Vertices Visited: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, to_string(traversal.size()) + "/" +
               to_string(vertices.size()) + "\n\n", BRIGHT_CYAN);

        return traversal;
    }

    /**
     * Performs Depth-First Search traversal from a starting vertex
     * @param start: Starting vertex for DFS
     * @param use_colored_output: Enable colored output
     * @return Vector of vertices in DFS order
     */
    vector<T> DFS(T start, bool use_colored_output = false) const {
        if (vertices.find(start) == vertices.end()) {
            throw invalid_argument("Start vertex not found in graph");
        }

        vector<T> traversal;
        set<T> visited;
        map<T, int> discoveryTime;
        map<T, int> finishTime;
        map<T, T> parent;
        int time = 0;

        // Print header
        cprint(use_colored_output, "\n╔════════════════════════════════════════╗\n",
               BRIGHT_BLACK, true);
        cprint(use_colored_output, "║   DEPTH-FIRST SEARCH TRAVERSAL         ║\n",
               BRIGHT_BLACK, true);
        cprint(use_colored_output, "╚════════════════════════════════════════╝\n",
               BRIGHT_BLACK, true);

        cprint(use_colored_output, "Starting from vertex: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, start, BRIGHT_BLUE);
        cout << "\n\n";

        parent[start] = start;

        // Perform DFS
        DFSUtil(start, visited, traversal, discoveryTime, finishTime,
                parent, time, use_colored_output);

        // Print DFS tree
        cout << "\n";
        cprint(use_colored_output, "DFS Tree Structure:\n", BRIGHT_GREEN, true);
        cprint(use_colored_output, "───────────────────\n", BRIGHT_GREEN);
        printDFSTree(start, parent, 0, use_colored_output, set<T>());

        // Print summary
        cout << "\n";
        cprint(use_colored_output, "Traversal Order: ", BRIGHT_WHITE, true);
        for (size_t i = 0; i < traversal.size(); i++) {
            if (i > 0) cprint(use_colored_output, " → ", BRIGHT_YELLOW);
            cprint(use_colored_output, traversal[i], BRIGHT_BLUE);
        }
        cout << "\n";

        cprint(use_colored_output, "Vertices Visited: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, to_string(traversal.size()) + "/" +
               to_string(vertices.size()) + "\n\n", BRIGHT_CYAN);

        return traversal;
    }

    
    /**
     * Displays the graph's adjacency list representation
     * @param use_colored_output: Enable colored output (default: false)
     */
    virtual void display(bool use_colored_output = false) const {
        if (vertices.empty()) {
            cprint(use_colored_output, "  Empty Graph\n", BRIGHT_WHITE, true);
            return;
        }
        
        cprint(use_colored_output, "Graph (Adjacency List", BRIGHT_WHITE, true);
        if (isDirected) cprint(use_colored_output, " for directed", BRIGHT_GREEN);
        if (isWeighted) cprint(use_colored_output, " & weighted", YELLOW);
        cprint(use_colored_output, " graph):\n", BRIGHT_WHITE, true);
        cprint(use_colored_output, "-----------------------\n", BRIGHT_WHITE);
        
        for (const auto& vertex : vertices) {
            cprint(use_colored_output, "  ", RESET);
            cprint(use_colored_output, vertex, BLUE);
            
            if (adjList.at(vertex).empty()) {
                cprint(use_colored_output, " --> ", isDirected ? BRIGHT_GREEN : BRIGHT_YELLOW);
                cprint(use_colored_output, "∅\n", BRIGHT_RED);
            } else {
                if (isDirected) {
                    cprint(use_colored_output, " -->", BRIGHT_GREEN);
                } else {
                    cprint(use_colored_output, " ---", BRIGHT_YELLOW);
                }
                
                bool first = true;
                for (const auto& neighbor : adjList.at(vertex)) {
                    if (!first) cprint(use_colored_output, ",", BRIGHT_WHITE);
                    
                    if (isWeighted) {
                        cprint(use_colored_output, " (", YELLOW);
                        cprint(use_colored_output, neighbor.second, CYAN);
                        cprint(use_colored_output, ")---> ", YELLOW);
                    } else {
                        cprint(use_colored_output, " ", RESET);
                    }
                    cprint(use_colored_output, neighbor.first, BLUE);
                    first = false;
                }
                cout << endl;
            }
        }
    }
    
    /**
     * Gets the number of vertices in the graph
     * @return Number of vertices
     */
    int getNumVertices() const { return numVertices; }
    
    /**
     * Gets the number of edges in the graph
     * @return Number of edges
     */
    int getNumEdges() const {
        int count = 0;
        for (const auto& pair : adjList) {
            count += pair.second.size();
        }
        return isDirected ? count : count / 2;
    }
    
    /**
     * Checks if the graph is connected using BFS
     * @return True if graph is connected
     */
    bool isConnected() const {
        if (vertices.empty()) return true;
        
        set<T> visited;
        queue<T> q;
        T start = *vertices.begin();
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            T vertex = q.front();
            q.pop();
            
            for (const auto& neighbor : adjList.at(vertex)) {
                if (visited.find(neighbor.first) == visited.end()) {
                    visited.insert(neighbor.first);
                    q.push(neighbor.first);
                }
            }
        }
        
        return visited.size() == vertices.size();
    }
    
    /**
     * Gets all vertices in the graph
     * @return Set of vertices
     */
    set<T> getVertices() const { return vertices; }
    
    /**
     * Gets the degree of a specified vertex
     * @param vertex: The vertex to check
     * @return Degree of the vertex (number of edges connected to it)
     */
    int getDegree(T vertex) const {
        if (vertices.find(vertex) == vertices.end()) {
            throw invalid_argument("Vertex not found in graph");
        }
        
        auto it = adjList.find(vertex);
        if (it == adjList.end()) return 0;
        
        if (isDirected) {
            // For directed graphs, return out-degree
            return it->second.size();
        } else {
            // For undirected graphs, return total degree
            return it->second.size();
        }
    }
    
    /**
     * Gets the in-degree of a vertex (directed graphs only)
     * @param vertex: The vertex to check
     * @return In-degree of the vertex
     */
    int getInDegree(T vertex) const {
        if (vertices.find(vertex) == vertices.end()) {
            throw invalid_argument("Vertex not found in graph");
        }
        
        if (!isDirected) {
            return getDegree(vertex);  // Same as degree for undirected
        }
        
        int inDegree = 0;
        for (const auto& pair : adjList) {
            for (const auto& neighbor : pair.second) {
                if (neighbor.first == vertex) {
                    inDegree++;
                }
            }
        }
        return inDegree;
    }
    
    /**
     * Gets the minimum degree among all vertices (Graph Radius)
     * @return Minimum vertex degree
     */
    int getMinDegree() const {
        if (vertices.empty()) return 0;
        
        int minDeg = INT_MAX;
        for (const auto& vertex : vertices) {
            int deg = getDegree(vertex);
            minDeg = min(minDeg, deg);
        }
        return minDeg;
    }
    
    /**
     * Gets the maximum degree among all vertices (Graph Diameter in terms of degree)
     * @return Maximum vertex degree
     */
    int getMaxDegree() const {
        if (vertices.empty()) return 0;
        
        int maxDeg = 0;
        for (const auto& vertex : vertices) {
            int deg = getDegree(vertex);
            maxDeg = max(maxDeg, deg);
        }
        return maxDeg;
    }
    
    /**
     * Calculates shortest distance between two vertices using BFS
     * @param src: Source vertex
     * @param dest: Destination vertex
     * @return Shortest distance (number of edges), -1 if no path exists
     */
    int getDistance(T src, T dest) const {
        if (vertices.find(src) == vertices.end() || 
            vertices.find(dest) == vertices.end()) {
            throw invalid_argument("Vertex not found in graph");
        }
        
        if (src == dest) return 0;
        
        map<T, int> distance;
        queue<T> q;
        set<T> visited;
        
        q.push(src);
        visited.insert(src);
        distance[src] = 0;
        
        while (!q.empty()) {
            T current = q.front();
            q.pop();
            
            auto it = adjList.find(current);
            if (it != adjList.end()) {
                for (const auto& neighbor : it->second) {
                    if (visited.find(neighbor.first) == visited.end()) {
                        visited.insert(neighbor.first);
                        distance[neighbor.first] = distance[current] + 1;
                        q.push(neighbor.first);
                        
                        if (neighbor.first == dest) {
                            return distance[neighbor.first];
                        }
                    }
                }
            }
        }
        
        return -1;  // No path exists
    }
    
    /**
     * Calculates the graph diameter (maximum shortest path between any two vertices)
     * @return Graph diameter, -1 if graph is disconnected
     */
    int getDiameter() const {
        if (vertices.empty()) return 0;
        if (vertices.size() == 1) return 0;
        
        int diameter = 0;
        
        for (const auto& src : vertices) {
            for (const auto& dest : vertices) {
                if (src != dest) {
                    int dist = getDistance(src, dest);
                    if (dist == -1) {
                        return -1;  // Graph is disconnected
                    }
                    diameter = max(diameter, dist);
                }
            }
        }
        
        return diameter;
    }
    
    /**
     * Calculates the graph radius (minimum eccentricity among all vertices)
     * Eccentricity of a vertex = maximum distance from it to any other vertex
     * @return Graph radius, -1 if graph is disconnected
     */
    int getRadius() const {
        if (vertices.empty()) return 0;
        if (vertices.size() == 1) return 0;
        
        int radius = INT_MAX;
        
        for (const auto& src : vertices) {
            int eccentricity = 0;
            
            for (const auto& dest : vertices) {
                if (src != dest) {
                    int dist = getDistance(src, dest);
                    if (dist == -1) {
                        return -1;  // Graph is disconnected
                    }
                    eccentricity = max(eccentricity, dist);
                }
            }
            
            radius = min(radius, eccentricity);
        }
        
        return radius;
    }
    
    /**
     * Calculates the girth (length of shortest cycle) of the graph
     * Also known as circumference when referring to smallest cycle
     * @return Girth of the graph, -1 if no cycle exists, INT_MAX if acyclic
     */
    int getGirth() const {
        if (vertices.empty()) return -1;
        
        int girth = INT_MAX;
        
        // For each vertex, do BFS and find shortest cycle through it
        for (const auto& start : vertices) {
            map<T, int> distance;
            queue<pair<T, T>> q;  // (current vertex, parent vertex)
            
            distance[start] = 0;
            
            auto it = adjList.find(start);
            if (it != adjList.end()) {
                for (const auto& neighbor : it->second) {
                    q.push({neighbor.first, start});
                    distance[neighbor.first] = 1;
                }
            }
            
            while (!q.empty()) {
                T current = q.front().first;
                T parent = q.front().second;
                q.pop();
                
                auto currentIt = adjList.find(current);
                if (currentIt != adjList.end()) {
                    for (const auto& neighbor : currentIt->second) {
                        if (distance.find(neighbor.first) == distance.end()) {
                            distance[neighbor.first] = distance[current] + 1;
                            q.push({neighbor.first, current});
                        } else if (neighbor.first != parent) {
                            // Found a cycle
                            int cycleLength = distance[current] + distance[neighbor.first] + 1;
                            girth = min(girth, cycleLength);
                        }
                    }
                }
            }
        }
        
        return (girth == INT_MAX) ? -1 : girth;
    }
    
    /**
     * Gets the circumference (length of longest cycle) of the graph
     * @return Circumference of the graph, -1 if no cycle exists
     */
    int getCircumference() const {
        if (vertices.empty()) return -1;
        
        int circumference = 0;
        
        // For each vertex, do DFS to find longest cycle
        for (const auto& start : vertices) {
            map<T, int> distance;
            set<T> visited;
            circumference = max(circumference, 
                               dfsLongestCycle(start, start, visited, distance, 0));
        }
        
        return (circumference == 0) ? -1 : circumference;
    }
    
    /**
     * Displays comprehensive graph properties
     * @param use_colored_output: Enable colored output (default: false)
     */
    void displayProperties(bool use_colored_output = false) const {
        cprint(use_colored_output, "\n=== Graph Properties ===\n", BRIGHT_WHITE, true);
        
        cprint(use_colored_output, "Number of Vertices: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, to_string(getNumVertices()) + "\n", BRIGHT_BLUE);
        
        cprint(use_colored_output, "Number of Edges: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, to_string(getNumEdges()) + "\n", BRIGHT_BLUE);
        
        if (!vertices.empty()) {
            cprint(use_colored_output, "Minimum Degree (Min vertex connections): ", BRIGHT_WHITE, true);
            cprint(use_colored_output, to_string(getMinDegree()) + "\n", BRIGHT_CYAN);
            
            cprint(use_colored_output, "Maximum Degree (Max vertex connections): ", BRIGHT_WHITE, true);
            cprint(use_colored_output, to_string(getMaxDegree()) + "\n", BRIGHT_CYAN);
            
            int radius = getRadius();
            cprint(use_colored_output, "Graph Radius (Min eccentricity): ", BRIGHT_WHITE, true);
            if (radius == -1) {
                cprint(use_colored_output, "Undefined (disconnected)\n", BRIGHT_RED);
            } else {
                cprint(use_colored_output, to_string(radius) + "\n", BRIGHT_GREEN);
            }
            
            int diameter = getDiameter();
            cprint(use_colored_output, "Graph Diameter (Max shortest path): ", BRIGHT_WHITE, true);
            if (diameter == -1) {
                cprint(use_colored_output, "Undefined (disconnected)\n", BRIGHT_RED);
            } else {
                cprint(use_colored_output, to_string(diameter) + "\n", BRIGHT_GREEN);
            }
            
            int girth = getGirth();
            cprint(use_colored_output, "Girth (Shortest cycle): ", BRIGHT_WHITE, true);
            if (girth == -1) {
                cprint(use_colored_output, "No cycle (Acyclic)\n", BRIGHT_YELLOW);
            } else {
                cprint(use_colored_output, to_string(girth) + "\n", BRIGHT_MAGNETA);
            }
            
            int circumference = getCircumference();
            cprint(use_colored_output, "Circumference (Longest cycle): ", BRIGHT_WHITE, true);
            if (circumference == -1) {
                cprint(use_colored_output, "No cycle (Acyclic)\n", BRIGHT_YELLOW);
            } else {
                cprint(use_colored_output, to_string(circumference) + "\n", BRIGHT_MAGNETA);
            }
        }
        
        cprint(use_colored_output, "Connected: ", BRIGHT_WHITE, true);
        if (isConnected()) {
            cprint(use_colored_output, "Yes\n", BRIGHT_GREEN);
        } else {
            cprint(use_colored_output, "No\n", BRIGHT_RED);
        }
        
        cprint(use_colored_output, "========================\n", BRIGHT_WHITE, true);
        cout << endl;
    }
    
    virtual ~Graph() {}

private:

    /**
     * Helper function for DFS traversal with timing
     */
    void DFSUtil(T vertex, set<T>& visited, vector<T>& traversal,
                 map<T, int>& discoveryTime, map<T, int>& finishTime,
                 map<T, T>& parent, int& time, bool use_colored_output) const {
        visited.insert(vertex);
        traversal.push_back(vertex);
        discoveryTime[vertex] = ++time;

        // Print discovery
        cprint(use_colored_output, "  Discovered: ", BRIGHT_WHITE);
        cprint(use_colored_output, "[", BRIGHT_WHITE);
        cprint(use_colored_output, vertex, BRIGHT_BLUE);
        cprint(use_colored_output, "]", BRIGHT_WHITE);
        cprint(use_colored_output, " at time ", BRIGHT_WHITE);
        cprint(use_colored_output, to_string(discoveryTime[vertex]), BRIGHT_CYAN);

        auto it = adjList.find(vertex);
        if (it != adjList.end()) {
            cprint(use_colored_output, " → Exploring: ", BRIGHT_YELLOW);
            bool first = true;
            for (const auto& neighbor : it->second) {
                if (!first) cprint(use_colored_output, ", ", BRIGHT_WHITE);
                cprint(use_colored_output, neighbor.first,
                       visited.find(neighbor.first) == visited.end() ?
                       BRIGHT_GREEN : BRIGHT_RED);
                first = false;
            }
        }
        cout << "\n";

        // Explore neighbors
        if (it != adjList.end()) {
            for (const auto& neighbor : it->second) {
                if (visited.find(neighbor.first) == visited.end()) {
                    parent[neighbor.first] = vertex;
                    DFSUtil(neighbor.first, visited, traversal, discoveryTime,
                           finishTime, parent, time, use_colored_output);
                }
            }
        }

        finishTime[vertex] = ++time;

        // Print finish
        cprint(use_colored_output, "  Finished:   ", BRIGHT_WHITE);
        cprint(use_colored_output, "[", BRIGHT_WHITE);
        cprint(use_colored_output, vertex, BRIGHT_BLUE);
        cprint(use_colored_output, "]", BRIGHT_WHITE);
        cprint(use_colored_output, " at time ", BRIGHT_WHITE);
        cprint(use_colored_output, to_string(finishTime[vertex]) + "\n", BRIGHT_CYAN);
    }

    /**
     * Helper function to print BFS tree structure
     */
    void printBFSTree(T vertex, const map<T, T>& parent,
                     const map<T, int>& level, bool use_colored_output,
                     const string& prefix = "", bool isLast = true) const {
        // Print current vertex
        cprint(use_colored_output, prefix);
        cprint(use_colored_output, isLast ? "└── " : "├── ", BRIGHT_GREEN);
        cprint(use_colored_output, "[", YELLOW);
        cprint(use_colored_output, vertex, BRIGHT_BLUE);
        cprint(use_colored_output, "]", YELLOW);

        int currentLevel = level.at(vertex);
        cprint(use_colored_output, " (L" + to_string(currentLevel) + ")\n",
               BRIGHT_YELLOW);

        // Find children (vertices whose parent is current vertex)
        vector<T> children;
        for (const auto& p : parent) {
            if (p.second == vertex && p.first != vertex) {
                children.push_back(p.first);
            }
        }

        // Sort children for consistent output
        sort(children.begin(), children.end());

        // Print children
        for (size_t i = 0; i < children.size(); i++) {
            string newPrefix = prefix + (isLast ? "    " : "│   ");
            printBFSTree(children[i], parent, level, use_colored_output,
                        newPrefix, i == children.size() - 1);
        }
    }

    /**
     * Helper function to print DFS tree structure
     */
    void printDFSTree(T vertex, const map<T, T>& parent, int depth,
                     bool use_colored_output, set<T> printed,
                     const string& prefix = "", bool isLast = true) const {
        if (printed.find(vertex) != printed.end()) return;
        printed.insert(vertex);

        // Print current vertex
        cprint(use_colored_output, prefix, BRIGHT_WHITE);
        cprint(use_colored_output, isLast ? "└── " : "├── ", BRIGHT_GREEN);
        cprint(use_colored_output, "[", YELLOW);
        cprint(use_colored_output, vertex, BRIGHT_BLUE);
        cprint(use_colored_output, "]", YELLOW);
        cprint(use_colored_output, " (depth " + to_string(depth) + ")\n",
               BRIGHT_YELLOW);

        // Find children
        vector<T> children;
        for (const auto& p : parent) {
            if (p.second == vertex && p.first != vertex) {
                children.push_back(p.first);
            }
        }

        sort(children.begin(), children.end());

        // Print children
        for (size_t i = 0; i < children.size(); i++) {
            string newPrefix = prefix + (isLast ? "    " : "│   ");
            printDFSTree(children[i], parent, depth + 1, use_colored_output,
                        printed, newPrefix, i == children.size() - 1);
        }
    }

    /**
     * Helper function for finding longest cycle using DFS
     */
    int dfsLongestCycle(T start, T current, set<T>& visited, 
                        map<T, int>& distance, int dist) const {
        visited.insert(current);
        distance[current] = dist;
        
        int maxCycle = 0;
        
        auto it = adjList.find(current);
        if (it != adjList.end()) {
            for (const auto& neighbor : it->second) {
                if (neighbor.first == start && dist > 1) {
                    // Found a cycle back to start
                    maxCycle = max(maxCycle, dist + 1);
                } else if (visited.find(neighbor.first) == visited.end()) {
                    maxCycle = max(maxCycle, 
                                  dfsLongestCycle(start, neighbor.first, visited, 
                                                 distance, dist + 1));
                }
            }
        }
        
        visited.erase(current);
        return maxCycle;
    }
};

// ============================================================================
// SPECIFIC GRAPH TYPES
// ============================================================================

/**
 * Null Graph: A graph with vertices but no edges
 * Also known as an edgeless graph
 */
template<typename T>
class NullGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates a null graph
     */
    NullGraph() : Graph<T>(false, false) {}
    
    /**
     * Adds vertices only (no edges allowed)
     */
    void addVertex(T vertex) {
        Graph<T>::addVertex(vertex);
    }
    
    /**
     * Overrides addEdge to prevent edge addition in null graph
     */
    void addEdge(T src, T dest, int weight = 1) override {
        throw logic_error("Cannot add edges to a Null Graph");
    }
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Null Graph with ", BRIGHT_YELLOW, true);
        cprint(use_colored_output, this->numVertices, BRIGHT_BLUE);
        cprint(use_colored_output, " vertices and 0 edges\n", BRIGHT_YELLOW);
        
        if (!this->vertices.empty()) {
            cprint(use_colored_output, "Vertices: ", BRIGHT_MAGNETA, true);
            bool first = true;
            for (const auto& v : this->vertices) {
                if (!first) cout << ", ";
                cprint(use_colored_output, v, BRIGHT_CYAN);
                first = false;
            }
            cout << endl;
        }
    }
};

/**
 * Trivial Graph: A graph with only one vertex and no edges
 * The simplest possible graph
 */
template<typename T>
class TrivialGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates a trivial graph with exactly 1 vertex
     */
    TrivialGraph(T vertex) : Graph<T>(false, false) {
        this->addVertex(vertex);
    }
    
    /**
     * Overrides addEdge to prevent edge addition in trivial graph
     */
    void addEdge(T src, T dest, int weight = 1) override {
        throw logic_error("Cannot add edges to a Trivial Graph");
    }
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Trivial Graph with 1 vertex and 0 edges\n", BRIGHT_YELLOW, true);
        cprint(use_colored_output, "Vertex: ", BRIGHT_MAGNETA, true);
        cprint(use_colored_output, *this->vertices.begin(), BRIGHT_BLUE);
        cout << endl;
    }
};

/**
 * Undirected Graph: Edges have no direction
 * If there's an edge from u to v, there's also an edge from v to u
 */
template<typename T>
class UndirectedGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates an undirected graph
     */
    UndirectedGraph() : Graph<T>(false, false) {}
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Undirected Graph:\n", BRIGHT_YELLOW, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Directed Graph (Digraph): Edges have direction
 * An edge from u to v doesn't imply an edge from v to u
 */
template<typename T>
class DirectedGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates a directed graph
     */
    DirectedGraph() : Graph<T>(true, false) {}
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Directed Graph:\n", BRIGHT_GREEN, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Connected Graph: There exists a path between every pair of vertices
 * All vertices are reachable from any starting vertex
 */
template<typename T>
class ConnectedGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates a connected graph
     */
    ConnectedGraph() : Graph<T>(false, false) {}
    
    /**
     * Validates and displays connection status
     */
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Connected Graph (Connected: ", BRIGHT_CYAN, true);
        if (this->isConnected()) {
            cprint(use_colored_output, "Yes", BRIGHT_GREEN);
        } else {
            cprint(use_colored_output, "No", BRIGHT_RED);
        }
        cprint(use_colored_output, "):\n", BRIGHT_CYAN, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Disconnected Graph: Contains at least two vertices with no path between them
 * The graph has multiple connected components
 */
template<typename T>
class DisconnectedGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates a disconnected graph
     */
    DisconnectedGraph() : Graph<T>(false, false) {}
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Disconnected Graph (Connected: ", BRIGHT_MAGNETA, true);
        if (this->isConnected()) {
            cprint(use_colored_output, "Yes", BRIGHT_GREEN);
        } else {
            cprint(use_colored_output, "No", BRIGHT_RED);
        }
        cprint(use_colored_output, "):\n", BRIGHT_MAGNETA, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Complete Graph: Every pair of distinct vertices is connected by a unique edge
 * A graph with n vertices has n(n-1)/2 edges
 */
template<typename T>
class CompleteGraph : public Graph<T> {
private:
    bool isComplete;
    
public:
    /**
     * Constructor: Creates a complete graph
     */
    CompleteGraph() : Graph<T>(false, false), isComplete(false) {}
    
    /**
     * Adds a vertex and connects it to all existing vertices
     */
    void addVertex(T vertex) {
        if (this->vertices.find(vertex) != this->vertices.end()) {
            return;
        }
        
        // Connect new vertex to all existing vertices
        for (const auto& v : this->vertices) {
            Graph<T>::addEdge(v, vertex);
        }
        
        Graph<T>::addVertex(vertex);
    }
    
    void display(bool use_colored_output = false) const override {
        cout << "Complete Graph K" << this->numVertices << " (All vertices connected):" << endl;
        cprint(use_colored_output, "Complete Graph\nNo of Vertices: ", BRIGHT_WHITE, true);
        cprint(use_colored_output, this->numVertices, GREEN, true);
        cprint(use_colored_output, "\n(All vertices are connected)\n", BRIGHT_WHITE, true);
        Graph<T>::display();
    }
};

/**
 * Cyclic Graph: Contains at least one cycle
 * A cycle is a path that starts and ends at the same vertex
 */
template<typename T>
class CyclicGraph : public Graph<T> {
private:
    /**
     * Helper function to detect cycle using DFS
     */
    bool hasCycleDFS(T vertex, set<T>& visited, T parent) const {
        visited.insert(vertex);
        
        for (const auto& neighbor : this->adjList.at(vertex)) {
            if (visited.find(neighbor.first) == visited.end()) {
                if (hasCycleDFS(neighbor.first, visited, vertex)) {
                    return true;
                }
            } else if (neighbor.first != parent) {
                return true;
            }
        }
        return false;
    }
    
public:
    /**
     * Constructor: Creates a cyclic graph
     * @param directed: Whether graph is directed
     */
    CyclicGraph(bool directed = false) : Graph<T>(directed, false) {}
    
    /**
     * Checks if graph contains a cycle
     * @return True if graph has at least one cycle
     */
    bool hasCycle() const {
        set<T> visited;
        for (const auto& vertex : this->vertices) {
            if (visited.find(vertex) == visited.end()) {
                T parent = T();
                if (hasCycleDFS(vertex, visited, parent)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Cyclic Graph (Has Cycle: ", BRIGHT_MAGNETA, true);
        if (hasCycle()) {
            cprint(use_colored_output, "Yes", BRIGHT_GREEN);
        } else {
            cprint(use_colored_output, "No", BRIGHT_RED);
        }
        cprint(use_colored_output, "):\n", BRIGHT_MAGNETA, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Directed Acyclic Graph (DAG): A directed graph with no cycles
 * Used in scheduling, dependency resolution, etc.
 */
template<typename T>
class DirectedAcyclicGraph : public Graph<T> {
private:
    /**
     * Helper function to detect cycle in directed graph using DFS
     */
    bool hasCycleDFS(T vertex, set<T>& visited, set<T>& recStack) const {
        visited.insert(vertex);
        recStack.insert(vertex);
        
        for (const auto& neighbor : this->adjList.at(vertex)) {
            if (visited.find(neighbor.first) == visited.end()) {
                if (hasCycleDFS(neighbor.first, visited, recStack)) {
                    return true;
                }
            } else if (recStack.find(neighbor.first) != recStack.end()) {
                return true;
            }
        }
        
        recStack.erase(vertex);
        return false;
    }
    
public:
    /**
     * Constructor: Creates a DAG
     */
    DirectedAcyclicGraph() : Graph<T>(true, false) {}
    
    /**
     * Validates that adding edge doesn't create a cycle
     */
    void addEdge(T src, T dest, int weight = 1) override {
        Graph<T>::addEdge(src, dest, weight);
        
        // Check if adding this edge created a cycle
        set<T> visited, recStack;
        for (const auto& vertex : this->vertices) {
            if (visited.find(vertex) == visited.end()) {
                if (hasCycleDFS(vertex, visited, recStack)) {
                    // Remove the edge that created the cycle
                    auto& neighbors = this->adjList[src];
                    neighbors.erase(
                        remove_if(neighbors.begin(), neighbors.end(),
                                  [dest](const pair<T,int>& p) { return p.first == dest; }),
                        neighbors.end()
                    );
                    throw logic_error("Adding this edge would create a cycle in DAG");
                }
            }
        }
    }
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Directed Acyclic Graph (DAG):\n", BRIGHT_GREEN, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Bipartite Graph: Vertices can be divided into two disjoint sets
 * Every edge connects a vertex from one set to a vertex in the other set
 */
template<typename T>
class BipartiteGraph : public Graph<T> {
private:
    /**
     * Checks if graph is bipartite using BFS coloring
     */
    bool isBipartiteCheck() const {
        if (this->vertices.empty()) return true;
        
        map<T, int> color; // -1: uncolored, 0: color1, 1: color2
        
        for (const auto& start : this->vertices) {
            if (color.find(start) != color.end()) continue;
            
            queue<T> q;
            q.push(start);
            color[start] = 0;
            
            while (!q.empty()) {
                T vertex = q.front();
                q.pop();
                
                for (const auto& neighbor : this->adjList.at(vertex)) {
                    if (color.find(neighbor.first) == color.end()) {
                        color[neighbor.first] = 1 - color[vertex];
                        q.push(neighbor.first);
                    } else if (color[neighbor.first] == color[vertex]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    
public:
    /**
     * Constructor: Creates a bipartite graph
     */
    BipartiteGraph() : Graph<T>(false, false) {}
    
    /**
     * Validates that graph remains bipartite after adding edge
     */
    void addEdge(T src, T dest, int weight = 1) override {
        Graph<T>::addEdge(src, dest, weight);
        
        if (!isBipartiteCheck()) {
            // Remove the edge that broke bipartiteness
            auto& neighbors = this->adjList[src];
            neighbors.erase(
                remove_if(neighbors.begin(), neighbors.end(),
                          [dest](const pair<T,int>& p) { return p.first == dest; }),
                neighbors.end()
            );
            
            auto& neighbors2 = this->adjList[dest];
            neighbors2.erase(
                remove_if(neighbors2.begin(), neighbors2.end(),
                          [src](const pair<T,int>& p) { return p.first == src; }),
                neighbors2.end()
            );
            
            throw logic_error("Adding this edge would break bipartite property");
        }
    }
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Bipartite Graph (Is Bipartite: ", BRIGHT_CYAN, true);
        if (isBipartiteCheck()) {
            cprint(use_colored_output, "Yes", BRIGHT_GREEN);
        } else {
            cprint(use_colored_output, "No", BRIGHT_RED);
        }
        cprint(use_colored_output, "):\n", BRIGHT_CYAN, true);
        Graph<T>::display(use_colored_output);
    }
};

/**
 * Weighted Graph: Each edge has an associated weight or cost
 * Used in shortest path algorithms, minimum spanning tree, etc.
 */
template<typename T>
class WeightedGraph : public Graph<T> {
public:
    /**
     * Constructor: Creates a weighted graph
     * @param directed: Whether graph is directed
     */
    WeightedGraph(bool directed = false) : Graph<T>(directed, true) {}
    
    void display(bool use_colored_output = false) const override {
        cprint(use_colored_output, "Weighted Graph:\n", BRIGHT_MAGNETA, true);
        Graph<T>::display(use_colored_output);
    }
};
#endif

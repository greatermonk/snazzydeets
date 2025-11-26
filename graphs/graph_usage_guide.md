# Graph Data Structure - Usage Guide

A comprehensive C++ graph implementation supporting 11 different graph types with generic type support (int, float, char, string, custom types).

## Table of Contents
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Basic Usage](#basic-usage)
- [Colored Output](#colored-output)
- [Graph Types and Use Cases](#graph-types-and-use-cases)
- [Method Reference](#method-reference)
- [Advanced Examples](#advanced-examples)
- [Best Practices](#best-practices)
- [Common Patterns](#common-patterns)
- [Performance Considerations](#performance-considerations)

---

## Quick Start

```cpp
#include "graph.h"

int main() {
    // Create a directed graph with integer vertices
    DirectedGraph<int> graph;
    
    // Add edges (vertices are auto-created)
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    
    // Display the graph
    graph.display();
    
    return 0;
}
```

**Compile:**
```bash
g++ -std=c++11 your_program.cpp -o your_program
./your_program
```

---

## Installation

1. **Download** the `graph.cpp` file
2. **Include** in your project:
   - Option A: Use as header by renaming to `graph.h`
   - Option B: Compile separately and link
3. **Compile** with C++11 or later

```bash
# Option A: Single file compilation
g++ -std=c++11 main.cpp -o program

# Option B: Separate compilation
g++ -std=c++11 -c graph.cpp -o graph.o
g++ -std=c++11 main.cpp graph.o -o program
```

---

## Basic Usage

### Creating a Graph

```cpp
// Syntax: GraphType<VertexType> graphName;

DirectedGraph<int> intGraph;           // Directed graph with integers
UndirectedGraph<string> stringGraph;   // Undirected graph with strings
WeightedGraph<char> charGraph(true);   // Weighted directed graph with chars
```

### Adding Vertices

```cpp
// Vertices are automatically added when creating edges
graph.addEdge(1, 2);  // Adds vertices 1 and 2 if they don't exist

// For graphs that need explicit vertex addition (Null, Complete):
NullGraph<int> nullG;
nullG.addVertex(1);
nullG.addVertex(2);
nullG.addVertex(3);
```

### Adding Edges

```cpp
// Unweighted graph
graph.addEdge(source, destination);

// Weighted graph
weightedGraph.addEdge(source, destination, weight);

// Examples:
DirectedGraph<int> dg;
dg.addEdge(1, 2);        // Edge from 1 to 2

WeightedGraph<string> wg(true);  // directed
wg.addEdge("A", "B", 10);        // A -> B with weight 10
```

### Displaying Graphs

```cpp
graph.display();  // Prints adjacency list representation
```

### Getting Graph Information

```cpp
int vertices = graph.getNumVertices();  // Get vertex count
int edges = graph.getNumEdges();        // Get edge count
bool connected = graph.isConnected();    // Check connectivity
set<T> verts = graph.getVertices();     // Get all vertices
```

---

## Graph Types and Use Cases

### 1. **Null Graph** - No Edges
```cpp
NullGraph<int> graph;
graph.addVertex(1);
graph.addVertex(2);
graph.addVertex(3);
// Cannot add edges
```

**Use Cases:**
- Initial state in graph construction algorithms
- Representing isolated entities
- Testing vertex-only operations

---

### 2. **Trivial Graph** - Single Vertex
```cpp
TrivialGraph<char> graph('A');
// Single vertex, no edges
```

**Use Cases:**
- Base case in recursive algorithms
- Singleton pattern implementations
- Minimal graph testing

---

### 3. **Undirected Graph** - Bidirectional Edges
```cpp
UndirectedGraph<string> socialNetwork;
socialNetwork.addEdge("Alice", "Bob");      // Alice ↔ Bob
socialNetwork.addEdge("Bob", "Charlie");    // Bob ↔ Charlie
```

**Use Cases:**
- **Social Networks**: Friendships (symmetric relationships)
- **Road Networks**: Bidirectional roads
- **Computer Networks**: Peer-to-peer connections
- **Collaboration Graphs**: Co-authorship, team projects

**Example: Social Network**
```cpp
UndirectedGraph<string> friends;
friends.addEdge("Alice", "Bob");
friends.addEdge("Bob", "Charlie");
friends.addEdge("Alice", "David");

if (friends.isConnected()) {
    cout << "Everyone is connected through mutual friends!" << endl;
}
```

---

### 4. **Directed Graph** - One-way Edges
```cpp
DirectedGraph<int> webGraph;
webGraph.addEdge(1, 2);  // Page 1 -> Page 2
webGraph.addEdge(2, 3);  // Page 2 -> Page 3
webGraph.addEdge(3, 1);  // Page 3 -> Page 1
```

**Use Cases:**
- **Web Page Links**: Hyperlinks (one-way)
- **Twitter Followers**: A follows B (not necessarily vice versa)
- **State Machines**: State transitions
- **Dependencies**: Module/package dependencies
- **Game AI**: State and decision trees

**Example: Task Dependencies**
```cpp
DirectedGraph<string> tasks;
tasks.addEdge("Design", "Development");
tasks.addEdge("Development", "Testing");
tasks.addEdge("Testing", "Deployment");
```

---

### 5. **Connected Graph** - All Vertices Reachable
```cpp
ConnectedGraph<int> network;
network.addEdge(1, 2);
network.addEdge(2, 3);
network.addEdge(3, 4);
network.display();  // Shows connectivity status
```

**Use Cases:**
- **Network Reliability**: Ensure all nodes can communicate
- **Transportation Networks**: All cities reachable
- **Sensor Networks**: Full coverage validation
- **Communication Systems**: No isolated components

**Validation:**
```cpp
if (network.isConnected()) {
    cout << "Network is fully connected!" << endl;
} else {
    cout << "Warning: Network has isolated components!" << endl;
}
```

---

### 6. **Disconnected Graph** - Isolated Components
```cpp
DisconnectedGraph<string> regions;
// Component 1
regions.addEdge("NYC", "Boston");
regions.addEdge("Boston", "Philly");

// Component 2 (isolated)
regions.addEdge("LA", "SF");
```

**Use Cases:**
- **Cluster Analysis**: Separate communities
- **Island Detection**: Geographic separation
- **Component Analysis**: Finding isolated subsystems
- **Network Failure Modeling**: Simulating disconnections

---

### 7. **Complete Graph** - All Vertices Connected
```cpp
CompleteGraph<char> fullMesh;
fullMesh.addVertex('A');
fullMesh.addVertex('B');
fullMesh.addVertex('C');
fullMesh.addVertex('D');
// Automatically creates all possible edges
```

**Use Cases:**
- **Fully Connected Networks**: Mesh topology
- **Tournament Scheduling**: Round-robin (everyone plays everyone)
- **Clique Detection**: Finding fully connected subgraphs
- **Broadcast Networks**: Every node can reach every other node

**Properties:**
- N vertices → N(N-1)/2 edges
- Maximum connectivity
- No single point of failure

---

### 8. **Cyclic Graph** - Contains Cycles
```cpp
CyclicGraph<int> circuit;
circuit.addEdge(1, 2);
circuit.addEdge(2, 3);
circuit.addEdge(3, 4);
circuit.addEdge(4, 1);  // Creates cycle

if (circuit.hasCycle()) {
    cout << "Cycle detected!" << endl;
}
```

**Use Cases:**
- **Circular Dependencies**: Detecting problematic circular references
- **Circular Routes**: Delivery circuits, patrol routes
- **Feedback Systems**: Control systems with feedback loops
- **Deadlock Detection**: Finding circular wait conditions

---

### 9. **Directed Acyclic Graph (DAG)** - No Cycles
```cpp
DirectedAcyclicGraph<string> buildSystem;
buildSystem.addEdge("Source", "Compile");
buildSystem.addEdge("Compile", "Link");
buildSystem.addEdge("Link", "Deploy");
// buildSystem.addEdge("Deploy", "Source");  // Would throw error!
```

**Use Cases:**
- **Build Systems**: Makefile dependencies, compilation order
- **Task Scheduling**: Project management (PERT/CPM)
- **Version Control**: Git commit history
- **Data Processing Pipelines**: ETL workflows
- **Course Prerequisites**: Academic planning
- **Inheritance Hierarchies**: Class relationships

**Example: Build Pipeline**
```cpp
DirectedAcyclicGraph<string> pipeline;
pipeline.addEdge("fetch_data", "clean_data");
pipeline.addEdge("clean_data", "transform_data");
pipeline.addEdge("transform_data", "load_data");
pipeline.addEdge("load_data", "generate_report");
```

**Cycle Prevention:**
```cpp
try {
    dag.addEdge("Deploy", "Source");  // Would create cycle
} catch (const logic_error& e) {
    cout << "Cannot add edge: " << e.what() << endl;
}
```

---

### 10. **Bipartite Graph** - Two-Set Division
```cpp
BipartiteGraph<string> matching;
// Set 1: Students
// Set 2: Courses
matching.addEdge("Alice", "Math");
matching.addEdge("Alice", "Physics");
matching.addEdge("Bob", "Math");
matching.addEdge("Charlie", "Physics");
```

**Use Cases:**
- **Job Matching**: Candidates ↔ Jobs
- **Student-Course**: Enrollment systems
- **Resource Allocation**: Tasks ↔ Workers
- **Network Flow**: Source ↔ Sink problems
- **Recommendation Systems**: Users ↔ Items
- **Dating Apps**: People ↔ Compatible matches

**Example: Job Assignment**
```cpp
BipartiteGraph<string> jobMatch;
jobMatch.addEdge("Developer_A", "Project_1");
jobMatch.addEdge("Developer_A", "Project_3");
jobMatch.addEdge("Developer_B", "Project_2");
jobMatch.addEdge("Designer_C", "Project_1");
```

**Validation:**
```cpp
// Graph validates bipartite property automatically
try {
    biGraph.addEdge("Student1", "Student2");  // Might break bipartiteness
} catch (const logic_error& e) {
    cout << "Edge would violate bipartite property!" << endl;
}
```

---

### 11. **Weighted Graph** - Edges with Costs
```cpp
WeightedGraph<string> routes(true);  // directed
routes.addEdge("NYC", "Boston", 215);      // 215 miles
routes.addEdge("Boston", "Philly", 305);   // 305 miles
routes.addEdge("NYC", "Philly", 95);       // 95 miles
```

**Use Cases:**
- **Navigation Systems**: Roads with distances/time
- **Network Routing**: Links with bandwidth/latency
- **Flight Networks**: Routes with prices/duration
- **Logistics**: Shipping costs, delivery time
- **Social Networks**: Relationship strength
- **Shortest Path Problems**: Dijkstra, Bellman-Ford

**Example: Shipping Network**
```cpp
WeightedGraph<string> shipping(true);
shipping.addEdge("Warehouse", "Store_A", 50);   // $50 shipping
shipping.addEdge("Warehouse", "Store_B", 75);   // $75 shipping
shipping.addEdge("Store_A", "Store_B", 25);     // $25 shipping
```

**Undirected vs Directed:**
```cpp
// Undirected weighted graph (bidirectional costs)
WeightedGraph<string> roads(false);
roads.addEdge("CityA", "CityB", 100);  // Same cost both ways

// Directed weighted graph (one-way or different costs)
WeightedGraph<string> flights(true);
flights.addEdge("NYC", "LA", 300);     // NYC → LA: $300
flights.addEdge("LA", "NYC", 250);     // LA → NYC: $250 (different!)
```

---

## Method Reference

### Constructor Parameters

| Graph Type | Template | Constructor Args | Notes |
|------------|----------|------------------|-------|
| `Graph<T>` | Required | `bool directed, bool weighted` | Base class |
| `NullGraph<T>` | Required | None | No edges allowed |
| `TrivialGraph<T>` | Required | `T vertex` | Single vertex |
| `UndirectedGraph<T>` | Required | None | Bidirectional edges |
| `DirectedGraph<T>` | Required | None | One-way edges |
| `ConnectedGraph<T>` | Required | None | Validates connectivity |
| `DisconnectedGraph<T>` | Required | None | Allows isolated components |
| `CompleteGraph<T>` | Required | None | Auto-generates edges |
| `CyclicGraph<T>` | Required | `bool directed = false` | Detects cycles |
| `DirectedAcyclicGraph<T>` | Required | None | Prevents cycles |
| `BipartiteGraph<T>` | Required | None | Validates two-set property |
| `WeightedGraph<T>` | Required | `bool directed = false` | Edges with weights |

### Core Methods

#### `addVertex(T vertex)`
Explicitly adds a vertex to the graph.

```cpp
CompleteGraph<int> graph;
graph.addVertex(1);  // Add vertex 1
graph.addVertex(2);  // Add vertex 2 (auto-connects to 1)
```

#### `addEdge(T src, T dest, int weight = 1)`
Adds an edge between two vertices.

**Parameters:**
- `src`: Source vertex
- `dest`: Destination vertex
- `weight`: Edge weight (default = 1)

```cpp
// Unweighted
graph.addEdge(1, 2);

// Weighted
weightedGraph.addEdge("A", "B", 50);
```

**Auto-creates vertices** if they don't exist.

#### `display(bool use_colored_output = false) const`
Prints the graph's adjacency list representation.

```cpp
// Without colors
graph.display();
graph.display(false);

// With colors (ANSI terminal colors)
graph.display(true);
```

**Output formats:**
- Directed: `vertex --> neighbor1, neighbor2`
- Undirected: `vertex --- neighbor1, neighbor2`
- Weighted: `vertex --(weight)--> neighbor`

**Color Scheme:**
- **Vertices**: Bright Blue
- **Undirected Edges**: Bright Yellow (`---`)
- **Directed Edges**: Bright Green (`-->`)
- **Weights**: Bright Magenta
- **Empty Set (∅)**: Bright Red
- **Headers**: Bold Bright White

---

## Colored Output

The implementation includes built-in support for ANSI colored terminal output to enhance readability.

### Enabling Colors

```cpp
// Set color flag
bool USE_COLORS = true;

// Display with colors
graph.display(USE_COLORS);
graph.displayProperties(USE_COLORS);
```

### Color Scheme

| Element | Color | Usage |
|---------|-------|-------|
| **Vertices** | Bright Blue | All vertex names/IDs |
| **Undirected Edges** | Bright Yellow | `---` connectors |
| **Directed Edges** | Bright Green | `-->` arrows |
| **Weights** | Bright Cyan (values)<br>Bright Magenta (brackets) | Edge weights in weighted graphs |
| **Empty Set (∅)** | Bright Red | Vertices with no edges |
| **Graph Names** | Bright Yellow/Green/Cyan/Magenta | Graph type headers |
| **Status (Yes)** | Bright Green | Connected, Has Cycle, etc. |
| **Status (No/Undefined)** | Bright Red | Disconnected, No Cycle, etc. |
| **Property Names** | Bold Bright White | "Number of Vertices", etc. |
| **Error Messages** | Red | Exception messages |

### Example Output

```cpp
DirectedGraph<string> graph;
graph.addEdge("A", "B");
graph.addEdge("B", "C");
graph.display(true);
```

**Colored Output:**
```
Directed Graph:                        [Bold Bright White + Bright Green]
Graph (Adjacency List for directed graph):
-----------------------
  A --> B                              [A: Bright Blue, -->: Bright Green, B: Bright Blue]
  B --> C                              [B: Bright Blue, -->: Bright Green, C: Bright Blue]
  C --> ∅                              [C: Bright Blue, ∅: Bright Red]
```

### Custom Color Helper

The implementation includes a `cprint()` helper function:

```cpp
template<typename T>
void cprint(bool use_color, const T& text, 
            const char* color = BRIGHT_WHITE, 
            bool make_bold = false);
```

**Usage:**
```cpp
bool colors = true;
cprint(colors, "Hello", BRIGHT_GREEN);           // Green text
cprint(colors, "World", BRIGHT_BLUE, true);      // Bold blue text
cprint(false, "No color", RED);                   // Plain text (color ignored)
```

### Available Colors

From the `colors` namespace:

**Standard Colors:**
- `BLACK`, `RED`, `GREEN`, `YELLOW`, `BLUE`, `MAGNETA`, `CYAN`, `WHITE`

**Bright Colors:**
- `BRIGHT_BLACK`, `BRIGHT_RED`, `BRIGHT_GREEN`, `BRIGHT_YELLOW`
- `BRIGHT_BLUE`, `BRIGHT_MAGNETA`, `BRIGHT_CYAN`, `BRIGHT_WHITE`

**Special:**
- `BOLD` - Bold text modifier
- `RESET` - Reset to default terminal colors

### Disabling Colors

```cpp
// Method 1: Pass false to display methods
graph.display(false);
graph.displayProperties(false);

// Method 2: Set global flag
bool USE_COLORS = false;
graph.display(USE_COLORS);
```

**When to disable:**
- Redirecting output to files: `./program > output.txt`
- Terminals that don't support ANSI codes (old Windows CMD)
- Automated testing/scripting
- Accessibility requirements

### Terminal Compatibility

**Supported:**
- ✅ Linux/Unix terminals (GNOME Terminal, Konsole, etc.)
- ✅ macOS Terminal and iTerm2
- ✅ Windows Terminal (Windows 10+)
- ✅ PowerShell (Windows 10+)
- ✅ VS Code integrated terminal
- ✅ Most SSH clients

**Not Supported:**
- ❌ Old Windows Command Prompt (pre-Windows 10)
- ❌ Basic text editors without ANSI support
- ❌ Plain text file output

#### `getNumVertices() const`
Returns the number of vertices.

```cpp
int count = graph.getNumVertices();
```

#### `getNumEdges() const`
Returns the number of edges.

```cpp
int edges = graph.getNumEdges();
// For undirected graphs, counts each edge once
```

#### `isConnected() const`
Checks if all vertices are reachable from any vertex.

```cpp
if (graph.isConnected()) {
    cout << "Graph is fully connected" << endl;
}
```

#### `getVertices() const`
Returns a set of all vertices.

```cpp
set<string> vertices = graph.getVertices();
for (const auto& v : vertices) {
    cout << v << " ";
}
```

---

### Graph Property Methods (New!)

#### `getDegree(T vertex) const`
Gets the degree of a specific vertex (number of edges connected to it).

```cpp
UndirectedGraph<string> social;
social.addEdge("Alice", "Bob");
social.addEdge("Alice", "Charlie");
social.addEdge("Alice", "David");

int degree = social.getDegree("Alice");  // Returns 3
cout << "Alice has " << degree << " connections" << endl;
```

**For directed graphs**: Returns out-degree (outgoing edges).

#### `getInDegree(T vertex) const`
Gets the in-degree of a vertex (incoming edges). For directed graphs only.

```cpp
DirectedGraph<int> web;
web.addEdge(1, 2);
web.addEdge(3, 2);
web.addEdge(4, 2);

int inDeg = web.getInDegree(2);   // Returns 3
int outDeg = web.getDegree(2);    // Returns 0
```

**For undirected graphs**: Same as `getDegree()`.

#### `getMinDegree() const`
Returns the minimum degree among all vertices (also known as graph's minimum connectivity).

```cpp
UndirectedGraph<int> graph;
graph.addEdge(1, 2);
graph.addEdge(2, 3);
graph.addEdge(2, 4);
graph.addEdge(3, 4);

int minDeg = graph.getMinDegree();  // Returns 1 (vertex 1 has degree 1)
```

**Use Cases:**
- Network vulnerability analysis (vertex with min degree is potential bottleneck)
- Finding leaf nodes or peripheral vertices

#### `getMaxDegree() const`
Returns the maximum degree among all vertices (highest connectivity).

```cpp
int maxDeg = graph.getMaxDegree();  // Returns 3 (vertex 2 has degree 3)
```

**Use Cases:**
- Finding hub nodes in networks
- Identifying most connected entities

#### `getDistance(T src, T dest) const`
Calculates the shortest path distance between two vertices using BFS.

```cpp
UndirectedGraph<string> cities;
cities.addEdge("NYC", "Boston");
cities.addEdge("Boston", "Portland");
cities.addEdge("NYC", "Philly");

int dist = cities.getDistance("NYC", "Portland");  // Returns 2
cout << "Shortest path: " << dist << " hops" << endl;

int noPath = cities.getDistance("NYC", "LA");  // Returns -1 (no path)
```

**Returns:**
- Number of edges in shortest path
- `-1` if no path exists
- `0` if source equals destination

**Note**: This counts edges (hops), not weights. For weighted shortest paths, implement Dijkstra's algorithm separately.

#### `getRadius() const`
Calculates the graph radius (minimum eccentricity).

```cpp
int radius = graph.getRadius();
```

**Definition**: 
- Eccentricity of vertex v = maximum distance from v to any other vertex
- Radius = minimum eccentricity among all vertices
- Represents the "center" distance of the graph

**Returns:**
- Graph radius value
- `-1` if graph is disconnected
- `0` if graph has 0 or 1 vertices

**Use Cases:**
- Finding optimal center location (e.g., warehouse placement)
- Network design optimization

#### `getDiameter() const`
Calculates the graph diameter (maximum shortest path between any two vertices).

```cpp
int diameter = graph.getDiameter();
```

**Definition**: Maximum distance between any pair of vertices.

**Returns:**
- Graph diameter value
- `-1` if graph is disconnected
- `0` if graph has 0 or 1 vertices

**Use Cases:**
- Network latency analysis (worst-case communication time)
- Social network "six degrees of separation"

**Relationship**: `Radius ≤ Diameter ≤ 2 × Radius`

#### `getGirth() const`
Calculates the length of the shortest cycle in the graph.

```cpp
UndirectedGraph<int> graph;
graph.addEdge(1, 2);
graph.addEdge(2, 3);
graph.addEdge(3, 4);
graph.addEdge(4, 1);  // Creates 4-cycle
graph.addEdge(2, 4);  // Creates 3-cycle

int girth = graph.getGirth();  // Returns 3 (smallest cycle)
```

**Returns:**
- Length of shortest cycle
- `-1` if graph is acyclic (no cycles)

**Use Cases:**
- Graph theory analysis
- Network loop detection
- Cycle-based optimization

#### `getCircumference() const`
Calculates the length of the longest cycle in the graph.

```cpp
int circumference = graph.getCircumference();
```

**Returns:**
- Length of longest cycle
- `-1` if graph is acyclic

**Use Cases:**
- Finding longest circular paths
- Tour planning
- Network resilience analysis

#### `displayProperties(bool use_colored_output = false) const`
Displays a comprehensive summary of all graph properties.

```cpp
// Without colors
graph.displayProperties();

// With colors
graph.displayProperties(true);
```

**Output Example:**
```
=== Graph Properties ===
Number of Vertices: 5
Number of Edges: 6
Minimum Degree (Min vertex connections): 1
Maximum Degree (Max vertex connections): 3
Graph Radius (Min eccentricity): 2
Graph Diameter (Max shortest path): 3
Girth (Shortest cycle): 3
Circumference (Longest cycle): 5
Connected: Yes
========================
```

**Colored Output:**
- Property names: Bold Bright White
- Numeric values: Bright Blue/Cyan/Green
- Status "Yes": Bright Green
- Status "No/Undefined": Bright Red
- "Acyclic": Bright Yellow

**Use Cases:**
- Quick graph analysis
- Debugging and validation
- Comparing different graph structures

---

### Graph Modification Methods

#### `deleteVertex(T vertex)`
Deletes a vertex and all edges connected to it.

```cpp
UndirectedGraph<int> graph;
graph.addEdge(1, 2);
graph.addEdge(2, 3);
graph.addEdge(3, 1);

bool deleted = graph.deleteVertex(2);  // Returns true
// Removes vertex 2 and edges (1,2) and (2,3)

graph.display();  // Now only shows vertices 1 and 3
```

**Returns:**
- `true` if vertex was successfully deleted
- `false` if vertex didn't exist

**Behavior:**
- Removes the vertex from the graph
- Removes all edges where this vertex is the source
- Removes all edges where this vertex is the destination
- Updates vertex and edge counts

**Use Cases:**
- Dynamic graph modifications
- Node removal in networks
- Deleting users/entities from social networks
- Removing failed nodes from topology

#### `deleteEdge(T src, T dest)`
Deletes an edge between two vertices.

```cpp
DirectedGraph<string> graph;
graph.addEdge("A", "B");
graph.addEdge("B", "C");

bool deleted = graph.deleteEdge("A", "B");  // Returns true
// Removes only the edge A -> B

// For undirected graphs, removes both directions
UndirectedGraph<int> undirGraph;
undirGraph.addEdge(1, 2);
undirGraph.deleteEdge(1, 2);  // Removes both 1-2 and 2-1
```

**Returns:**
- `true` if edge was successfully deleted
- `false` if edge didn't exist

**Use Cases:**
- Breaking connections in networks
- Removing relationships
- Edge removal in dynamic graphs

#### `join(const Graph<T>& other)`
Joins another graph with this graph (union operation). Modifies the current graph.

```cpp
UndirectedGraph<int> graph1;
graph1.addEdge(1, 2);
graph1.addEdge(2, 3);

UndirectedGraph<int> graph2;
graph2.addEdge(3, 4);
graph2.addEdge(4, 5);

graph1.join(graph2);  // graph1 now contains all vertices and edges
graph1.display();     // Shows: 1-2-3-4-5
```

**Behavior:**
- Adds all vertices from `other` to `this`
- Adds all edges from `other` to `this`
- Avoids duplicate edges
- Checks compatibility (directed/undirected, weighted/unweighted)

**Throws:**
- `logic_error` if graphs have incompatible types

**Compatibility Requirements:**
- Both graphs must be either directed or undirected
- Both graphs must be either weighted or unweighted

**Use Cases:**
- Merging network components
- Combining social network groups
- Aggregating data from multiple sources
- Building larger graphs from subgraphs

#### `operator+(const Graph<T>& other)`
Creates a new graph that is the union of two graphs. Non-modifying operation.

```cpp
DirectedGraph<char> g1;
g1.addEdge('A', 'B');
g1.addEdge('B', 'C');

DirectedGraph<char> g2;
g2.addEdge('C', 'D');
g2.addEdge('D', 'E');

Graph<char> g3 = g1 + g2;  // Creates new graph
// g1 and g2 remain unchanged
// g3 contains all vertices and edges from both

g3.display();
```

**Returns:** New `Graph<T>` object containing the union

**Difference from `join()`:**
- `join()` modifies the left graph
- `operator+` creates a new graph without modifying either operand

**Use Cases:**
- Non-destructive graph combination
- Creating temporary merged graphs
- Functional programming style operations

---

### Graph Traversal Methods

#### `BFS(T start, bool use_colored_output = false)`
Performs Breadth-First Search traversal from a starting vertex.

```cpp
UndirectedGraph<int> graph;
graph.addEdge(1, 2);
graph.addEdge(1, 3);
graph.addEdge(2, 4);
graph.addEdge(2, 5);
graph.addEdge(3, 6);

// Perform BFS from vertex 1
vector<int> traversal = graph.BFS(1, true);  // With colors

// Result: [1, 2, 3, 4, 5, 6]
for (int v : traversal) {
    cout << v << " ";
}
```

**Output Features:**
- Beautiful ASCII art header
- Level-by-level visualization
- Tree structure display with Unicode box drawing
- Color-coded vertices and levels
- Traversal order summary
- Visit statistics

**Output Example:**
```
╔════════════════════════════════════════╗
║   BREADTH-FIRST SEARCH TRAVERSAL       ║
╚════════════════════════════════════════╝
Starting from vertex: 1

Level 0: [1]
Level 1: [2] → [3]
Level 2: [4] → [5] → [6]

BFS Tree Structure:
───────────────────
└── [1] (L0)
    ├── [2] (L1)
    │   ├── [4] (L2)
    │   └── [5] (L2)
    └── [3] (L1)
        └── [6] (L2)

Traversal Order: 1 → 2 → 3 → 4 → 5 → 6
Vertices Visited: 6/6
```

**Returns:** `vector<T>` containing vertices in BFS order

**Throws:**
- `invalid_argument` if start vertex doesn't exist

**Algorithm Properties:**
- Time Complexity: O(V + E)
- Space Complexity: O(V)
- Explores level by level
- Finds shortest path in unweighted graphs
- Uses queue data structure

**Use Cases:**
- Finding shortest path (unweighted graphs)
- Level-order traversal
- Finding connected components
- Web crawling
- Social network analysis (degrees of separation)
- Broadcasting in networks

#### `DFS(T start, bool use_colored_output = false)`
Performs Depth-First Search traversal from a starting vertex.

```cpp
DirectedGraph<char> graph;
graph.addEdge('A', 'B');
graph.addEdge('A', 'C');
graph.addEdge('B', 'D');
graph.addEdge('C', 'E');

// Perform DFS from vertex 'A'
vector<char> traversal = graph.DFS('A', true);  // With colors

// Result: ['A', 'B', 'D', 'C', 'E']
for (char v : traversal) {
    cout << v << " ";
}
```

**Output Features:**
- Beautiful ASCII art header (magenta theme)
- Discovery and finish times
- Real-time exploration status
- Color-coded visited/unvisited neighbors
- Tree structure with depth indicators
- Complete traversal summary

**Output Example:**
```
╔════════════════════════════════════════╗
║   DEPTH-FIRST SEARCH TRAVERSAL         ║
╚════════════════════════════════════════╝
Starting from vertex: A

  Discovered: [A] at time 1 → Exploring: B, C
  Discovered: [B] at time 2 → Exploring: D
  Discovered: [D] at time 3 → Exploring: 
  Finished:   [D] at time 4
  Finished:   [B] at time 5
  Discovered: [C] at time 6 → Exploring: E
  Discovered: [E] at time 7 → Exploring: 
  Finished:   [E] at time 8
  Finished:   [C] at time 9
  Finished:   [A] at time 10

DFS Tree Structure:
───────────────────
└── [A] (depth 0)
    ├── [B] (depth 1)
    │   └── [D] (depth 2)
    └── [C] (depth 1)
        └── [E] (depth 2)

Traversal Order: A → B → D → C → E
Vertices Visited: 5/5
```

**Returns:** `vector<T>` containing vertices in DFS order

**Throws:**
- `invalid_argument` if start vertex doesn't exist

**Algorithm Properties:**
- Time Complexity: O(V + E)
- Space Complexity: O(V)
- Explores as deep as possible before backtracking
- Uses recursion (implicit stack)
- Records discovery and finish times

**Use Cases:**
- Topological sorting
- Cycle detection
- Strongly connected components
- Maze solving
- Puzzle solving (Sudoku, etc.)
- Path finding in games
- Dependency resolution

#### BFS vs DFS Comparison

| Feature | BFS | DFS |
|---------|-----|-----|
| **Exploration** | Level by level | Deep as possible |
| **Data Structure** | Queue (FIFO) | Stack (LIFO/Recursion) |
| **Shortest Path** | ✅ Yes (unweighted) | ❌ No |
| **Memory** | High (stores entire level) | Low (stores path) |
| **Best For** | Shortest path, nearest neighbors | Exploring all paths, backtracking |
| **Completeness** | ✅ Complete | ✅ Complete |
| **Tree Output** | Level indicators | Depth indicators |

**When to use BFS:**
- Finding shortest path
- Level-order processing
- Nearest neighbor searches
- Broadcasting/flooding

**When to use DFS:**
- Topological sort
- Finding cycles
- Pathfinding with constraints
- Exploring all possibilities

### Special Methods

#### `hasCycle() const` - CyclicGraph only
Detects if the graph contains any cycle.

```cpp
CyclicGraph<int> graph;
graph.addEdge(1, 2);
graph.addEdge(2, 3);
graph.addEdge(3, 1);  // Creates cycle

if (graph.hasCycle()) {
    cout << "Cycle detected!" << endl;
}
```

---

## Advanced Examples

### Example 1: Social Network Analysis with Properties

```cpp
UndirectedGraph<string> socialNetwork;

// Build network
socialNetwork.addEdge("Alice", "Bob");
socialNetwork.addEdge("Bob", "Charlie");
socialNetwork.addEdge("Charlie", "David");
socialNetwork.addEdge("David", "Alice");
socialNetwork.addEdge("Alice", "Eve");

// Display structure
socialNetwork.display();

// Analyze properties
socialNetwork.displayProperties();

// Find influencers (high degree vertices)
cout << "Connection Analysis:" << endl;
for (const auto& person : socialNetwork.getVertices()) {
    int connections = socialNetwork.getDegree(person);
    cout << person << " has " << connections << " friends" << endl;
}

// Calculate network metrics
cout << "\nNetwork Metrics:" << endl;
cout << "Network diameter: " << socialNetwork.getDiameter() 
     << " degrees of separation" << endl;
cout << "Network radius: " << socialNetwork.getRadius() << endl;

// Check specific distances
cout << "\nDistance Analysis:" << endl;
cout << "Shortest path Alice to David: " 
     << socialNetwork.getDistance("Alice", "David") << " hops" << endl;
cout << "Shortest path Bob to Eve: " 
     << socialNetwork.getDistance("Bob", "Eve") << " hops" << endl;

// Find central person (minimum eccentricity)
int minEcc = INT_MAX;
string centralPerson;
for (const auto& person : socialNetwork.getVertices()) {
    int maxDist = 0;
    for (const auto& other : socialNetwork.getVertices()) {
        if (person != other) {
            maxDist = max(maxDist, socialNetwork.getDistance(person, other));
        }
    }
    if (maxDist < minEcc) {
        minEcc = maxDist;
        centralPerson = person;
    }
}
cout << "\nMost central person: " << centralPerson 
     << " (eccentricity: " << minEcc << ")" << endl;
```

### Example 2: Web Page Ranking Analysis

```cpp
DirectedGraph<string> webPages;

// Build web graph
webPages.addEdge("HomePage", "About");
webPages.addEdge("HomePage", "Products");
webPages.addEdge("HomePage", "Contact");
webPages.addEdge("Products", "Product1");
webPages.addEdge("Products", "Product2");
webPages.addEdge("Product1", "Contact");
webPages.addEdge("Product2", "Contact");
webPages.addEdge("About", "HomePage");

webPages.display();

// Analyze page importance
cout << "\nPage Importance Analysis (In-Degree):" << endl;
for (const auto& page : webPages.getVertices()) {
    cout << page << ":" << endl;
    cout << "  Outgoing links: " << webPages.getDegree(page) << endl;
    cout << "  Incoming links: " << webPages.getInDegree(page) << endl;
}

// Find most referenced page
int maxInDegree = 0;
string mostReferenced;
for (const auto& page : webPages.getVertices()) {
    int inDeg = webPages.getInDegree(page);
    if (inDeg > maxInDegree) {
        maxInDegree = inDeg;
        mostReferenced = page;
    }
}
cout << "\nMost referenced page: " << mostReferenced 
     << " (" << maxInDegree << " incoming links)" << endl;

webPages.displayProperties();
```

### Example 3: Network Topology Analysis

```cpp
UndirectedGraph<int> network;

// Build network topology
network.addEdge(1, 2);
network.addEdge(1, 3);
network.addEdge(2, 4);
network.addEdge(3, 4);
network.addEdge(4, 5);
network.addEdge(4, 6);
network.addEdge(5, 7);
network.addEdge(6, 7);

network.display();
network.displayProperties();

// Identify critical nodes (high degree = potential bottlenecks)
cout << "\nCritical Node Analysis:" << endl;
int avgDegree = (2 * network.getNumEdges()) / network.getNumVertices();
cout << "Average degree: " << avgDegree << endl;

for (const auto& node : network.getVertices()) {
    int deg = network.getDegree(node);
    if (deg > avgDegree) {
        cout << "Node " << node << " is a hub (degree: " << deg << ")" << endl;
    } else if (deg == 1) {
        cout << "Node " << node << " is a leaf (degree: " << deg << ")" << endl;
    }
}

// Analyze network reliability
cout << "\nReliability Metrics:" << endl;
cout << "Minimum degree: " << network.getMinDegree() 
     << " (weakest link)" << endl;
cout << "Maximum degree: " << network.getMaxDegree() 
     << " (strongest hub)" << endl;
cout << "Diameter: " << network.getDiameter() 
     << " (worst-case latency)" << endl;

// Check redundancy (cycles)
int girth = network.getGirth();
if (girth != -1) {
    cout << "Network has redundancy - shortest cycle length: " 
         << girth << endl;
} else {
    cout << "Network is a tree - no redundancy!" << endl;
}
```

### Example 4: Distance Matrix Generation

```cpp
UndirectedGraph<char> graph;
graph.addEdge('A', 'B');
graph.addEdge('B', 'C');
graph.addEdge('C', 'D');
graph.addEdge('D', 'A');
graph.addEdge('A', 'C');

// Generate distance matrix
cout << "Distance Matrix:" << endl;
cout << "    ";
for (const auto& v : graph.getVertices()) {
    cout << v << "  ";
}
cout << endl;

for (const auto& src : graph.getVertices()) {
    cout << src << "   ";
    for (const auto& dest : graph.getVertices()) {
        if (src == dest) {
            cout << "0  ";
        } else {
            int dist = graph.getDistance(src, dest);
            cout << dist << "  ";
        }
    }
    cout << endl;
}

graph.displayProperties();
```

### Example 5: Cycle Detection and Analysis

```cpp
CyclicGraph<int> circuit;

// Build graph with multiple cycles
circuit.addEdge(1, 2);
circuit.addEdge(2, 3);
circuit.addEdge(3, 4);
circuit.addEdge(4, 5);
circuit.addEdge(5, 1);  // 5-cycle
circuit.addEdge(2, 5);  // Creates 4-cycle
circuit.addEdge(3, 5);  // Creates 3-cycle

circuit.display();

// Analyze cycles
cout << "\nCycle Analysis:" << endl;
cout << "Graph has cycles: " << (circuit.hasCycle() ? "Yes" : "No") << endl;

int girth = circuit.getGirth();
int circumference = circuit.getCircumference();

cout << "Shortest cycle (girth): " << girth << " edges" << endl;
cout << "Longest cycle (circumference): " << circumference << " edges" << endl;

if (girth == 3) {
    cout << "Warning: Graph contains triangles (3-cycles)" << endl;
}

circuit.displayProperties();
```

### Example 2: Task Dependency System (DAG)

```cpp
DirectedAcyclicGraph<string> projectTasks;

try {
    // Define task dependencies
    projectTasks.addEdge("Requirements", "Design");
    projectTasks.addEdge("Design", "Frontend");
    projectTasks.addEdge("Design", "Backend");
    projectTasks.addEdge("Frontend", "Integration");
    projectTasks.addEdge("Backend", "Integration");
    projectTasks.addEdge("Integration", "Testing");
    projectTasks.addEdge("Testing", "Deployment");
    
    // This would fail (creates cycle):
    // projectTasks.addEdge("Deployment", "Requirements");
    
    cout << "Task dependency graph created successfully" << endl;
    projectTasks.display();
    
} catch (const logic_error& e) {
    cerr << "Error: " << e.what() << endl;
}
```

### Example 3: Weighted Route Planning

```cpp
WeightedGraph<string> cityNetwork(false);  // undirected

// Add routes with distances (km)
cityNetwork.addEdge("New York", "Boston", 346);
cityNetwork.addEdge("New York", "Philadelphia", 152);
cityNetwork.addEdge("Boston", "Philadelphia", 435);
cityNetwork.addEdge("Philadelphia", "Washington DC", 225);
cityNetwork.addEdge("New York", "Washington DC", 362);

cityNetwork.display();

cout << "Total cities: " << cityNetwork.getNumVertices() << endl;
cout << "Total routes: " << cityNetwork.getNumEdges() << endl;
```

### Example 4: Bipartite Matching (Students-Courses)

```cpp
BipartiteGraph<string> enrollment;

try {
    // Students enrolling in courses
    enrollment.addEdge("Alice", "Data Structures");
    enrollment.addEdge("Alice", "Algorithms");
    enrollment.addEdge("Bob", "Data Structures");
    enrollment.addEdge("Bob", "Database Systems");
    enrollment.addEdge("Charlie", "Algorithms");
    enrollment.addEdge("Charlie", "Database Systems");
    
    // This maintains bipartite property
    enrollment.display();
    
    // This would fail (students connected to students):
    // enrollment.addEdge("Alice", "Bob");
    
} catch (const logic_error& e) {
    cerr << "Error: " << e.what() << endl;
}
```

### Example 5: Complete Network (Full Mesh)

```cpp
CompleteGraph<char> meshNetwork;

// Add nodes - they automatically connect to all existing nodes
meshNetwork.addVertex('A');
meshNetwork.addVertex('B');
meshNetwork.addVertex('C');
meshNetwork.addVertex('D');

cout << "Complete graph K" << meshNetwork.getNumVertices() << endl;
cout << "Total edges: " << meshNetwork.getNumEdges() << endl;
// K4 has 4 vertices and 6 edges: 4*(4-1)/2 = 6

meshNetwork.display();
```

---

## Best Practices

### 1. **Choose the Right Graph Type**

```cpp
// ✅ Good: Use DirectedGraph for one-way relationships
DirectedGraph<string> twitter;
twitter.addEdge("Alice", "Bob");  // Alice follows Bob

// ❌ Bad: Using UndirectedGraph for asymmetric relationships
UndirectedGraph<string> twitter;  // Makes it mutual (incorrect!)
```

### 2. **Use Appropriate Vertex Types**

```cpp
// ✅ Good: Meaningful vertex types
DirectedGraph<string> emailNetwork;
emailNetwork.addEdge("alice@example.com", "bob@example.com");

WeightedGraph<int> ipNetwork(true);  // IP addresses as integers
ipNetwork.addEdge(192168001001, 192168001002, 100);  // latency in ms

// ✅ Good: Use structs for complex data
struct City {
    string name;
    int population;
    // Must implement comparison operators for use in set/map
    bool operator<(const City& other) const {
        return name < other.name;
    }
};
```

### 3. **Handle Exceptions Properly**

```cpp
try {
    DirectedAcyclicGraph<string> dag;
    dag.addEdge("A", "B");
    dag.addEdge("B", "C");
    dag.addEdge("C", "A");  // Would create cycle
} catch (const logic_error& e) {
    cerr << "Cannot add edge: " << e.what() << endl;
    // Handle error appropriately
}
```

### 4. **Validate Graph Properties**

```cpp
// Check connectivity before processing
if (!graph.isConnected()) {
    cout << "Warning: Graph has disconnected components" << endl;
    // Handle accordingly
}

// Verify cycle detection for CyclicGraph
CyclicGraph<int> graph;
// ... add edges ...
if (graph.hasCycle()) {
    cout << "Cycle detected - may need special handling" << endl;
}
```

### 5. **Memory Efficiency**

```cpp
// ✅ Good: Use appropriate types for large graphs
DirectedGraph<int> largeGraph;  // Integers use less memory than strings

// ✅ Good: Reserve space if you know the size
// (Modify the class to support this if needed)

// ❌ Bad: Using strings unnecessarily
DirectedGraph<string> graph;
graph.addEdge("1", "2");  // Use int instead!
```

---

## Common Patterns

### Pattern 1: Graph Traversal

```cpp
// BFS-style traversal (using isConnected as reference)
void traverseGraph(const Graph<int>& graph) {
    set<int> visited;
    queue<int> q;
    
    auto vertices = graph.getVertices();
    if (vertices.empty()) return;
    
    int start = *vertices.begin();
    q.push(start);
    visited.insert(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        cout << "Visiting: " << current << endl;
        
        // Process neighbors (access via graph methods)
    }
}
```

### Pattern 2: Path Validation

```cpp
// Check if path exists between two vertices
bool pathExists(const ConnectedGraph<string>& graph,
                const string& src, const string& dest) {
    auto vertices = graph.getVertices();
    
    // If both vertices exist and graph is connected, path exists
    return vertices.count(src) > 0 && 
           vertices.count(dest) > 0 && 
           graph.isConnected();
}
```

### Pattern 3: Cycle Detection Pattern

```cpp
void analyzeCycles(const CyclicGraph<int>& graph) {
    if (graph.hasCycle()) {
        cout << "Graph contains cycles - unsuitable for topological sort" << endl;
        cout << "Consider using DAG for hierarchical structures" << endl;
    } else {
        cout << "Graph is acyclic - safe for dependency resolution" << endl;
    }
}
```

### Pattern 4: Bipartite Validation

```cpp
void validateMatching(BipartiteGraph<string>& matching) {
    try {
        // Add edges
        matching.addEdge("Student1", "Course1");
        matching.addEdge("Student1", "Course2");
        
        // Bipartiteness is automatically validated
        cout << "Valid bipartite matching" << endl;
        
    } catch (const logic_error& e) {
        cout << "Invalid matching: " << e.what() << endl;
    }
}
```

---

## Performance Considerations

### Time Complexity

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| `addVertex()` | O(1) average | Hash map insertion |
| `addEdge()` | O(1) average | Plus validation for special types |
| `deleteVertex(v)` | O(V + E) | Must remove all edges to/from v |
| `deleteEdge(u, v)` | O(degree(u)) | Searches adjacency list |
| `join(other)` | O(V' + E') | V', E' are vertices/edges in other |
| `operator+` | O(V + E + V' + E') | Creates new graph |
| `BFS(start)` | O(V + E) | Visits all vertices and edges once |
| `DFS(start)` | O(V + E) | Visits all vertices and edges once |
| `getNumVertices()` | O(1) | Direct count |
| `getNumEdges()` | O(V) | Iterates through adjacency list |
| `isConnected()` | O(V + E) | BFS traversal |
| `getDegree(v)` | O(1) | Direct lookup |
| `getInDegree(v)` | O(V + E) | Scans all edges (directed) |
| `getMinDegree()` | O(V) | Checks all vertices |
| `getMaxDegree()` | O(V) | Checks all vertices |
| `getDistance(u, v)` | O(V + E) | BFS traversal |
| `getRadius()` | O(V² × (V + E)) | All-pairs distances |
| `getDiameter()` | O(V² × (V + E)) | All-pairs distances |
| `getGirth()` | O(V × (V + E)) | BFS from each vertex |
| `getCircumference()` | O(V × (V + E)) | DFS from each vertex |
| `hasCycle()` | O(V + E) | DFS traversal |
| `display()` | O(V + E) | Prints all edges |
| `displayProperties()` | O(V² × (V + E)) | Computes all metrics |

**V** = Number of Vertices, **E** = Number of Edges, **V'**, **E'** = Vertices/Edges in other graph

**Note**: For dense graphs where E ≈ V², some operations approach O(V³) complexity.

### Space Complexity

- **Adjacency List**: O(V + E)
- Better than adjacency matrix for sparse graphs (E << V²)
- Additional O(V) space for BFS/DFS operations

### Optimization Tips

```cpp
// ✅ Good: Batch property queries
graph.displayProperties();  // Computes all metrics once
int diameter = graph.getDiameter();
int radius = graph.getRadius();

// ❌ Avoid: Redundant distance calculations
for (auto v1 : vertices) {
    for (auto v2 : vertices) {
        graph.getDistance(v1, v2);  // O(V² × (V+E)) - expensive!
    }
}

// ✅ Good: Cache distances if needed multiple times
map<pair<T,T>, int> distCache;
for (auto v1 : vertices) {
    for (auto v2 : vertices) {
        distCache[{v1, v2}] = graph.getDistance(v1, v2);
    }
}
// Use distCache[{v1, v2}] for O(1) lookups

// ✅ Good: Check simple properties first
if (graph.getNumVertices() == 0) {
    // Handle empty graph
    return;
}

// ✅ Good: Use getDegree() instead of iterating edges
int degree = graph.getDegree(vertex);  // O(1)
// Better than manually counting edges

// ✅ Good: Early termination
int dist = graph.getDistance(src, dest);
if (dist == -1) {
    cout << "No path exists, skipping further analysis" << endl;
    return;
}
```

### Performance Considerations for Large Graphs

```cpp
// For graphs with thousands of vertices:

// 1. Avoid computing diameter/radius unless necessary
// These are O(V² × (V+E)) operations - very expensive!

// 2. Use isConnected() first to check if metrics are meaningful
if (!graph.isConnected()) {
    cout << "Graph disconnected - diameter/radius undefined" << endl;
    // Skip expensive computations
}

// 3. For frequent distance queries, consider preprocessing
// Implement Floyd-Warshall or store a distance matrix

// 4. Use appropriate graph type
// DirectedGraph vs UndirectedGraph affects performance
// UndirectedGraph stores edges twice (both directions)
```

---

## Error Handling

### Common Exceptions

```cpp
// 1. Adding edges to Null/Trivial graphs
try {
    NullGraph<int> ng;
    ng.addVertex(1);
    ng.addEdge(1, 2);  // Throws logic_error
} catch (const logic_error& e) {
    // Handle: "Cannot add edges to a Null Graph"
}

// 2. Creating cycles in DAG
try {
    DirectedAcyclicGraph<int> dag;
    dag.addEdge(1, 2);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);  // Throws logic_error
} catch (const logic_error& e) {
    // Handle: "Adding this edge would create a cycle in DAG"
}

// 3. Breaking bipartite property
try {
    BipartiteGraph<int> bg;
    bg.addEdge(1, 2);
    bg.addEdge(2, 3);
    bg.addEdge(3, 1);  // Throws logic_error (odd cycle)
} catch (const logic_error& e) {
    // Handle: "Adding this edge would break bipartite property"
}
```

---

## Testing Your Implementation

```cpp
void testGraphs() {
    // Test 1: Basic connectivity
    UndirectedGraph<int> test1;
    test1.addEdge(1, 2);
    test1.addEdge(2, 3);
    assert(test1.isConnected() == true);
    
    // Test 2: Disconnected components
    DisconnectedGraph<int> test2;
    test2.addEdge(1, 2);
    test2.addEdge(3, 4);
    assert(test2.isConnected() == false);
    
    // Test 3: Cycle detection
    CyclicGraph<int> test3;
    test3.addEdge(1, 2);
    test3.addEdge(2, 3);
    test3.addEdge(3, 1);
    assert(test3.hasCycle() == true);
    
    cout << "All tests passed!" << endl;
}
```

---

## Contributing

When extending this implementation:

1. **Maintain template support** for all graph types
2. **Follow naming conventions** (camelCase for methods)
3. **Add comprehensive docstrings** for new methods
4. **Validate input** and throw appropriate exceptions
5. **Update this USAGE.md** with new features

---

## License

This implementation is provided as-is for educational and commercial use.

---

## Support

For issues, questions, or contributions:
- Open an issue on the repository
- Refer to the code comments for implementation details
- Check the examples above for common use cases

**Happy Graph Building! 🚀**

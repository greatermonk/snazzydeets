# Tree Data Structures - Usage Guide

A comprehensive C++ implementation of various tree data structures with practical examples and best practices.

##  Table of Contents

- [Quick Start](#quick-start)
- [Compilation](#compilation)
- [Tree Types Overview](#tree-types-overview)
- [Detailed Usage](#detailed-usage)
- [Use Case Recommendations](#use-case-recommendations)
- [Performance Comparison](#performance-comparison)
- [Best Practices](#best-practices)
- [Common Pitfalls](#common-pitfalls)

---

##  Quick Start

### Basic Example

```cpp
#include "tree_implementation.cpp"  // Include the tree implementations

int main() {
    // Create a Binary Search Tree
    BinarySearchTree<int> bst;
    
    // Insert values
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    
    // Search for a value
    bool found = bst.search(30);  // Returns true
    
    // Display the tree
    bst.display();
    
    return 0;
}
```

---

##  Compilation

### Using g++
```bash
g++ -std=c++11 -o tree_demo trees.cpp
./tree_demo
```

### Using clang++
```bash
clang++ -std=c++11 -o tree_demo trees.cpp
./tree_demo
```

### With optimization
```bash
g++ -std=c++11 -O2 -o tree_demo trees.cpp
```

---

##  Tree Types Overview

| Tree Type | Best For | Time Complexity | Space Complexity |
|-----------|----------|-----------------|------------------|
| **Binary Search Tree** | Simple ordered data | O(log n) avg, O(n) worst | O(n) |
| **AVL Tree** | Frequent searches, guaranteed balance | O(log n) | O(n) |
| **Red-Black Tree** | Balanced insertions/deletions | O(log n) | O(n) |
| **B-Tree** | Database indexing, file systems | O(log n) | O(n) |
| **Trie** | String prefix matching, autocomplete | O(m) where m = string length | O(ALPHABET_SIZE × N × M) |
| **Segment Tree** | Range queries, updates | O(log n) | O(4n) |
| **Binary Indexed Tree** | Prefix sums, frequency tables | O(log n) | O(n) |
| **N-ary Tree** | Hierarchical data, file systems | Varies | O(n) |

---

##  Detailed Usage

### 1. Binary Search Tree (BST)

**When to use:** Simple ordered data storage, learning tree concepts

```cpp
// Create a BST
BinarySearchTree<int> bst;

// Insert values
bst.insert(50);
bst.insert(30);
bst.insert(70);
bst.insert(20);
bst.insert(40);

// Search for a value
if (bst.search(30)) {
    cout << "Value found!" << endl;
}

// Display in sorted order (inorder traversal)
bst.inorder();  // Output: 20 30 40 50 70

// Display tree structure
bst.display();
```

**Arguments:**
- `insert(T value)`: Value to insert (any comparable type)
- `search(T value)`: Value to search for
- No arguments for `inorder()` and `display()`


---

### 2. AVL Tree (Self-Balancing BST)

**When to use:** Need guaranteed O(log n) operations, frequent searches

```cpp
// Create an AVL tree
AVLTree<int> avl;

// Insert values (automatically balanced)
avl.insert(10);
avl.insert(20);
avl.insert(30);  // This would trigger rotations
avl.insert(40);
avl.insert(50);

// Display shows heights at each node
avl.display();

// Inorder traversal (sorted)
avl.inorder();
```

**Key Features:**
- Automatic balancing after each insertion
- Height information displayed in format: `(value)[h=height]`
- Better than BST when you need consistent performance


---

### 3. Red-Black Tree

**When to use:** Balanced tree with faster insertion than AVL

```cpp
// Create a Red-Black tree
RedBlackTree<int> rbt;

// Insert values
rbt.insert(10);
rbt.insert(20);
rbt.insert(30);
rbt.insert(15);
rbt.insert(25);

// Display shows colors: [R] = Red, [B] = Black
rbt.display();
```

**Properties:**
- Less strict balancing than AVL (fewer rotations)
- Better for insertion-heavy workloads
- Used in: C++ STL `map`, Linux kernel scheduler


---

### 4. B-Tree

**When to use:** Database indexing, file systems, disk-based storage

```cpp
// Create a B-Tree with minimum degree 3
BTree<int> btree(3);

// Insert keys
btree.insert(10);
btree.insert(20);
btree.insert(30);

// Search for a key
if (btree.search(20)) {
    cout << "Key found!" << endl;
}
```

**Arguments:**
- Constructor: `BTree(int t)` where `t` is minimum degree
  - Minimum degree `t` means each node has:
    - Minimum `t-1` keys
    - Maximum `2t-1` keys

**Minimum degree guidelines:**
```cpp
BTree<int> btree(2);   // 2-3-4 tree (small, testing)
BTree<int> btree(3);   // Standard B-tree
BTree<int> btree(100); // Database index (large pages)
```

---

### 5. Trie (Prefix Tree)

**When to use:** Autocomplete, spell checkers, IP routing, dictionary

```cpp
// Create a Trie
Trie trie;

// Insert words
trie.insert("hello");
trie.insert("world");
trie.insert("help");
trie.insert("heap");

// Search for complete word
if (trie.search("hello")) {
    cout << "Word exists!" << endl;
}

// Check prefix
if (trie.startsWith("hel")) {
    cout << "Words starting with 'hel' exist!" << endl;
}

// Display structure (* marks word endings)
trie.display();
```

**Methods:**
- `insert(string word)`: Add a word
- `search(string word)`: Check if exact word exists
- `startsWith(string prefix)`: Check if any word has this prefix


---

### 6. Segment Tree

**When to use:** Range sum queries, range minimum/maximum queries

```cpp
// Create array
vector<int> arr = {1, 3, 5, 7, 9, 11};

// Build segment tree from array
SegmentTree segTree(arr);

// Query sum in range [L, R] (0-indexed)
int sum = segTree.query(1, 3);  // Sum of arr[1] to arr[3]
cout << "Sum [1,3]: " << sum << endl;  // Output: 15

// Update value at index
segTree.update(1, 10);  // arr[1] = 10

// Query again
sum = segTree.query(1, 3);  // Now: 10 + 5 + 7 = 22

// Display structure
segTree.display();
```

**Methods:**
- `SegmentTree(vector<int> arr)`: Constructor with array
- `query(int L, int R)`: Get sum of range [L, R]
- `update(int idx, int value)`: Update value at index

---

### 7. Binary Indexed Tree (Fenwick Tree)

**When to use:** Prefix sums, frequency counting, cumulative frequencies

```cpp
// Create BIT with size 6
BinaryIndexedTree bit(6);

// Update values (add to index)
bit.update(0, 1);  // arr[0] += 1
bit.update(1, 3);  // arr[1] += 3
bit.update(2, 5);  // arr[2] += 5
bit.update(3, 7);  // arr[3] += 7

// Get prefix sum from 0 to idx
int prefixSum = bit.query(2);  // Sum of arr[0..2]

// Get range sum [L, R]
int rangeSum = bit.rangeQuery(1, 3);  // Sum of arr[1..3]

// Display structure
bit.display();
```

**Methods:**
- `BinaryIndexedTree(int size)`: Constructor with size
- `update(int idx, int delta)`: Add delta to arr[idx]
- `query(int idx)`: Get prefix sum [0, idx]
- `rangeQuery(int L, int R)`: Get sum [L, R]


---

### 8. N-ary Tree

**When to use:** File systems, organization charts, XML/HTML DOM

```cpp
// Create N-ary tree
NaryTree<int> nary;

// Create root
nary.createRoot(1);

// Get root to add children
NaryNode<int>* root = nary.getRoot();

// Add children to root
nary.addChild(root, 2);
nary.addChild(root, 3);
nary.addChild(root, 4);

// Add children to a child node
NaryNode<int>* child2 = root->children[0];
nary.addChild(child2, 5);
nary.addChild(child2, 6);

// Display structure
nary.display();

// Level order traversal
nary.levelOrder();
```

**Methods:**
- `createRoot(T value)`: Create root node
- `getRoot()`: Get pointer to root
- `addChild(NaryNode<T>* parent, T value)`: Add child to parent


---

##  Use Case Recommendations

### Choose Binary Search Tree when:
-  Learning data structures
-  Simple ordered data storage
-  No strict performance requirements
>  Don't use for: Production systems with random data (can become unbalanced)

### Choose AVL Tree when:
-  Frequent search operations
-  Need guaranteed O(log n) performance
-  Read-heavy workloads
>  Don't use for: Write-heavy systems (more rotations than Red-Black)

### Choose Red-Black Tree when:
-  Balanced read/write operations
-  Need good overall performance
-  Implementing standard containers (like C++ `map`)
-  Kernel-level data structures

### Choose B-Tree when:
-  Database indexing
-  File system implementation
-  Large datasets on disk
-  Block-based storage systems
> ❌ Don't use for: Small in-memory datasets

### Choose Trie when:
-  Autocomplete systems
-  Spell checkers
-  Dictionary implementations
-  IP routing tables
-  Prefix matching
> Don't use for: Storing non-string data, memory-constrained systems

### Choose Segment Tree when:
-  Range queries (sum, min, max)
-  Array range updates
-  Computational geometry
>  Don't use for: Simple prefix sums (use BIT instead)

### Choose Binary Indexed Tree when:
-  Prefix sum queries
-  Frequency tables
-  Cumulative distributions
-  Memory efficiency important
>  Don't use for: Complex range queries (use Segment Tree)

### Choose N-ary Tree when:
-  File systems
-  Organization hierarchies
-  XML/HTML DOM
-  Directory structures
>  Don't use for: Searching/sorting (use BST variants)

---

##  Performance Comparison

### Insert Operation
```
Input: 1 million random integers

BST:           ~500ms (worst case: 30,000ms if unbalanced)
AVL Tree:      ~800ms (guaranteed)
Red-Black:     ~600ms (guaranteed)
```

### Search Operation
```
Input: Search 100,000 times in 1 million elements

BST:           ~200ms avg (worst: 10,000ms)
AVL Tree:      ~150ms (guaranteed)
Red-Black:     ~180ms (guaranteed)
```

### Range Query
```
Input: 1 million elements, 10,000 queries

Segment Tree:  ~50ms
BIT:           ~30ms (for prefix sums only)
```

---

##  Best Practices

### 1. Template Usage
```cpp
// Works with any comparable type
BinarySearchTree<int> intTree;
BinarySearchTree<double> doubleTree;
BinarySearchTree<string> stringTree;

// Custom objects (must define < operator)
struct Person {
    string name;
    int age;
    bool operator<(const Person& other) const {
        return age < other.age;
    }
};
BinarySearchTree<Person> personTree;
```

### 2. Memory Management
```cpp
// Trees automatically manage memory
{
    BinarySearchTree<int> bst;
    bst.insert(10);
    // Memory freed when bst goes out of scope
}

// For N-ary trees, manually manage if needed
NaryNode<int>* node = new NaryNode<int>(10);
// Remember to delete if created manually
delete node;
```

### 3. Large Datasets
```cpp
// For large datasets, use appropriate tree
vector<int> largeData(1000000);
// Fill with data...

// Good: O(log n) operations guaranteed
AVLTree<int> avl;
for (int val : largeData) {
    avl.insert(val);
}

// Bad: Could degrade to O(n)
BinarySearchTree<int> bst;
for (int val : largeData) {
    bst.insert(val);  // Might become unbalanced
}
```

### 4. String Operations
```cpp
// Trie is optimal for prefix operations
Trie dictionary;
vector<string> words = {"apple", "application", "apply"};

for (const string& word : words) {
    dictionary.insert(word);
}

// Fast prefix matching
if (dictionary.startsWith("app")) {
    // Show suggestions
}
```

### 5. Range Queries
```cpp
// Use Segment Tree for complex range queries
vector<int> data = {1, 2, 3, 4, 5};
SegmentTree segTree(data);

// Multiple range queries are efficient
for (int i = 0; i < 1000; i++) {
    int sum = segTree.query(0, 2);
}

// Use BIT for simple prefix sums (more memory efficient)
BinaryIndexedTree bit(5);
for (int i = 0; i < data.size(); i++) {
    bit.update(i, data[i]);
}
```

---

##  Common Pitfalls

### 1. Unbalanced BST
```cpp
//  Bad: Sequential insertion creates linked list
BinarySearchTree<int> bst;
for (int i = 1; i <= 100; i++) {
    bst.insert(i);  // O(n) height!
}

//  Good: Use AVL or Red-Black for guaranteed balance
AVLTree<int> avl;
for (int i = 1; i <= 100; i++) {
    avl.insert(i);  // O(log n) height guaranteed
}
```

### 2. Segment Tree Indexing
```cpp
vector<int> arr = {1, 2, 3, 4, 5};
SegmentTree segTree(arr);

//  Wrong: Forgetting 0-based indexing
int sum = segTree.query(1, 4);  // Queries arr[1] to arr[4]

//  Correct: Be aware of indexing
int sum = segTree.query(0, 4);  // Queries arr[0] to arr[4] (entire array)
```

### 3. BIT Update Semantics
```cpp
BinaryIndexedTree bit(5);

//  Wrong: Thinking update sets value
bit.update(0, 5);  // This ADDS 5, doesn't set to 5
bit.update(0, 3);  // Now value is 8, not 3!

//  Correct: Update adds delta
bit.update(0, 5);   // value = 5
bit.update(0, -2);  // value = 3 (added -2)
```

### 4. Trie Memory Usage
```cpp
//  Bad: Inserting very long strings
Trie trie;
trie.insert(veryLongString);  // Each character = new node

//  Good: Consider memory for large dictionaries
// For 1 million words, average length 10 = ~10 million nodes
// Each node has HashMap overhead
```

### 5. N-ary Tree Manual Management
```cpp
//  Bad: Losing reference to nodes
NaryNode<int>* node = root->children[0];
// If root is deleted, this pointer becomes invalid

//  Good: Keep track of tree structure
// Always access through tree's root
NaryNode<int>* root = tree.getRoot();
```

---

## 🔍 Debugging Tips

### Visualize Your Tree
```cpp
// Always display tree structure when debugging
bst.insert(50);
bst.insert(30);
bst.display();  // See actual structure

// Check if tree is balanced
avl.display();  // Heights shown for each node
```

### Verify Insertion Order
```cpp
// BST behavior depends on insertion order
vector<int> data = {50, 30, 70, 20, 40};  // Balanced
vector<int> sorted = {20, 30, 40, 50, 70};  // Unbalanced!

// Test with both
```

### Test Edge Cases
```cpp
// Empty tree
bst.search(10);  // Should handle gracefully

// Single element
bst.insert(5);
bst.display();

// Duplicates (BST doesn't allow)
bst.insert(5);
bst.insert(5);  // Only one instance
```

---

##  Integration Examples

### Example 1: Contact Management System
```cpp
class Contact {
public:
    string name;
    string phone;
    
    bool operator<(const Contact& other) const {
        return name < other.name;
    }
};

// Use AVL for fast lookup
AVLTree<Contact> contacts;

// Add contacts
Contact c1{"Alice", "123-456"};
Contact c2{"Bob", "789-012"};
contacts.insert(c1);
contacts.insert(c2);
```

### Example 2: Log Analysis System
```cpp
// Use Segment Tree for timestamp range queries
vector<int> logCounts = {10, 25, 15, 30, 20, 40};  // Logs per hour
SegmentTree logTree(logCounts);

// How many logs between hours 2 and 4?
int count = logTree.query(2, 4);

// Hour 3 had spike
logTree.update(3, 50);
```

### Example 3: Autocomplete Search
```cpp
class SearchEngine {
private:
    Trie dictionary;
    
public:
    void addWord(const string& word) {
        dictionary.insert(word);
    }
    
    bool hasCompletions(const string& prefix) {
        return dictionary.startsWith(prefix);
    }
    
    void search(const string& query) {
        if (dictionary.search(query)) {
            cout << "Exact match found!" << endl;
        } else if (dictionary.startsWith(query)) {
            cout << "Showing suggestions..." << endl;
        }
    }
};
```

---

# An Explanation of Tree Data Structures

A **tree** is a non-linear, hierarchical data structure that consists of a collection of nodes connected by edges. Unlike linear data structures (like arrays or linked lists) which have a logical start and end, trees represent hierarchical relationships. The topmost node is called the **root**, and from there, it branches out into several other nodes, much like an upside-down real-life tree. 🌳

![Tree Structure](tree_diagrams/tree_structure.jpg)

---

## Core Terminologies

To understand trees, you must be familiar with the following terms:

* **Node:** The fundamental part of a tree that contains data and may link to other nodes.
* **Edge:** The connection or link between two nodes.
* **Root:** The topmost node in a tree, which has no parent. A tree has only one root.
* **Parent:** A node that has an edge to a child node.
* **Child:** A node that has an edge from a parent node.
* **Siblings:** Nodes that share the same parent.
* **Leaf Node (or External Node):** A node that has no children.
* **Internal Node:** A node that has at least one child.
* **Path:** A sequence of nodes and edges connecting a node with a descendant.
* **Level:** The level of a node represents the number of edges on the path from the root to that node. The root is at level 0.
* **Height of a Tree:** The number of edges on the longest path from the root to a leaf node. The height of a tree with a single node is 0.
* **Depth of a Node:** The number of edges from the root to that node. The depth of the root is 0.
* **Subtree:** A tree consisting of a node and all of its descendants.

---

![Tree Terminologies](tree_diagrams/tree_terminologies.jpg)

## General Types of Trees

Trees can be broadly classified based on their structure and the number of children a node can have. Some high-level categories include:

* **General Tree:** A tree where there is no constraint on the number of children a node can have.
* **Binary Tree:** A tree in which each node can have at most two children (a left child and a right child).
* **Search Trees:** Trees that are specifically structured to allow for efficient searching, insertion, and deletion of items (e.g., Binary Search Tree, B-Tree).
* **Balanced Trees:** Search trees that automatically keep their height small, ensuring that operations remain efficient (e.g., AVL Tree, Red-Black Tree).


![Tree Types](tree_diagrams/tree_types.jpg)

---

## General Applications of Trees

Trees are fundamental in computer science and have numerous applications:

* **File Systems:** Representing the hierarchical structure of files and directories. 📁
* **Databases:** Indexing data for efficient retrieval (e.g., B-Trees, B+ Trees). 💾
* **Networking:** Structuring routing tables for efficient packet forwarding. 🌐
* **Compilers:** Representing the syntax of a program in an Abstract Syntax Tree (AST).
* **GUI Frameworks:** Representing the structure of UI elements (e.g., HTML DOM).
* **Artificial Intelligence:** Used in decision-making algorithms (e.g., Decision Trees). 🤖


![Tree Applications](tree_diagrams/tree_applications.png)

---

## Specific Types of Trees


### 1. Binary Search Trees (BST)

* **Definition:** A Binary Search Tree is a node-based binary tree data structure which has the following properties:
    1.  The left subtree of a node contains only nodes with keys lesser than the node’s key.
    2.  The right subtree of a node contains only nodes with keys greater than the node’s key.
    3.  The left and right subtree each must also be a binary search tree.
    4.  There must be no duplicate nodes.

* **ASCII Diagram / Example:** A BST created from inserting the numbers: `8, 3, 10, 1, 6, 14, 4, 7, 13`.

    ```
              11
             / \
            /   \
           7     15
          / \    / \
         4   9  10  25
    ```

* **Application:** Used to implement dictionaries, associative arrays, and symbol tables in compilers. They are efficient for search, insert, and delete operations, with an average time complexity of $O(\log n)$.


![Binary Search Trees (BST)](tree_diagrams/Binary-Search-tree.png)


---

### 2. AVL Trees

* **Definition:** An AVL (Adelson-Velsky and Landis) tree is a self-balancing Binary Search Tree. The heights of the two child subtrees of any node differ by at most one. This property is maintained by performing "rotations" whenever an insertion or deletion causes the tree to become unbalanced. The difference in heights is called the **Balance Factor**.

* **ASCII Diagram / Example:** An AVL tree maintains a balance factor of -1, 0, or 1 for every node.

    ```
              33 (BF: 1)
             /  \
            /    \
  (BF: -1) 13     53 (BF: -1)
          /  \      \ 
 (BF: 0) 9    21     61 (BF: 0)
        / \   (BF: 1)  
(BF: 0)8   11    
          (BF: 0) 
    ```

* **Application:** Used in scenarios that require fast lookups where insertions and deletions are less frequent, such as database indexing where fast retrieval is critical.


![AVL Trees](tree_diagrams/avl-tree.png)

---

### 3. B-Tree

* **Definition:** A B-Tree is a self-balancing tree data structure that maintains sorted data and allows for operations in logarithmic time. Unlike binary trees, a B-Tree node can have more than two children. They are optimized for systems that read and write large blocks of data, making them ideal for storage systems like disks.

* **ASCII Diagram / Example:** A B-Tree of order 5 (a node can have at most 5 children and 4 keys).

    ```
                   --------[100]-----------         - -
                  /                    \    
                [35|65]             [130|180]----|------------|          
              /    |    \               |        |            |
        [10|20] [40|50] [70|80|90] [110|120] [140|160] [190|240|260]
    ```

* **Application:** The primary data structure for databases (e.g., MySQL, PostgreSQL) and modern filesystems (e.g., NTFS, HFS+, ext4).


![B-Trees](tree_diagrams/b_trees.png)

---

### 4. Red-Black Tree

* **Definition:** A Red-Black Tree is another type of self-balancing Binary Search Tree. Each node has an extra bit for storing color ("red" or "black"). A set of rules governing the node colors ensures that the tree remains approximately balanced during insertions and deletions.

* **ASCII Diagram / Example:** `B` = Black, `R` = Red. Every path from the root to a NIL leaf has the same number of black nodes.

    ```
              13(B)
             /   \
            /     \
          8(R)     17(B)
         /   \       /   \
       1(B)  11(B)  15(R) 25(B)
                       \
                        27(R)
    ```

* **Application:** Used in the implementation of `std::map` and `std::set` in C++, Java's `TreeMap` and `TreeSet`, and the Linux kernel's Completely Fair Scheduler (CFS).


![Red Black Trees](tree_diagrams/red_black_tree.jpg)

---

### 5. Trie (Prefix Tree)

* **Definition:** A Trie, also known as a prefix tree, is a tree-like data structure that stores a dynamic set of strings. Each node represents a single character, and the path from the root to a specific node represents a prefix. A special marker often indicates the end of a complete word.

* **ASCII Diagram / Example:** A Trie storing the words: "A", "TO", "TEA", "TED", "TEN", "I", "IN", "INN". `(*)` denotes the end of a word.

    ```
           (root)
           / | \
          A* I* T
             |   | \
             N* O* E-A*
             |      | \
             N* D* N*
    ```

* **Application:** Autocomplete and predictive text systems, spell checkers, dictionary lookups, and IP routing tables.


![Trie](tree_diagrams/trie.jpg)

---

### 6. Segment Tree

* **Definition:** A Segment Tree is a tree data structure for storing information about intervals or segments. It allows for efficiently querying a property (like sum, minimum, or maximum) over a given range. It is typically a complete binary tree where each node represents an interval.

* **ASCII Diagram / Example:** A Segment Tree for Range Sum Query on the array `A = [2, 5, 1, 4, 9, 3]`. Each node stores the sum of its corresponding range.

    ```
                  [0-5] Sum=24
                 /            \
            [0-2] Sum=8        [3-5] Sum=16
           /       \          /          \
    [0-1] Sum=7  [2-2] Sum=1  [3-4] Sum=13  [5-5] Sum=3
      /    \                      /    \
    [0] 2  [1] 5                [3] 4  [4] 9
    ```

* **Application:** Solving range query problems in competitive programming, computational geometry, and real-time data processing for range-based statistics.


![Segment Tree](tree_diagrams/segment_tree.png)

---

### 7. Binary Indexed Tree (BIT) / Fenwick Tree

* **Definition:** A Binary Indexed Tree, or Fenwick Tree, is a data structure that can efficiently update element values and calculate prefix sums in an array. It is more space-efficient than a Segment Tree for prefix-sum problems but is generally less versatile. Its structure is implicit and is managed using bitwise operations on array indices.

* **ASCII Diagram / Example:** The structure is implicit in an array. For an array `A`, the BIT `T` stores cumulative sums. `T[i]` stores the sum of `A` in the range `[i - (i & -i) + 1, i]`. The diagram shows the conceptual parent-child relationship for calculating sums.

    ```
    Array A: [3, 2, -1, 6, 5, 4, -3, 3]

    BIT Array T (conceptual parent-child relation for queries):
    T[1] = A[1]
    T[2] = A[1]+A[2]
    T[3] = A[3]
    T[4] = A[1]+A[2]+A[3]+A[4]
    T[5] = A[5]
    T[6] = A[5]+A[6]
    T[7] = A[7]
    T[8] = A[1]+...+A[8]
    ```

* **Application:** Efficiently calculating prefix sums and solving problems involving range updates/queries, often used in competitive programming.


![Binary Indexed Tree](tree_diagrams/binary_indexed_tree.jpg)

---

### 8. N-ary trees (or General Trees)

* **Definition:** An N-ary tree is a tree in which each node can have at most N children. A general tree is one where there is no limit on the number of children a node can have. This is the most generic form of a tree.

* **ASCII Diagram / Example:** An N-ary tree representing a simplified file system directory.

    ```
            / (root)
          /    |      \
         /     |       \
    home/   usr/       etc/
      |      /  \      /   \
      |     /    \    /     \
    user/  bin/  lib/ ssh/   nginx/
    ```

* **Application:** Representing file systems, organizational charts, family trees, and the Document Object Model (DOM) in HTML.


![N-ary Trees](tree_diagrams/nary_tree.jpg)

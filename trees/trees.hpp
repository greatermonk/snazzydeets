#ifndef TREES_HPP
#define TREES_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include "../console_colors/colours.hpp"

using namespace std;
using namespace colors;
// ============================================================================
// BASE TREE NODE CLASSES
// ============================================================================

/**
 * Base class for all tree nodes
 * Provides common interface for tree operations
 */
template<typename T>
class TreeNode {
public:
    T data;
    virtual ~TreeNode() = default;
};
/**
 * Structure to hold search results for all tree types
 * level: The level at which node is found (1-indexed, root = 1)
 * position: Position at that level (0 = leftmost)
 * found: Whether the value was found
 */
struct SearchResult {
    int level;
    int position;
    bool found;
    
    SearchResult() : level(-1), position(-1), found(false) {}
    SearchResult(int l, int p) : level(l), position(p), found(true) {}
    
    /**
     * Display search result in readable format
     */
    void print(bool use_color = false) const {
        if (found) {
            cprint(use_color, "\nFound at Level: ");
            cprint(use_color, level, BRIGHT_CYAN, true);
            cprint(use_color, "\n Position: ");
            cprint(use_color, position, BRIGHT_CYAN, true);
            if (level > 1) {
                cprint(use_color, "(", BRIGHT_BLACK);
                if (position == 0) cprint(use_color, "leftmost");
                else if (position == 1) cprint(use_color, "right");
                else { cprint(use_color,""); }
                cprint(use_color, ")", BLACK);
            }
            cout << endl;
            cout << endl;
        } else {
            cprint(use_color, "Not Found", BRIGHT_RED, true);
            cout << endl;
        }
    }
};
// ============================================================================
// 1. BINARY SEARCH TREE (BST)
// ============================================================================

/**
 * Node class for Binary Search Tree
 */
template<typename T>
class BSTNode : public TreeNode<T> {
public:
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(T value) : left(nullptr), right(nullptr) {
        this->data = value;
    }
};

/**
 * Binary Search Tree implementation
 * Properties: Left subtree < Node < Right subtree
 */
template<typename T>
class BinarySearchTree {
private:
    BSTNode<T>* root;
    
    /**
     * Helper function to insert a value recursively
     */
    BSTNode<T>* insertHelper(BSTNode<T>* node, T value) {
        if (node == nullptr) {
            return new BSTNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        
        return node;
    }
    
    /**
     * Helper function to search for a value with level and position
     * Returns SearchResult with level and position information
     */
    SearchResult searchHelper(BSTNode<T>* node, T value, int currentLevel, int position) {
        if (node == nullptr) {
            return SearchResult();
        }
        
        if (node->data == value) {
            return SearchResult(currentLevel, position);
        }
        
        if (value < node->data) {
            return searchHelper(node->left, value, currentLevel + 1, position * 2);
        }
        return searchHelper(node->right, value, currentLevel + 1, position * 2 + 1);
    }
    /**
     * Helper function for inorder traversal
     */
    void inorderHelper(BSTNode<T>* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

     /**
     * Helper to get height of a specific node with given value
     */
    int getNodeHeightHelper(BSTNode<T>* node, T value) {
        if (node == nullptr) {
           throw logic_error("Can't get the height of the node as Tree is empty!");
        }

        if (node->data == value) {
            return calculateHeight(node);
        }

        if (value < node->data) {
            return getNodeHeightHelper(node->left, value);
        }
        return getNodeHeightHelper(node->right, value);
    }

    /**
     * Calculate height of a given node
     * Height = longest path from node to leaf
     */
    int calculateHeight(BSTNode<T>* node) {
        if (node == nullptr) return -1;

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        return max(leftHeight, rightHeight) + 1;
    }

    /**
     * Get depth of a specific node (distance from root)
     */
    int getNodeDepthHelper(BSTNode<T>* node, T value, int depth) {
        if (node == nullptr) {
            throw logic_error("Tree doesn't have any leaf nodes. Add some nodes using BSTNode.insert() method!");
        }

        if (node->data == value) {
            return depth;
        }

        if (value < node->data) {
            return getNodeDepthHelper(node->left, value, depth + 1);
        }
        return getNodeDepthHelper(node->right, value, depth + 1);
    }

public:
    BinarySearchTree() : root(nullptr) {}
    
    /**
     * Insert a value into the BST
     * Time Complexity: O(log n) average, O(n) worst
     */
    void insert(T value) {
        root = insertHelper(root, value);
    }
    
     /**
     * Search for a value in the BST
     * Returns SearchResult with level (1-indexed) and position
     * Position follows complete binary tree indexing (0 = leftmost)
     * Time Complexity: O(log n) average, O(n) worst
     * 
     * @throws runtime_error if tree is empty
     */
    SearchResult search(T value) {
        if (root == nullptr) {
            throw runtime_error("Cannot search in empty tree");
        }
        return searchHelper(root, value, 1, 0);
    }
    /**
     * Display tree in inorder traversal (sorted order)
     */
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
    
    /**
     * Display tree structure in ASCII format
     */
    void display(bool use_color = false) {
        cout << "Binary Search Tree Structure:\n";
        displayHelper(root, "", true, use_color);
    }

    int getNodeHeight(T value) {
        if (root == nullptr) {
            throw runtime_error("Cannot get height from empty tree");
        }
        return getNodeHeightHelper(root, value);
    }

    /**
     * Get depth of a specific node
     * Depth = distance from root (root has depth 0)
     * Returns nullopt if node not found
     * Time Complexity: O(log n) average, O(n) worst
     *
     * @throws runtime_error if tree is empty
     */
    int getNodeDepth(T value) {
        if (root == nullptr) {
            throw runtime_error("Cannot get depth from empty tree");
        }
        return getNodeDepthHelper(root, value, 0);
    }

    /**
     * Get height of entire tree
     * Time Complexity: O(n)
     */
    int getTreeHeight() {
        if (root == nullptr) return -1;
        return calculateHeight(root);
    }
    
private:
    /**
     * Helper function to display tree structure recursively
     * Uses box-drawing characters for visual representation
     */
   void displayHelper(BSTNode<T>* node, string prefix, bool isRight, bool use_color) {
        if (node == nullptr) return;
        
        cout << prefix;
        if (isRight) {
            cprint(use_color, "|-- ", BRIGHT_GREEN);
        } else {
            cprint(use_color, "`-- ", BRIGHT_GREEN);
        }
        cprint(use_color, "(", BRIGHT_YELLOW);
        cprint(use_color, node->data, BRIGHT_BLUE);
        cprint(use_color, ")", BRIGHT_YELLOW);
        cout << endl;
        
        if (node->left != nullptr || node->right != nullptr) {
            if (node->right != nullptr) {
                displayHelper(node->right, prefix + (isRight ? "|   " : "    "), true, use_color);
            }
            if (node->left != nullptr) {
                displayHelper(node->left, prefix + (isRight ? "|   " : "    "), false, use_color);
            }
        }
    }
};

// ============================================================================
// 2. AVL TREE (Self-Balancing BST)
// ============================================================================

/**
 * Node class for AVL Tree
 */
template<typename T>
class AVLNode {
public:
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;
    
    AVLNode(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

/**
 * AVL Tree implementation - Self-balancing binary search tree
 * Maintains height balance: |height(left) - height(right)| <= 1
 */
template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;
    
    /**
     * Get height of a node
     */
    int getHeight(AVLNode<T>* node) {
        return node ? node->height : 0;
    }
    
    /**
     * Get balance factor of a node
     */
    int getBalance(AVLNode<T>* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    /**
     * Right rotation for balancing
     */
    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    /**
     * Left rotation for balancing
     */
    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    /**
     * Insert a value and maintain AVL property
     */
    AVLNode<T>* insertHelper(AVLNode<T>* node, T value) {
        if (node == nullptr) {
            return new AVLNode<T>(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        } else {
            return node; // Duplicate values not allowed
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        int balance = getBalance(node);
        
        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }
        
        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }
        
        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }

    SearchResult searchHelper(AVLNode<T>* node, T value, int level, int position){
                 if (node == nullptr){
                    return SearchResult();
                 }

                 if (node->data == value){
                    return SearchResult(level, position);
                 }

                 if (value < node->data){
                    return searchHelper(node->left, value, level+1, position*2);
                 }
                 return searchHelper(node->right, value, level+1, position*2+1);
    }
    
    /**
     * Inorder traversal helper
     */
    void inorderHelper(AVLNode<T>* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
     /**
     * Get height of specific node
     */
    int getNodeHeightHelper(AVLNode<T>* node, T value) {
        if (node == nullptr) {
            throw logic_error("Tree dosen't have any leaf nodes. Add some nodes");
        }

        if (node->data == value) {
            return node->height - 1; // Convert from stored height to actual height
        }

        if (value < node->data) {
            return getNodeHeightHelper(node->left, value);
        }
        return getNodeHeightHelper(node->right, value);
    }

    /**
     * Get depth of specific node
     */
    int getNodeDepthHelper(AVLNode<T>* node, T value, int depth) {
        if (node == nullptr) {
            throw logic_error("Tree dosen't have any leaf nodes. Add some nodes");
        }

        if (node->data == value) {
            return depth;
        }

        if (value < node->data) {
            return getNodeDepthHelper(node->left, value, depth + 1);
        }
        return getNodeDepthHelper(node->right, value, depth + 1);
    }

public:
    AVLTree() : root(nullptr) {}
    
    /**
     * Insert a value into AVL tree
     * Time Complexity: O(log n)
     */
    void insert(T value) {
        root = insertHelper(root, value);
    }
    
    /**
     * Display tree in sorted order
     */
    void inorder() {
        inorderHelper(root);
        cout << endl;
    }
    
    /**
     * Display AVL tree structure in ASCII format with heights
     */
    void display(bool use_color = false) {
        cout << "AVL Tree Structure (with heights):\n";
        displayHelper(root, "", true, use_color);
    }

     /**
     * Get height of a specific node
     * Returns nullopt if node not found
     * Time Complexity: O(log n)
     *
     * @throws runtime_error if tree is empty
     */
    int getNodeHeight(T value) {
        if (root == nullptr) {
            throw runtime_error("Cannot get height from empty tree");
        }
        return getNodeHeightHelper(root, value);
    }

    /**
     * Get depth of a specific node
     * Returns nullopt if node not found
     * Time Complexity: O(log n)
     *
     * @throws runtime_error if tree is empty
     */
    int getNodeDepth(T value) {
        if (root == nullptr) {
            throw runtime_error("Cannot get depth from empty tree");
        }
        return getNodeDepthHelper(root, value, 0);
    }

    /**
     * Get height of entire tree
     * Time Complexity: O(1)
     */
    int getTreeHeight() {
        if (root == nullptr) return -1;
        return root->height - 1;
    }

    SearchResult search(T value){
                 if (root == nullptr){
                    throw logic_error("Can't retrieve the specified value as tree has no nodes");
                 }
                 return searchHelper(root, value, 1, 0);
    }
    
private:
    /**
     * Helper to display AVL tree with height information
     */
    void displayHelper(AVLNode<T>* node, string prefix, bool isRight, bool use_color) {
        if (node == nullptr) return;

        cout << prefix;
        if (isRight) {
            cprint(use_color, "|-- ", BRIGHT_GREEN);
        } else {
            cprint(use_color, "`-- ", BRIGHT_GREEN);
        }
        cprint(use_color, "(", BRIGHT_YELLOW);
        cprint(use_color, node->data, BRIGHT_BLUE);
        cprint(use_color, ")", BRIGHT_YELLOW);
        cprint(use_color, "[", BRIGHT_YELLOW);
        cprint(use_color, "h=", BRIGHT_WHITE);
        cprint(use_color, node->height, BRIGHT_CYAN);
        cprint(use_color, "]", BRIGHT_YELLOW);
        cout << endl;

        if (node->left != nullptr || node->right != nullptr) {
            if (node->right != nullptr) {
                displayHelper(node->right, prefix + (isRight ? "|   " : "    "), true, use_color);
            }
            if (node->left != nullptr) {
                displayHelper(node->left, prefix + (isRight ? "|   " : "    "), false, use_color);
            }
        }
    }
};

// ============================================================================
// 3. B-TREE
// ============================================================================

/**
 * Node class for B-Tree
 */
template<typename T>
class BTreeNode {
public:
    vector<T> keys;
    vector<BTreeNode*> children;
    bool isLeaf;
    int minDegree; // Minimum degree (t)
    
    BTreeNode(int t, bool leaf) : isLeaf(leaf), minDegree(t) {}
    
    /**
     * Search for a key in this node
     */
    bool search(T key) {
        int i = 0;
        while (i < keys.size() && key > keys[i]) {
            i++;
        }
        
        if (i < keys.size() && keys[i] == key) {
            return true;
        }
        
        if (isLeaf) {
            return false;
        }
        
        return children[i]->search(key);
    }
};

/**
 * B-Tree implementation
 * Properties: Balanced tree with multiple keys per node
 * All leaves at same level
 */
template<typename T>
class BTree {
private:
    BTreeNode<T>* root;
    int minDegree; // Minimum degree
    
public:
    /**
     * Constructor
     * @param t Minimum degree (defines range of keys)
     */
    BTree(int t) : root(nullptr), minDegree(t) {}
    
    /**
     * Search for a key in the B-Tree
     * Time Complexity: O(log n)
     */
    bool search(T key) {
        return root ? root->search(key) : false;
    }
    
    /**
     * Insert a key into the B-Tree
     * Note: Full implementation requires split operations
     */
    void insert(T key) {
        if (root == nullptr) {
            root = new BTreeNode<T>(minDegree, true);
            root->keys.push_back(key);
        }
        // Full insertion logic with node splitting omitted for brevity
    }
};

// ============================================================================
// 4. RED-BLACK TREE
// ============================================================================

enum Color { _RED, _BLACK };

/**
 * Node class for Red-Black Tree
 */
template<typename T>
class RBNode {
public:
    T data;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    Color color;
    
    RBNode(T value) : data(value), left(nullptr), right(nullptr), 
                      parent(nullptr), color(_RED) {}
};

/**
 * Red-Black Tree implementation
 * Properties:
 * 1. Every node is either red or black
 * 2. Root is black
 * 3. All leaves (NULL) are black
 * 4. Red nodes have black children
 * 5. All paths from node to leaves have same number of black nodes
 */
template<typename T>
class RedBlackTree {
private:
    RBNode<T>* root;
    RBNode<T>* NIL; // Sentinel node
    
    /**
     * Left rotation
     */
    void leftRotate(RBNode<T>* x) {
        RBNode<T>* y = x->right;
        x->right = y->left;
        
        if (y->left != NIL) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }
    
    /**
     * Right rotation
     */
    void rightRotate(RBNode<T>* y) {
        RBNode<T>* x = y->left;
        y->left = x->right;
        
        if (x->right != NIL) {
            x->right->parent = y;
        }
        
        x->parent = y->parent;
        
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        
        x->right = y;
        y->parent = x;
    }
    
    /**
     * Fix violations after insertion
     */
    void fixInsert(RBNode<T>* k) {
        while (k->parent && k->parent->color == _RED) {
            if (k->parent == k->parent->parent->left) {
                RBNode<T>* u = k->parent->parent->right;
                
                if (u && u->color == _RED) {
                    k->parent->color = _BLACK;
                    u->color = _BLACK;
                    k->parent->parent->color = _RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = _BLACK;
                    k->parent->parent->color = _RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                RBNode<T>* u = k->parent->parent->left;
                
                if (u && u->color == _RED) {
                    k->parent->color = _BLACK;
                    u->color = _BLACK;
                    k->parent->parent->color = _RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = _BLACK;
                    k->parent->parent->color = _RED;
                    leftRotate(k->parent->parent);
                }
            }
        }
        root->color = _BLACK;
    }
    
    /**
     * Helper for insertion
     */
    void insertHelper(RBNode<T>* node) {
        RBNode<T>* y = nullptr;
        RBNode<T>* x = root;
        
        while (x != NIL && x != nullptr) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        
        node->parent = y;
        
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        
        node->left = NIL;
        node->right = NIL;
        node->color = _RED;
        
        fixInsert(node);
    }

public:
    RedBlackTree() {
        NIL = new RBNode<T>(T());
        NIL->color = _BLACK;
        root = NIL;
    }
    
    /**
     * Insert a value into the Red-Black tree
     * Time Complexity: O(log n)
     */
    void insert(T value) {
        RBNode<T>* node = new RBNode<T>(value);
        insertHelper(node);
    }

    SearchResult search(T value) {
        if (root == NIL || root == nullptr) {
            throw runtime_error("Cannot search in empty tree");
        }
        return searchHelper(root, value, 1, 0);
    }
    
    /**
     * Display Red-Black tree structure with color coding
     */
    void display() {
        cout << "Red-Black Tree Structure:\n";
        cout << "(R) = Red node, (B) = Black node\n";
        displayHelper(root, "", true);
    }

    /**
     * Get height of a specific node
     * Returns nullopt if node not found
     * Time Complexity: O(log n)
     *
     * @throws runtime_error if tree is empty
     */
    int getNodeHeight(T value) {
        if (root == NIL || root == nullptr) {
            throw runtime_error("Cannot get height from empty tree");
        }
        return getNodeHeightHelper(root, value);
    }

    /**
     * Get depth of a specific node
     * Returns nullopt if node not found
     * Time Complexity: O(log n)
     *
     * @throws runtime_error if tree is empty
     */
    int getNodeDepth(T value) {
        if (root == NIL || root == nullptr) {
            throw runtime_error("Cannot get depth from empty tree");
        }
        return getNodeDepthHelper(root, value, 0);
    }

    /**
     * Get height of entire tree
     * Time Complexity: O(n)
     */
    int getTreeHeight() {
        if (root == NIL || root == nullptr) return -1;
        return calculateHeight(root);
    }
    
private:
       /**
     * Get height of specific node
     */
    int getNodeHeightHelper(RBNode<T>* node, T value) {
        if (node == nullptr || node == NIL) {
           throw logic_error("Can't get height of node as tree as no leaf nodes.");
        }
        
        
        if (node->data == value) {
            return calculateHeight(node);
        }
        
        if (value < node->data) {
            return getNodeHeightHelper(node->left, value);
        }
        return getNodeHeightHelper(node->right, value);
    }

    SearchResult searchHelper(RBNode<T>* node, T value, int level, int position) {
        if (node == nullptr || node == NIL) {
            return SearchResult();
        }

        if (node->data == value) {
            return SearchResult(level, position);
        }

        if (value < node->data) {
            return searchHelper(node->left, value, level + 1, position * 2);
        }
        return searchHelper(node->right, value, level + 1, position * 2 + 1);
    }
    
    /**
     * Calculate height from a given node
     */
    int calculateHeight(RBNode<T>* node) {
        if (node == nullptr || node == NIL) return -1;
        
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        
        return max(leftHeight, rightHeight) + 1;
    }
    
    /**
     * Get depth of specific node
     */
    int getNodeDepthHelper(RBNode<T>* node, T value, int depth) {
        if (node == nullptr || node == NIL) {
            throw logic_error("Can't get depth of the node as tree has no leaf nodes");
        }
        
        if (node->data == value) {
            return depth;
        }
        
        if (value < node->data) {
            return getNodeDepthHelper(node->left, value, depth + 1);
        }
        return getNodeDepthHelper(node->right, value, depth + 1);
    }

    /**
     * Helper to display Red-Black tree with colors
     */
    void displayHelper(RBNode<T>* node, string prefix, bool isRight) {
        if (node == nullptr || node == NIL) return;
        
        cout << prefix;
        cout << (isRight ?  "|-- "  :  "`-- " );
        cout << "(" << node->data << ")";
        cout << (node->color == _RED ?  "[R]"  :  "[B]" ) << endl;
        
        if ((node->left != NIL && node->left != nullptr) || 
            (node->right != NIL && node->right != nullptr)) {
            if (node->right != NIL && node->right != nullptr) {
                displayHelper(node->right, prefix + (isRight ?  "|   "  : "    "), true);
            }
            if (node->left != NIL && node->left != nullptr) {
                displayHelper(node->left, prefix + (isRight ?  "|   "  : "    "), false);
            }
        }
    }
};

// ============================================================================
// 5. TRIE (PREFIX TREE)
// ============================================================================

/**
 * Node class for Trie
 */
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

/**
 * Trie implementation for efficient string storage and retrieval
 * Used for prefix matching and autocomplete
 */
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }
    
    /**
     * Insert a word into the Trie
     * Time Complexity: O(m) where m is length of word
     */
    void insert(const string& word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        
        current->isEndOfWord = true;
    }

     /**
     * Search for a word and return its depth/level
     * Returns SearchResult with level and position (position = path encoding)
     * Time Complexity: O(m) where m is word length
     *
     * @throws runtime_error if tree is empty
     */
    SearchResult search_index(const string& word) {
        if (root == nullptr) {
            throw runtime_error("Cannot search in empty trie");
        }

        TrieNode* current = root;
        int level = 0;
        int position = 0;

        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return SearchResult(); // Not found
            }

            // Calculate position based on character order in children
            int charPos = 0;
            for (auto& pair : current->children) {
                if (pair.first == ch) break;
                charPos++;
            }

            position = position * 26 + (ch - 'a'); // Encode path
            current = current->children[ch];
            level++;
        }

        if (current->isEndOfWord) {
            return SearchResult(level, position);
        }

        return SearchResult(); // Prefix exists but not a complete word
    }
    
    /**
     * Search for a complete word in the Trie
     * Time Complexity: O(m)
     */
    bool search(const string& word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return current->isEndOfWord;
    }
    
    /**
     * Check if any word in the Trie starts with given prefix
     * Time Complexity: O(m)
     */
    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return true;
    }
     /**
     * Get depth of a word (number of characters)
     * Returns nullopt if word not found
     * Time Complexity: O(m)
     *
     * @throws runtime_error if tree is empty
     */
    int getWordDepth(const string& word) {
        if (root == nullptr) {
            throw runtime_error("Cannot get depth from empty trie");
        }

        TrieNode* current = root;
        int depth = 0;

        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                throw logic_error("Cat get depth of the word from the trie as is doesn't have the mentioned word");
            }
            current = current->children[ch];
            depth++;
        }

        if (current->isEndOfWord) {
            return depth;
        }

        return -1;
    }

    /**
     * Get maximum depth of trie (longest word length)
     * Time Complexity: O(n) where n is total characters
     */
    int getMaxDepth() {
      //  if (root == nullptr) return 0;
        return (root == nullptr) ? 0 : getMaxDepthHelper(root, 0);
    }
    
    /**
     * Display Trie structure in ASCII format
     * Shows the prefix tree with word endings marked
     */
    void display(bool use_color = false) {
        cout << "Trie Structure (* = word ending):\n";
        cout << "Root\n";
        displayHelper(root, "", true, use_color);
    }
    
private:
     /**
     * Helper to get maximum depth
     */
    int getMaxDepthHelper(TrieNode* node, int currentDepth) {
        if (node == nullptr) return currentDepth;

        int maxDepth = currentDepth;

        for (auto& pair : node->children) {
            maxDepth = max(maxDepth, getMaxDepthHelper(pair.second, currentDepth + 1));
        }

        return maxDepth;
    }
    /**
     * Helper to display Trie structure recursively
     */
    void displayHelper(TrieNode* node, string prefix, bool isLast, bool use_color) {
        if (node == nullptr) return;

        int count = 0;
        for (auto& pair : node->children) {
            count++;
            bool isLastChild = (count == node->children.size());

            cout << prefix;
            if (isLast) {
                cprint(use_color, "`-- ", BRIGHT_GREEN);
            } else {
                cprint(use_color, "|-- ", BRIGHT_GREEN);
            }
            cprint(use_color, "[", BRIGHT_YELLOW);
            cprint(use_color, pair.first, BRIGHT_BLUE);
            cprint(use_color, "]", BRIGHT_YELLOW);

            if (pair.second->isEndOfWord) {
                cprint(use_color, " *", RED, true);
            }
            cout << endl;

            displayHelper(pair.second, prefix + (isLast ? "    " : "|   "), isLastChild, use_color);
        }
    }
};

// ============================================================================
// 6. SEGMENT TREE
// ============================================================================

/**
 * Segment Tree implementation for range queries
 * Supports range sum queries and point updates
 */
class SegmentTree {
private:
    vector<int> tree;
    int n;
    
    /**
     * Build the segment tree recursively
     */
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    /**
     * Update a value at given index
     */
    void updateHelper(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                updateHelper(2 * node, start, mid, idx, value);
            } else {
                updateHelper(2 * node + 1, mid + 1, end, idx, value);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    /**
     * Query sum in range [L, R]
     */
    int queryHelper(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return 0; // Outside range
        }
        
        if (L <= start && end <= R) {
            return tree[node]; // Completely inside range
        }
        
        int mid = (start + end) / 2;
        int leftSum = queryHelper(2 * node, start, mid, L, R);
        int rightSum = queryHelper(2 * node + 1, mid + 1, end, L, R);
        
        return leftSum + rightSum;
    }

public:
    /**
     * Constructor: build segment tree from array
     */
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    /**
     * Update value at index
     * Time Complexity: O(log n)
     */
    void update(int idx, int value) {
        updateHelper(1, 0, n - 1, idx, value);
    }
    
    /**
     * Query sum in range [L, R]
     * Time Complexity: O(log n)
     */
    int query(int L, int R) {
        return queryHelper(1, 0, n - 1, L, R);
    }
    
    /**
     * Display Segment Tree structure
     * Shows internal nodes with their ranges and values
     */
    void display(bool use_color = false) {
       cprint(use_color, "Segment Tree Structure:\n", BOLD);
       cprint(use_color, "Format: ", BRIGHT_WHITE);
       cprint(use_color, "[", BRIGHT_YELLOW);
       cprint(use_color, "range", BRIGHT_BLUE);
       cprint(use_color, "]", BRIGHT_YELLOW);
       cprint(use_color, " = ", BRIGHT_WHITE);
       cprint(use_color, "value", BRIGHT_CYAN);
       cout << endl;
       displayHelper(1, 0, n - 1, "", true, use_color);
   }

private:
    /**
     * Helper to display segment tree with ranges
     */
    void displayHelper(int node, int start, int end, string prefix, bool isRight, bool use_color) {
        if (node >= tree.size() || start > end) return;

        cout << prefix;
        if (node == 1) {
            cprint(use_color, node, MAGNETA, true);
        } else if (isRight) {
            cprint(use_color, "|-- ", BRIGHT_GREEN);
        } else {
            cprint(use_color, "`-- ", BRIGHT_GREEN);
        }
        cprint(use_color, "[", BRIGHT_YELLOW);
        cprint(use_color, start, BRIGHT_BLUE);
        cprint(use_color, ",", BRIGHT_WHITE);
        cprint(use_color, end, BRIGHT_BLUE);
        cprint(use_color, "]", BRIGHT_YELLOW);
        cprint(use_color, " = ", BRIGHT_WHITE);
        cprint(use_color, tree[node], BRIGHT_CYAN);
        cout << endl;

        if (start != end) {
            int mid = (start + end) / 2;
            string newPrefix = (node == 1) ? "" : prefix + (isRight ? "|   " : "    ");
            displayHelper(2 * node, start, mid, newPrefix, true, use_color);
            displayHelper(2 * node + 1, mid + 1, end, newPrefix, false, use_color);
        }
    }
};

// ============================================================================
// 7. BINARY INDEXED TREE (FENWICK TREE)
// ============================================================================

/**
 * Binary Indexed Tree (Fenwick Tree) implementation
 * Efficient for prefix sum queries and point updates
 */
class BinaryIndexedTree {
private:
    vector<int> tree;
    int n;

public:
    /**
     * Constructor: initialize BIT with given size
     */
    BinaryIndexedTree(int size) : n(size) {
        tree.resize(n + 1, 0);
    }
    
    /**
     * Update value at index by adding delta
     * Time Complexity: O(log n)
     */
    void update(int idx, int delta) {
        idx++; // BIT uses 1-based indexing
        while (idx <= n) {
            tree[idx] += delta;
            idx += idx & (-idx); // Add last set bit
        }
    }
    
    /**
     * Query prefix sum from 0 to idx
     * Time Complexity: O(log n)
     */
    int query(int idx) {
        idx++; // BIT uses 1-based indexing
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx); // Remove last set bit
        }
        return sum;
    }
    
    /**
     * Query range sum from L to R
     * Time Complexity: O(log n)
     */
    int rangeQuery(int L, int R) {
        return query(R) - (L > 0 ? query(L - 1) : 0);
    }
    
    /**
     * Display Binary Indexed Tree structure
     * Shows the internal representation
     */
    void display(bool use_color = false) {
        cprint(use_color, "Binary Indexed Tree (Fenwick Tree):\n", BOLD);
        cprint(use_color, "Index --> Value (cumulative)\n", BRIGHT_WHITE);
        for (int i = 1; i <= n; i++) {
            cprint(use_color, "  ");
            cprint(use_color, i, BRIGHT_CYAN);
            cprint(use_color, " --> ", BRIGHT_WHITE);
            cprint(use_color, tree[i], BRIGHT_BLUE);

            // Show which indices this node is responsible for
            int range = i & (-i);
            cprint(use_color, " [", BRIGHT_YELLOW);
            cprint(use_color, "covers ", BRIGHT_WHITE);
            cprint(use_color, (i - range + 1), BRIGHT_CYAN);
            cprint(use_color, "-", BRIGHT_WHITE);
            cprint(use_color, i, BRIGHT_CYAN);
            cprint(use_color, "]", BRIGHT_YELLOW);
            cout << endl;
        }
    }
};

// ============================================================================
// 8. N-ARY TREE
// ============================================================================

/**
 * Node class for N-ary Tree
 */
template<typename T>
class NaryNode {
public:
    T data;
    vector<NaryNode*> children;
    
    NaryNode(T value) : data(value) {}
};

/**
 * N-ary Tree implementation
 * Each node can have any number of children
 */


template<typename T>
class NaryTree {
private:
    NaryNode<T>* root;
    
    /**
     * Helper for level order traversal
     */
    void levelOrderHelper(NaryNode<T>* node) {
        if (node == nullptr) return;
        
        queue<NaryNode<T>*> q;
        q.push(node);
        
        while (!q.empty()) {
            int size = q.size();
            
            for (int i = 0; i < size; i++) {
                NaryNode<T>* current = q.front();
                q.pop();
                
                cout << current->data << " ";
                
                for (auto child : current->children) {
                    q.push(child);
                }
            }
            cout << endl;
        }
    }

public:
    SearchResult search(T node_value){
         queue<pair<NaryNode<T>*, pair<int, int>>> q;
         q.push(make_pair(root, make_pair(1, 0)));
        
         while (!q.empty()){
               int levelsize = q.size();
               int levelpos = 0;

               for (int i = 0; i < levelsize; i++){
                   pair<NaryNode<T>*, pair<int, int>> frontpair = q.front();
                   q.pop();

                   NaryNode<T>* node = frontpair.first;
                   int level = frontpair.second.first;
                   int pos = frontpair.second.second;

                   if (node->data == node_value){
                      return SearchResult(level, levelpos);
                   }

                   for (size_t j = 0; j < node->children.size(); j++){
                       q.push(make_pair(node->children[j], make_pair(level+1, static_cast<int>(j))));
                   }
                   levelpos++;
               }
         }
         return SearchResult(); // Not found
    }

    NaryTree() : root(nullptr) {}
    
    /**
     * Create root node with given value
     */
    void createRoot(T value) {
        root = new NaryNode<T>(value);
    }
    
    /**
     * Add child to a parent node
     * Note: In practice, you'd need a way to find the parent node
     */
    void addChild(NaryNode<T>* parent, T value) {
        if (parent == nullptr) return;
        parent->children.push_back(new NaryNode<T>(value));
    }
    
    /**
     * Get root node for manual tree construction
     */
    NaryNode<T>* getRoot() {
        return root;
    }
    
    /**
     * Level order traversal (BFS)
     * Time Complexity: O(n)
     */
    void levelOrder() {
        levelOrderHelper(root);
    }
    
    /**
     * Display N-ary tree structure in ASCII format
     */
    void display(bool use_color = false) {
        cout << "N-ary Tree Structure:\n";
        displayHelper(root, "", true, true, use_color);
    }

    int getNodeHeight(T node_value){
        if (root == nullptr) throw logic_error("Can't retrieve Node Height");
        NaryNode<T>* targetnode = findNode(root, node_value);
    
        return (targetnode == nullptr) ? -1 : calculateHeight(targetnode);
    }

    int getNodeDepth(T node_value){
        return (root == nullptr) ? -1 : getNodeDepthHelper(root, node_value, 0);
    }

    int getTreeHeight(){
        return (root == nullptr) ? -1 : calculateHeight(root);
    }

    
private:
    /**
     * Find a node with given value
     */
    NaryNode<T>* findNode(NaryNode<T>* node, T value) {
        if (node == nullptr) return nullptr;

        if (node->data == value) return node;

        for (auto child : node->children) {
            NaryNode<T>* result = findNode(child, value);
            if (result != nullptr) return result;
        }

        return nullptr;
    }

    /**
     * Calculate height of a node
     */
    int calculateHeight(NaryNode<T>* node) {
        if (node == nullptr) return -1;

        if (node->children.empty()) return 0;

        int maxHeight = -1;
        for (auto child : node->children) {
            maxHeight = max(maxHeight, calculateHeight(child));
        }

        return maxHeight + 1;
    }

    /**
     * Get depth helper
     */
    int getNodeDepthHelper(NaryNode<T>* node, T value, int depth) {
        if (node == nullptr) throw logic_error("Can't retrieve node height as the Nary Tree has no leaf nodes");
        if (node->data == value) return depth;
        for (auto child : node->children) {
            int result = getNodeDepthHelper(child, value, depth + 1);
            if (result != -1) return result;
        }
        return -1;
    }
    /**
     * Helper to display N-ary tree structure
     */
     void displayHelper(NaryNode<T>* node, string prefix, bool isLast, bool isRoot, bool use_color) {
        if (node == nullptr) return;

        if (!isRoot) {
            cout << prefix;
            if (isLast) {
                cprint(use_color, "`-- ", BRIGHT_GREEN);
            } else {
                cprint(use_color, "|-- ", BRIGHT_GREEN);
            }
        } 
        
        cprint(use_color, "(", BRIGHT_YELLOW);
        cprint(use_color, node->data, BRIGHT_BLUE);
        cprint(use_color, ")", BRIGHT_YELLOW);

        if (!node->children.empty()) {
            cprint(use_color, " --> ", BRIGHT_WHITE);
            cprint(use_color, "[", BRIGHT_YELLOW);
            cprint(use_color, node->children.size(), BRIGHT_CYAN);
            cprint(use_color, " children", BRIGHT_WHITE);
            cprint(use_color, "]", BRIGHT_YELLOW);
        }
        cout << endl;

        for (size_t i = 0; i < node->children.size(); i++) {
            bool isLastChild = (i == node->children.size() - 1);
            string newPrefix = isRoot ? "" : prefix + (isLast ? "    " : "|   ");
            displayHelper(node->children[i], newPrefix, isLastChild, false, use_color);
        }
    }
};
#endif

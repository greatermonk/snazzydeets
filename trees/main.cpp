#include "trees.hpp"

using namespace std;


int main(){
    BinarySearchTree<short> bst;
    bst.insert(100); // -> Root Node
    bst.insert(80); 
    bst.insert(120);
    bst.insert(60); 
    bst.insert(90); 
    bst.insert(110);
    bst.insert(130);

    bst.insert(50); 
    bst.insert(70); 
    bst.insert(105);
    bst.insert(115);
    bst.insert(85); 
    bst.insert(95); 
    bst.insert(125);
    bst.insert(135);
    
    cout << "Inorder traversal: ";
    bst.inorder();
    bst.display(true);
    
    // Enhanced search
    cout << "\nSearch operations:\n";
    try {
        SearchResult result = bst.search(125);
        cout << "Searching for 125: ";
        result.print();
        
        result = bst.search(95);
        cout << "Searching for 95: ";
        result.print();
        
        result = bst.search(110);
        cout << "Searching for 110: ";
        result.print();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    // Height and depth queries
    cout << "\nHeight and Depth queries:\n";
    try {
        auto height = bst.getNodeHeight(85);
        if (height) {
            cout << "Height of node 85: " << height << endl;
        }
        
        auto depth = bst.getNodeDepth(105);
        if (depth) {
            cout << "Depth of node 105: " << depth << endl;
        }
        
        cout << "Tree height: " << bst.getTreeHeight() << endl;
        
        // Try root node
        height = bst.getNodeHeight(100);
        if (!height) {
            cout << "Node 100: Not found\n";
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "\n";
    
    // 2. AVL Tree
    cout << "2. AVL TREE (Self-Balancing):\n";
    cout << "==============================\n";
    AVLTree<int> avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    
    cout << "Inorder traversal: ";
    avl.inorder();
    avl.display(true);
    
    cout << "\nSearch operations:\n";
    try {
        SearchResult result = avl.search(25);
        cout << "Searching for 25: ";
        result.print();
        
        cout << "Tree height: " << avl.getTreeHeight() << endl;
        
        auto depth = avl.getNodeDepth(40);
        if (depth) {
            cout << "Depth of node 40: " << depth << endl;
        }
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "\n";
    
    // 3. Red-Black Tree
    cout << "3. RED-BLACK TREE:\n";
    cout << "==================\n";
    RedBlackTree<int> rbt;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(5);
    rbt.display();
    
    cout << "\nSearch operations:\n";
    try {
        SearchResult result = rbt.search(15);
        cout << "Searching for 15: ";
        result.print();
        
        auto height = rbt.getNodeHeight(20);
        if (height) {
            cout << "Height of node 20: " << height << endl;
        }
        
        cout << "Tree height: " << rbt.getTreeHeight() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "\n";
    
    // 4. Trie
    cout << "4. TRIE (Prefix Tree):\n";
    cout << "======================\n";
    Trie trie;
    trie.insert("hello");
    trie.insert("world");
    trie.insert("help");
    trie.insert("heap");
    trie.insert("wonder");
    trie.display(true);
    
    cout << "\nSearch operations:\n";
    try {
        SearchResult result = trie.search_index("hello");
        cout << "Searching for 'hello': ";
        result.print();
        
        result = trie.search_index("hel");
        cout << "Searching for 'hel': ";
        result.print();
        
        auto depth = trie.getWordDepth("world");
        if (depth) {
            cout << "Depth of 'world': " << depth << endl;
        }
        
       cout << "Searching for the word 'hello': " << trie.search("hello") << endl;
        
        cout << "Max depth: " << trie.getMaxDepth() << endl;
        cout << "Starts with 'hel': " << (trie.startsWith("hel") ? "Yes" : "No") << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "\n";
    
    // 5. Segment Tree
    cout << "5. SEGMENT TREE:\n";
    cout << "================\n";
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    cout << "Array: [";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]\n";
    SegmentTree segTree(arr);
    segTree.display(true);
    cout << "Sum of range [1, 3]: " << segTree.query(1, 3) << "\n";
    segTree.update(1, 10);
    cout << "After updating index 1 to 10:\n";
    cout << "Sum of range [1, 3]: " << segTree.query(1, 3) << "\n\n";
    
    // 6. Binary Indexed Tree
    cout << "6. BINARY INDEXED TREE (Fenwick Tree):\n";
    cout << "=======================================\n";
    BinaryIndexedTree bit(6);
    bit.update(0, 1);
    bit.update(1, 3);
    bit.update(2, 5);
    bit.update(3, 7);
    bit.update(4, 9);
    bit.update(5, 11);
    bit.display(true);
    cout << "Prefix sum up to index 2: " << bit.query(2) << "\n";
    cout << "Range sum [1, 3]: " << bit.rangeQuery(1, 3) << "\n\n";
    
    // 7. N-ary Tree
    cout << "7. N-ARY TREE:\n";
    cout << "==============\n";
    NaryTree<int> nary;
    nary.createRoot(1);
    NaryNode<int>* root = nary.getRoot();
    nary.addChild(root, 2);
    nary.addChild(root, 3);
    nary.addChild(root, 4);
    
    // Add children to node 2
    NaryNode<int>* node2 = root->children[0];
    nary.addChild(node2, 5);
    nary.addChild(node2, 6);
    
    // Add children to node 3
    NaryNode<int>* node3 = root->children[1];
    nary.addChild(node3, 7);
    
    // Add children to node 4
    NaryNode<int>* node4 = root->children[2];
    nary.addChild(node4, 8);
    nary.addChild(node4, 9);
    nary.addChild(node4, 10);
    
    nary.display(true);
    
    cout << "\nSearch operations:\n";
    try {
        SearchResult result = nary.search(5);
        cout << "Searching for 5: ";
        result.print();
        
        result = nary.search(7);
        cout << "Searching for 7: ";
        result.print();
        
        auto height = nary.getNodeHeight(2);
        if (height) {
            cout << "Height of node 2: " << height << endl;
        }
        
        auto depth = nary.getNodeDepth(8);
        if (depth) {
            cout << "Depth of node 8: " << depth << endl;
        }
        
        cout << "Tree height: " << nary.getTreeHeight() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\nLevel order traversal:\n";
    nary.levelOrder();
    
    // Edge case testing
    cout << "\n8. EDGE CASE TESTING:\n";
    cout << "=====================\n";
    
    // Empty tree search
    cout << "Testing empty tree:\n";
    BinarySearchTree<int> emptyBst;
    try {
        emptyBst.search(10);
    } catch (const exception& e) {
        cout << "Expected error: " << e.what() << endl;
    }
    
    // Single node tree
    cout << "\nSingle node tree:\n";
    BinarySearchTree<int> singleBst;
    singleBst.insert(42);
    SearchResult single = singleBst.search(42);
    cout << "Searching for 42 in single-node tree: ";
    single.print();
    cout << "Height: " << singleBst.getTreeHeight() << endl;
    
    cout << "\n=== END OF DEMONSTRATION ===\n";
    
    return 0;
}

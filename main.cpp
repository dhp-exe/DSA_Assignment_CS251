#include "VectorStore.h" 

// --- Helper Functions for Testing ---

// Helper for AVLTree::inorderTraversal
void printAVLData(const int& data) {
    cout << data << " ";
}

// Helper function to print RBT node info
void printRBTNode(RedBlackTree<int, int>::RBTNode* node) {
    if (node == nullptr) {
        cout << "nullptr";
        return;
    }
    cout << node->key;
}

// --- AVL Tree Test Function ---
void testAVLTree() {
    cout << "=================================" << endl;
    cout << "   STARTING AVLTree TEST SUITE   " << endl;
    cout << "=================================" << endl;

    // Use AVLTree<int, int> for testing
    AVLTree<int, int> tree;

    // --- Test 1: Initial State ---
    cout << "--- Test 1: Initial State (Constructor, empty, getSize, getHeight) ---" << endl;
    cout << "Is tree empty? " << boolalpha << tree.empty() << endl; // Expected: true
    cout << "Tree size: " << tree.getSize() << endl; // Expected: 0
    cout << "Tree height: " << tree.getHeight() << endl; // Expected: 0
    cout << "Tree structure: " << endl;
    tree.printTreeStructure(); // Expected: NULL
    cout << "-------------------------------" << endl << endl;

    // --- Test 2: Insertion (insert, rotateLeft, rotateRight, balance) ---
    // We will insert keys that force all 4 rotation cases
    cout << "--- Test 2: Insertion & Balancing ---" << endl;
    
    // Insert 10 (Root)
    tree.insert(10, 10);
    // Insert 20 (Causes RR setup)
    tree.insert(20, 20);
    // Insert 30 (Triggers RR rotation at 10)
    cout << "Inserting 10, 20, 30 (triggers RR):" << endl;
    tree.insert(30, 30);
    tree.printTreeStructure();
    cout << endl;

    // Insert 5 (Causes LL setup)
    tree.insert(5, 5);
    // Insert 3 (Triggers LL rotation at 10)
    cout << "Inserting 5, 3 (triggers LL):" << endl;
    tree.insert(3, 3);
    tree.printTreeStructure();
    cout << endl;

    // Insert 25 (Causes RL setup at 30)
    cout << "Inserting 25 (triggers RL):" << endl;
    tree.insert(25, 25);
    tree.printTreeStructure();
    cout << endl;

    // Insert 7 (Causes LR setup at 5)
    cout << "Inserting 7 (triggers LR):" << endl;
    tree.insert(7, 7);
    tree.printTreeStructure();
    cout << "-------------------------------" << endl << endl;

    // --- Test 3: State After Insertion (getSize, getHeight, empty) ---
    cout << "--- Test 3: State After Insertion ---" << endl;
    cout << "Is tree empty? " << tree.empty() << endl; // Expected: false
    cout << "Tree size: " << tree.getSize() << endl; // Expected: 7
    cout << "Tree height: " << tree.getHeight() << endl; // Expected: 3
    cout << "-------------------------------" << endl << endl;

    // --- Test 4: Contains ---
    cout << "--- Test 4: Contains ---" << endl;
    cout << "Contains 10 (root)? " << tree.contains(10) << endl; // Expected: true
    cout << "Contains 7 (leaf)? " << tree.contains(7) << endl; // Expected: true
    cout << "Contains 99 (non-existent)? " << tree.contains(99) << endl; // Expected: false
    cout << "-------------------------------" << endl << endl;

    // --- Test 5: Inorder Traversal ---
    cout << "--- Test 5: Inorder Traversal ---" << endl;
    cout << "Inorder: ";
    tree.inorderTraversal(printAVLData); // Expected: 3 5 7 10 20 25 30
    cout << endl;
    cout << "-------------------------------" << endl << endl;

    // --- Test 6: Removal (remove, findMin, balance_Remove) ---
    cout << "--- Test 6: Removal & Rebalancing ---" << endl;
    // Case 1: Remove a leaf (7)
    cout << "Removing 7 (leaf):" << endl;
    tree.remove(7);
    tree.printTreeStructure();
    cout << "Size after: " << tree.getSize() << endl; // Expected: 6
    cout << "Contains 7? " << tree.contains(7) << endl; // Expected: false
    cout << endl;

    // Case 2: Remove a node with one child (5)
    cout << "Removing 5 (node with one child, 3):" << endl;
    tree.remove(5);
    tree.printTreeStructure();
    cout << "Size after: " << tree.getSize() << endl; // Expected: 5
    cout << "Contains 5? " << tree.contains(5) << endl; // Expected: false
    cout << endl;

    // Case 3: Remove a node with two children (20 - root)
    // Per spec: uses smallest in right subtree (25)
    cout << "Removing 20 (root, node with two children):" << endl;
    tree.remove(20);
    tree.printTreeStructure();
    cout << "Size after: " << tree.getSize() << endl; // Expected: 4
    cout << "Contains 20? " << tree.contains(20) << endl; // Expected: false
    cout << "Contains 25 (successor)? " << tree.contains(25) << endl; // Expected: true
    cout << endl;

    // Case 4: Remove non-existent key (99)
    cout << "Removing 99 (non-existent):" << endl;
    tree.remove(99);
    tree.printTreeStructure();
    cout << "Size after: " << tree.getSize() << endl; // Expected: 4
    cout << "-------------------------------" << endl << endl;

    // --- Test 7: Clear (Destructor test) ---
    cout << "--- Test 7: Clear ---" << endl;
    tree.clear();
    cout << "Is tree empty? " << tree.empty() << endl; // Expected: true
    cout << "Tree size: " << tree.getSize() << endl; // Expected: 0
    cout << "Tree height: " << tree.getHeight() << endl; // Expected: 0
    cout << "Tree structure: " << endl;
    tree.printTreeStructure(); // Expected: NULL
    cout << "-------------------------------" << endl << endl;

    cout << "========= AVLTree TEST COMPLETE =========\n\n" << endl;
}


// --- Red-Black Tree Test Function ---
void testRedBlackTree() {
    cout << "=====================================" << endl;
    cout << "   STARTING RedBlackTree TEST SUITE   " << endl;
    cout << "=====================================" << endl;

    // Use RedBlackTree<int, int> for testing
    RedBlackTree<int, int> rbt;

    // --- Test 1: Initial State (Constructor, empty, size) ---
    cout << "--- Test 1: Initial State ---" << endl;
    cout << "Is tree empty? " << boolalpha << rbt.empty() << endl; // Expected: true
    cout << "Tree size: " << rbt.size() << endl; // Expected: 0
    cout << "Tree structure: " << endl;
    rbt.printTreeStructure(); // Expected: NULL
    cout << "-------------------------------" << endl << endl;

    // --- Test 2: Insertion (insert, fixInsert, RBTNode methods, rotations) ---
    // Insert a sequence that forces recoloring and rotations
    cout << "--- Test 2: Insertion & Balancing ---" << endl;
    int keys[] = {10, 20, 30, 15, 25, 5, 1, 40, 50};
    cout << "Inserting: 10, 20, 30, 15, 25, 5, 1, 40, 50" << endl;
    for (int key : keys) {
        rbt.insert(key, key);
    }
    rbt.printTreeStructure();
    cout << endl;

    // --- Test 3: State After Insertion (size, empty) ---
    cout << "--- Test 3: State After Insertion ---" << endl;
    cout << "Is tree empty? " << rbt.empty() << endl; // Expected: false
    cout << "Tree size: " << rbt.size() << endl; // Expected: 9
    cout << "-------------------------------" << endl << endl;

    // --- Test 4: Find & Contains ---
    cout << "--- Test 4: Find & Contains ---" << endl;
    cout << "Find 15 (exists): "; printRBTNode(rbt.find(15)); cout << endl; // Expected: 15
    cout << "Find 99 (non-existent): "; printRBTNode(rbt.find(99)); cout << endl; // Expected: nullptr
    cout << "Contains 40 (exists)? " << rbt.contains(40) << endl; // Expected: true
    cout << "Contains 99 (non-existent)? " << rbt.contains(99) << endl; // Expected: false
    cout << "-------------------------------" << endl << endl;

    // --- Test 5: Bounds (lowerBound, upperBound, lowerBoundNode, upperBoundNode) ---
    cout << "--- Test 5: Lower/Upper Bound ---" << endl;
    bool found = false;
    // Lower Bound (>= key)
    cout << "Lower bound of 25 (>= 25): "; printRBTNode(rbt.lowerBound(25, found)); cout << " (found: " << found << ")" << endl; // Exp: 25
    cout << "Lower bound of 22 (>= 22): "; printRBTNode(rbt.lowerBound(22, found)); cout << " (found: " << found << ")" << endl; // Exp: 25
    cout << "Lower bound of 99 (>= 99): "; printRBTNode(rbt.lowerBound(99, found)); cout << " (found: " << found << ")" << endl; // Exp: nullptr
    // Upper Bound (> key)
    cout << "Upper bound of 25 (> 25): "; printRBTNode(rbt.upperBound(25, found)); cout << " (found: " << found << ")" << endl; // Exp: 30
    cout << "Upper bound of 22 (> 22): "; printRBTNode(rbt.upperBound(22, found)); cout << " (found: " << found << ")" << endl; // Exp: 25
    cout << "Upper bound of 50 (> 50): "; printRBTNode(rbt.upperBound(50, found)); cout << " (found: " << found << ")" << endl; // Exp: nullptr
    cout << "-------------------------------" << endl << endl;

    // --- Test 6: Removal (remove, fixRemove, findMax, transplant) ---
    // Per spec: uses largest in left subtree (predecessor)
    cout << "--- Test 6: Removal & Rebalancing ---" << endl;
    // Case 1: Remove a leaf (1)
    cout << "Removing 1 (leaf):" << endl;
    rbt.remove(1);
    cout << "Size after: " << rbt.size() << endl; // Expected: 8
    cout << "Contains 1? " << rbt.contains(1) << endl; // Expected: false
    cout << endl;

    // Case 2: Remove a node with one child (5)
    cout << "Removing 5 (node with one child):" << endl;
    rbt.remove(5);
    cout << "Size after: " << rbt.size() << endl; // Expected: 7
    cout << "Contains 5? " << rbt.contains(5) << endl; // Expected: false
    cout << endl;

    // Case 3: Remove a node with two children (10)
    // Predecessor is 5 (which we removed), so it should be empty
    // Let's remove 20 instead. Predecessor is 15.
    cout << "Removing 20 (node with two children):" << endl;
    rbt.remove(20);
    rbt.printTreeStructure();
    cout << "Size after: " << rbt.size() << endl; // Expected: 6
    cout << "Contains 20? " << rbt.contains(20) << endl; // Expected: false
    cout << endl;

    // Case 4: Remove root (15)
    cout << "Removing 15 (root):" << endl;
    rbt.remove(15);
    rbt.printTreeStructure();
    cout << "Size after: " << rbt.size() << endl; // Expected: 5
    cout << "Contains 15? " << rbt.contains(15) << endl; // Expected: false
    cout << endl;

    // Case 5: Remove non-existent key (99)
    cout << "Removing 99 (non-existent):" << endl;
    rbt.remove(99);
    cout << "Size after: " << rbt.size() << endl; // Expected: 5
    cout << "-------------------------------" << endl << endl;

    // --- Test 7: Clear (Destructor test) ---
    cout << "--- Test 7: Clear ---" << endl;
    rbt.clear();
    cout << "Is tree empty? " << rbt.empty() << endl; // Expected: true
    cout << "Tree size: " << rbt.size() << endl; // Expected: 0
    cout << "Tree structure: " << endl;
    rbt.printTreeStructure(); // Expected: NULL
    cout << "-------------------------------" << endl << endl;

    cout << "========= RedBlackTree TEST COMPLETE =========\n\n" << endl;
}

// --- Main Function ---
int main() {
    
    testAVLTree();
    
    testRedBlackTree();

    return 0;
}
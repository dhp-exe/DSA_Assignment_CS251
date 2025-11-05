#include "VectorStore.h" 

// Helper function for inorderTraversal, now prints an int
void printData(const int& data) {
    cout << data << " ";
}

int main() {
    // We will use AVLTree<int, int> for this test.
    AVLTree<int, int> tree;

    // --- Test 1: Initial State ---
    cout << "--- Test 1: Initial State ---" << endl;
    cout << "Is tree empty? " << boolalpha << tree.empty() << endl; // Expected: true
    cout << "Tree size: " << tree.getSize() << endl; // Expected: 0
    cout << "Tree height: " << tree.getHeight() << endl; // Expected: 0
    cout << "Tree structure: " << endl;
    tree.printTreeStructure(); // Expected: NULL
    cout << "-------------------------------" << endl << endl;

    // --- Test 2: Insertion ---
    // We will insert keys that force all 4 rotation cases
    // based on your getHeight() balancing logic.
    cout << "--- Test 2: Insertion ---" << endl;
    
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

    // --- Test 3: State After Insertion ---
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
    tree.inorderTraversal(printData); // Expected: 3 5 7 10 20 25 30
    cout << endl;
    cout << "-------------------------------" << endl << endl;

    // --- Test 6: Removal ---
    cout << "--- Test 6: Removal ---" << endl;
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
    // Your findMin logic will find 25 as successor
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

    // --- Test 7: Clear ---
    cout << "--- Test 7: Clear ---" << endl;
    tree.clear();
    cout << "Is tree empty? " << tree.empty() << endl; // Expected: true
    cout << "Tree size: " << tree.getSize() << endl; // Expected: 0
    cout << "Tree height: " << tree.getHeight() << endl; // Expected: 0
    cout << "Tree structure: " << endl;
    tree.printTreeStructure(); // Expected: NULL
    cout << "-------------------------------" << endl << endl;

    cout << "All AVLTree tests complete." << endl;

    return 0;
}
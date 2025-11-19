#include "VectorStore.h" 
#include <map>      // For mock embedding
#include <iomanip>  // For setprecision

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



// =========================================================
//           TEST HELPER FUNCTIONS
// =========================================================

// Global Mock Database
map<string, vector<float>> mockDB;

// Mock Embedding Function
// Looks up the string in mockDB. If not found, returns a default vector.
vector<float>* mockEmbeddingFunc(const string& text) {
    if (mockDB.find(text) != mockDB.end()) {
        return new vector<float>(mockDB[text]);
    }
    // Default for unknown text (should not happen in this strict test)
    return new vector<float>({0.0, 0.0, 0.0});
}

// Mock V2 for testing setEmbeddingFunction
vector<float>* mockEmbeddingFuncV2(const string& text) {
    return new vector<float>({100.0, 100.0, 100.0});
}

// Helper to print vectors
void printVec(const vector<float>* vec) {
    if (!vec) { cout << "nullptr" << endl; return; }
    cout << "{ ";
    for (size_t i = 0; i < vec->size(); ++i) {
        cout << (*vec)[i] << (i == vec->size() - 1 ? " " : ", ");
    }
    cout << "}";
}

// Helper to print arrays
void printArray(int* arr, int size) {
    if (!arr) { cout << "[]" << endl; return; }
    cout << "[ ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << (i == size - 1 ? " " : ", ");
    }
    cout << "]" << endl;
}

// Helper for forEach testing
void printRecordInfo(vector<float>& vec, int id, string& text) {
    cout << "   [ID: " << id << "] \"" << text << "\" Vec: ";
    cout << "{ " << vec[0] << ", " << vec[1] << ", ... }" << endl;
}

// =========================================================
//           VECTORSTORE COMPLETE TEST SUITE (FIXED)
// =========================================================

void testVectorStore() {
    cout << fixed << setprecision(4);
    cout << "=========================================" << endl;
    cout << "    COMPREHENSIVE VECTORSTORE TEST       " << endl;
    cout << "=========================================" << endl;

    // --- 1. SETUP & INITIALIZATION ---
    cout << "\n--- [1] Setup & Constructor ---" << endl;
    
    // Configuration
    int dimension = 3;
    vector<float> refVec = {0.0, 0.0, 0.0};
    
    // Populate Mock DB with predictable data
    mockDB.clear();
    // Vector A: Close diagonal
    mockDB["A"] = {1.0, 1.0, 1.0};  
    // Dist from (0,0,0): sqrt(3) ~ 1.732
    
    // Vector B: Farther diagonal
    mockDB["B"] = {2.0, 2.0, 2.0};  
    // Dist from (0,0,0): sqrt(12) ~ 3.464
    
    // Vector C: Far out diagonal
    mockDB["C"] = {5.0, 5.0, 5.0};  
    // Dist from (0,0,0): sqrt(75) ~ 8.660
    
    // Vector D: Axis aligned (Orthogonal to A/B/C in direction)
    mockDB["D"] = {4.0, 0.0, 0.0};  
    // Dist from (0,0,0): 4.000
    
    // Vectors for Preprocessing test
    mockDB["Short"] = {1.0, 1.0};             // Needs padding
    mockDB["Long"]  = {9.0, 9.0, 9.0, 9.0};   // Needs truncation

    VectorStore vs(dimension, mockEmbeddingFunc, refVec);
    
    cout << "Created Store. Size: " << vs.size() << ", Empty: " << boolalpha << vs.empty() << endl;
    cout << "Reference Vector: "; printVec(vs.getReferenceVector()); cout << endl;

    // --- 2. PREPROCESSING ---
    cout << "\n--- [2] Preprocessing (Padding/Truncation) ---" << endl;
    
    vector<float>* p1 = vs.preprocessing("Short");
    cout << "'Short' (1,1) -> Pad to 3D: "; printVec(p1); cout << endl;
    delete p1;

    vector<float>* p2 = vs.preprocessing("Long");
    cout << "'Long' (9,9,9,9) -> Trunc to 3D: "; printVec(p2); cout << endl;
    delete p2;

    // --- 3. INSERTION & STATE UPDATE ---
    cout << "\n--- [3] Insertion & Internal State ---" << endl;
    
    vs.addText("A"); // ID 0, Dist 1.732
    vs.addText("B"); // ID 1, Dist 3.464
    vs.addText("C"); // ID 2, Dist 8.660
    vs.addText("D"); // ID 3, Dist 4.000
    
    cout << "Added A, B, C, D." << endl;
    cout << "Current Size: " << vs.size() << endl;
    
    // Expected Average: (1.732 + 3.464 + 8.660 + 4.000) / 4 = 17.856 / 4 = 4.464
    cout << "Average Distance: " << vs.getAverageDistance() << endl;
    
    // Root Vector should be closest to Average (4.464).
    // A(1.73), B(3.46), D(4.00), C(8.66). 
    // Diff: A(2.73), B(1.00), D(0.46), C(4.19). 
    // Closest is D (ID 3).
    cout << "Root Vector ID (Closest to Avg): " << vs.getRootVector()->id << " (Expected: 3)" << endl;

    // --- 4. SORTING & TRAVERSAL (AVL CHECK) ---
    cout << "\n--- [4] Sorting & Traversal (AVL Structure) ---" << endl;
    // Sorted by Distance from (0,0,0):
    // 1. A (1.732) - ID 0
    // 2. B (3.464) - ID 1
    // 3. D (4.000) - ID 3
    // 4. C (8.660) - ID 2
    
    vector<int> sortedIds = vs.getAllIdsSortedByDistance();
    cout << "IDs sorted by Distance: "; 
    printArray(sortedIds.data(), sortedIds.size()); 
    // Expected: [0, 1, 3, 2]

    cout << "Getters by Index (Index 0 = Closest):" << endl;
    cout << "Idx 0 Text: " << vs.getRawText(0) << " (Exp: A)" << endl;
    cout << "Idx 2 Text: " << vs.getRawText(2) << " (Exp: D)" << endl;

    cout << "forEach Iteration:" << endl;
    vs.forEach(printRecordInfo);

    // --- 5. SEARCH: NEAREST NEIGHBOR ---
    cout << "\n--- [5] FindNearest (Metric Tests) ---" << endl;
    
    vector<float> query = {1.1, 1.1, 1.1}; 
    cout << "Query Vector: {1.1, 1.1, 1.1}" << endl;
    
    // Euclidean: Closest is A (1.1 vs 1.0)
    int idEuc = vs.findNearest(query, "euclidean");
    cout << "Nearest (Euclidean): ID " << idEuc << " (Exp: 0)" << endl;

    // Cosine: 
    // A, B, C are all parallel to query (Sim = 1.0). 
    // D is orthogonal-ish (Sim < 1.0).
    int idCos = vs.findNearest(query, "cosine");
    cout << "Nearest (Cosine): ID " << idCos << " (Exp: 0, 1, or 2)" << endl;

    // Manhattan: Closest is A
    int idMan = vs.findNearest(query, "manhattan");
    cout << "Nearest (Manhattan): ID " << idMan << " (Exp: 0)" << endl;

    // --- 6. SEARCH: TOP K ---
    cout << "\n--- [6] Top K Nearest ---" << endl;
    // Query at Origin
    vector<float> origin = {0, 0, 0};
    
    // Top 3 Euclidean from Origin: Should be A(1.7), B(3.4), D(4.0) -> IDs [0, 1, 3]
    int* topK = vs.topKNearest(origin, 3, "euclidean");
    cout << "Top 3 Euclidean from {0,0,0}: ";
    printArray(topK, 3);
    delete[] topK;

    // Top 2 Cosine from {1.1,1.1,1.1}:
    int* topKCos = vs.topKNearest(query, 2, "cosine");
    cout << "Top 2 Cosine from {1.1,1.1,1.1}: ";
    printArray(topKCos, 2);
    delete[] topKCos;

    // --- 7. RANGE & BOUNDING BOX ---
    cout << "\n--- [7] Range & Box Queries ---" << endl;
    
    // Range From Root (Filter by Distance from {0,0,0})
    int* rangeRoot = vs.rangeQueryFromRoot(3.0, 5.0);
    cout << "RangeFromRoot [3.0, 5.0]: "; 
    printArray(rangeRoot, 2); // Expected ~ [1, 3]
    delete[] rangeRoot;

    // Bounding Box
    vector<float> minB = {0,0,0}, maxB = {3,3,3};
    int* box = vs.boundingBoxQuery(minB, maxB);
    cout << "BoundingBox {0,0,0}->{3,3,3}: ";
    printArray(box, 2); // Expected [0, 1]
    delete[] box;

    // --- 8. ADVANCED UTILS ---
    cout << "\n--- [8] Advanced Utilities ---" << endl;
    
    cout << "Max Distance: " << vs.getMaxDistance() << " (Exp: ~8.66)" << endl;
    cout << "Min Distance: " << vs.getMinDistance() << " (Exp: ~1.73)" << endl;

    // Centroid of all vectors
    vector<VectorRecord*> allRecs = vs.getAllVectorsSortedByDistance();
    VectorRecord centroid = vs.computeCentroid(allRecs);
    cout << "Centroid: "; printVec(centroid.vector);
    delete centroid.vector; // Cleanup manual vector

    // Estimate D
    double EstD = vs.estimateD_Linear(query, 2, vs.getAverageDistance(), *vs.getReferenceVector());
    cout << "EstimateD (k=2): " << EstD << endl;

    // (REMOVED private method call to findVectorNearestToDistance)

    // --- 9. REMOVAL ---
    cout << "\n--- [9] Removal ---" << endl;
    
    // Current Order: A(0), B(1), D(3), C(2)
    // Remove index 1 -> Removes "B".
    cout << "Removing index 1 (Vector B)..." << endl;
    vs.removeAt(1);
    
    cout << "New Size: " << vs.size() << endl;
    vector<int> newIds = vs.getAllIdsSortedByDistance();
    cout << "Remaining IDs: "; printArray(newIds.data(), newIds.size());
    // Expected: [0, 3, 2] (A, D, C)

    // --- 10. MODIFYING REFERENCE VECTOR ---
    cout << "\n--- [10] Set Reference Vector ---" << endl;
    
    // Change Ref to {4.0, 0.0, 0.0} (Location of Vector D)
    vector<float> newRef = {4.0, 0.0, 0.0};
    vs.setReferenceVector(newRef);
    cout << "Reference changed to {4,0,0}." << endl;
    cout << "New Average Distance: " << vs.getAverageDistance() << endl;
    
    // New Sorted Order should be: D (closest), A, C
    vector<int> reSortedIds = vs.getAllIdsSortedByDistance();
    cout << "IDs sorted by New Ref: "; printArray(reSortedIds.data(), reSortedIds.size());
    // Expected IDs: [3, 0, 2]
    
    cout << "Check Index 0 Text: " << vs.getRawText(0) << " (Exp: D)" << endl;

    // --- 11. SET EMBEDDING FUNCTION ---
    cout << "\n--- [11] Set Embedding Function ---" << endl;
    vs.setEmbeddingFunction(mockEmbeddingFuncV2);
    vs.addText("Huge"); // Returns {100, 100, 100}
    cout << "Added 'Huge'. Last vector val: " << vs.getVector(vs.size()-1)->vector->at(0) << endl;

    // --- 12. CLEAR & CLEANUP ---
    cout << "\n--- [12] Clear ---" << endl;
    vs.clear();
    cout << "Cleared. Size: " << vs.size() << endl;

    cout << "\n=========================================" << endl;
    cout << "          TEST SUITE COMPLETE            " << endl;
    cout << "=========================================" << endl;
}


// --- Main Function ---
int main() {
    
    //testAVLTree();
    //testRedBlackTree();

    testVectorStore();

    return 0;
}
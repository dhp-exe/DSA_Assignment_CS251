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
// =========================================================
//           VECTORSTORE TEST SUITE
// =========================================================
// =========================================================

// --- Helper: Mock Embedding Function ---
// Creates predictable vectors based on text input
map<string, vector<float>> mockDB;
vector<float>* mockEmbeddingFunc(const string& text) {
    if (mockDB.find(text) != mockDB.end()) {
        return new vector<float>(mockDB[text]);
    }
    // Default for unknown text
    return new vector<float>({0.1, 0.2, 0.3, 0.4, 0.5});
}

// --- Helper: Mock Embedding Function V2 (for setEmbeddingFunction) ---
vector<float>* mockEmbeddingFuncV2(const string& text) {
    if (text == "new") {
        return new vector<float>({99.0, 98.0, 97.0});
    }
    return new vector<float>({-1.0, -1.0, -1.0});
}

// --- Helper: Print a vector<float> ---
void printVec(const vector<float>* vec) {
    if (vec == nullptr) {
        cout << "nullptr" << endl;
        return;
    }
    cout << "{ ";
    for (size_t i = 0; i < vec->size(); ++i) {
        cout << (*vec)[i] << (i == vec->size() - 1 ? " " : ", ");
    }
    cout << "}" << endl;
}

// --- Helper: Print array (for topK) ---
void printArray(int* arr, int size) {
    if (arr == nullptr) {
        cout << "nullptr" << endl;
        return;
    }
    cout << "[ ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << (i == size - 1 ? " " : ", ");
    }
    cout << "]" << endl;
}

// --- Helper: forEach test ---
void forEachPrinter(vector<float>& vec, int id, string& rawText) {
    cout << "  -> ID: " << id << ", Text: \"" << rawText << "\", Vec[0]: " << vec[0] << endl;
}

// --- Main VectorStore Test Function ---
void testVectorStore() {
    cout << fixed << setprecision(4);
    cout << "=====================================" << endl;
    cout << "   STARTING VectorStore TEST SUITE   " << endl;
    cout << "=====================================" << endl;

    // --- Setup ---
    int dimension = 3;
    vector<float> refVec = {0.0, 0.0, 0.0};
    
    // Populate mock DB
    mockDB["apple"] = {1.0, 2.0, 3.0};     // Dist: sqrt(1+4+9) = sqrt(14) ~ 3.7416
    mockDB["banana"] = {4.0, 4.0, 4.0};    // Dist: sqrt(16+16+16) = sqrt(48) ~ 6.9282
    mockDB["carrot"] = {1.0, 1.0, 1.0};    // Dist: sqrt(1+1+1) = sqrt(3) ~ 1.7320
    mockDB["short"] = {1.0, 2.0};          // For preprocessing test (padding)
    mockDB["long"] = {5.0, 6.0, 7.0, 8.0}; // For preprocessing test (truncating)

    // --- Test 1: Constructor & Initial State ---
    cout << "--- Test 1: Constructor & Initial State ---" << endl;
    VectorStore vs(dimension, mockEmbeddingFunc, refVec);
    cout << "vs.size(): " << vs.size() << endl; // Expected: 0
    cout << "vs.empty(): " << boolalpha << vs.empty() << endl; // Expected: true
    cout << "vs.getAverageDistance(): " << vs.getAverageDistance() << endl; // Expected: 0.0
    cout << "vs.getRootVector(): " << (vs.getRootVector() == nullptr ? "nullptr" : "NOT NULL") << endl; // Expected: nullptr
    cout << "vs.getReferenceVector(): "; printVec(vs.getReferenceVector()); // Expected: {0, 0, 0}
    cout << "-------------------------------" << endl << endl;

    // --- Test 2: preprocessing ---
    cout << "--- Test 2: preprocessing ---" << endl;
    vector<float>* shortVec = vs.preprocessing("short"); // Should pad
    cout << "Preprocessing 'short' (dim=2): "; printVec(shortVec); // Expected: {1, 2, 0}
    delete shortVec;
    
    vector<float>* longVec = vs.preprocessing("long"); // Should truncate
    cout << "Preprocessing 'long' (dim=4): "; printVec(longVec); // Expected: {5, 6, 7}
    delete longVec;
    
    vector<float>* goodVec = vs.preprocessing("apple"); // Should be exact
    cout << "Preprocessing 'apple' (dim=3): "; printVec(goodVec); // Expected: {1, 2, 3}
    delete goodVec;
    cout << "-------------------------------" << endl << endl;

    // --- Test 3: addText & State Update ---
    cout << "--- Test 3: addText & State Update ---" << endl;
    vs.addText("apple"); // ID 0, Dist 3.7416
    vs.addText("banana"); // ID 1, Dist 6.9282
    vs.addText("carrot"); // ID 2, Dist 1.7320
    cout << "Added 3 vectors ('apple', 'banana', 'carrot')" << endl;
    cout << "vs.size(): " << vs.size() << endl; // Expected: 3
    cout << "vs.empty(): " << vs.empty() << endl; // Expected: false
    
    // Check AvgDist: (3.7416 + 6.9282 + 1.7320) / 3 = 12.4018 / 3 = 4.1339
    cout << "vs.getAverageDistance(): " << vs.getAverageDistance() << endl; // Expected: 4.1339

    // Check RootVector (closest to 4.1339)
    // Diff 'apple' (3.7416): |3.7416 - 4.1339| = 0.3923
    // Diff 'banana' (6.9282): |6.9282 - 4.1339| = 2.7943
    // Diff 'carrot' (1.7320): |1.7320 - 4.1339| = 2.4019
    // Root should be 'apple' (ID 0)
    cout << "vs.getRootVector()->id: " << vs.getRootVector()->id << endl; // Expected: 0
    cout << "-------------------------------" << endl << endl;

    // --- Test 4: In-order Getters (Sorted by Distance) ---
    // Order by dist: 'carrot' (1.7320), 'apple' (3.7416), 'banana' (6.9282)
    // Index:           0                 1                 2
    // ID:              2                 0                 1
    cout << "--- Test 4: In-order Getters (getRawText, getId, getVector) ---" << endl;
    cout << "vs.getId(0): " << vs.getId(0) << endl; // Expected: 2
    cout << "vs.getRawText(0): " << vs.getRawText(0) << endl; // Expected: carrot
    
    cout << "vs.getId(1): " << vs.getId(1) << endl; // Expected: 0
    cout << "vs.getRawText(1): " << vs.getRawText(1) << endl; // Expected: apple

    cout << "vs.getId(2): " << vs.getId(2) << endl; // Expected: 1
    cout << "vs.getVector(2)->vector[0]: " << vs.getVector(2)->vector->at(0) << endl; // Expected: 4.0
    
    try {
        vs.getVector(99);
    } catch (const out_of_range& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }
    cout << "-------------------------------" << endl << endl;

    // --- Test 5: removeAt ---
    // Removing index 1 ('apple', ID 0, the root vector)
    cout << "--- Test 5: removeAt ---" << endl;
    cout << "Removing at index 1 ('apple')..." << endl;
    vs.removeAt(1);
    cout << "vs.size(): " << vs.size() << endl; // Expected: 2
    
    // Check new AvgDist: (6.9282 + 1.7320) / 2 = 8.6602 / 2 = 4.3301
    cout << "vs.getAverageDistance(): " << vs.getAverageDistance() << endl; // Expected: 4.3301

    // Check new RootVector (closest to 4.3301)
    // Diff 'banana' (6.9282): |6.9282 - 4.3301| = 2.5981
    // Diff 'carrot' (1.7320): |1.7320 - 4.3301| = 2.5981
    // (Tie, implementation dependent, will pick one)
    cout << "vs.getRootVector()->id: " << vs.getRootVector()->id << endl; // Expected: 1 or 2
    
    // Check new order
    // Order: 'carrot' (1.7320), 'banana' (6.9282)
    // Index: 0                 1
    cout << "vs.getId(0): " << vs.getId(0) << endl; // Expected: 2
    cout << "vs.getId(1): " << vs.getId(1) << endl; // Expected: 1
    cout << "-------------------------------" << endl << endl;

    // --- Test 6: Traversal/Iteration (forEach, getAll...) ---
    cout << "--- Test 6: Traversal/Iteration ---" << endl;
    cout << "Testing forEach:" << endl;
    vs.forEach(forEachPrinter); // Expected: ID 2, ID 1
    
    cout << "Testing getAllIdsSortedByDistance:" << endl;
    vector<int> ids = vs.getAllIdsSortedByDistance();
    printArray(ids.data(), ids.size()); // Expected: [2, 1]
    
    cout << "Testing getAllVectorsSortedByDistance:" << endl;
    vector<VectorRecord*> recs = vs.getAllVectorsSortedByDistance();
    cout << "Found " << recs.size() << " records. First record ID: " << recs[0]->id << endl; // Expected: 2, 2
    cout << "-------------------------------" << endl << endl;

    // --- Test 7: Distance Metrics (non-const) ---
    cout << "--- Test 7: Distance Metrics ---" << endl;
    vector<float> v1 = {1, 2, 3};
    vector<float> v2 = {4, 5, 6};
    cout << "v1={1,2,3}, v2={4,5,6}" << endl;
    cout << "l2Distance: " << vs.l2Distance(v1, v2) << endl; // Expected: 5.1961
    cout << "l1Distance: " << vs.l1Distance(v1, v2) << endl; // Expected: 9.0
    cout << "cosineSimilarity: " << vs.cosineSimilarity(v1, v2) << endl; // Expected: 0.9746
    cout << "-------------------------------" << endl << endl;

    // --- Test 8: setReferenceVector & setEmbeddingFunction ---
    cout << "--- Test 8: setReferenceVector & setEmbeddingFunction ---" << endl;
    vector<float> newRef = {1, 1, 1};
    vs.setReferenceVector(newRef);
    cout << "Reference vector set to {1, 1, 1}" << endl;
    cout << "vs.getReferenceVector(): "; printVec(vs.getReferenceVector());
    // Distances recomputed from {1,1,1}
    // 'banana' (vec {4,4,4}): dist = sqrt(3^2+3^2+3^2) = sqrt(27) ~ 5.1961
    // 'carrot' (vec {1,1,1}): dist = 0.0
    // New AvgDist: (5.1961 + 0.0) / 2 = 2.5980
    // New Root: 'carrot' (ID 2), diff |0.0 - 2.5980| = 2.5980
    //           'banana' (ID 1), diff |5.1961 - 2.5980| = 2.5980
    // (Tie, will pick one)
    cout << "vs.getAverageDistance(): " << vs.getAverageDistance() << endl; // Expected: 2.5980
    cout << "vs.getRootVector()->id: " << vs.getRootVector()->id << endl; // Expected: 1 or 2
    
    // Test new order
    // Order: 'carrot' (0.0), 'banana' (5.1961)
    cout << "vs.getId(0): " << vs.getId(0) << endl; // Expected: 2
    cout << "vs.getId(1): " << vs.getId(1) << endl; // Expected: 1

    vs.setEmbeddingFunction(mockEmbeddingFuncV2);
    vs.addText("new"); // ID 3, Vec {99, 98, 97}
    cout << "Set new embedding func, added 'new' (ID 3)" << endl;
    cout << "vs.size(): " << vs.size() << endl; // Expected: 3
    cout << "vs.getVector(2)->vector[0]: " << vs.getVector(2)->vector->at(0) << endl; // Expected: 99.0
    cout << "-------------------------------" << endl << endl;

    // --- Test 9: Const Methods (Overloads) ---
    cout << "--- Test 9: Const-Overloaded Methods ---" << endl;
    const VectorStore& constVS = vs;
    cout << "constVS.empty(): " << constVS.empty() << endl; // Expected: false
    cout << "constVS.l2Distance: " << constVS.l2Distance(v1, v2) << endl; // Expected: 5.1961
    cout << "constVS.l1Distance: " << constVS.l1Distance(v1, v2) << endl; // Expected: 9.0
    cout << "constVS.cosineSimilarity: " << constVS.cosineSimilarity(v1, v2) << endl; // Expected: 0.9746
    cout << "-------------------------------" << endl << endl;

    // --- Test 10: Search (findNearest, estimateD) ---
    // Data: 'carrot' (ID 2, {1,1,1}), 'banana' (ID 1, {4,4,4}), 'new' (ID 3, {99,98,97})
    cout << "--- Test 10: Search (findNearest, estimateD) ---" << endl;
    vector<float> query = {2.0, 2.0, 2.0};
    cout << "Query vector: {2, 2, 2}" << endl;
    
    // findNearest (euclidean)
    // dist(q, carrot): sqrt(1^2+1^2+1^2) = sqrt(3) ~ 1.732
    // dist(q, banana): sqrt(2^2+2^2+2^2) = sqrt(12) ~ 3.464
    // dist(q, new): ... very large
    cout << "findNearest (euclidean): ID " << vs.findNearest(query, "euclidean") << endl; // Expected: 2
    
    // findNearest (manhattan)
    // dist(q, carrot): |1|+|1|+|1| = 3.0
    // dist(q, banana): |2|+|2|+|2| = 6.0
    cout << "findNearest (manhattan): ID " << vs.findNearest(query, "manhattan") << endl; // Expected: 2

    // findNearest (cosine)
    // cos(q, carrot): 1.0 (parallel)
    // cos(q, banana): 1.0 (parallel)
    // cos(q, new): ...
    cout << "findNearest (cosine): ID " << vs.findNearest(query, "cosine") << endl; // Expected: 1, 2, or 3
    
    try {
        vs.findNearest(query, "invalid");
    } catch (const invalid_metric& e) {
        cout << "Caught expected exception: " << e.what() << endl;
    }

    double D = vs.estimateD_Linear(query, 2, vs.getAverageDistance(), *vs.getReferenceVector());
    cout << "estimateD_Linear(k=2): " << D << endl; // Expected: > 0.0
    cout << "-------------------------------" << endl << endl;

    // --- Test 11: topKNearest ---
    cout << "--- Test 11: topKNearest ---" << endl;
    cout << "topKNearest(k=2, euclidean): " << endl;
    int* topK = vs.topKNearest(query, 2, "euclidean");
    // Should print m value
    // Distances: carrot (1.732), banana (3.464), new (large)
    // Top 2: [2, 1]
    printArray(topK, 2); // Expected: [2, 1]
    delete[] topK;
    
    try {
        vs.topKNearest(query, 99, "euclidean");
    } catch (const invalid_k_value& e) {
        cout << "Caught expected exception for k > size" << endl;
    }
    cout << "-------------------------------" << endl << endl;

    // --- Test 12: Range & Bounding Box Queries ---
    cout << "--- Test 12: Range & Bounding Box Queries ---" << endl;
    // constVS.rangeQuery
    cout << "rangeQuery(radius=3.0, euclidean): ";
    int* range = constVS.rangeQuery(query, 3.0, "euclidean");
    printArray(range, 1); // Expected: [2]
    delete[] range;

    // constVS.rangeQueryFromRoot
    // Root is ID 1 or 2. Let's assume 2 ({1,1,1})
    // Data: 'carrot' (ID 2, {1,1,1}), 'banana' (ID 1, {4,4,4}), 'new' (ID 3, {99,98,97})
    // dist(root, carrot) = 0.0
    // dist(root, banana) = sqrt(3^2+3^2+3^2) = 5.196
    // dist(root, new) = ... large
    cout << "rangeQueryFromRoot(min=1.0, max=6.0): ";
    int* rangeRoot = constVS.rangeQueryFromRoot(1.0, 6.0);
    printArray(rangeRoot, 1); // Expected: [1]
    delete[] rangeRoot;

    // constVS.boundingBoxQuery
    vector<float> minB = {0, 0, 0};
    vector<float> maxB = {5, 5, 5};
    cout << "boundingBoxQuery(min={0,0,0}, max={5,5,5}): ";
    int* box = constVS.boundingBoxQuery(minB, maxB);
    printArray(box, 2); // Expected: [2, 1]
    delete[] box;
    cout << "-------------------------------" << endl << endl;

    // --- Test 13: Advanced Utils ---
    cout << "--- Test 13: Advanced Utils ---" << endl;
    cout << "getMaxDistance (from root): " << constVS.getMaxDistance() << endl; // Expected: > 0
    cout << "getMinDistance (from ref): " << constVS.getMinDistance() << endl; // Expected: 0.0 (carrot)
    
    // computeCentroid
    // Data: 'carrot' (ID 2, {1,1,1}), 'banana' (ID 1, {4,4,4}), 'new' (ID 3, {99,98,97})
    // Sum = {104, 103, 102}
    // Centroid = {34.66, 34.33, 34.00}
    vector<VectorRecord*> allRecs = constVS.getAllVectorsSortedByDistance();
    VectorRecord centroid = constVS.computeCentroid(allRecs);
    cout << "computeCentroid (vec[0]): " << centroid.vector->at(0) << endl; // Expected: 34.6667
    delete centroid.vector; // Must delete vector from computeCentroid

    cout << "-------------------------------" << endl << endl;

    // --- Test 14: Clear ---
    cout << "--- Test 14: Clear ---" << endl;
    vs.clear();
    cout << "vs.size() after clear: " << vs.size() << endl; // Expected: 0
    cout << "vs.empty() after clear: " << vs.empty() << endl; // Expected: true
    cout << "vs.getRootVector() after clear: " << (vs.getRootVector() == nullptr ? "nullptr" : "NOT NULL") << endl; // Expected: nullptr
    cout << "vs.getReferenceVector() (should persist): "; printVec(vs.getReferenceVector()); // Expected: {1, 1, 1}
    cout << "-------------------------------" << endl << endl;

    cout << "========= VectorStore TEST COMPLETE =========\n\n" << endl;
}


// --- Main Function ---
int main() {
    
    //testAVLTree();
    //testRedBlackTree();

    testVectorStore();

    return 0;
}
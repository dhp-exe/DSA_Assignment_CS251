#include "VectorStore.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// --- Helper for Embedding ---
// A deterministic embedding function for testing
// Maps "A" -> {1.0}, "B" -> {2.0}, etc.
vector<float>* testEmbedding(const string& text) {
    vector<float>* vec = new vector<float>();
    if (text == "A") vec->push_back(1.0f);      // Dist to 0: 1
    else if (text == "B") vec->push_back(2.0f); // Dist to 0: 2
    else if (text == "C") vec->push_back(5.0f); // Dist to 0: 5
    else if (text == "D") vec->push_back(4.0f); // Dist to 0: 4
    else if (text == "PAD") vec->push_back(2.0f); // Len 2, needs padding
    else if (text == "TRUNC") { vec->push_back(1.0f); vec->push_back(2.0f); vec->push_back(3.0f); }
    else {
         // Default Ascii conversion
        for (char c : text) vec->push_back((float)c);
    }
    return vec;
}

// ====================================================
// TEST 001: AVL Insert & Rotations
// Covers: Insert, LL, RR, LR, RL rotations
// ====================================================
void test_001() {
    cout << "=== Test 001: AVL Insert & Rotations ===" << endl;
    AVLTree<int, int> avl;

    cout << "1. RR Rotation Case (Insert 10, 20, 30)" << endl;
    avl.insert(10, 10); avl.insert(20, 20); avl.insert(30, 30);
    avl.printTreeStructure(); // Exp: 20 at root, 10 left, 30 right

    cout << "2. LL Rotation Case (Insert 5, 4)" << endl;
    // Tree is 20(10,30). Insert 5 -> 10->5. Insert 4 -> triggers LL at 10.
    avl.insert(5, 5); avl.insert(4, 4); 
    avl.printTreeStructure(); 

    cout << "3. LR Rotation Case (Insert 7)" << endl;
    // Insert 7 under 5. 5 is left child of 10 (now 5 is root of that subtree).
    // If structure allows, force LR.
    avl.insert(7, 7);
    avl.printTreeStructure();

    cout << "4. Check Inorder (Should be sorted)" << endl;
    avl.inorderTraversal([](const int& val) { cout << val << " "; });
    cout << endl;
}

// ====================================================
// TEST 002: AVL Delete & Properties
// Covers: Delete (Leaf, 1 Child, 2 Children), Clear, Empty
// ====================================================
void test_002() {
    cout << "\n=== Test 002: AVL Delete & Properties ===" << endl;
    AVLTree<int, int> avl;
    // Build: 50, 30, 70, 20, 40, 60, 80
    avl.insert(50, 50); avl.insert(30, 30); avl.insert(70, 70);
    avl.insert(20, 20); avl.insert(40, 40); avl.insert(60, 60); avl.insert(80, 80);
    
    cout << "Initial Tree:" << endl;
    avl.printTreeStructure();

    cout << "Before: Contains 20? " << avl.contains(20) << endl; // 1
    cout << "1. Remove Leaf (20):" << endl;
    avl.remove(20);
    cout << "Contains 20? " << avl.contains(20) << endl; // 0

    cout << "2. Remove Node with 1 Child (assume we create one, or just remove 30):" << endl;
    avl.remove(30); // 30 has children 40 (since 20 removed). 
    avl.printTreeStructure();

    cout << "3. Remove Node with 2 Children (50 - Root):" << endl;
    avl.remove(50); // Should replace with successor (60)
    avl.printTreeStructure();

    cout<< "4. Remove 40: "<<endl;
    avl.remove(40);
    avl.printTreeStructure();

    cout<<"5. Remove 99: "<<endl;   //node not found
    avl.remove(99);
    avl.printTreeStructure();

    cout << "6. Clear Tree" << endl;
    cout << "Before: Empty? " << avl.empty() << endl; // 0
    avl.clear();
    cout << "After: Empty? " << avl.empty() << endl; // 1
}

// ====================================================
// HELPER CLASS: Expose Protected Methods
// ====================================================
// This class inherits from RedBlackTree to access protected members
class TestableRBT : public RedBlackTree<int, int> {
public:
    // Wrapper for protected lowerBoundNode
    RBTNode* callLowerBoundNode(int key) {
        return this->lowerBoundNode(key);
    }

    // Wrapper for protected upperBoundNode
    RBTNode* callUpperBoundNode(int key) {
        return this->upperBoundNode(key);
    }
};

// ====================================================
// TEST 003: RBT Internal Logic & Bounds
// ====================================================
void test_003() {
    cout << "\n=== Test 003: RBT Internal Logic & Bounds ===" << endl;
    
    // USE THE DERIVED CLASS instead of RedBlackTree
    TestableRBT rbt;
    
    // Insert keys to build the structure
    // Structure roughly: Root=20, Left=10, Right=30...
    int keys[] = {10, 20, 30, 15, 25, 5, 1}; 
    for(int k : keys) rbt.insert(k, k);
    
    rbt.printTreeStructure();

    bool found = false;
    RedBlackTree<int, int>::RBTNode* node;

    cout << "\n--- Comparison: First Node Met (Protected) vs Tightest Bound (Public) ---" << endl;

    // SCENARIO 1: Lower Bound with Key = 12
    // Logic: Start at Root (20). 20 >= 12? Yes. 
    // -> lowerBoundNode returns 20 immediately.
    // -> lowerBound continues left to find 15.
    cout << "\n[Key = 12]" << endl;
    
    // Call wrapper instead of direct protected method
    node = rbt.callLowerBoundNode(12);
    cout << "lowerBoundNode(12) [First >=]   : " << (node ? to_string(node->key) : "NULL") << " (Exp: 20 - Root)" << endl;

    node = rbt.lowerBound(12, found);
    cout << "lowerBound(12)     [Smallest >=] : " << (node ? to_string(node->key) : "NULL") << " (Exp: 15)" << endl;


    // SCENARIO 2: Upper Bound with Key = 22
    // Logic: Start at Root (20). 20 > 22? No. Go Right (30).
    // -> upperBoundNode returns 30 immediately.
    // -> upperBound continues left to find 25.
    cout << "\n[Key = 22]" << endl;

    node = rbt.callUpperBoundNode(22);
    cout << "upperBoundNode(22) [First >]    : " << (node ? to_string(node->key) : "NULL") << " (Exp: 30)" << endl;

    node = rbt.upperBound(22, found);
    cout << "upperBound(22)     [Smallest >]  : " << (node ? to_string(node->key) : "NULL") << " (Exp: 25)" << endl;


    // SCENARIO 3: Exact Match with Key = 15
    // Logic: Root (20) >= 15.
    // -> lowerBoundNode returns 20.
    // -> lowerBound finds 15.
    cout << "\n[Key = 15 (Exact Match)]" << endl;

    node = rbt.callLowerBoundNode(15);
    cout << "lowerBoundNode(15) [First >=]   : " << (node ? to_string(node->key) : "NULL") << " (Exp: 20)" << endl;

    node = rbt.lowerBound(15, found);
    cout << "lowerBound(15)     [Smallest >=] : " << (node ? to_string(node->key) : "NULL") << " (Exp: 15)" << endl;
}

// ====================================================
// TEST 004: RBT Deletion
// Covers: Simple delete, Double Black fix
// ====================================================
void test_004() {
    cout << "\n=== Test 004: RBT Deletion Sequence (1..10) ===" << endl;
    RedBlackTree<int, int> rbt;
    
    // Insert 1..10
    // Resulting Tree typically has 4 as Black Root for this sequence in many RBT implementations
    for(int i=1; i<=10; ++i) rbt.insert(i, i);

    cout << "--- Initial State (1..10) ---" << endl;
    rbt.printTreeStructure();
    cout << "Initial Size: " << rbt.size() << endl;

    // ---------------------------------------------------------
    // 1. Remove 1
    // Context: 1 is the smallest key. In a 1..10 tree, it is usually a LEAF.
    // If 1 is Black, this triggers the "Double Black" fixup cases.
    // ---------------------------------------------------------
    cout << "\n--- Removing 1 (Leaf Node) ---" << endl;
    rbt.remove(1);
    
    cout << "Structure after removing 1:" << endl;
    rbt.printTreeStructure();
    cout << "Contains 1? " << (rbt.contains(1) ? "Yes" : "No") << endl;

    // ---------------------------------------------------------
    // 2. Remove 4
    // Context: In a standard RBT construction of 1..10, 4 is often the ROOT.
    // Even if not root, it likely has 2 children (left side 2,3..., right side 5,6...).
    // Expectation: The algorithm must find the PREDECESSOR (max of left subtree),
    // swap data, and delete the predecessor position.
    // ---------------------------------------------------------
    cout << "\n--- Removing 4 (Internal Node / Likely Root with 2 Children) ---" << endl;
    rbt.remove(4);

    cout << "Structure after removing 4:" << endl;
    rbt.printTreeStructure();
    cout << "Contains 4? " << (rbt.contains(4) ? "Yes" : "No") << endl;

    // ---------------------------------------------------------
    // 3. Remove 5
    // Context: 5 is a mid-range value. After removing 4, the structure changes significantly.
    // This tests removing a node that might have shifted positions due to previous rebalancing.
    // ---------------------------------------------------------
    cout << "\n--- Removing 5 (Mid-range Node) ---" << endl;
    rbt.remove(5);

    cout << "Structure after removing 5:" << endl;
    rbt.printTreeStructure();
    cout << "Contains 5? " << (rbt.contains(5) ? "Yes" : "No") << endl;

    cout << "\nFinal Size: " << rbt.size() << endl;
}

// ====================================================
// TEST 005: VectorStore Management
// Covers: Preprocessing, Add, Average Update, RemoveAt, SetReference
// ====================================================
void test_005() {
    cout << "\n=== Test 005: VectorStore Management ===" << endl;
    vector<float> ref = {0.0, 0.0};
    // Dimension 2
    VectorStore vs(2, testEmbedding, ref); 

    // 1. Preprocessing Test
    // "PAD" -> {1.0}. Dim is 2. Should become {1.0, 0.0}
    vs.addText("PAD"); 
    // "TRUNC" -> {1,2,3}. Dim is 2. Should become {1.0, 2.0}
    vs.addText("TRUNC");

    cout << "Vec 0 (PAD): " << (*vs.getVector(0)->vector)[0] << ", " << (*vs.getVector(0)->vector)[1] << endl;
    cout << "Vec 1 (TRUNC): " << (*vs.getVector(1)->vector)[0] << ", " << (*vs.getVector(1)->vector)[1] << endl;

    vs.clear();

    // 2. Root Update Logic
    // Ref = {0}. 
    // Add A(1). Avg=1. Root=A.
    // Add B(2). Avg=1.5. Root=A(dist 1) or B(dist 2)? |1-1.5|=0.5, |2-1.5|=0.5. Usually keeps old if equal, or updates.
    // Add C(5). Avg=(1+2+5)/3 = 2.66. Root should be B(2) (|2-2.66|=0.66 vs A(1)|1-2.66|=1.66).
    vs.addText("A"); cout << "Added 'A'. Avg Dist: " << vs.getAverageDistance() << endl;
    vs.addText("B"); cout << "Added 'B'. Avg Dist: " << vs.getAverageDistance() << endl;
    vs.addText("C"); cout << "Added 'C'. Avg Dist: " << vs.getAverageDistance() << endl;
    
    cout << "Avg Dist: " << vs.getAverageDistance() << endl;
    cout << "Current Root ID: " << vs.getRootVector()->id << " (Text: " << vs.getRootVector()->rawText << ")" << endl;

    // 3. Set Reference Vector
    cout << "Changing Reference to {10.0, 0.0}..." << endl;
    // A={1,0} dist 9. B={2,0} dist 8. C={5,0} dist 5.
    // New Avg = (9+8+5)/3 = 7.33.
    // Root should be B (dist 8, diff 0.66) 
    vs.setReferenceVector({10.0, 0.0});
    cout << "New Avg: " << vs.getAverageDistance() << endl;
    cout << "New Root ID: " << vs.getRootVector()->id << " (Exp: B's ID)" << endl;
    
    // 4. Remove At
    cout << "Removing Index 0 (Closest to Ref)..." << endl;
    // Current distances: C(5), B(8), A(9). Sorted: C, B, A.
    // Index 0 is C.
    vs.removeAt(0);
    cout << "Size after remove: " << vs.size() << endl; // 2
    cout << "New 0th element text: " << vs.getRawText(0) << endl; // Should be B
}

// ====================================================
// TEST 006: VectorStore Search & Advanced
// Covers: findNearest, topK, Range, BoundingBox
// ====================================================
void printArray(int* arr, int size) {
    if (!arr) {
        cout << "[]" << endl;
        return;
    }
    cout << "[ ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << (i == size - 1 ? " " : ", ");
    }
    cout << "]" << endl;
}

// ====================================================
// TEST 006: Comprehensive VectorStore Test
// ====================================================
void test_006() {
    cout << fixed << setprecision(4);
    cout << "=========================================" << endl;
    cout << "    COMPREHENSIVE VECTORSTORE TEST       " << endl;
    cout << "=========================================" << endl;

    // --- 1. SETUP ---
    // Use Dimension 2. 
    // 'A' -> {1.0} becomes {1.0, 0.0} after padding.
    cout << "\n--- [1] Setup (2 Dimensions) ---" << endl;
    vector<float> refVec = {0.0, 0.0}; 
    VectorStore vs(2, testEmbedding, refVec);

    // Insert A, B, C, D
    // Distances from {0,0}:
    // A {1,0} -> 1.0
    // B {2,0} -> 2.0
    // C {5,0} -> 5.0
    // D {4,0} -> 4.0
    vs.addText("A"); // ID 0
    vs.addText("B"); // ID 1
    vs.addText("C"); // ID 2
    vs.addText("D"); // ID 3

    cout << "Added A, B, C, D." << endl;
    cout << "Size: " << vs.size() << endl;
    
    // --- 2. TRAVERSAL CHECK ---
    // Expected Sort Order (Ascending Dist): A(1), B(2), D(4), C(5)
    // IDs: 0, 1, 3, 2
    cout << "\n--- [2] Sorting Check (AVL) ---" << endl;
    vector<int> sortedIds = vs.getAllIdsSortedByDistance();
    cout << "IDs sorted by Dist: [ ";
    for(int id : sortedIds) cout << id << " ";
    cout << "] (Exp: 0 1 3 2)" << endl; 

    // --- 3. NEAREST NEIGHBOR ---
    cout << "\n--- [3] FindNearest ---" << endl;
    vector<float> query = {1.1f, 0.0f}; // Close to A {1,0}
    
    // Euclidean: A is closest.
    cout << "Nearest (Euclidean): ID " << vs.findNearest(query, "euclidean") << " (Exp: 0)" << endl;

    // Cosine: A, B, C, D are all on X-axis {X, 0}. 
    // They all have Cosine Sim = 1.0 with Query {1.1, 0}. 
    // The result depends on tree traversal order (likely returns first or last visited).
    cout << "Nearest (Cosine): ID " << vs.findNearest(query, "cosine") << " (Exp: Any valid ID)" << endl;

    // --- 4. TOP K (Hardcoded Size) ---
    cout << "\n--- [4] Top K Nearest ---" << endl;
    vector<float> origin = {0.0, 0.0};
    
    // Top 3 from Origin: A(1), B(2), D(4). (C is 5, too far).
    int* topK = vs.topKNearest(origin, 3, "euclidean");
    cout << "Top 3 Euclidean from Origin: ";
    printArray(topK, 3); // Expect: [0, 1, 3] (in that order)
    delete[] topK;

    // --- 5. RANGE QUERY (Hardcoded Size) ---
    cout << "\n--- [5] Range Query ---" << endl;
    // Range [1.5, 4.5]
    // A(1.0) -> Out (Too small)
    // B(2.0) -> In
    // D(4.0) -> In
    // C(5.0) -> Out (Too big)
    // Matches: B(ID 1) and D(ID 3). Size = 2.
    cout << "Range Query [1.5, 4.5] (Exp IDs: 1, 3): ";
    int* rangeIds = vs.rangeQueryFromRoot(1.5, 4.5);
    printArray(rangeIds, 2); 
    delete[] rangeIds;

    // --- 6. BOUNDING BOX (Hardcoded Size) ---
    cout << "\n--- [6] Bounding Box ---" << endl;
    // Box: Min {0,0}, Max {3,3}
    // A {1,0} -> In
    // B {2,0} -> In
    // D {4,0} -> Out (X=4 > MaxX=3)
    // C {5,0} -> Out
    // Matches: A(ID 0) and B(ID 1). Size = 2.
    cout << "Bounding Box {0,0}->{3,3} (Exp IDs: 0, 1): ";
    int* boxIds = vs.boundingBoxQuery({-1.0,-1.0}, {3.0,3.0});
    printArray(boxIds, 2); 
    delete[] boxIds;

    // --- 7. ADVANCED UTILS ---
    cout << "\n--- [7] Advanced Utils ---" << endl;
    cout << "Max Dist: " << vs.getMaxDistance() << " (Exp: 5.0000 - C)" << endl;
    cout << "Min Dist: " << vs.getMinDistance() << " (Exp: 1.0000 - A)" << endl;
    
    // Estimate D
    // k=2, Avg=(1+2+5+4)/4 = 3.0. Ref={0,0}. Query={1.1, 0}.
    double estD = vs.estimateD_Linear(query, 2, vs.getAverageDistance(), *vs.getReferenceVector());
    cout << "EstimateD (k=2): " << estD << endl;

    // --- 8. REMOVAL ---
    cout << "\n--- [8] Removal ---" << endl;
    // Current Sorted Order: A(0), B(1), D(3), C(2)
    // Index 1 corresponds to 'B' (ID 1).
    cout << "Removing index 1 (Vector B)..." << endl;
    vs.removeAt(1);
    
    vector<int> remIds = vs.getAllIdsSortedByDistance();
    cout << "Remaining IDs: [ ";
    for(int id : remIds) cout << id << " ";
    cout << "] (Exp: 0 3 2 -> A, D, C)" << endl;

    // --- 9. SET REFERENCE ---
    cout << "\n--- [9] Set Reference Vector ---" << endl;
    // Move reference to {4.0, 0.0} (Where D is).
    // New Distances:
    // D {4,0}: Dist 0.0
    // C {5,0}: Dist 1.0
    // A {1,0}: Dist 3.0
    // New Sort Order: D(3), C(2), A(0)
    vs.setReferenceVector({4.0, 0.0});
    cout << "Ref changed to {4,0}." << endl;
    cout << "New Closest (Index 0) Text: " << vs.getRawText(0) << " (Exp: D)" << endl;
    
    // Verify Sort Order
    vector<int> newSort = vs.getAllIdsSortedByDistance();
    cout << "New IDs Sorted: [ ";
    for(int id : newSort) cout << id << " ";
    cout << "] (Exp: 3 2 0)" << endl;

    // --- 10. PREPROCESSING CHECK ---
    cout << "\n--- [10] Preprocessing Check ---" << endl;
    // Add PAD {2.0} -> Should become {2.0, 0.0} (Dist 2.0 from new ref {4,0})
    // Add TRUNC {1,2,3} -> Should become {1.0, 2.0} (Dist from {4,0} = sqrt(3^2 + 2^2) = sqrt(13) ~3.6)
    vs.addText("PAD");
    vs.addText("TRUNC");
    cout << "Size after PAD/TRUNC: " << vs.size() << endl;
    cout << "Last Vector (TRUNC) Y-val: " << (*vs.getVector(vs.size()-1)->vector)[1] << " (Exp: 2.0)" << endl;

    // --- 11. CLEANUP ---
    cout << "\n--- [11] Clear ---" << endl;
    vs.clear();
    cout << "Cleared. Size: " << vs.size() << endl;
    
    cout << "=========================================" << endl;
}

int main() {
    //test_001();
    //test_002();
    //test_003();
    //test_004();
    test_005();
    test_006();
    return 0;
}
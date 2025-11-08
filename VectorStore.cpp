// NOTE: Per assignment rules, only this single include is allowed here.
#include "VectorStore.h"

// =====================================
// Helper functions
// =====================================

// Helper function to print n spaces for tree visualization
void printNSpace(int n) {
    for (int i = 0; i < n; i++) {
        cout << " ";
    }
}

// =====================================
// AVLTree<K, T> implementation
// =====================================

template <class K, class T>
void AVLTree<K, T>::printTreeStructure() const {
    int height = this->getHeight();
		if (this->root == NULL)
		{
			cout << "NULL\n";
			return;
		}
		queue<AVLNode *> q;
		q.push(root);
		AVLNode *temp;
		int count = 0;
		int maxNode = 1;
		int level = 0;
		int space = pow(2, height);
		printNSpace(space / 2);
		while (!q.empty())
		{
			temp = q.front();
			q.pop();
			if (temp == NULL)
			{
				cout << " ";
				q.push(NULL);
				q.push(NULL);
			}
			else
			{
				cout << temp->data;
				q.push(temp->pLeft);
				q.push(temp->pRight);
			}
			printNSpace(space);
			count++;
			if (count == maxNode)
			{
				cout << endl;
				count = 0;
				maxNode *= 2;
				level++;
				space /= 2;
				printNSpace(space / 2);
			}
			if (level == height)
				return;
		}
}

//TODO: Implement all AVLTree<K, T> methods here

template <class K, class T>
AVLTree<K, T>::AVLTree() {
    root = nullptr;
}

template <class K, class T>
AVLTree<K, T>::~AVLTree() {
    clear();
}

// ROTATIONS
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>:: rotateRight(AVLNode*& node) {
    AVLNode* pivot = node->pLeft;
    node->pLeft = pivot->pRight;
    pivot->pRight = node;
    return pivot;
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>:: rotateLeft(AVLNode*& node) {
    AVLNode* pivot = node->pRight;
    node->pRight = pivot->pLeft;
    pivot->pLeft = node;
    return pivot;
}

// INSERTION
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::balanceLeft(AVLNode*& node) {
    AVLNode* leftChild = node->pLeft;
    if (leftChild->balance == LH) { // Case 1: Left-Left (LL)
        // Single Right Rotation
        node = rotateRight(node);
        node->balance = EH;
        node->pRight->balance = EH;
    } 
    else { // Case 2: Left-Right (LR)
        AVLNode* grandChild = leftChild->pRight;
        node->pLeft = rotateLeft(node->pLeft);
        node = rotateRight(node);

        // Update balances based on grandchild's original balance
        if (grandChild->balance == LH) {
            node->balance = EH;
            node->pLeft->balance = EH;
            node->pRight->balance = RH;
        } 
        else if (grandChild->balance == RH) {
            node->balance = EH;
            node->pLeft->balance = LH;
            node->pRight->balance = EH;
        } 
        else { // grandChild was EH
            node->balance = EH;
            node->pLeft->balance = EH;
            node->pRight->balance = EH;
        }
    }
    return node;
}

template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::balanceRight(AVLNode*& node) {
    AVLNode* rightChild = node->pRight;
    if (rightChild->balance == RH) { // Case 3: Right-Right (RR)
        // Single Left Rotation
        node = rotateLeft(node);
        node->balance = EH;
        node->pLeft->balance = EH;
    } 
    else { // Case 4: Right-Left (RL)
        AVLNode* grandChild = rightChild->pLeft;
        node->pRight = rotateRight(node->pRight);
        node = rotateLeft(node);
        
        // Update balances based on grandchild's original balance
        if (grandChild->balance == LH) {
            node->balance = EH;
            node->pLeft->balance = RH;
            node->pRight->balance = EH;
        } 
        else if (grandChild->balance == RH) {
            node->balance = EH;
            node->pLeft->balance = EH;
            node->pRight->balance = LH;
        } 
        else { // grandChild was EH
            node->balance = EH;
            node->pLeft->balance = EH;
            node->pRight->balance = EH;
        }
    }
    return node;
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::insertHelper(
    AVLNode*& node, const K& key, const T& value, bool& taller) 
{
    if (node == nullptr) {
        node = new AVLNode(key, value); // Constructor sets balance = EH
        taller = true;
        return node;
    }

    if (key < node->key) {
        node->pLeft = insertHelper(node->pLeft, key, value, taller);

        if (taller) { 
            // Update balance factor
            if (node->balance == LH) {
                node = balanceLeft(node);
                taller = false; 
            } else if (node->balance == EH) { 
                node->balance = LH;
                taller = true; 
            } else { 
                node->balance = EH;
                taller = false; // Height did not increase
            }
        }
    } 
    else if (key > node->key) {
        node->pRight = insertHelper(node->pRight, key, value, taller);

        if (taller) { 
            // Update balance factor
            if (node->balance == LH) {
                node->balance = EH;
                taller = false;
            } else if (node->balance == EH) { 
                node->balance = RH;
                taller = true; 
            } else { 
                node = balanceRight(node); 
                taller = false; // Height did not increase
            }
        }
    } 
    else {
        // Duplicate key found
        taller = false;
    }

    return node;
}
template <class K, class T>
void AVLTree<K, T>::insert(const K& key, const T& value) {
    bool taller = false;
    this->root = insertHelper(this->root, key, value, taller);
}

//  REMOVAL
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::findMin(AVLNode* node) const {
    if (!node || !node->pLeft) return node;
    return findMin(node->pLeft);
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::balanceRight_Remove(AVLNode*& node, bool& shorter) 
{
    if (node->balance == LH) { 
        node->balance = EH;
       
    } 
    else if (node->balance == EH) {  // Height balanced
        node->balance = RH;
        shorter = false; 
    } 
    else { // node->balance == RH (Right Heavy)
        AVLNode* rightChild = node->pRight;
        if (rightChild->balance == LH) { // RL Case
            AVLNode* grandChild = rightChild->pLeft;
            node->pRight = rotateRight(node->pRight);
            node = rotateLeft(node);
            // Update balances
            if (grandChild->balance == EH) {
                node->balance = EH; node->pLeft->balance = EH; node->pRight->balance = EH;
            } 
            else if (grandChild->balance == LH) {
                node->balance = EH; node->pLeft->balance = RH; node->pRight->balance = EH;
            } 
            else { // grandChild->balance == RH
                node->balance = EH; node->pLeft->balance = EH; node->pRight->balance = LH;
            }
            shorter = true;
        } 
        else { // RR Case (or child is EH)
            node = rotateLeft(node);
            if (rightChild->balance == EH) {
                node->balance = LH; node->pLeft->balance = RH; shorter = false;
            } 
            else { // rightChild->balance == RH
                node->balance = EH; node->pLeft->balance = EH; shorter = true;
            }
        }
    }
    return node;
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::balanceLeft_Remove(
    AVLNode*& node, bool& shorter) 
{
    if (node->balance == RH) {
        node->balance = EH;
    } 
    else if (node->balance == EH) {
        node->balance = LH;
        shorter = false; // Stop
    } 
    else { 
        // Unbalanced
        AVLNode* leftChild = node->pLeft;
        if (leftChild->balance == RH) { // LR Case
            AVLNode* grandChild = leftChild->pRight;
            node->pLeft = rotateLeft(node->pLeft);
            node = rotateRight(node);
            // Update balances
            if (grandChild->balance == EH) {
                node->balance = EH; node->pLeft->balance = EH; node->pRight->balance = EH;
            } 
            else if (grandChild->balance == LH) {
                node->balance = EH; node->pLeft->balance = EH; node->pRight->balance = RH;
            } 
            else { // grandChild->balance == RH
                node->balance = EH; node->pLeft->balance = LH; node->pRight->balance = EH;
            }
            shorter = true;
        } 
        else { // LL Case (or child is EH)
            node = rotateRight(node);
            if (leftChild->balance == EH) {
                node->balance = RH; node->pRight->balance = LH; shorter = false;
            } 
            else { // leftChild->balance == LH
                node->balance = EH; node->pRight->balance = EH; shorter = true;
            }
        }
    }
    return node;
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::removeHelper(
    AVLNode*& node, const K& key, bool& shorter, bool& success) 
{
    if (node == nullptr) {
        // Key not found
        shorter = false;
        success = false;
        return nullptr;
    }

    if (key < node->key) {
        // 1. Delete from LEFT subtree
        node->pLeft = removeHelper(node->pLeft, key, shorter, success);
        if (shorter) {
            // Left subtree shrunk, rebalance this node
            node = balanceRight_Remove(node, shorter); 
        }
    } 
    else if (key > node->key) {
        // 2. Delete from RIGHT subtree
        node->pRight = removeHelper(node->pRight, key, shorter, success);
        if (shorter) {
            // Right subtree shrunk, rebalance this node
            node = balanceLeft_Remove(node, shorter);
        }
    } 
    else {
        // 3. Key found. This is the node to delete.
        success = true;
        if (node->pLeft == nullptr) {
            // Case 1: 0 or 1 child (right)
            AVLNode* temp = node->pRight;
            delete node;
            node = temp;
            shorter = true; // This subtree is now shorter
        } else if (node->pRight == nullptr) {
            // Case 2: 1 child (left)
            AVLNode* temp = node->pLeft;
            delete node;
            node = temp;
            shorter = true;
        } else {
            // Case 3: 2 children
            AVLNode* successor = findMin(node->pRight);
            
            // Copy successor's data to this node
            node->key = successor->key;
            node->data = successor->data;
            
            node->pRight = removeHelper(node->pRight, successor->key, shorter, success);
            
            if (shorter) {
                node = balanceLeft_Remove(node, shorter);
            }
        }
    }
    return node;
}

template <class K, class T>
void AVLTree<K, T>::remove(const K& key) {
    bool shorter = false;
    bool success = false;
    this->root = removeHelper(this->root, key, shorter, success);
}

// CONTAINS
template <class K, class T>
bool AVLTree<K, T>:: containsHelper(AVLNode* node, const K& key) const {
    if (node == nullptr) {
        return false;
    }
    if (key < node->key) {
        return containsHelper(node->pLeft, key);
    }
    else if (key > node->key) {
        return containsHelper(node->pRight, key);
    }
    else{
        return true;
    }
    return false;
}
template <class K, class T>
bool AVLTree<K, T>:: contains(const K& key) const {
    return containsHelper(root, key);
}

// GET HEIGHT
template <class K, class T>
int AVLTree<K,T>:: getHeightHelper(AVLNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = getHeightHelper(node->pLeft);
    int rightHeight = getHeightHelper(node->pRight);
    return 1 + max(leftHeight, rightHeight);
}
template <class K, class T>
int AVLTree<K, T>::getHeight() const {
    if (root == nullptr) {
        return 0;
    }
    return getHeightHelper(root);
}

// GET SIZE
template <class K, class T>
int AVLTree<K,T>:: getSizeHelper(AVLNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getSizeHelper(node->pLeft) + getSizeHelper(node->pRight);
}
template <class K, class T>
int AVLTree<K, T>::getSize() const {
    if (root == nullptr) {
        return 0;
    }
    return getSizeHelper(root);
}

// CLEAR
template <class K, class T>
void AVLTree<K,T>::clearHelper( AVLNode* node) {
    if (node != nullptr) {
        clearHelper(node->pLeft);
        clearHelper(node->pRight);
        delete node;
    }
}
template <class K, class T>
void AVLTree<K, T>::clear() {
    clearHelper(root);
    root = nullptr;
}

// EMPTY
template <class K, class T>
bool AVLTree<K, T>::empty() const {
    return root == nullptr;
}

// INORDER TRAVERSAL
template <class K, class T>
void AVLTree<K, T>::inorderHelper(AVLNode* node, void (*action)(const T&)) const {
    if (node != nullptr) {
        inorderHelper(node->pLeft, action);
        action(node->data);
        inorderHelper(node->pRight, action);
    }
}
template <class K, class T>
void AVLTree<K, T>::inorderTraversal(void (*action)(const T&)) const {
    inorderHelper(root, action);
}


// =====================================
// RedBlackTree<K, T> implementation
// =====================================

template <class K, class T>
void RedBlackTree<K, T>::printTreeStructure() const {
    if (this->root == nullptr) {
        cout << "NULL\n";
        return;
    }
    
    queue<RBTNode*> q;
    q.push(root);
    RBTNode* temp;
    int count = 0;
    int maxNode = 1;
    int level = 0;
    
    // Calculate tree height for spacing
    int height = 0;
    queue<RBTNode*> heightQ;
    heightQ.push(root);
    while (!heightQ.empty()) {
        int size = heightQ.size();
        height++;
        for (int i = 0; i < size; i++) {
            RBTNode* node = heightQ.front();
            heightQ.pop();
            if (node->left) heightQ.push(node->left);
            if (node->right) heightQ.push(node->right);
        }
    }
    
    int space = pow(2, height);
    printNSpace(space / 2);
    
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        
        if (temp == nullptr) {
            cout << "NULL";
            q.push(nullptr);
            q.push(nullptr);
        } else {
            // Print node data and color as tuple: (data, color)
            cout << "(" << temp->data << ",";
            if (temp->color == RED) {
                cout << "R)";
            } else {
                cout << "B)";
            }
            
            q.push(temp->left);
            q.push(temp->right);
        }
        
        printNSpace(space);
        count++;
        
        if (count == maxNode) {
            cout << endl;
            count = 0;
            maxNode *= 2;
            level++;
            space /= 2;
            printNSpace(space / 2);
        }
        
        if (level == height) {
            return;
        }
    }
}

//TODO: Implement all other RedBlackTree<K, T> methods here
// RBTNode CONSTRUCTOR & COLORING
template <class K, class T>
RedBlackTree<K, T>::RBTNode::RBTNode(const K& key, const T& value)
    : key(key), 
      data(value), 
      color(RED),       // New nodes are always RED
      parent(nullptr), 
      left(nullptr), 
      right(nullptr) {
    // The constructor body is empty
}
template <class K, class T>
void RedBlackTree<K, T>::RBTNode::recolorToRed() {
    this->color = RED;
}
template <class K, class T>
void RedBlackTree<K, T>::RBTNode::recolorToBlack() {
    this->color = BLACK;
}

// RBT CONSTRUCTOR & DESTRUCTOR
template <class K, class T>
RedBlackTree<K, T>::RedBlackTree() {
    root = nullptr;
}
template <class K, class T>
RedBlackTree<K, T>::~RedBlackTree() {
    clear();
}

// ROTATIONS
template <class K, class T>
void RedBlackTree<K, T>:: rotateLeft(RBTNode* node) {
    RBTNode* pivot = node->right;
    node->right = pivot->left;

    if (pivot->left != nullptr) {
        pivot->left->parent = node;
    }
    pivot->parent = node->parent;

    if (node->parent == nullptr) {
        root = pivot;
    } 
    else if (node == node->parent->left) {
        node->parent->left = pivot;
    } 
    else {
        node->parent->right = pivot;
    }
    pivot->left = node;
    node->parent = pivot;
}
template <class K, class T>
void RedBlackTree<K,T>:: rotateRight(RBTNode* node){
    RBTNode* pivot = node->left;
    node->left = pivot->right;

    if(pivot->right != nullptr){
        pivot->right->parent = node;
    }
    pivot->parent = node->parent;

    if(!node->parent){
        root = pivot;
    }
    else if( node == node->parent->left){
        node->parent->left = pivot;
    }
    else{
        node->parent->right = pivot;
    }
    pivot->right = node;
    node->parent = pivot;
}

// LOWERBOUND & UPPERBOUND NODE
template <class K, class T>
typename RedBlackTree<K, T>::RBTNode* RedBlackTree<K, T>:: lowerBoundNode(const K& key) const {
    RBTNode* cur = root;
    RBTNode* res = nullptr;

    while (cur) {
        if (cur->key >= key) {
            res = cur;
            cur = cur->left;
        } 
        else {
            cur = cur->right;
        }
    }
    return res;
}
template <class K, class T>
typename RedBlackTree<K, T>::RBTNode* RedBlackTree<K, T>:: upperBoundNode(const K& key) const {
    RBTNode* cur = root;
    RBTNode* res = nullptr;

    while (cur) {
        if (cur->key > key) {
            res = cur;
            cur = cur->left;
        } 
        else {
            cur = cur->right;
        }
    }
    return res;
}
// EMPTY
template <class K, class T>
bool RedBlackTree<K, T>:: empty() const {
    return root == nullptr;
}

// SIZE
template <class K, class T>
int RedBlackTree<K, T>::getSize(RBTNode* node) const{
    if (!node){
        return 0;
    }
    return 1 + getSize(node->left) + getSize(node->right);
}
template <class K, class T>
int RedBlackTree<K, T>:: size() const {
    if (root == nullptr) {
        return 0;
    }
    return getSize(root);
}

// CLEAR
template <class K, class T>
void RedBlackTree<K,T>:: clearHelper(RBTNode* node){
    if(node){
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}
template <class K, class T>
void RedBlackTree<K,T>:: clear(){
    clearHelper(root);
    root = nullptr;
}

// INSERT
template <class K, class T>
void RedBlackTree<K, T>::fixInsert(RBTNode* node) {
    while (node != root && node->parent->color == Color::RED) {
        RBTNode* parent = node->parent;
        RBTNode* grandparent = parent->parent;

        // CASE 1: Parent is left child of grandparent
        if (parent == grandparent->left) {
            RBTNode* uncle = grandparent->right;

            // Case 1A: Uncle is red → recolor and move up
            if (uncle && uncle->color == Color::RED) {
                parent->recolorToBlack();
                uncle->recolorToBlack();
                grandparent->recolorToRed();
                node = grandparent;
            }
            else { // uncle is black
                // Case 1B: node is right child → rotate left
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                }
                // Case 1C: node is left child → rotate right
                parent->recolorToBlack();
                grandparent->recolorToRed();
                rotateRight(grandparent);
            }
        }
        // CASE 2: Parent is right child of grandparent (mirror)
        else {
            RBTNode* uncle = grandparent->left;

            // Case 2A: Uncle is red
            if (uncle && uncle->color == Color::RED) {
                parent->recolorToBlack();
                uncle->recolorToBlack();
                grandparent->recolorToRed();
                node = grandparent;
            }
            else { // uncle is black 
                // Case 2B: node is left child → rotate right
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                }
                // Case 2C: node is right child → rotate left
                parent->recolorToBlack();
                grandparent->recolorToRed();
                rotateLeft(grandparent);
            }
        }
    }

    // Root must always be black
    root->recolorToBlack();
}

template <class K, class T>
void RedBlackTree<K, T>:: insert(const K& key, const T& value) {
    RBTNode* newNode = new RBTNode(key, value); //red node
    if(root == nullptr){
        newNode->recolorToBlack();
        root = newNode;
        return;
    }
    else{
        RBTNode* parent = nullptr;
        RBTNode* current = root;
        while (current) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } 
            else if (key > current->key) {
                current = current->right;
            } 
            else {
                delete newNode; // Duplicate keys 
                return;
            }
        }
        newNode->parent = parent;
        if (key < parent->key) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }
    fixInsert(newNode);
}

// FIND
template <class K, class T>
typename RedBlackTree<K, T>::RBTNode* RedBlackTree<K, T>:: find(const K& key) const {
    RBTNode* cur = root;
    while (cur) {
        if (key < cur->key) {
            cur = cur->left;
        } 
        else if (key > cur->key) {
            cur = cur->right;
        }
        else {
            return cur; // Key found
        }
    }
    return nullptr; // Key not found
}

// REMOVE
template <class K, class T>
typename RedBlackTree<K, T>::RBTNode*
RedBlackTree<K, T>::findMax(RBTNode* node) const {
    while (node->right)
        node = node->right;
    return node;
}

template <class K, class T>
void RedBlackTree<K, T>::transplant(RBTNode* u, RBTNode* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left) // u is left child
        u->parent->left = v;
    else                           // u is right child
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

template <class K, class T>
void RedBlackTree<K, T>::fixRemove(RBTNode* x, RBTNode* xParent) {

    // x is the replacing node
    while (x != root && (x == nullptr || x->color == Color::BLACK)) {

        // Case 1: x is left child
        if (x == (xParent ? xParent->left : nullptr)) {
            RBTNode* w = xParent->right; // w is sibling of x

            // Case 1a: sibling is red
            if (w && w->color == Color::RED) {
                w->recolorToBlack();
                xParent->recolorToRed();
                rotateLeft(xParent);
                w = xParent->right;
            }

            // Case 1b: sibling and its children are black
            if (w == nullptr || ((w->left == nullptr || w->left->color == Color::BLACK) &&
                 (w->right == nullptr || w->right->color == Color::BLACK))) {
                if (w) w->recolorToRed();
                x = xParent;
                xParent = x->parent;
            } 
            else { 
                // Case 1c: sibling is black and  left: red, right: black
                if (w && (w->right == nullptr || w->right->color == Color::BLACK)) {
                    if (w->left) w->left->recolorToBlack();
                    w->recolorToRed();
                    rotateRight(w);
                    w = xParent->right;
                }

                // Case 1d: sibling's right is red
                if (w) w->color = xParent->color;
                xParent->recolorToBlack();
                if (w && w->right) w->right->recolorToBlack();
                rotateLeft(xParent);
                x = root;
                break;
            }
        } 
        // Case 2: x is right child (mirror)
        else {
            RBTNode* w = xParent->left;
            // Case 2a: sibling is red
            if (w && w->color == Color::RED) {
                w->recolorToBlack();
                xParent->recolorToRed();
                rotateRight(xParent);
                w = xParent->left;
            }
            // Case 2b: both sibling and its children are black
            if (w == nullptr ||
                ((w->right == nullptr || w->right->color == Color::BLACK) &&
                 (w->left == nullptr || w->left->color == Color::BLACK))) {
                if (w) w->recolorToRed();
                x = xParent;
                xParent = x->parent;
            }
            
            else {
                // Case 2c: sibling is black and  left: black, right: red
                if (w && (w->left == nullptr || w->left->color == Color::BLACK)) {
                    if (w->right) w->right->recolorToBlack();
                    w->recolorToRed();
                    rotateLeft(w);
                    w = xParent->left;
                }
                // Case 2d: sibling's left is red
                if (w) w->color = xParent->color;
                xParent->recolorToBlack();
                if (w && w->left) w->left->recolorToBlack();
                rotateRight(xParent);
                x = root;
                break;
            }
        }
    }

    if (x) x->recolorToBlack();
    if (root) root->recolorToBlack();
}
template <class K, class T>
void RedBlackTree<K, T>::remove(const K& key) {
    RBTNode* node = find(key);
    if (!node) return; // key not found

    RBTNode* y = node;
    RBTNode* x = nullptr;
    RBTNode* xParent = nullptr;
    Color originalColor = y->color;

    // Case 1: node has 0 or 1 child
    if (node->left == nullptr) {
        x = node->right;
        xParent = node->parent;
        transplant(node, node->right);
    } 
    else if (node->right == nullptr) {
        x = node->left;
        xParent = node->parent;
        transplant(node, node->left);
    } 
    // Case 2: node has 2 children
    else {
        // Use predecessor (largest in left subtree)
        y = findMax(node->left);
        originalColor = y->color;
        x = y->left;

        if (y->parent == node) {
            xParent = y;
            if (x) x->parent = y;
        } 
        else {
            xParent = y->parent;
            transplant(y, y->left);
            y->left = node->left;
            if (y->left) y->left->parent = y;
        }

        transplant(node, y);
        y->right = node->right;
        if (y->right) y->right->parent = y;
        y->color = node->color;
    }

    delete node;

    // If deleted node was black, fix double-black violation
    if (originalColor == Color::BLACK)
        fixRemove(x, xParent);
}

// CONTAINS
template <class K, class T>
bool RedBlackTree<K, T>::contains(const K& key) const{
    return find(key) != nullptr;
}

// LOWERBOUND & UPPERBOUND
template <class K, class T>
typename RedBlackTree<K, T>::RBTNode* RedBlackTree<K, T>::lowerBound(const K& key, bool& found) const {
    
    RBTNode* result = this->lowerBoundNode(key);

    if (result == nullptr) {
        found = false;
    } 
    else {
        found = true;
    }

    return result;
}
template <class K, class T>
typename RedBlackTree<K, T>::RBTNode* RedBlackTree<K, T>::upperBound(const K& key, bool& found) const {
    
    RBTNode* result = this->upperBoundNode(key);

    if (result == nullptr) {
        found = false;
    } else {
        found = true;
    }

    return result;
}






// =====================================
// VectorRecord implementation
// =====================================

// Overload operator << for VectorRecord - prints only the id
std::ostream& operator<<(std::ostream& os, const VectorRecord& record) {
    os << record.id;
    return os;
}

// =====================================
// VectorStore implementation
// =====================================

//TODO: Implement all VectorStore methods here

//CONSTRUCTOR
VectorStore::VectorStore( int dimension, 
    vector<float>* (*embeddingFunction)(const string&),
    const vector<float>& referenceVector){
    
    this->dimension = dimension;
    this->embeddingFunction = embeddingFunction;
    this->count = 0;
    this->averageDistance = 0.0;

    // Allocate the trees (empty)
    this->vectorStore = new AVLTree<double, VectorRecord>();        //avl
    this->normIndex   = new RedBlackTree<double, VectorRecord>();   //rbt

    // Copy reference vector
    this->referenceVector = new vector<float>(referenceVector);

    // No root vector yet
    this->rootVector = nullptr;     //root vector of avl
}
// DESRUCTOR
VectorStore::~VectorStore()
{
    // Clear all AVL and Red-Black tree contents
    if (vectorStore) {
        vectorStore->clear();
        delete vectorStore;
        vectorStore = nullptr;
    }

    if (normIndex) {
        normIndex->clear();
        delete normIndex;
        normIndex = nullptr;
    }

    // Delete rootVector and referenceVector
    if (rootVector) {
        delete rootVector;
        rootVector = nullptr;
    }

    if (referenceVector) {
        delete referenceVector;
        referenceVector = nullptr;
    }
}

//SIZE
int VectorStore::size() {
    return this->count;
}

//EMPTY
bool VectorStore::empty(){
    return this->count == 0;
}

//CLEAR
void VectorStore::clear(){
    if(vectorStore) vectorStore->clear(); // clear avl
    if(normIndex)   normIndex->clear(); // clear RBT
    this->count = 0;
    this->averageDistance = 0.0;
    
    if(rootVector){
        delete rootVector;
        rootVector = nullptr;
    }
}
// PREPROCESSING AND DATA MANAGEMENT

vector<float>* VectorStore::preprocessing(string rawText) {
    // Call embeddingFunction to map the text to a vector
    vector<float>* vec = embeddingFunction(rawText);
    if (!vec) return nullptr;

    // if size > dimension -> truncate trailing
    if (vec->size() > static_cast<size_t>(dimension)) {
        vec->resize(dimension);
    }

    // if size < dimension -> pad with 0's
    else if (vec->size() < static_cast<size_t>(dimension)) {
        vec->insert(vec->end(), dimension - vec->size(), 0.0f);
    }

    // Return the normalized vector
    return vec;
}

void VectorStore::addText(string rawText) {
    
    // use preprocessing to convert text into a vector.
    vector<float>* newVec = this->preprocessing(rawText);
    if (newVec == nullptr) {
        return; 
    }

    // Compute distance from the reference vector.
    // for the AVL Tree
    double distFromRef = l2Distance(*newVec, *this->referenceVector);

    // Update the average distance.
    double totalDistance = (this->averageDistance * this->count) + distFromRef;
    int old_count = this->count;
    this->count++; 
    this->averageDistance = totalDistance / this->count;

    // Compute the "Euclidean norm" of the vector.
    // for the Red-Black Tree
    double vecNorm = 0.0;
    for (float val : *newVec) {
        vecNorm += val * val;
    }
    vecNorm = sqrt(vecNorm);

    // newID = current max id + 1
    int maxId = -1;
    if (old_count > 0) {
        // use AVL to traverse

        queue<AVLTree<double, VectorRecord>::AVLNode*> q;
        q.push(this->vectorStore->root); 

        while(!q.empty()) {
            AVLTree<double, VectorRecord>::AVLNode* node = q.front();
            q.pop();
            
            if(node == nullptr) continue;

            if (node->data.id > maxId) {
                maxId = node->data.id;
            }
            
            if(node->pLeft) q.push(node->pLeft);
            if(node->pRight) q.push(node->pRight);
        }
    }
    int newId = maxId + 1;

    // Create the new record
    VectorRecord newRecord(newId, rawText, newVec, distFromRef);
    newRecord.norm = vecNorm;

    // If the store is empty, sets this vector as the root vector.
    if (old_count == 0) {
        this->rootVector = new VectorRecord(newRecord);
    } 
    // If the store is not empty:
    else {
        // Check if new vector's distance is closer to the average
        double rootDistToAvg = fabs(this->rootVector->distanceFromReference - this->averageDistance);
        double newDistToAvg = fabs(newRecord.distanceFromReference - this->averageDistance);

        if (newDistToAvg < rootDistToAvg) {
            // This new vector becomes the rootVector
            delete this->rootVector;
            this->rootVector = new VectorRecord(newRecord); 
        }
    }
    // insert vector into AVL 
    this->vectorStore->insert(distFromRef, newRecord);
    
    // insert vector into RBT
    this->normIndex->insert(newRecord.norm, newRecord);
}

// helper for finding vector at given index with INORDER Traversal
static VectorRecord* getNthRecordInorder(AVLTree<double, VectorRecord>::AVLNode* node, 
    int& counter, int targetIndex) {

    if (node == nullptr) {
        return nullptr;
    }

    //Traverse Left Subtree
    VectorRecord* result = getNthRecordInorder(node->pLeft, counter, targetIndex);
    if (result != nullptr) {
        return result; 
    }

    //Visit Current Node
    if (counter == targetIndex) {
        return &(node->data); 
    }
    counter++; // Increment counter *after* visiting

    //Traverse Right Subtree
    return getNthRecordInorder(node->pRight, counter, targetIndex);
}

VectorRecord* VectorStore::getVector(int index) {
    if (index < 0 || index >= this->count) {
        throw out_of_range("Index is invalid!");
    }
    
    int counter = 0;
    // getRoot() is a public method of AVLTree
    return getNthRecordInorder(this->vectorStore->getRoot(), counter, index);
}

string VectorStore::getRawText(int index) {
    if (index < 0 || index >= this->count) {
        throw out_of_range("Index is invalid!");
    }
    
    int counter = 0;
    VectorRecord* record = getNthRecordInorder(this->vectorStore->getRoot(), counter, index);
    
    return record->rawText;
}

int VectorStore::getId(int index) {
    if (index < 0 || index >= this->count) {
        throw out_of_range("Index is invalid!");
    }
    
    int counter = 0;
    VectorRecord* record = getNthRecordInorder(this->vectorStore->getRoot(), counter, index);
    
    return record->id;
}

bool VectorStore::removeAt(int index) {
    if (index < 0 || index >= this->count) {
        throw out_of_range("Index is invalid!");
    }

    int counter = 0;
    VectorRecord* recordPtr = getNthRecordInorder(this->vectorStore->getRoot(), counter, index);

    VectorRecord recordToRemove = *recordPtr;
    
    double avlKey = recordToRemove.distanceFromReference;
    double rbtKey = recordToRemove.norm;
    int removedId = recordToRemove.id;
    bool wasRoot = (this->rootVector != nullptr && removedId == this->rootVector->id);

    // Free the vector's memory
    delete recordToRemove.vector;

    // Remove from both trees
    this->vectorStore->remove(avlKey);
    this->normIndex->remove(rbtKey);

    // Update average distance
    double oldTotalDistance = this->averageDistance * this->count;
    double newTotalDistance = oldTotalDistance - recordToRemove.distanceFromReference;
    
    this->count--; // Decrement count
    
    if (this->count == 0) {
        this->averageDistance = 0.0;
    } 
    else {
        this->averageDistance = newTotalDistance / this->count;
    }

    // Handle root vector replacement
    if (this->count == 0) { //store is empty
        delete this->rootVector;
        this->rootVector = nullptr;
    } 
    else if (wasRoot) {
        // find newRoot
        
        queue<AVLTree<double, VectorRecord>::AVLNode*> q;
        q.push(this->vectorStore->getRoot());

        VectorRecord* newRoot = nullptr;
        double minDiff = -1.0; // Use -1.0 = not set

        while (!q.empty()) {
            AVLTree<double, VectorRecord>::AVLNode* node = q.front();
            q.pop();
            
            if (node == nullptr) continue;

            // Get pointer to the record *inside* the node
            VectorRecord* currentRecord = &(node->data);
            double diff = fabs(currentRecord->distanceFromReference - this->averageDistance);

            if (newRoot == nullptr || diff < minDiff) {
                minDiff = diff;
                newRoot = currentRecord;
            }

            if (node->pLeft) q.push(node->pLeft);
            if (node->pRight) q.push(node->pRight);
        }
        
        // Delete the old rootVector
        delete this->rootVector;
        // Make a new copy of the new root
        this->rootVector = new VectorRecord(*newRoot);
    }

    return true;
}


// REFERENCE VECTOR AND EMBEDDING FUNCTION MANAGEMENT
void VectorStore::setReferenceVector(const vector<float>& newReference) {

    delete this->referenceVector;
    this->referenceVector = new vector<float>(newReference);

    // If the store is empty -> done
    if (this->count == 0) {
        return;
    }

    // re-calculate all distances and rebuild the AVL tree.
    vector<VectorRecord> allRecords;
    allRecords.reserve(this->count); // Reserve space

    // use AVL to traverse
    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->root);

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();

        if (node == nullptr) continue;
        
        // Store a *copy* of the record.
        allRecords.push_back(node->data);

        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }

    // clear both trees
    this->vectorStore->clear();
    this->normIndex->clear();

    // Re-compute distances and update average
    double totalDistance = 0.0;
    for (VectorRecord& rec : allRecords) {
        rec.distanceFromReference = l2Distance(*rec.vector, *this->referenceVector);
        totalDistance += rec.distanceFromReference;
    }

    this->averageDistance = totalDistance / this->count;

    // Find the new root vector
    VectorRecord* newRoot = nullptr;
    double minDiff = -1.0; // -1 = not set

    for (VectorRecord& rec : allRecords) {
        double diff = fabs(rec.distanceFromReference - this->averageDistance);
        
        if (newRoot == nullptr || diff < minDiff) {
            minDiff = diff;
            newRoot = &rec; // Point to the record in our vector
        }
    }

    // Update new rootVector 
    delete this->rootVector;
    this->rootVector = new VectorRecord(*newRoot);

    // Reconstruct the AVL tree (and RBT)
    for (const VectorRecord& rec : allRecords) {
        // Insert into AVL tree with new distance
        this->vectorStore->insert(rec.distanceFromReference, rec);
        
        // Re-insert into RBT
        this->normIndex->insert(rec.norm, rec);
    }
}

vector<float>* VectorStore::getReferenceVector() const {
    return this->referenceVector;
}
VectorRecord* VectorStore::getRootVector() const {
    return this->rootVector;
}
double VectorStore::getAverageDistance() const {
    return this->averageDistance;
}
void VectorStore::setEmbeddingFunction(vector<float>* (*newEmbeddingFunction)(const string&)) {
    this->embeddingFunction = newEmbeddingFunction;
}

// TRAVERSAL AND ITERATION
static void inorder_helper(AVLTree<double, VectorRecord>::AVLNode* node, void (*action)(vector<float>&, int, string&)){
    if (node == nullptr) return;
    // left -> action -> right
    inorder_helper(node->pLeft, action);
    action(*(node->data.vector), node->data.id, node->data.rawText);
    inorder_helper(node->pRight, action);
}

void VectorStore::forEach(void (*action)(vector<float>&, int, string&)) {
    
    inorder_helper(this->vectorStore->getRoot(), action);
}

static void inorder_getid_helper(AVLTree<double, VectorRecord>::AVLNode* node, vector<int>& idVector){
    if (node == nullptr) return;
   
    inorder_getid_helper(node->pLeft, idVector);
    
    idVector.push_back(node->data.id); // Add the ID
    
    inorder_getid_helper(node->pRight, idVector);
}
vector<int> VectorStore::getAllIdsSortedByDistance() const {
    vector<int> ids;
    if (this->count > 0) {
        ids.reserve(this->count); // Optimize allocation
        inorder_getid_helper(this->vectorStore->getRoot(), ids);
    }
    return ids;
}

static void inorder_getVector_helper(AVLTree<double, VectorRecord>::AVLNode* node, vector<VectorRecord*>& recordVector)
{
    if (node == nullptr) return;

    inorder_getVector_helper(node->pLeft, recordVector);
    
    // Add a pointer to the VectorRecord data inside the AVL node
    recordVector.push_back(&(node->data));
    
    inorder_getVector_helper(node->pRight, recordVector);
}

vector<VectorRecord*> VectorStore::getAllVectorsSortedByDistance() const {

    vector<VectorRecord*> records;
    if (this->count > 0) {
        records.reserve(this->count); // Optimize allocation
        
        inorder_getVector_helper(this->vectorStore->getRoot(), records);
    }
    return records;
}




// DISTANCE METRICS
double VectorStore::cosineSimilarity(const vector<float>& v1, const vector<float>& v2) {
    if (v1.size() != v2.size() || v1.empty()) {
        return 0.0; // Or handle error
    }

    double dotProduct = 0.0;
    double normA = 0.0;
    double normB = 0.0;

    for (size_t i = 0; i < v1.size(); ++i) {
        dotProduct += v1[i] * v2[i];
        normA += v1[i] * v1[i];
        normB += v2[i] * v2[i];
    }

    // Handle potential division by zero 
    if (normA == 0.0 || normB == 0.0) {
        return 0.0; 
    }

    return dotProduct / (sqrt(normA) * sqrt(normB));
}
// Manhattan Distance (L1)
double VectorStore::l1Distance(const vector<float>& v1, const vector<float>& v2) {
    if(v1.size() != v2.size() || v1.empty()) {
        return 0.0; // Or handle error
    }

    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        sum += fabs(v1[i] - v2[i]);
    }
    return sum;
}
// Euclidean Distance (L2)
double VectorStore::l2Distance(const vector<float>& v1, const vector<float>& v2) {
    if(v1.size() != v2.size() || v1.empty()) {
        return 0.0; // Or handle error
    }
    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        double diff = v1[i] - v2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

// ESTIMATING THRESHOLD D FROM k
double VectorStore::estimateD_Linear(
    const vector<float>& query, 
    int k, 
    double averageDistance, 
    const vector<float>& reference, 
    double c0_bias, 
    double c1_slope) 
{
    // Formula: D = |dr - averageDistance| + c1_slope * averageDistance * k + c0_bias
    double dr = l2Distance(query, reference);
    double D = fabs(dr - averageDistance) + (c1_slope * averageDistance * k) + c0_bias;
    return D;
}
 
// NEAREST NEIGHBOR SEARCH
int VectorStore::findNearest(const vector<float>& query, string metric){
    if(this->empty()){
        return -1; // Store is empty
    }
    bool maximize;
    double bestDistance;

    if(metric == "cosine"){
        maximize = true;
        bestDistance = -2.0; // Cosine similarity ranges from -1 to 1
    }
    else if(metric == "euclidean" || metric == "manhattan"){
        maximize = false;
        bestDistance = 1.0e30; // A large number
    }
    else {
        throw invalid_metric("Invalid metric");
    }
    
    int bestId = -1;

    // use AVL to traverse
    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->root);

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();

        if (node == nullptr) continue;

        VectorRecord& currentRecord = node->data;
        double currentDistance;

        // Calculate the score based on the chosen metric
        if (metric == "euclidean") {
            currentDistance = l2Distance(query, *(currentRecord.vector));
        } 
        else if (metric == "manhattan") {
            currentDistance = l1Distance(query, *(currentRecord.vector));
        } 
        else if(metric == "cosine"){ 
            currentDistance = cosineSimilarity(query, *(currentRecord.vector));
        }

        // Update the best-scoring vector
        if (maximize) {
            // For cosine, we want the MAXIMUM score
            if (currentDistance > bestDistance) {
                bestDistance = currentDistance;
                bestId = currentRecord.id;
            }
        } 
        else {
            // For distance, we want the MINIMUM score
            if (currentDistance < bestDistance) {
                bestDistance = currentDistance;
                bestId = currentRecord.id;
            }
        }
        
        // Continue traversal
        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }
    
    return bestId;
}


// Helper function to collect candidates within [minNorm, maxNorm]
static void collectCandidates(
    RedBlackTree<double, VectorRecord>::RBTNode* node,
    double minNorm, double maxNorm,
    vector<VectorRecord*>& candidates)
{
    if (node == nullptr) {
        return;
    }
    //check left
    if (node->key > minNorm) {
        collectCandidates(node->left, minNorm, maxNorm, candidates);
    }
    // if the current node is in range, add it.
    if (node->key >= minNorm && node->key <= maxNorm) {
        candidates.push_back(&(node->data));
    }
    //check right
    if (node->key < maxNorm) {
        collectCandidates(node->right, minNorm, maxNorm, candidates);
    }
}
int* VectorStore:: topKNearest(const vector<float>& query, int k, string metric) {
    if (k <= 0 || k > this->count) {
        throw invalid_k_value();
    }
    
    bool maximize; // true for cosine, false for distances

    if (metric == "cosine") {
        maximize = true;
    } 
    else if (metric == "euclidean" || metric == "manhattan") {
        maximize = false;
    } 
    else {
        throw invalid_metric();
    }
    // 1. Compute query norm 
    double nq = 0.0;
    for (float val : query) {
        nq += val * val;
    }
    nq = sqrt(nq);

    // 2. Estimate radius D 
    double D = estimateD_Linear(query, k, this->averageDistance, *(this->referenceVector));

    // 3. Filter using Red Black Tree
    vector<VectorRecord*> candidates;
    // Get the RBT root
    RedBlackTree<double, VectorRecord>::RBTNode* rbtRoot = this->normIndex->root;
    
    collectCandidates(rbtRoot, nq - D, nq + D, candidates);

    int m = candidates.size();
    cout << "Value m: " << m << endl;

    // 4. Compute distance and select top k
    if (m == 0) {
        return new int[0]; // no candidate -> return empty dynamic array
    }

    // cosine -> use a min-heap to keep the k LARGEST scores.
    // distance -> use max-heap to keep the k SMALLEST distances.
    
    if (maximize) { // Cosine (use min-heap)
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> min_heap;

        for (VectorRecord* rec : candidates) {
            double score = cosineSimilarity(query, *(rec->vector));
            
            if (min_heap.size() < (size_t)k) {
                min_heap.push({score, rec->id});
            } else if (score > min_heap.top().first) {
                min_heap.pop();
                min_heap.push({score, rec->id});
            }
        }
        int result_size = min_heap.size();
        int* top_ids = new int[result_size];
        // Pop from min-heap -> ascending order of score
        for (int i = 0; i < result_size; i++) {
            top_ids[i] = min_heap.top().second; // {score, id}
            min_heap.pop();
        }
        return top_ids;
    }
    else{   // Euclidean or Manhattan (use max-heap)
        priority_queue<pair<double, int>> max_heap; // {distance, id}
        for(VectorRecord* rec: candidates){
            double distance;

            if(metric == "euclidean"){
                distance = l2Distance(query, *(rec->vector));
            }
            else{ //manhattan
                distance = l1Distance(query, *(rec->vector));
            }

            if(max_heap.size() < (size_t)k){
                max_heap.push({distance, rec->id});
            }
            else if(distance < max_heap.top().first){
                max_heap.pop();
                max_heap.push({distance, rec->id});
            }
        }
        int result_size = max_heap.size();
        int* top_ids = new int[result_size];
        // Pop from max-heap -> descending order of distance
        for(int i = result_size - 1; i >= 0; i--){
            top_ids[i] = max_heap.top().second; // <distance, id>
            max_heap.pop();
        }
        return top_ids;
    }
}

// OVERLOADED FUNCTIONS
bool VectorStore::empty() const{
    return this->count == 0;
}
double VectorStore::l1Distance(const vector<float>& v1, const vector<float>& v2) const {
    if(v1.size() != v2.size() || v1.empty()) {
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        sum += fabs(v1[i] - v2[i]);
    }
    return sum;
}

double VectorStore::l2Distance(const vector<float>& v1, const vector<float>& v2) const {
    if(v1.size() != v2.size() || v1.empty()) {
        return 0.0;
    }
    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        double diff = v1[i] - v2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}
double VectorStore::cosineSimilarity(const vector<float>& v1, const vector<float>& v2) const {
    if (v1.size() != v2.size() || v1.empty()) {
        return 0.0; // Or handle error
    }

    double dotProduct = 0.0;
    double normA = 0.0;
    double normB = 0.0;

    for (size_t i = 0; i < v1.size(); ++i) {
        dotProduct += v1[i] * v2[i];
        normA += v1[i] * v1[i];
        normB += v2[i] * v2[i];
    }

    // Handle potential division by zero 
    if (normA == 0.0 || normB == 0.0) {
        return 0.0; 
    }

    return dotProduct / (sqrt(normA) * sqrt(normB));
}
// RANGE QUERY
int* VectorStore::rangeQueryFromRoot(double minDist, double maxDist) const {
    
    vector<int> matchingIds;

    // If store is empty or there's no root vector, return empty array
    if (this->empty() || this->rootVector == nullptr) {
        return new int[0];
    }

    // Get the root vector's coordinates
    const vector<float>* rootCoords = this->rootVector->vector;

    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->getRoot());

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();

        if (node == nullptr) continue;

        if (node->data.id != this->rootVector->id) {
            // Calculate Euclidean distance from this node to the root vector
            double dist = l2Distance(*(node->data.vector), *rootCoords);

            // Check if it's in the range
            if (dist >= minDist && dist <= maxDist) {
                matchingIds.push_back(node->data.id);
            }
        } 
        else {
             // Check the root vector itself (distance is 0)
            if (0.0 >= minDist && 0.0 <= maxDist) {
                matchingIds.push_back(node->data.id);
            }
        }

        // Continue traversal
        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }

    // Convert the vector of IDs to a dynamic int array
    int* idArray = new int[matchingIds.size()];
    for (size_t i = 0; i < matchingIds.size(); ++i) {
        idArray[i] = matchingIds[i];
    }

    return idArray;
}
int* VectorStore::rangeQuery(const vector<float>& query, double radius, string metric) const {
    
    bool maximize; // true for cosine (>= radius)
    bool validMetric = true;

    if (metric == "cosine") {
        maximize = true;
    } 
    else if (metric == "euclidean" || metric == "manhattan") {
        maximize = false;
    } 
    else {
        validMetric = false;
    }

    if (!validMetric) {
        throw invalid_metric("Invalid metric!");
    }

    vector<int> matchingIds;
    // use AVL to traverse
    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->getRoot());

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();

        if (node == nullptr) continue;

        VectorRecord& currentRecord = node->data;
        double score;

        // Calculate the score using the const-overloaded helpers
        if (metric == "euclidean") {
            score = l2Distance(query, *(currentRecord.vector));
        } 
        else if (metric == "manhattan") {
            score = l1Distance(query, *(currentRecord.vector));
        } 
        else { // "cosine"
            score = cosineSimilarity(query, *(currentRecord.vector));
        }

        // Check if the score is within the radius
        bool inRange = false;
        if (maximize) {
            // For cosine, "within radius" means score is >= radius
            if (score >= radius) {
                inRange = true;
            }
        } 
        else {
            // For distance, "within radius" means distance is <= radius
            if (score <= radius) {
                inRange = true;
            }
        }

        if (inRange) {
            matchingIds.push_back(currentRecord.id);
        }

        // Continue traversal
        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }

    // Convert the vector of IDs to a dynamic int array
    int* idArray = new int[matchingIds.size()];
    for (size_t i = 0; i < matchingIds.size(); ++i) {
        idArray[i] = matchingIds[i];
    }

    return idArray;
}

int* VectorStore::boundingBoxQuery(const vector<float>& minBound, const vector<float>& maxBound) const {
    
    vector<int> matchingIds;

    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->getRoot());

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();

        if (node == nullptr) continue;

        VectorRecord& currentRecord = node->data;
        vector<float>* vec = currentRecord.vector;

        bool isInside = true;
        // Check every dimension
        for (int i = 0; i < this->dimension; ++i) {
            // Check if the vector's coordinate is outside the bounds
            if ((*vec)[i] < minBound[i] || (*vec)[i] > maxBound[i]) {
                isInside = false;
                break;
            }
        }

        if (isInside) {
            matchingIds.push_back(currentRecord.id);
        }

        // Continue traversal
        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }

    // Convert the vector of IDs to a dynamic int array
    int* idArray = new int[matchingIds.size()];
    for (size_t i = 0; i < matchingIds.size(); ++i) {
        idArray[i] = matchingIds[i];
    }

    return idArray;
}

// ADVANCED UTILS METHODS
double VectorStore::getMaxDistance() const {
    if (this->empty()) {
        return 0.0;
    }
    const vector<float>* rootCoords = this->rootVector->vector;
    double maxDist = 0.0;

    // use AVL to traverse
    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->root);

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();
        
        if (node == nullptr) continue;

        double dist = l2Distance(*(node->data.vector), *rootCoords);
        if (dist > maxDist) {
            maxDist = dist;
        }

        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }

    return maxDist;
}

double VectorStore::getMinDistance() const {
    if (this->empty()) {
        return 0.0;
    }
    const vector<float>* rootCoords = this->rootVector->vector;
    double minDist = 0.0;

    // use AVL to traverse
    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->root);

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();
        
        if (node == nullptr) continue;

        double dist = l2Distance(*(node->data.vector), *rootCoords);
        if (minDist == 0.0 || dist < minDist) {
            minDist = dist;
        }

        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }

    return minDist;
}

VectorRecord VectorStore::computeCentroid(const vector<VectorRecord*>& records) const {
    int m = records.size();// m is number of vectors
    if (m == 0) {
        return VectorRecord(); // Return default-constructed record
    }

    int d = this->dimension; // d is dimensionality
    vector<double> sumVector(d, 0.0); // Use double for precision

    // Sum all vectors
    for (VectorRecord* rec : records) {
        for (int i = 0; i < d; i++) {
            sumVector[i] += (*(rec->vector))[i];
        }
    }

    // Create the new centroid vector
    vector<float>* centroidVec = new vector<float>();
    centroidVec->reserve(d);

    // Average the sums
    for (int i = 0; i < d; ++i) {
        centroidVec->push_back(static_cast<float>(sumVector[i] / m));
    }

    // Return a new VectorRecord for the centroid
    return VectorRecord(-1, "centroid", centroidVec, 0.0);
}

VectorRecord* VectorStore::findVectorNearestToDistance(double targetDistance) const {
    if (this->empty()) {
        return nullptr;
    }

    VectorRecord* bestRecord = nullptr;
    double minDiff = -1.0; // -1 = not set

    queue<AVLTree<double, VectorRecord>::AVLNode*> q;
    q.push(this->vectorStore->getRoot());

    while (!q.empty()) {
        AVLTree<double, VectorRecord>::AVLNode* node = q.front();
        q.pop();
        if (node == nullptr) continue;

        double currentDiff = fabs(node->data.distanceFromReference - targetDistance);

        if (bestRecord == nullptr || currentDiff < minDiff) {
            minDiff = currentDiff;
            bestRecord = &(node->data);
        }

        if (node->pLeft) q.push(node->pLeft);
        if (node->pRight) q.push(node->pRight);
    }
    return bestRecord;
}

// PRIVATE HELPER IMPLEMENTATIONS

double VectorStore::distanceByMetric(const vector<float>& a, const vector<float>& b, const string& metric) const 
{
    if (metric == "euclidean") {
        return l2Distance(a, b);
    } else if (metric == "manhattan") {
        return l1Distance(a, b);
    } else if (metric == "cosine") {
        return cosineSimilarity(a, b);
    }
    
    throw invalid_metric();
}


// Explicit template instantiation for the type used by VectorStore
template class AVLTree<double, VectorRecord>;
template class AVLTree<double, double>;
template class AVLTree<int, double>;
template class AVLTree<int, int>;
template class AVLTree<double, string>;
template class AVLTree<int, string>;

template class RedBlackTree<double, VectorRecord>;
template class RedBlackTree<double, double>;
template class RedBlackTree<int, double>;
template class RedBlackTree<int, int>;
template class RedBlackTree<double, string>;
template class RedBlackTree<int, string>;




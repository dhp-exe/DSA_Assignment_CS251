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
    AVLNode* newRoot = node->pLeft;
    node->pLeft = newRoot->pRight;
    newRoot->pRight = node;
    return newRoot;
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>:: rotateLeft(AVLNode*& node) {
    AVLNode* newRoot = node->pRight;
    node->pRight = newRoot->pLeft;
    newRoot->pLeft = node;
    return newRoot;
}

// INSERTION
template <class K, class T>
int AVLTree<K, T>::getBalance(AVLNode* node) {
    if (!node) return 0;
    return getHeightHelper(node->pLeft) - getHeightHelper(node->pRight);
}

template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>:: insertNode( AVLNode* node, const K& key, const T& value){
    if(node == nullptr) {
        return new AVLNode(key, value);
    }
    if(key < node->key) {
        node->pLeft = insertNode(node->pLeft, key, value);
    } 
    else if(key > node->key) {
        node->pRight = insertNode(node->pRight, key, value);
    } 
    else { 
        return node; // Duplicate keys
    }

    int balanceFactor = getBalance(node);

    // left left
    if(balanceFactor > 1 && key < node->pLeft->key) {
        return rotateRight(node);
    }
    // right right
    if(balanceFactor < -1 && key > node->pRight->key) {
        return rotateLeft(node);
    }
    // left right
    if(balanceFactor > 1 && key > node->pLeft->key) {
        node->pLeft = rotateLeft(node->pLeft);
        return rotateRight(node);
    }
    // right left
    if(balanceFactor < -1 && key < node->pRight->key) {
        node->pRight = rotateRight(node->pRight);
        return rotateLeft(node);
    }

    return node;

}

template<class K, class T>
void AVLTree<K, T>:: insert(const K& key, const T& value) {
    root = insertNode(root, key, value);
}

//  REMOVAL
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::findMin(AVLNode* node) {
    if (!node || !node->pLeft) return node;
    return findMin(node->pLeft);
}
template <class K, class T>
typename AVLTree<K, T>::AVLNode* AVLTree<K, T>::removeNode(AVLNode* node, const K& key) {
    if (node == nullptr) return nullptr;

    if (key < node->key)
        node->pLeft = removeNode(node->pLeft, key);
    else if (key > node->key)
        node->pRight = removeNode(node->pRight, key);
    else {
        // node found
            // case 1: node with 1 or 0 child
        if (!node->pLeft || !node->pRight) {
            AVLNode* temp = node->pLeft ? node->pLeft : node->pRight;
            if (!temp) {
                delete node;
                return nullptr;
            } 
            else {
                AVLNode* del = node;
                node = temp;
                delete del;
            }
        } 
        else {
            // case 2: node with two children
            AVLNode* minNode = findMin(node->pRight);
            node->key = minNode->key;
            node->data = minNode->data;
            node->pRight = removeNode(node->pRight, minNode->key);
        }
    }

    // rebalance the tree
    if (!node) return node;

    int balance = getBalance(node);

    // Left heavy
    if (balance > 1 && getBalance(node->pLeft) >= 0){
        return rotateRight(node);
    }
    // Right heavy
    if (balance < -1 && getBalance(node->pRight) <= 0){
        return rotateLeft(node);
    }
    // Left Right
    if (balance > 1 && getBalance(node->pLeft) < 0) {
        node->pLeft = rotateLeft(node->pLeft);
        return rotateRight(node);
    }
    // Right Left
    if (balance < -1 && getBalance(node->pRight) > 0) {
        node->pRight = rotateRight(node->pRight);
        return rotateLeft(node);
    }

    return node;
}

template <class K, class T>
void AVLTree<K, T>:: remove(const K& key) {
    root = removeNode(root, key);
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




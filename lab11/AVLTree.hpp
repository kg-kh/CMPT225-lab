#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
struct AVLNode {
    AVLNode<T>* left;
    AVLNode<T>* right;
    int key;
    T data;
    int height;

    AVLNode(int key, const T& value)
        : key(key),
          data(value),
          left(nullptr),
          right(nullptr),
          height(0)
    {}
};

// implement the following functions to make the AVLTree work
// You are allowed to use some helpful functions like std::max or std::sort,
// but not any containers like std::vector or std::map
template <typename T>
class AVLTree {
private:
    AVLNode<T>* root = nullptr;
public:

    //Q1: Basic Height functions

    int getHeight(AVLNode<T>* node) const {
        // TODO: implement this function
        // return 0 if node is null, otherwise node->height
        //throw std::logic_error("not implemented!");
        if ( node == nullptr) return 0;
        return node->height;
    }

    void updateHeight(AVLNode<T>* updateNode) {
        // TODO: implement this function
        //throw std::logic_error("not implemented!");
        if ( updateNode == nullptr) return;

        int LeftH= getHeight(updateNode->left);
        int rightH= getHeight(updateNode->right);

        updateNode->height = std:: max(LeftH, rightH) +1;
    }

    //Q2: rotations

    AVLNode<T>* rotateLeft(AVLNode<T>* node) {
        // TODO: implement this function
        //throw std::logic_error("not implemented!");
        if (node == nullptr) return node;

        AVLNode<T>* newRoot = node-> right;
        AVLNode<T>* temp = newRoot->left;

        newRoot->left = node;
        node->right= temp;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;

    }
    AVLNode<T>* rotateRight(AVLNode<T>* node) {
        // TODO: implement this function
        //throw std::logic_error("not implemented!");
        if (node == nullptr) return node;

    AVLNode<T>* newRoot = node->left;
    AVLNode<T>* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    // update heights
    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
    }
    int getBalance(AVLNode<T> * node) {
        if (node == nullptr) return 0;
        return getHeight(node->left)-getHeight(node->right);
    }

    // Q3: insert and balance

    void insert(int key, const T& data) {
        this->root = insertHelper(this-> root, key, data);
        return;
    }

    AVLNode<T>* insertHelper(AVLNode<T>* insertAtNode, int key, const T& data) {
        // TODO: implement this function
         // BST insert
    if (insertAtNode == nullptr)
        return new AVLNode<T>(key, data);

    if (key < insertAtNode->key)
        insertAtNode->left = insertHelper(insertAtNode->left, key, data);
    else if (key >insertAtNode->key)
        insertAtNode->right = insertHelper(insertAtNode->right, key, data);
    else
        return insertAtNode; // no duplicates

    // update height
    updateHeight(insertAtNode);

    // balance
    return restructure(insertAtNode);
       // throw std::logic_error("not implemented!");
    }

    AVLNode<T>* restructure(AVLNode<T>* restructureAtNode) {
        // TODO: implement this function
        //throw std::logic_error("not implemented!");
         int balance = getBalance(restructureAtNode);

    // LEFT HEAVY
    if (balance > 1) {
        // LL case
        if (getBalance(restructureAtNode->left) >= 0)
            return rotateRight(restructureAtNode);

        // LR case
        restructureAtNode->left = rotateLeft(restructureAtNode->left);
        return rotateRight(restructureAtNode);
    }

    // RIGHT HEAVY
    if (balance < -1) {
        // RR case
        if (getBalance(restructureAtNode->right) <= 0)
            return rotateLeft(restructureAtNode);

        // RL case
        restructureAtNode->right = rotateRight(restructureAtNode->right);
        return rotateLeft(restructureAtNode);
    }

    return restructureAtNode;
    }

};
int main() {
    AVLTree<int> tree;

    // Test 1: RR case (should trigger LEFT rotation)
    tree.insert(10, 10);
    tree.insert(20, 20);
    tree.insert(30, 30);

    std::cout << "Inserted 10, 20, 30 (RR case)\n";

    // Test 2: LL case (should trigger RIGHT rotation)
    tree.insert(5, 5);
    tree.insert(2, 2);

    std::cout << "Inserted 5, 2 (LL case)\n";

    // Test 3: LR case
    tree.insert(8, 8);

    std::cout << "Inserted 8 (LR case)\n";

    // Test 4: RL case
    tree.insert(25, 25);

    std::cout << "Inserted 25 (RL case)\n";

    std::cout << "All test cases executed successfully!\n";

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // ── Exercise 1 ─────────────────────────────────────────
    // TODO: implement this function
    Node* sortedArrayToBST(vector<int>& nums, int left, int right) {
        // your code here
    if (left > right) return nullptr;

    int mid = (left + right) / 2;

    Node* node = new Node(nums[mid]);

    node->left = sortedArrayToBST(nums, left, mid - 1);
    node->right = sortedArrayToBST(nums, mid + 1, right);

    return node;
        

        

    }

    // ── Exercise 2 Helpers ─────────────────────────────────
    // TODO: implement these two functions
    // Hint: in a BST, where is the smallest value always located?
    //       where is the largest?
    int findMinRecursive(Node* node) {
        // your code here
        if (node->left == nullptr)
        return node->value;

    return findMinRecursive(node->left);
    }

    int findMaxRecursive(Node* node) {
        // your code here
        if (node->right == nullptr)
        return node->value;

    return findMaxRecursive(node->right);
    }

    // ── Exercise 3 Helper ──────────────────────────────────
    // TODO: implement this function
    // Hint: count(node) = 1 + count(left subtree) + count(right subtree)
    int countNodesRecursive(Node* node) {
        // your code here
        if (node == nullptr)
        return 0;

        return 1 + countNodesRecursive(node->left)
             + countNodesRecursive(node->right);
    }

    // ── DO NOT MODIFY BELOW ────────────────────────────────
    int heightRecursive(Node* node) {
        if (!node) return -1;
        return 1 + max(heightRecursive(node->left), heightRecursive(node->right));
    }

    void inorderRecursive(Node* node, vector<int>& result) {
        if (!node) return;
        inorderRecursive(node->left, result);
        result.push_back(node->value);
        inorderRecursive(node->right, result);
    }

    Node* insertRecursive(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value) node->left = insertRecursive(node->left, value);
        else if (value > node->value) node->right = insertRecursive(node->right, value);
        return node;
    }

    void destroyTree(Node* node) {
        if (!node) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroyTree(root); }

    void insert(int value) { root = insertRecursive(root, value); }

    // ── Exercise 1 public ──────────────────────────────────
    void fromSortedArray(vector<int>& nums) {
        destroyTree(root);
        // your code here
         root = sortedArrayToBST(nums, 0, nums.size() - 1);
    }

    // ── Exercise 2 public ──────────────────────────────────
    int findMin() {
        if (!root) throw runtime_error("Tree is empty");
        // your code here
         return findMinRecursive(root);
    }

    int findMax() {
        if (!root) throw runtime_error("Tree is empty");
        // your code here
        return findMaxRecursive(root);
    }

    // ── Exercise 3 public ──────────────────────────────────
    int countNodes() {
        // your code here
        return countNodesRecursive(root);
    }

    int height() { return heightRecursive(root); }

    vector<int> inorder() {
        vector<int> result;
        inorderRecursive(root, result);
        return result;
    }
};

// ── Tests ────────────────────────────────────────────────────
void testExercise1() {
    cout << "=== Exercise 1: Sorted Array to Balanced BST ===\n";
    struct TestCase { vector<int> input; int maxHeight; };
    vector<TestCase> tests = {
        {{0},                    0},
        {{1, 2},                 1},
        {{-10, -3, 0, 5, 9},    2},
        {{1, 2, 3, 4, 5, 6, 7}, 2},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        BST bst;
        bst.fromSortedArray(tests[i].input);
        bool inorderOk = (bst.inorder() == tests[i].input);
        bool heightOk = (bst.height() <= tests[i].maxHeight);
        if (inorderOk && heightOk) {
            cout << "  Test " << i + 1 << ": PASS\n"; passed++;
        }
        else {
            cout << "  Test " << i + 1 << ": FAIL";
            if (!inorderOk) cout << " (inorder mismatch)";
            if (!heightOk)  cout << " (height=" << bst.height()
                << ", expected <=" << tests[i].maxHeight << ")";
            cout << "\n";
        }
    }
    cout << "  " << passed << "/" << tests.size() << " passed\n\n";
}

void testExercise2() {
    cout << "=== Exercise 2: Find Min and Max ===\n";
    struct TestCase { vector<int> vals; int expectedMin; int expectedMax; };
    vector<TestCase> tests = {
        {{5},             5,   5},
        {{5, 3, 7},       3,   7},
        {{5, 3, 7, 1, 9}, 1,   9},
        {{10, 5, 20, 3},  3,  20},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        BST bst;
        for (int v : tests[i].vals) bst.insert(v);
        bool minOk = (bst.findMin() == tests[i].expectedMin);
        bool maxOk = (bst.findMax() == tests[i].expectedMax);
        if (minOk && maxOk) {
            cout << "  Test " << i + 1 << ": PASS\n"; passed++;
        }
        else {
            cout << "  Test " << i + 1 << ": FAIL";
            if (!minOk) cout << " (min=" << bst.findMin()
                << ", expected=" << tests[i].expectedMin << ")";
            if (!maxOk) cout << " (max=" << bst.findMax()
                << ", expected=" << tests[i].expectedMax << ")";
            cout << "\n";
        }
    }
    cout << "  " << passed << "/" << tests.size() << " passed\n\n";
}

void testExercise3() {
    cout << "=== Exercise 3: Count Nodes ===\n";
    struct TestCase { vector<int> vals; int expected; };
    vector<TestCase> tests = {
        {{},              0},
        {{1},             1},
        {{5, 3, 7},       3},
        {{5, 3, 7, 1, 9}, 5},
        {{1, 2, 3, 4, 5}, 5},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        BST bst;
        for (int v : tests[i].vals) bst.insert(v);
        bool ok = (bst.countNodes() == tests[i].expected);
        if (ok) {
            cout << "  Test " << i + 1 << ": PASS\n"; passed++;
        }
        else {
            cout << "  Test " << i + 1 << ": FAIL"
                << " (got=" << bst.countNodes()
                << ", expected=" << tests[i].expected << ")\n";
        }
    }
    cout << "  " << passed << "/" << tests.size() << " passed\n\n";
}

int main() {
    testExercise1();
    testExercise2();
    testExercise3();
    return 0;
}
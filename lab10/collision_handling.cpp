#include <iostream>
using namespace std;

/*
    Lab 10 - Problem 2: Collision Handling with Separate Chaining

    Scenario:
    You are tracking how many times each book was checked out from a small
    campus help-desk library. Each checkout is represented by a book ID.
    Multiple different book IDs may hash to the same bucket, so you must
    handle collisions correctly.

    In this problem, implement a hash table with separate chaining:
    - the table is an array of bucket heads
    - each bucket stores a singly linked list of nodes
    - each node stores a book ID and its checkout count

    Required operations:
    1. recordCheckout(bookId)
       - If the book already exists, increase its count.
       - Otherwise insert a new node at the front of the correct chain.
    2. getCheckoutCount(bookId, countOut)
       - Search the correct chain and return the count.
    3. removeBook(bookId)
       - Remove the node from its chain if it exists.
    4. bucketSize(index)
       - Return the number of nodes in one bucket.
    5. maxChainLength()
       - Return the largest bucket size in the table.

    Rules:
    - Do not use STL containers.
    - Use the hash function key % capacity.
    - This lab focuses on separate chaining, so collisions are expected.
*/

struct Node {
    int bookId;
    int count;
    Node* next;
};

class CheckoutTable {
private:
    Node** buckets;
    int cap;

public:
    explicit CheckoutTable(int capacity)
        : buckets(nullptr), cap(capacity) {
        // TODO 1:
        // Allocate an array of Node* of length cap.
        // Initialize every bucket head to nullptr.

        buckets = new Node * [cap];
        for (int i = 0; i < cap; i++){
            buckets[i] = nullptr;
        }
    }

    ~CheckoutTable() {
        // TODO 2:
        // Delete every node in every chain.
        // Then delete the buckets array.
        for (int i = 0; i < cap ; i++) {
            Node * curr = buckets[i];
            while ( curr != nullptr){
                Node * temp = curr;
                curr = curr-> next;
                delete temp;
            }
        }
        delete [] buckets;
    }

    int hashIndex(int key) const {
        // TODO 3:
        // Return a non-negative bucket index in [0, cap - 1].
        //return -1;
         return key % cap;
    }

    void recordCheckout(int bookId) {
        // TODO 4:
        // Find the correct bucket.
        // Traverse the chain:
        //   - if bookId already exists, increment count and return
        // If not found:
        //   - create a new node
        //   - set count to 1
        //   - insert it at the front of the chain
        int index = hashIndex(bookId);
        Node* curr = buckets[index];

        while (curr != nullptr) {
            if (curr->bookId == bookId) {
                curr->count++;
                return;
            }
            curr = curr->next;
        }

        Node* newNode = new Node{bookId, 1, buckets[index]};
        buckets[index] = newNode;
    }

    bool getCheckoutCount(int bookId, int& countOut) const {
        // TODO 5:
        // Search the correct bucket.
        // If found, set countOut and return true.
        // Otherwise return false.
        int index = hashIndex(bookId);
        Node* curr = buckets[index];

        while (curr != nullptr) {
            if (curr->bookId == bookId) {
                countOut = curr->count;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool removeBook(int bookId) {
        // TODO 6:
        // Remove the node containing bookId from its chain.
        // Be careful when the node is the first node in the bucket.
        int index = hashIndex(bookId);
        Node* curr = buckets[index];
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->bookId == bookId) {
                if (prev == nullptr) {
                    buckets[index] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    int bucketSize(int index) const {
        // TODO 7:
        // Count how many nodes are stored in buckets[index].
        // return -1;
        int count = 0;
        Node* curr = buckets[index];

        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    int maxChainLength() const {
        // TODO 8:
        // Check every bucket and return the largest bucket size.
        // return -1;

        int maxLen = 0;

        for (int i = 0; i < cap; i++) {
            int size = bucketSize(i);
            if (size > maxLen) {
                maxLen = size;
            }
        }
        return maxLen;
    }

    void printTable() const {
        for (int i = 0; i < cap; i++) {
            cout << "[" << i << "]";
            Node* curr = buckets[i];

            if (curr == nullptr) {
                cout << " empty";
            }

            while (curr != nullptr) {
                cout << " -> (" << curr->bookId << ", " << curr->count << ")";
                curr = curr->next;
            }

            cout << "\n";
        }
    }
};

int main() {
    CheckoutTable table(10);

    int checkouts[] = {10, 20, 30, 1, 11, 21, 31, 20, 11, 30, 42};
    int n = sizeof(checkouts) / sizeof(checkouts[0]);

    for (int i = 0; i < n; i++) {
        table.recordCheckout(checkouts[i]);
    }

    cout << "Table after processing checkouts:\n";
    table.printTable();

    int count = 0;
    if (table.getCheckoutCount(20, count)) {
        cout << "\nBook 20 checkout count: " << count << "\n";
    } else {
        cout << "\nBook 20 not found\n";
    }

    if (table.getCheckoutCount(99, count)) {
        cout << "Book 99 checkout count: " << count << "\n";
    } else {
        cout << "Book 99 not found\n";
    }

    cout << "Remove book 21: " << table.removeBook(21) << "\n";
    cout << "Remove book 77: " << table.removeBook(77) << "\n";
    cout << "Bucket size at index 0: " << table.bucketSize(0) << "\n";
    cout << "Maximum chain length: " << table.maxChainLength() << "\n";

    cout << "\nFinal table:\n";
    table.printTable();

    return 0;
}

#include <iostream>
using namespace std;

/*
    Lab 10 - Problem 1: Hash Table Fundamentals

    Scenario:
    You are building a small score lookup system for a lab section.
    Each student is identified by an integer student ID, and the system
    stores one integer score for that ID.

    In this problem, you will implement a basic hash table using:
    - an array of entries
    - a simple hash function: key % capacity
    - one slot per index

    To keep the focus on basic hash table operations, this file does NOT
    handle collisions. If two different keys map to the same index, the
    insertion should fail and return false.

    Tasks:
    1. Implement the constructor and destructor.
    2. Implement the hash function.
    3. Implement insert/update, search, remove, and loadFactor.
    4. Use the provided driver to test your table.

    Rules:
    - Do not use STL containers.
    - A slot is either empty or occupied.
    - If insertOrUpdate is called with an existing key, update its score.
    - If insertOrUpdate is called with a different key that hashes to an
      occupied slot, return false.
*/

struct Entry {
    int key;
    int value;
    bool occupied;
};

class ScoreTable {
private:
    Entry* table;
    int cap;
    int used;

public:
    explicit ScoreTable(int capacity)
        : table(nullptr), cap(capacity), used(0) {
        // TODO 1:
        // Allocate the array of Entry objects.
        // Mark every slot as unoccupied.
        table = new Entry[cap];
        for (int i = 0; i < cap; i++) {
            table[i].occupied = false;
        }
    }

    ~ScoreTable() {
        // TODO 2:
        // Free the dynamically allocated array.
         delete[] table;
    }

    int hashIndex(int key) const {
        // TODO 3:
        // Return a non-negative index in the range [0, cap - 1].
        // return -1;
                return key % cap;

    }

    bool insertOrUpdate(int studentId, int score) {
        // TODO 4:
        // Compute the hashed index.
        // If the slot is empty:
        //   - store the key and value
        //   - mark it occupied
        //   - increase used
        //   - return true
        // If the slot already stores the same key:
        //   - update the score
        //   - return true
        // If the slot stores a different key:
        //   - return false
        int index = hashIndex(studentId);

        if (!table[index].occupied) {
            table[index].key = studentId;
            table[index].value = score;
            table[index].occupied = true;
            used++;
            return true;
        }

        if (table[index].key == studentId) {
            table[index].value = score;
            return true;
        }

        return false;
    }

    bool getScore(int studentId, int& scoreOut) const {
        // TODO 5:
        // Find the hashed slot.
        // Return true and set scoreOut if the key is present.
        // Otherwise return false.
        int index = hashIndex(studentId);

        if (table[index].occupied && table[index].key == studentId) {
            scoreOut = table[index].value;
            return true;
        }

        return false;
    }

    bool remove(int studentId) {
        // TODO 6:
        // If the hashed slot contains this key:
        //   - mark the slot unoccupied
        //   - decrease used
        //   - return true
        // Otherwise return false.
         int index = hashIndex(studentId);

        if (table[index].occupied && table[index].key == studentId) {
            table[index].occupied = false;
            used--;
            return true;
        }

        return false;
    }

    float loadFactor() const {
        // TODO 7:
        // Return used / cap as a floating-point value.
        // return -1.0f;
        return (float)used / cap;
    }

    void printTable() const {
        for (int i = 0; i < cap; i++) {
            cout << "[" << i << "] ";
            if (table[i].occupied) {
                cout << "ID=" << table[i].key << ", Score=" << table[i].value;
            } else {
                cout << "empty";
            }
            cout << "\n";
        }
    }
};

int main() {
    ScoreTable scores(11);

    cout << boolalpha;

    cout << "Insert 1001 -> 85: " << scores.insertOrUpdate(1001, 85) << "\n";
    cout << "Insert 1003 -> 92: " << scores.insertOrUpdate(1003, 92) << "\n";
    cout << "Insert 1008 -> 76: " << scores.insertOrUpdate(1008, 76) << "\n";
    cout << "Insert 1010 -> 88: " << scores.insertOrUpdate(1010, 88) << "\n";
    cout << "Insert 1015 -> 95: " << scores.insertOrUpdate(1015, 95) << "\n";

    cout << "\nTable after initial inserts:\n";
    scores.printTable();

    cout << "\nUpdate 1008 -> 80: " << scores.insertOrUpdate(1008, 80) << "\n";

    int score = 0;
    if (scores.getScore(1008, score)) {
        cout << "Score for 1008: " << score << "\n";
    } else {
        cout << "1008 not found\n";
    }

    cout << "Remove 1003: " << scores.remove(1003) << "\n";
    cout << "Remove 9999: " << scores.remove(9999) << "\n";
    cout << "Load factor: " << scores.loadFactor() << "\n";

    cout << "\nFinal table:\n";
    scores.printTable();

    return 0;
}

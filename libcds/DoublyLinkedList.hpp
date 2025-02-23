// =================================================================
// DoublyLinkedList.h
//  Description     Definition of Doubly Linked List class
//  Date            2025.02.22
//  Author          jtpeller
// =================================================================

#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <cstddef>
#include <iostream>
#include <mutex>

/**
 * DoublyLinkedList - Class to create a doubly linked list.
 * Features:
 *      Templated data type
 *      Thread safe using mutexes
 *      List operations (insert, indexOf, remove, print, etc.)
 *      Destructor
 */
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t len;
    mutable std::mutex mtx;

public:
    // returned for not found in indexOf
    const size_t npos = static_cast<size_t>(-1);

    // initialization list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // destructor definition
    ~DoublyLinkedList() {
        std::lock_guard<std::mutex> lock(mtx);
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // returns whether the value exists in the list.
    bool has(const T& value) const {
        std::lock_guard<std::mutex> lock(mtx);
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // returns the index of the value. If it is not found, returns -1
    size_t indexOf(const T& value) const {
        std::lock_guard<std::mutex> lock(mtx);
        Node* current = head;
        size_t index = 0;
        while (current) {
            if (current->data == value) {
                return index;
            }
            index++;
            current = current->next;
        }
        return npos;
    }

    // appends a node to the beginning of the list. Beginning is chosen as default for O(1) insertions.
    void insert(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        Node* newNode = new Node(value);

        // two possibilities: list is empty, or has elements.
        if (!head) {
            // list is empty
            head = tail = newNode;
        }
        else {
            // list not empty
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        len++;

        return;
    }

    // inserts value at a specified "index". Index is simply a count.
    bool insertAt(size_t index, const T& value) {
        // initialize
        std::lock_guard<std::mutex> lock(mtx);
        Node* newNode = new Node(value);

        // insert as normal. don't use insert because list is already locked!
        if (index == 0) {
            // update new node
            newNode->next = head;
            newNode->prev = nullptr; // no previous node

            // update head
            head->prev = newNode;
            head = newNode;

            // update size & return success
            len++;
            return true;
        }

        // traverse to index
        Node* current = head;
        for (size_t i = 0; current && i < index - 1; ++i) {
            current = current->next;
        }

        // insert if OK
        if (current) {
            // update next ptrs
            newNode->next = current->next; // set newNode's next to next
            current->next = newNode;       // set current's next to newNode.

            // update prev ptrs. only set next's prev if next isn't null!
            newNode->prev = current;
            if (newNode->next) {
                newNode->next->prev = newNode;
            }

            len++;
            return true;
        }

        // index is out of bounds, delete new node!
        delete newNode;
        return false;
    }

    // prints the list, separated by spaces.
    void print() const {
        std::lock_guard<std::mutex> lock(mtx);
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // removes the specified value. This removes the first value found, not all instances.
    bool remove(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    // update previous node's next to current's next
                    current->prev->next = current->next;
                }
                if (current->next) {
                    // update next node's prev to current's prev
                    current->next->prev = current->prev;
                }

                head = current->next;
                delete current;
                len--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // returns the size of the list.
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return len;
    }
};

#endif // DOUBLY_LINKED_LIST_HPP

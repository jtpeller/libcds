// =================================================================
// LinkedList.hpp
//  Description     Definition & Implementation of LinkedList
//  Date            2025.02.15
//  Author          jtpeller
// =================================================================

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>
#include <iostream>
#include <mutex>

/**
 * LinkedList - Class to create a singly linked list.
 * Features:
 *      Templated data type
 *      Thread safe using mutexes
 *      List operations (insert, indexOf, remove, print, etc.)
 *      Destructor
 */
template <typename T> class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t len;
    mutable std::mutex mtx;

public:
    // returned when index is not found for indexOf();
    const size_t npos = static_cast<size_t>(-1);

    // default with nullptr head.
    LinkedList() : head(nullptr) {}

    // Destroys the linked list
    ~LinkedList() {
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

        // not found, return size_t(-1)
        return npos;
    }

    // appends a node to the beginning of the list. Beginning is chosen as default for O(1) insertions.
    void insert(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        len++;
        return;
    }

    // inserts value at a specified "index". Index is simply a count.
    bool insertAt(size_t index, const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        Node* newNode = new Node(value);

        // insert as normal, but don't use insert bc of mutex
        if (index == 0) {
            newNode->next = head;
            head = newNode;
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
            newNode->next = current->next;  // set newNode's next to next
            current->next = newNode;        // set current's next to newNode.
            len++;
            return true;    // successful insertion
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
        Node* prev = nullptr;
        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                delete current;
                len--;
                return true;
            }
            prev = current;
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

#endif // LINKED_LIST_HPP

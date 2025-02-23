// =================================================================
// LinkedList.test.cpp
//  Description     Unit tests for LinkedList
//  Date            2025.02.22
//  Author          jtpeller
// =================================================================

#include "LinkedList.hpp"
#include <iostream>
#include <thread>
#include <cassert>

// define macro for removal (value itself doesn't matter)
#ifndef REMOVAL_VALUE
#define REMOVAL_VALUE 420
#endif

class TestLinkedList {

private:
    // tests has()
    static void testHas() {
        LinkedList<int> list;
        for (size_t i = 0; i < 10; ++i) {
            list.insert(i);
        }
        for (size_t i = 5; i < 10; ++i) {
            assert(list.has(i));
        }
    }

    // tests indexOf()
    static void testIndexOf() {
        // initialize list
        LinkedList<int> list;
        size_t size = 10;
        for (size_t i = 0; i < size; ++i) {
            list.insert(i);
        }

        // execute search. Recall insertions are always at the front!
        for (size_t i = 0; i < size; ++i) {
            assert(list.indexOf(i) == (size - (i + 1)));
        }
    }

    // tests size()
    static void testSize() {
        // inits
        LinkedList<int> list;
        size_t size = 10;

        // verify size is updated after every insert
        for (size_t i = 1; i <= size; ++i) {
            list.insert(i);
            assert(list.size() == i);
        }
        assert(list.size() == size);

        // verify size is updated after every remove
        for (size_t i = 1; i <= size; ++i) {
            list.remove(i);
            assert(list.size() == (size - i));
        }
        assert(list.size() == 0);
    }

    // tests insert()
    static void testInsert() {
        // inits
        LinkedList<int> list;
        size_t size = 100;

        // execute insertions. verify size and has are correct as well.
        for (size_t i = 1; i <= size; ++i) {
            list.insert(i);
            assert(list.size() == i);
            assert(list.has(i));
        }
    }

    // tests remove()
    static void testRemove() {
        // initialize list
        LinkedList<int> list;
        size_t size = 20;
        for (size_t i = 0; i < size; ++i) {
            list.insert(i);
        }

        // execute removal, and ensure value is removed and size is updated.
        for (size_t i = 1; i <= (size / 2); ++i) {
            assert(list.remove(i));
            assert(!list.has(i));
            assert(list.size() == (size - i));
        }
    }

    // tests insertAt()
    static void testInsertAt() {
        // initialize list
        LinkedList<int> list;
        list.insert(50);
        list.insert(60);

        // insert at some other indexes
        assert(list.insertAt(0, 100));
        assert(list.insertAt(2, 200));
        assert(!list.insertAt(6, 300));    // fails due to out of range.

        // ensure has returns properly
        assert(list.has(100));
        assert(list.has(200));
        assert(!list.has(300));

        // ensure index of (on top of has, just for extra checks)
        assert(list.indexOf(100) == 0);
        assert(list.indexOf(200) == 2);
        assert(list.indexOf(300) == list.npos);
    }

    // used for testThreadSafe()
    static void threadInsert(LinkedList<int>* list) {
        list->insert(REMOVAL_VALUE);
        size_t many_times = 200000;
        for (size_t i = 1; i <= many_times; i++) {
            list->insert(REMOVAL_VALUE + i);
        }
    }

    // used for testThreadSafe()
    static void threadRemove(LinkedList<int>* list) {
        list->remove(REMOVAL_VALUE);
    }

    // verifies thread safe property of LinkedList
    static void testThreadSafe() {
        // initialize list
        LinkedList<int> list;
        list.insert(50);
        list.insert(60);

        // create threads
        std::thread t1(threadInsert, &list);
        std::thread t2(threadRemove, &list);

        // join threads
        t1.join();
        t2.join();

        // make assertion
        assert(!list.has(REMOVAL_VALUE));
    }

public:
    void executeTests() {
        std::cout << "=== Testing linked_list.h ===" << std::endl;

        // create threads
        std::thread t1(testHas);
        std::thread t2(testIndexOf);
        std::thread t3(testSize);
        std::thread t4(testInsert);
        std::thread t5(testInsertAt);
        std::thread t6(testRemove);
        std::thread t7(testThreadSafe);

        // don't forget to join!
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();

        std::cout << "=== All tests passed! ===" << std::endl;
    }
};


int main() {
    TestLinkedList test;
    test.executeTests();
    return 0;
}

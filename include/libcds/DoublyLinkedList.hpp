// =================================================================
// DoublyLinkedList.hpp
//  Description     Declaration of DoublyLinkedList
//  Date            2025.02.22
//  Author          jtpeller
// =================================================================

#ifndef CDS_DOUBLYLINKED_HPP
#define CDS_DOUBLYLINKED_HPP

#include <cstddef>
#include <iostream>
#include <libcds/DataStructure.hpp>
#include <mutex>

namespace CDS
{
    /**
     * DoublyLinkedList - Class to create a doubly linked list.
     * Features:
     *      Templated data type
     *      Thread safe using mutexes
     *      List operations (insert, indexOf, remove, print, etc.)
     *      Destructor
     */
    template <typename T>
    class DoublyLinkedList : IList<T>
    {
    private:
        struct Node
        {
            T data;
            Node* next;
            Node* prev;

            Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
        };

        Node* head;
        Node* tail;
        size_t size;
        mutable std::mutex mtx;

    public:
        // returned for not found in indexOf
        const size_t npos = static_cast<size_t>(-1);

        // initialization list
        DoublyLinkedList()
            : head(nullptr), tail(nullptr), size(0)
        {
        }

        // destructor definition
        virtual ~DoublyLinkedList();

        // IDataStructure members
        virtual bool Search(const T& value) override;
        virtual void Print() override;
        virtual bool Remove(const T& value) override;
        virtual void Clear() override;
        virtual size_t Size() override;

        // IList members
        virtual size_t IndexOf(const T& value) override;
        virtual bool Insert(const T& value) override;
        virtual bool Insert(const T& value, size_t index) override;
        virtual T* Get(size_t index) override;
    };
} // namespace CDS

#include <libcds/DoublyLinkedList.tpp>

#endif // CDS_DOUBLYLINKED_HPP

// =================================================================
// LinkedList.hpp
//  Description     Declaration of LinkedList
//  Date            2025.02.15
//  Author          jtpeller
// =================================================================

#ifndef CDS_LINKEDLIST_HPP
#define CDS_LINKEDLIST_HPP

#include <cstddef>
#include <iostream>
#include <libcds/DataStructure.hpp>
#include <mutex>

namespace CDS
{
    /**
     * LinkedList - Class to create a singly linked list.
     * Features:
     *      Templated data type
     *      Thread safe using mutexes
     *      List operations (insert, indexOf, remove, print, etc.)
     *      Destructor
     */
    template <typename T>
    class LinkedList : IList<T>
    {
    private:
        struct Node
        {
            T data;
            Node* next;

            Node(const T& value) : data(value), next(nullptr) {}
        };

        Node* head;
        size_t size;
        mutable std::mutex mtx;

    public:
        // returned when index is not found for indexOf();
        const size_t npos = static_cast<size_t>(-1);

        // default constructor
        LinkedList() : head(nullptr), size(0) {}

        // destructor
        virtual ~LinkedList();

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

#include <libcds/LinkedList.tpp>

#endif // CDS_LINKEDLIST_HPP

// =================================================================
// DoublyLinkedList.tpp
//  Description     Templated Implementation of DoublyLinkedList
//  Date            2025.07.02
//  Author          jtpeller
// =================================================================

#include <libcds/DoublyLinkedList.hpp>

// Destructor deletes each node in the list.
template <typename T>
CDS::DoublyLinkedList<T>::~DoublyLinkedList()
{
    std::lock_guard<std::mutex> lock(mtx);
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Searches for $value in the list.
template <typename T>
bool
CDS::DoublyLinkedList<T>::Search(const T& value)
{
    std::lock_guard<std::mutex> lock(mtx);

    // check edge cases
    // ... list is empty
    if (head == nullptr || size == 0)
        return false;

    // otherwise, traverse, return status.
    Node* current = head;
    while (current)
    {
        if (current->data == value)
            return true;
        current = current->next;
    }
    return false;
}

// Retrieves value at index
template <typename T>
T*
CDS::DoublyLinkedList<T>::Get(size_t index)
{
    std::lock_guard<std::mutex> lock(mtx);

    // check edge cases
    // ... index out of range
    if (index >= size)
        return nullptr;
    // ... list is empty
    if (head == nullptr || size == 0)
        return nullptr;

    // otherwise, index is OK. traverse and retrieve
    Node* current = head;
    size_t count = 0;
    while (count < index)
    {
        current = current->next;
        count++;
    }
    return &current->data;
}

// Searches for value. If found, returns its index. If not found, returns npos.
template <typename T>
size_t
CDS::DoublyLinkedList<T>::IndexOf(const T& value)
{
    std::lock_guard<std::mutex> lock(mtx);

    // handle edge case: list is empty
    if (head == nullptr || size == 0)
        return npos;

    // otherwise, count till its found and return.
    Node* current = head;
    size_t index = 0;
    while (current != nullptr)
    {
        if (current->data == value)
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return npos;
}

// inserts a value at index 0
template <typename T>
bool
CDS::DoublyLinkedList<T>::Insert(const T& value)
{
    return Insert(value, 0);
}

template <typename T>
bool
CDS::DoublyLinkedList<T>::Insert(const T& value, size_t index)
{
    std::lock_guard<std::mutex> lock(mtx);

    // Report failure if index > size
    if (index > size)
        return false;

    // Otherwise define the node.
    Node* newNode = new Node(value);

    // list is empty
    if (head == nullptr)
    {
        head = tail = newNode;
    }
    // index is at the beginning
    else if (index == 0)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    // index is at the end
    else if (index == size)
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    // index is somewhere in the middle
    else
    {
        // traverse to node just before insertion.
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i)
            current = current->next;

        // perform insertion
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;

        // no danglers, just to be safe
        current = nullptr;
    }

    // do not leave newNode dangling
    newNode = nullptr;

    // insertion was successful. increment size & indicate success
    size++;
    return true;
}

// prints the list, separated by spaces
template <typename T>
void
CDS::DoublyLinkedList<T>::Print()
{
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;
    while (current)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// removes the specified value. This removes the first value found, not all
// instances.
template <typename T>
bool
CDS::DoublyLinkedList<T>::Remove(const T& value)
{
    std::lock_guard<std::mutex> lock(mtx);

    // handle edge case (list is empty)
    if (head == nullptr)
        return false;

    // otherwise, remove if possible.
    // traverse to find the node
    Node* current = head;
    while (current != nullptr && current->data != value)
        current = current->next;

    // value is now found. handle removal

    // if it's the head...
    if (current == head)
    {
        // head points to next node
        head = current->next;

        // if it's not nullptr, then its previous should be
        if (head != nullptr)
            head->prev = nullptr;
        // otherwise, list is empty now.
        else
            tail = nullptr;
    }
    // if it's the tail...
    else if (current == tail)
    {
        // move tail to previous
        tail = current->prev;
        if (tail != nullptr)
            tail->next = nullptr;
    }
    // or, it's just a middle node...
    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    // delete, update size, and return
    delete current;
    size--;
    return true;
}

template <typename T>
void
CDS::DoublyLinkedList<T>::Clear()
{
    std::lock_guard<std::mutex> lock(mtx);
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
size_t
CDS::DoublyLinkedList<T>::Size()
{
    std::lock_guard<std::mutex> lock(mtx);
    return size;
}

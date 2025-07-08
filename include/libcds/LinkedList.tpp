// =================================================================
// LinkedList.tpp
//  Description     Template Implementation of LinkedList
//  Date            2025.07.02
//  Author          jtpeller
// =================================================================

#include <libcds/LinkedList.hpp>

// Destructor deletes each node in the list.
template <typename T>
CDS::LinkedList<T>::~LinkedList()
{
    std::lock_guard<std::mutex> lock(mtx);
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Searches for $value in the list.
template <typename T>
bool
CDS::LinkedList<T>::Search(const T& value)
{
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;
    while (current)
    {
        if (current->data == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Retrieves value at index
template <typename T>
T*
CDS::LinkedList<T>::Get(size_t index)
{
    // first check if index is in range
    if (index >= size)
    {
        // index is out of range, return nullptr
        return nullptr;
    }

    // otherwise, index is OK, lock, traverse, and retrieve
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;

    size_t count = 0;
    while (count <= index)
        current = current->next;
    return &current->data;
}

// Searches for value. If found, returns its index. If not found, returns npos.
template <typename T>
size_t
CDS::LinkedList<T>::IndexOf(const T& value)
{
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;
    size_t index = 0;
    while (current)
    {
        if (current->data == value)
        {
            return index;
        }
        index++;
        current = current->next;
    }
    return npos;
}

// Inserts to the beginning of the list.
// Beginning is chosen as default for O(1) insertions.
template <typename T>
bool
CDS::LinkedList<T>::Insert(const T& value)
{
    return Insert(value, 0);
}

template <typename T>
bool
CDS::LinkedList<T>::Insert(const T& value, size_t index)
{
    std::lock_guard<std::mutex> lock(mtx);

    // Report failure if index > size
    if (index > size)
        return false;

    // Otherwise, define the node.
    Node* newNode = new Node(value);

    // list is empty
    if (head == nullptr)
    {
        head = newNode;
    }
    // index is at the beginning
    else if (index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    // otherwise, index is in the middle or at the end
    else
    {
        // traverse to node just before insert
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i)
            current = current->next;

        // perform insertion
        newNode->next = current->next;
        current->next = newNode;
    }

    // insertion was successful. increment size & indicate success
    size++;
    return true;
}

// prints the list, separated by spaces
template <typename T>
void
CDS::LinkedList<T>::Print()
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

// removes the specified value. This removes the first value found, not all instances.
template <typename T>
bool
CDS::LinkedList<T>::Remove(const T& value)
{
    std::lock_guard<std::mutex> lock(mtx);
    Node* current = head;
    Node* prev = nullptr;
    while (current)
    {
        if (current->data == value)
        {
            if (prev)
                prev->next = current->next;
            else
                head = current->next;
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

template <typename T>
void
CDS::LinkedList<T>::Clear()
{
    while (head)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

template <typename T>
size_t
CDS::LinkedList<T>::Size()
{
    std::lock_guard<std::mutex> lock(mtx);
    return size;
}

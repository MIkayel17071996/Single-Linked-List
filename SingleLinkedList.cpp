#include "SingleLinkedList.h"

template <typename T>
SingleLinkedList<T>::SingleLinkedList()
    : m_head(nullptr), m_tail(nullptr), m_size(0)
{
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const T value)
    : m_head(nullptr), m_tail(nullptr), m_size(0)
{
    push_front(value);
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(const T value, const size_t count)
    : m_head(nullptr), m_tail(nullptr), m_size(0)
{
    for (int i = 0; i < count; ++i)
    {
        push_front(value);
    }
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
    clear();
}

template <typename T>
void SingleLinkedList<T>::push_front(T value)
{
    Node *newNode = new Node(value);

    if (m_head == nullptr)
    {
        m_head = m_tail = newNode;
        newNode->m_next = nullptr;
    }
    else
    {
        newNode->m_next = m_head;
        m_head = newNode;
    }
    ++m_size;
}

template <typename T>
void SingleLinkedList<T>::push_back(T value)
{
    Node *newNode = new Node(value);
    newNode->m_next = nullptr;

    if (m_tail == nullptr)
    {
        m_head = m_tail = newNode;
    }
    else
    {
        m_tail->m_next = newNode;
        m_tail = newNode;
    }

    ++m_size;
}

template <typename T>
void SingleLinkedList<T>::pop_front()
{
    if (m_head == nullptr)
    {
        std::cerr << "Cannot do pop_front operation, <The List is empty>" << std::endl;
        return;
    }

    Node *current = m_head;
    m_head = m_head->m_next;

    if (m_head == nullptr)
    {
        m_tail == nullptr;
    }

    delete current;
    --m_size;
}

template <typename T>
void SingleLinkedList<T>::pop_back()
{
    if (m_head == nullptr)
    {
        std::cerr << "Cannot do pop_back operation, <The List is empty>" << std::endl;
        return;
    }

    if (m_head->m_next == nullptr)
    {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
    }
    else
    {
        Node *current = m_head;

        while (current->m_next != m_tail)
        {
            current = current->m_next;
        }

        delete m_tail;
        m_tail = current;
        m_tail->m_next = nullptr;
    }

    --m_size;
}

template <typename T>
void SingleLinkedList<T>::insert(T value, int position)
{
    if (position < 0 || position > m_size)
    {
        std::cerr << "Cannot do Insert operation <The position out of the range>" << std::endl;
        return;
    }

    if (position == 0)
    {
        push_front(value);
        return;
    }

    Node *newNode = new Node(value);
    Node *current = m_head;

    for (int i = 1; i < position; ++i)
    {
        current = current->m_next;
    }

    newNode->m_next = current->m_next;
    current->m_next = newNode;

    if (newNode->m_next == nullptr)
    {
        m_tail = newNode;
    }

    ++m_size;
}

template <typename T>
void SingleLinkedList<T>::erase(int position)
{
    if (position < 0 || position >= m_size)
    {
        std::cerr << "Cannot do Erase operation <The position out of the range>" << std::endl;
        return;
    }

    if (position == 0)
    {
        pop_front();
        return;
    }

    Node *prev = m_head;
    for (int i = 1; i < position; ++i)
    {
        prev = prev->m_next;
    }

    Node *nodeToDelete = prev->m_next;
    prev->m_next = nodeToDelete->m_next;

    if (nodeToDelete == m_tail)
    {
        m_tail = prev;
    }

    delete nodeToDelete;
    --m_size;
}

template <typename T>
bool SingleLinkedList<T>::search(T value) const
{
    if (m_head == nullptr)
    {
        std::cerr << "Cannot do Search operation, <The List is empty>" << std::endl;
        return false;
    }

    Node *current = m_head;

    while (current != nullptr)
    {
        if (current->m_data == value)
        {
            return true;
        }
        current = current->m_next;
    }

    return false;
}

template <typename T>
void SingleLinkedList<T>::printList() const
{
    if (m_head == nullptr)
    {
        std::cerr << "There is noting to print , <The List is empty>" << std::endl;
        return;
    }

    Node *current = m_head;

    while (current != nullptr)
    {
        std::cout << current->m_data << " ";
        current = current->m_next;
    }

    std::cout << std::endl;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return (m_head == nullptr || m_size == 0);
}

template <typename T>
int SingleLinkedList<T>::getSize() const
{
    return m_size;
}

template <typename T>
void SingleLinkedList<T>::clear() noexcept
{
    Node *current = m_head;
    Node *next = current;

    while (current != nullptr)
    {
        next = current->m_next;
        delete current;
        current = next;
    }

    m_head = m_tail = nullptr;
    m_size = 0;
}

template <typename T>
typename SingleLinkedList<T>::Iterator
SingleLinkedList<T>::begin() noexcept
{
    return Iterator(m_head);
}

template <typename T>
typename SingleLinkedList<T>::Iterator
SingleLinkedList<T>::end() noexcept
{
    return Iterator(nullptr);
}

template <typename T>
typename SingleLinkedList<T>::Const_Iterator
SingleLinkedList<T>::cbegin() const noexcept
{
    return Const_Iterator(m_head);
}

template <typename T>
typename SingleLinkedList<T>::Const_Iterator
SingleLinkedList<T>::cend() const noexcept
{
    return Const_Iterator(nullptr);
}

template <typename T>
T &SingleLinkedList<T>::getMidNode()
{
    if (m_head == nullptr)
    {
        throw std::logic_error("EMPTY LIST CANNOT FIND THE MID ELEMENT");
    }

    Node *slow = m_head;
    Node *fast = m_head->m_next;

    while (fast != nullptr && fast->m_next != nullptr)
    {
        fast = fast->m_next->m_next;
        slow = slow->m_next;
    }

    return slow->m_data;
}

template <typename T>
void SingleLinkedList<T>::reverse()
{
    if (m_head == nullptr)
        return;

    Node *prev = nullptr;
    Node *current = m_head;
    Node *next = nullptr;
    m_tail = m_head;

    while (current != nullptr)
    {
        next = current->m_next;
        current->m_next = prev;
        prev = current;
        current = next;
    }

    m_head = prev;
}

template <typename T>
void SingleLinkedList<T>::reverseRecursive(Node *ptr)
{
    if (ptr == nullptr || ptr->m_next == nullptr)
    {
        m_head = ptr; 
        return;
    }

    reverseRecursive(ptr->m_next);
    ptr->m_next->m_next = ptr;

    ptr->m_next = nullptr;
}

template <typename T>
bool SingleLinkedList<T>::isCycled()
{
    Node* slow = m_head;
    Node* fast = m_head;
    
    while (fast != nullptr && fast->m_next != nullptr)
    {

        fast = fast->m_next->m_next;
        slow = slow->m_next;

        if (slow == fast)
        {
            return true;
        }
     
    }

    return false;
    
}

template <typename T>
void SingleLinkedList<T>::merge(SingleLinkedList& other)
{
    Node* tmp;
    while (this->m_head != nullptr && other.m_head != nullptr)
    {
        if (m_head -> m_data <= other.m_head->m_data)
        {
            tmp->m_data = this->m_head->m_data;
            tmp = tmp->m_next;
            this->m_head = this->m_head->m_next;
        } else {
            tmp->m_data = other.m_head->m_data;
            tmp = tmp->m_next;
            other.m_head = other.m_head->m_next;
        }
    }

    while (this->m_head != nullptr)
    {
        tmp->m_data  = this->m_head->m_data;
        tmp = tmp->m_next;
        this->m_head = this->m_head->m_next;
    }
    

     while (other.m_head != nullptr)
    {
        tmp->m_data = other.m_head->m_data;
        tmp = tmp->m_next;
        other.m_head = other.m_head->m_next;
    }
    
    m_size += other.m_size;
}

//template <typename T>


////////////////////ITERATORS///////////////////////////
///////////////////BASE ITERATOR////////////////////////
template <typename T>
SingleLinkedList<T>::BaseIterator::BaseIterator(Node *other)
    : m_node(other)
{
}

template <typename T>
SingleLinkedList<T>::BaseIterator ::BaseIterator(const BaseIterator &other)
    : m_node(other.m_node)
{
}

template <typename T>
bool SingleLinkedList<T>::BaseIterator ::operator==(const BaseIterator &other) const
{
    return m_node == other.m_node;
}

template <typename T>
bool SingleLinkedList<T>::BaseIterator ::operator!=(const BaseIterator &other) const
{
    return m_node != other.m_node;
}

///////////////////CONST ITERATOR////////////////////////
template <typename T>
SingleLinkedList<T>::Const_Iterator::Const_Iterator()
    : BaseIterator(nullptr)
{
}

template <typename T>
SingleLinkedList<T>::Const_Iterator::Const_Iterator(Node *node)
    : BaseIterator(node)
{
}

template <typename T>
const typename SingleLinkedList<T>::Const_Iterator &
SingleLinkedList<T>::Const_Iterator::operator=(const Const_Iterator &other)
{
    if (this != &other)
    {
        this->m_node = other.m_node;
    }
    return *this;
}

template <typename T>
const T &SingleLinkedList<T>::Const_Iterator::operator*() const
{
    return (this->m_node->m_data);
}

template <typename T>
const T *SingleLinkedList<T>::Const_Iterator::operator->() const
{
    return &(this->m_node->m_data);
}

template <typename T>
const typename SingleLinkedList<T>::Const_Iterator &
SingleLinkedList<T>::Const_Iterator::operator++()
{
    this->m_node = this->m_node->m_next;
    return *this;
}

template <typename T>
const typename SingleLinkedList<T>::Const_Iterator &
SingleLinkedList<T>::Const_Iterator::operator++(int)
{
    Const_Iterator temp = *this;
    this->m_node = this->m_node->m_next;
    return temp;
}

////////////////////ITERATOR/////////////////////////////
template <typename T>
SingleLinkedList<T>::Iterator::Iterator()
    : Const_Iterator(nullptr)
{
}

template <typename T>
SingleLinkedList<T>::Iterator::Iterator(Node *node)
    : Const_Iterator(node)
{
}

template <typename T>
typename SingleLinkedList<T>::Iterator &
SingleLinkedList<T>::Iterator::operator=(const Iterator &other)
{
    if (this != &other)
    {
        this->m_node = other.m_node;
    }

    return *this;
}

template <typename T>
T &SingleLinkedList<T>::Iterator::operator*()
{
    return (this->m_node->m_data);
}

template <typename T>
T *SingleLinkedList<T>::Iterator::operator->()
{
    return &(this->m_node->m_data);
}

template <typename T>
typename SingleLinkedList<T>::Iterator &
SingleLinkedList<T>::Iterator::operator++()
{
    this->m_node = this->m_node->m_next;
    return *this;
}

template <typename T>
typename SingleLinkedList<T>::Iterator &
SingleLinkedList<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    this->m_node = this->m_node->m_next;
    return temp;
}
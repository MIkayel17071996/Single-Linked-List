#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include <iostream>
#include <initializer_list>

template <typename T>
class SingleLinkedList
{
private:
    class Node
    {
    public:
        Node(T value)
            : m_data(value), m_next(nullptr)
        {
        }

        T m_data;
        Node *m_next;
    };

public:
    class BaseIterator
    {
        friend class SingleLinkedList<T>;

    protected:
        BaseIterator(Node *);
        BaseIterator(const BaseIterator &);

    public:
        bool operator==(const BaseIterator &) const;
        bool operator!=(const BaseIterator &other) const;

    protected:
        Node *m_node;
    };

    class Const_Iterator : public BaseIterator
    {
        friend class SingleLinkedList<T>;

    public:
        Const_Iterator();
        Const_Iterator(Node *node);
        const Const_Iterator &operator=(const Const_Iterator &other);

        const T &operator*() const;
        const T *operator->() const;

        const Const_Iterator &operator++();
        const Const_Iterator &operator++(int);
    };

    class Iterator : public Const_Iterator
    {
        friend class SingleLinkedList<T>;

    public:
        Iterator();
        Iterator(Node *node);
        Iterator &operator=(const Iterator &other);

        T &operator*();
        T *operator->();

        Iterator &operator++();
        Iterator &operator++(int);
    };

public:
    SingleLinkedList();
    SingleLinkedList(const T value);
    SingleLinkedList(const T value, const size_t count);
    // SingleLinkedList(std::initializer_list<T>);

    ~SingleLinkedList();

public:
    void push_front(T value);
    void push_back(T value);
    void pop_front();
    void pop_back();
    void insert(T value, int position);
    void erase(int position);
    bool search(T value) const;
    void printList() const;
    bool isEmpty() const;
    int getSize() const;
    void clear() noexcept;
    Node* getHead()
    {
        return m_head;
    }

public:
    Iterator begin() noexcept;
    Iterator end() noexcept;
    Const_Iterator cbegin() const noexcept;
    Const_Iterator cend() const noexcept;

public:
    void merge(SingleLinkedList&);
    bool isCycled();
    // sort
    T &getMidNode();
    void reverse();
    void reverseRecursive(Node*);
// private:
    Node *m_head;
    Node *m_tail;
    size_t m_size;

     bool isPalindrome() {
        if (!m_head || !m_head->m_next) return true;

        Node* slow = m_head;
        Node* fast = m_head;

        while (fast && fast->m_next) {
            slow = slow->m_next;
            fast = fast->m_next->m_next;
        }

        Node* secondHalf = reverse(slow);
        Node* firstHalf = m_head;

        Node* tmp = secondHalf;
        bool isPalin = true;
        while (tmp) {
            if (firstHalf->val != tmp->val) {
                return false;
            }
            firstHalf = firstHalf->m_next;
            tmp = tmp->m_next;
        }


        return true;
    }
};

#include "SingleLinkedList.cpp"

#endif // SINGLELINKEDLIST_H

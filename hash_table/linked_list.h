#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// includes
#include <memory>

// bring std namespace into local scope
using namespace std;

template <class T>
class Linked_List
{
private:
    struct Node
    {
        T data;
        unique_ptr<Node> next = nullptr; // pointer to next Node

        Node(const T& data) : data(data) {};
    };
    unique_ptr<Node> head;
    Node* tail = nullptr; // head and tail pointer
    size_t size = 0; // number of nodes
public:

    // Insert a node at the end of the Linked_List
    void append(const T& data)
    {
        // check if list is empty
        if (size == 0)
        {
            // if empty, assign head and tail to new node
            head = make_unique<Node>(data);
            tail = head.get();
        } else
        {
            // otherwise, insert new node after tail
            // and set tail to new node
            tail->next = make_unique<Node>(data);
            tail = tail->next.get();
        }

        // increment size for each new node
        size++;
    }

    // Print the Linked_List to stdout
    void print()
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head.get();

        // iterate through Linked_List
        while (cur_node != nullptr)
        {
            // print cur_node to stdout
            cout << cur_node->data << " -> ";

            // set cur_node to next node
            cur_node = cur_node->next.get();
        }

        // print  // and new line to stdout
        cout << "//\n"; 
    }
};

#endif
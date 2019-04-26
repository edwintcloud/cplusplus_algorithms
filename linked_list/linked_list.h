#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// includes
#include <memory>
#include <vector>
#include <optional>

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

    // Insert a node containing given data at the end of this Linked_List
    template<typename A>
    void append(const A& data)
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

    // Return an array of all the data in this Linked_List
    vector<T> items()
    {
        // make an empty array of list size
        vector<T> result;

        // set cur_node to head of Linked_List
        Node* cur_node = head.get();

        // set each item in array to node data
        while(cur_node != nullptr)
        {
            result.push_back(cur_node->data);
            cur_node = cur_node->next.get();
        }

        // return array
        return result;
    }

    // Find a node in this Linked_List that satisfies the given quality(function returning bool)
    // and return the data from that node
    template<typename Func> T* find(Func quality)
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head.get();

        // iterate through nodes
        while(cur_node != nullptr)
        {
            // check to see if node satisfies quality function
            if (quality(cur_node->data))
            {
                return &cur_node->data;
            }
            // set cur_node to next node
            cur_node = cur_node->next.get();
        }

        // return nullptr if not found
        return nullptr;
    }

    // Remove the node containing the given data from this Linked_List
    bool remove(const T& data)
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head.get();

        // keep track of the previous node with prev_node
        Node* prev_node = nullptr;

        // iterate through each node in the Linked_List
        while(cur_node != nullptr)
        {
            // if we find the node with given data
            if(cur_node->data == data)
            {
                // if the cur_node is the head of the Linked_List
                if(cur_node == head.get())
                {
                    // update head to next node
                    // IMPORTANT: Here we are releasing the ownership of cur_node next
                    // from it's unique_ptr. If we didn't use reset to assign the pointer
                    // to head (another unique_ptr) and forgot to delete, this would cause
                    // a memory leak!
                    head.reset(cur_node->next.release());
                    // set cur_node next to nullptr
                    // cur_node->next = nullptr;
                } else if(cur_node == tail) // or if cur_node is the tail
                {
                    // set prev_node->next to nullptr
                    prev_node->next = nullptr;
                    // set tail to prev_node
                    tail = prev_node;
                } else // otherwise
                {
                    // set prev_node next to cur_node next (skipping node)
                    // IMPORTANT: See above.
                    prev_node->next.reset(cur_node->next.release());
                    // set cur_node next to nullptr
                    cur_node->next = nullptr;
                }

                // decrement size for each node removed
                size--;
                
                // return true if successful
                return true;
            }

            // move to next node
            prev_node = cur_node;
            cur_node = cur_node->next.get(); 
        }

        // return false if node was not found
        return false;
    }

    // Print this Linked_List to stdout
    void print()
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head.get();

        // iterate through Linked_List
        while (cur_node != nullptr)
        {
            // print cur_node to stdout
            printf("%s -> ", cur_node->data.c_str());

            // set cur_node to next node
            cur_node = cur_node->next.get();
        }

        // print  // and new line to stdout
        cout << "//\n"; 
    }
};

#endif
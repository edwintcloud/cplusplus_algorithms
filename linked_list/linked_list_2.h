#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// includes
#include <vector>

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next; // pointer to next Node

        // constructor
        Node(const T& data) : data(data), next(nullptr) {};
    };
    Node *head, *tail; // head and tail pointer
    size_t size; // number of nodes

public:

    // constructor
    LinkedList() : head(nullptr), tail(nullptr), size(0) {};

    // destructor
    ~LinkedList() 
    {
        Node* curNode;
        while(head != nullptr) {
            curNode = head;
            head = head->next;
            delete curNode;
        }
    }

    // Insert a node containing given data at the end of this Linked_List
    template<typename A>
    void append(const A& data)
    {
        // create the new node (allocates memory)
        Node* newNodePtr = new Node(data);

        // check if list is empty
        if (size == 0)
        {
            // if empty, assign head and tail to new node
            head = newNodePtr;
            tail = newNodePtr;
        } else
        {
            // otherwise, set tail next to point to new node
            // and update the tail to new node
            tail->next = newNodePtr;
            tail = newNodePtr;
        }

        // increment size for each new node
        size++;
    }

    // Return an array of all the data in this Linked_List
    std::vector<T> items()
    {
        // make an empty vector
        std::vector<T> result;

        // set cur_node to head of Linked_List
        Node* cur_node = head;

        // set each item in array to node data
        while(cur_node != nullptr)
        {
            result.push_back(cur_node->data);
            cur_node = cur_node->next;
        }

        // shrink vector to save memory
        result.shrink_to_fit();

        // return vector
        return result;
    }

    // Find a node in this Linked_List that satisfies the given quality(function returning bool)
    // and return the data from that node
    template<typename Func> T* find(Func quality)
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head;

        // iterate through nodes
        while(cur_node != nullptr)
        {
            // check to see if node satisfies quality function
            if (quality(cur_node->data))
            {
                return &cur_node->data;
            }
            // set cur_node to next node
            cur_node = cur_node->next;
        }

        // return nullptr if not found
        return nullptr;
    }

    // Remove the node containing the given data from this Linked_List
    bool remove(const T& data)
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head;

        // keep track of the previous node with prev_node
        Node* prev_node = nullptr;

        // iterate through each node in the Linked_List
        while(cur_node != nullptr)
        {
            // if we find the node with given data
            if(cur_node->data == data)
            {
                Node *curNodeNextPtr = cur_node->next;

                // if the cur_node is the head of the Linked_List
                if(prev_node == nullptr)
                {
                    // update head to point to next node
                    head = curNodeNextPtr;
                } else // otherwise
                {
                    // set prev_node next to point to cur_node next (skipping cur_node node)
                    prev_node->next = curNodeNextPtr;
                }

                // IMPORTANT: Here we must delete cur_node to prevent a memory leak!
                delete cur_node;

                // decrement size for each node removed
                size--;
                
                // return true if successful
                return true;
            }

            // move to next node
            prev_node = cur_node;
            cur_node = cur_node->next; 
        }

        // return false if node was not found
        return false;
    }

    // Print this Linked_List to stdout
    void print()
    {
        // set cur_node to head of Linked_List
        Node* cur_node = head;

        // iterate through Linked_List
        while (cur_node != nullptr)
        {
            // print cur_node to stdout
            printf("%s -> ", cur_node->data.c_str());

            // set cur_node to next node
            cur_node = cur_node->next;
        }

        // print  // and new line to stdout
        std::cout << "//\n"; 
    }
};

#endif
//===================================================================
// File: unrolled_linked_list.h
//
// Desc: Unrolled Linked List Class and Implementation.
//
// Copyright © 2019 Edwin Cloud. All rights reserved.
//===================================================================

#ifndef UNROLLEDLINKEDLIST_H
#define UNROLLEDLINKEDLIST_H

//-------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------


template <class T>
class Unrolled_Linked_List
{
private:
    struct Node
    {
        T data;
        struct Node *next; // pointer to next Node
        Node(const T& data) : data(data) {};
    }
    struct Block
    {
        struct Node *head;
    }
    struct Node *head;
    size_t block_size = 0;
    size_t size = 0;
public:
    // Insert a node containing given data in this Unrolled_Linked_List.
    template<typename A>
    void insert(const A& data)
    {
        
    }
};


#endif
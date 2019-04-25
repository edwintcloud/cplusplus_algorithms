#ifndef BUFFER_H
#define BUFFER_H

#include <memory>
#include <mutex>

// bring std namespace into local scope
using namespace std;

// We will implement the buffer with a templated class so the buffer
// can be an array of any defined type
template <class T>
class Circular_Buffer
{
private:
    mutex buffer_mutex; // we will use a mutex for thread safety
    unique_ptr<T[]> buffer; // using a smart pointer is safer (and we don't have to implement a destructor)
    size_t head = 0; // size_t is an unsigned long
    size_t tail = 0;
    size_t max_size;
    T empty_item;
public:
    // size must be explicitly specified
    // here we use a member initialization list to initialize values
    explicit Circular_Buffer<T>(size_t max_size) : 
        buffer(unique_ptr<T[]>(new T[max_size])), max_size(max_size) {};

    void enqueue(T item) 
    {

        // lock class data with mutex
        lock_guard<mutex> lock(buffer_mutex);

        // [TODO] if buffer is full, throw an error
        if(is_full()) return;

        // insert item at back of buffer
        buffer[tail] = item;

        // increment tail
        tail = (tail + 1) % max_size;
        
    }

    T dequeue() {
        
        // lock class data with mutex
        lock_guard<mutex> lock(buffer_mutex);

        // [TODO] if buffer is empty, throw an error
        if(is_empty()) return empty_item;

        // get item at head
        T item = buffer[head];

        // set item at head to null
        T empty;
        buffer[head] = empty_item;

        // move head foward
        head = (head + 1) % max_size;

        // return item
        return item;
    }
    
    T front() 
    {
        
        // return item at head
        return buffer[head];

    }

    void reset() 
    {
        
        // lock class data with mutex
        lock_guard<mutex> lock(buffer_mutex);

        // set head equal to tail
        head = tail;

    }

    bool is_empty() const 
    {

        // buffer is empty when head == tail
        return head == tail;
        
    }

    bool is_full() const 
    {

        // buffer is full when tail is one before the head
        return tail == (head - 1) % max_size;
        
    }
 
    size_t size() const 
    {

        if (tail >= head) return tail - head;
        return max_size - head - tail;

    }
};
#endif
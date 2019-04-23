#include <cstdio>
#include <memory>
#include <mutex>

// bring std namespace into local scope
using namespace std;

// Definition

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
    explicit Circular_Buffer<T>(size_t max_size);
    void enqueue(T item);
    T dequeue();
    T front();
    void reset();
    bool is_empty() const;
    bool is_full() const;
    size_t size() const;
};

// Implementation

template<class T>
Circular_Buffer<T>::Circular_Buffer(size_t max_size) 
{
    buffer = unique_ptr<T[]>(new T[max_size]);
    this->max_size = max_size;
}

template<class T>
void Circular_Buffer<T>::enqueue(T item) 
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

template<class T>
T Circular_Buffer<T>::dequeue() {
    
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

template<class T>
T Circular_Buffer<T>::front() 
{
    
    // return item at head
    return buffer[head];

}

template<class T>
void Circular_Buffer<T>::reset() 
{
    
    // lock class data with mutex
    lock_guard<mutex> lock(buffer_mutex);

    // set head equal to tail
    head = tail;

}

template<class T>
bool Circular_Buffer<T>::is_empty() const 
{

    // buffer is empty when head == tail
    return head == tail;
    
}

template<class T>
bool Circular_Buffer<T>::is_full() const 
{

    // buffer is full when tail is one before the head
    return tail == (head - 1) % max_size;
    
}

template<class T>
size_t Circular_Buffer<T>::size() const 
{

    if (tail >= head) return tail - head;
    return max_size - head - tail;

}

// Main Function
int main() {

    Circular_Buffer<uint32_t> cb(10);

    printf("\n === CircularBuffer Test ===\n");
	printf("Size: %zu\n", cb.size());

	uint32_t x = 1;
	printf("Enqueue 1, val: %d\n", x);
	cb.enqueue(x);
    printf("Size: %zu\n", cb.size());
    x = 2;
	printf("Enqueue 1, val: %d\n", x);
	cb.enqueue(x);
    printf("Size: %zu\n", cb.size());
	printf("Enqueue 1, val: %d\n", x);
	cb.enqueue(x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
    x = cb.dequeue();
	printf("Dequeue: %d\n", x);
    printf("Size: %zu\n", cb.size());
	printf("Empty: %d\n", cb.is_empty());

 }
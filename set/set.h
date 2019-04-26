#ifndef SET_H
#define SET_H

#include <memory>
#include <vector>
#include <functional>
#include "../linked_list/linked_list.h"

template<class T>
class Set
{
private:
    vector<unique_ptr<Linked_List<T>>> buckets;
    size_t _size = 0; // number of items in the set
    size_t _intial_num_buckets = 11; // initial number of buckets

    // Returns bucket index for specified entry.
    size_t _get_index(T entry)
    {
        // generate hash from entry
        size_t _hash = hash<T>{}(entry);
        // return the remainder of _hash divided by number of buckets
        return _hash % buckets.size();
    }

    // Resizes a set's buckets and rehashes all entries.
    void _resize()
    {
        // compute new bucket size (double the previous size)
        size_t _new_size = buckets.size() * 2;
        // create a temporary copy of all items in the set
        vector<T> _temp_items = items();
        // clear buckets vector, deleting all entries (Linked_List's will be
        // automatically deallocated by unique_ptr's deconstructor)
        buckets.clear();
        // reset size to 0
        _size = 0;
        // iterate new_size number of times
        for(int i = 0; i < _new_size; i++)
        {
            // initialize a unique_ptr to a new Linked_List
            // for each new bucket
            buckets.push_back(unique_ptr<Linked_List<T>>(new Linked_List<T>));
        }
        // add all items from _temp_items back into the set
        for(T entry : _temp_items) add(entry);
    }
public:
    // Default constructor initializes vector of buckets of default size.
    Set()
    {
        // iterate _intial_num_buckets times
        for(int i = 0; i < _intial_num_buckets; i++)
        {
            // initialize a unique_ptr to a new Linked_List
            // for each new bucket
            buckets.push_back(unique_ptr<Linked_List<T>>(new Linked_List<T>));
        }

    };

    // Returns the size of a set.
    size_t size()
    {
        return _size;
    }

    // Returns a vector of all items in a set.
    vector<T> items()
    {
        // create new vector to hold items
        vector<T> _items;

        // iterate through each bucket and add each item 
        // in each bucket to _items
        for(int i = 0; i < buckets.size(); i++)
        {
            for(T entry : buckets[i]->items())
            {
                _items.push_back(entry);
            }
        }

        // return _items
        return _items;
    }

    // Prints a formatted version of a set to stdout.
    void print()
    {
        // iterate through each bucket
        for(int i = 0; i < buckets.size(); i++)
        {
            // print current bucket
            printf("[%i] : ", i);
            // iterate through each entry in current bucket
            for(T entry : buckets[i]->items())
            {
                // print bucket entry (in Linked_List format)
                printf("%s -> ", entry.c_str());
            }
            // print end signal and new line
            printf("//\n");
        }
        // print new line
        printf("\n");
    }

    // Adds an entry to a set.
    void add(T entry)
    {
        // find the bucket that the entry belongs to
        unique_ptr<Linked_List<T>>* bucket = &buckets[_get_index(entry)];
        // try to find the entry in the bucket
        T* bucket_entry = (*bucket)->find([entry](T cur_entry){ return cur_entry == entry; });
        // if entry was not found in bucket
        if(bucket_entry == nullptr)
        {
            // increment size of set
            _size++;
        } else // if entry was found in bucket
        {
            // remove entry from bucket
            (*bucket)->remove(*bucket_entry);
        }
        // append entry to end of bucket
        (*bucket)->append(entry);

        // if load factor exceeds .66, perform a resize
        if(float(_size/buckets.size()) > 0.66) _resize();
    }

    // Removes an entry from a set.
    void remove(T entry)
    {
        // find the bucket that the entry belongs to
        unique_ptr<Linked_List<T>>* bucket = &buckets[_get_index(entry)];
        // try to find the entry in the bucket
        T* bucket_entry = (*bucket)->find([entry](T cur_entry){ return cur_entry == entry; });
        // if entry was found in bucket
        if(bucket_entry != nullptr)
        {
            // remove item from bucket
            (*bucket)->remove(*bucket_entry);
            // decrement size of set
            _size--;
        } else // if entry was not found in bucket
        {
            // throw invalid_argument exception
            throw invalid_argument("E001: Invalid arguments specified for method. Entry was not found in this set.");
        }
    }

    // Returns true if entry is found in a set and false otherwise.
    bool contains(T entry)
    {
        // find the bucket that the entry belongs to
        unique_ptr<Linked_List<T>>* bucket = &buckets[_get_index(entry)];
        // try to find the entry in the bucket
        T* bucket_entry = (*bucket)->find([entry](T cur_entry){ return cur_entry == entry; });
        // if entry was found in bucket, return true
        if(bucket_entry != nullptr) return true;
        // otherwise, return false
        return false;
    }

    // Returns a new set containing all entries from a set and entries from the
    // specified other_set . Sets must be of the same type.
    Set union_(Set& other_set)
    {
        // create new set
        Set<T> result;
        // add all entries from this set to result set
        for(T entry : items()) result.add(entry);
        // add all entries from other_set to result set
        for(T entry : other_set.items()) result.add(entry);
        // return result set
        return result;
    }

    // Returns a new set containing entries from a set and specified other_set
    // that are in both sets. Sets must be of the same type.
    Set intersection_(Set& other_set)
    {
        // create new set
        Set<T> result;
        // if this set has more items than other_set
        if(_size > other_set._size)
        {
            // iterate over entries in this set
            for(T entry : items())
            {
                // if other_set contains the current entry, add
                // entry to result set
                if(other_set.contains(entry)) result.add(entry);

            }
        } else // if other_set has more items than this set
        {
            // iterate over entries in other_set
            for(T entry : other_set.items())
            {
                // if this set contains the current entry, add
                // entry to result set
                if(contains(entry)) result.add(entry);
            }
        }
        // return result set
        return result;
    }

    // Returns a new set containing entries from a set that are not in the specified
    // other_set. Sets must be of the same type.
    Set difference_(Set& other_set)
    {
        // create new set
        Set<T> result;
        // iterate over entries in this set
        for(T entry : items())
        {
            // if current entry is not found in other_set,
            // add entry to result set
            if(!other_set.contains(entry)) result.add(entry);
        }
        // return result set
        return result;
    }

    // Returns true if specified other_set is a subset of a set, otherwise returns false.
    // Sets must be of the same type.
    bool is_subset(Set& other_set)
    {
        // iterate over entries in this set
        for(T entry : items())
        {
            // if current entry is not found in other_set, return false
            if(!other_set.contains(entry)) return false;
        }
        // if all entries from this set are found in other_set, return true
        return true;
    }

    // Overload | operator with union operation for two sets.
    Set operator|(Set& other_set)
    {
        return union_(other_set);
    }

    // Overload & operator with intersection operation for two sets.
    Set operator&(Set& other_set)
    {
        return intersection_(other_set);
    }

    // Overload - operator with difference operation for two sets.
    Set operator-(Set& other_set)
    {
        return difference_(other_set);
    }
};

#endif
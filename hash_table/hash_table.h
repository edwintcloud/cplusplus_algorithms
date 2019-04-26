#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include <vector>
#include <utility>
#include <functional>
#include "../linked_list/linked_list.h"

using namespace std;

template<typename K, typename V>
class Hash_Table
{
private:
    vector<unique_ptr<Linked_List<pair<K, V>>>> buckets;
    size_t _size = 0; // number of key-value entries
protected:

    // Return bucket index for key
    uint8_t get_bucket_index(K key)
    {
        // generate hash
        uint16_t computed_hash = hash<K>{}(key);

        // use hash to find index
        return computed_hash % buckets.size();
    }

    // Resize this Hash Table's buckets and rehash all key-value entries.
    void resize()
    {
        // compute new_size
        size_t new_size = buckets.size() * 2;

        // get all items in Hash Table
        vector<pair<K, V>> table_items = items();

        // clear buckets vector, deleting all unique_ptr
        buckets.clear();

        // reset _size to 0
        _size = 0;

        // create buckets of Linked_List
        for(int i=0; i < new_size; i++)
        {
            // create a unique_ptr to a new Linked_List and
            // add to buckets vector array
            buckets.push_back(unique_ptr<Linked_List<pair<K, V>>>(new Linked_List<pair<K, V>>));
        }
        
        // hash items
        for(int i=0;i < table_items.size();i++)
        {
            set(table_items[i].first, table_items[i].second);
        }
    }

public:

    Hash_Table(size_t num_buckets = 11) 
    {
        // create buckets of Linked_List
        for(int i=0; i < num_buckets; i++)
        {
            // create a unique_ptr to a new Linked_List and
            // add to buckets vector array
            buckets.push_back(unique_ptr<Linked_List<pair<K, V>>>(new Linked_List<pair<K, V>>));
        }
    };

    // Return the size of this Hash Table
    size_t size()
    {
        return _size;
    }

    // Returns vector of all items in this Hash Table.
    vector<pair<K, V>> items()
    {
        vector<pair<K, V>> result;
        for(int i=0;i < buckets.size();i++)
        {
            vector<pair<K,V>> bucket = buckets[i]->items();
            for (int j=0;j < bucket.size(); j++)
            {
                result.push_back(bucket[j]);
            }
        }
        return result;
    }

    // Print the items in this Hash_Table to stdout
    void print()
    {
        for(int i=0;i < buckets.size();i++)
        {
            printf("[%i] : ", i);
            vector<pair<K,V>> bucket = buckets[i]->items();
            for (int j=0;j < bucket.size(); j++)
            {
                printf("{%s:%s} -> ", bucket[j].first.c_str(), bucket[j].second.c_str());
            }
            printf("//\n");
        }
    }

    // Insert or update the given key with the given value
    void set(K key, V value)
    {
        // find the bucket that the given key belongs to
        unique_ptr<Linked_List<pair<K, V>>>* ll = &buckets[get_bucket_index(key)];

        // check first if key exists in ll
        pair<K, V>* entry = (*ll)->find([key](pair<K, V> x){ return x.first == key; });

        // if key was found in ll
        if (entry != nullptr)
        {
            // remove entry from ll
            (*ll)->remove(*entry);
        } else
        {
            // increment size otherwise
            _size++;
        }

        pair<K, V> data = {key, value};

        // insert key-value into Hash_Table in either case
        (*ll)->append(data);

        // if load factor exceeds .66, resize table
        if(float(_size/buckets.size()) > 0.66) resize();
    }

    // Return the value associated with a given key
    V get(K key)
    {
        // find the bucket that the given key belongs to
        unique_ptr<Linked_List<pair<K, V>>>* ll = &buckets[get_bucket_index(key)];

        // find the entry in ll
        pair<K, V>* entry = (*ll)->find([key](pair<K, V> x){ return x.first == key; });

        // return value if not nullptr
        if(entry != nullptr)
        {
            return (*entry).second;
        }

        // throw invalid argument exception if key not found
        throw invalid_argument("E001: Invalid Arguments specified for method. Key was not found in Hash Table.");
    }

    // Remove the given key and its associated value
    void remove(K key)
    {
        // find the bucket that the given key belongs to
        unique_ptr<Linked_List<pair<K, V>>>* bucket = &buckets[get_bucket_index(key)];

        // find the entry in bucket
        pair<K, V>* entry = (*bucket)->find([key](pair<K, V> x){ return x.first == key; });

        // return value if not nullptr
        if(entry != nullptr)
        {
            // remove item from bucket
            (*bucket)->remove(*entry);

            // decrement size for each entry removed
            _size--;

        } else // otherwise
        {
            // throw invalid argument exception if key not found
            throw invalid_argument("E001: Invalid Arguments specified for method. Key was not found in Hash Table.");
        }
        
    }

    // Returns true or false depending on if specified key is found in this Hash Table.
    bool contains(K key)
    {
        // find the bucket that the given key belongs to
        unique_ptr<Linked_List<pair<K, V>>>* bucket = &buckets[get_bucket_index(key)];

        // find the entry in bucket
        pair<K, V>* entry = (*bucket)->find([key](pair<K, V> x){ return x.first == key; });

        // return true if entry is not nullptr
        if(entry != nullptr) return true;

        // otherwise return false
        return false;
    }
};

#endif
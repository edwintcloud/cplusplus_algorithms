#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include <vector>
#include <utility>
#include "../linked_list/linked_list.h"

using namespace std;

template<typename K, typename V>
class Hash_Table
{
private:
    vector<unique_ptr<Linked_List<pair<K, V>>>> buckets;
    size_t size = 0; // number of key-value entries
protected:

    // Return a string hash using Hashing Function (based on djb2 algorithm)
    uint16_t compute_hash(string data)
    {
        // initialize hash to 5381 (8th prime)
        uint16_t hash = 5381;

        // iterate over data string
        for(char& c : data)
        {
            hash = (hash << 5) + hash + int(c);
        }

        // return computed hash
        return hash;
    }

    // Return bucket index for key
    uint8_t get_bucket_index(K key)
    {
        // convert key to string
        string strKey = (string)key;

        // we can use & bitwise to find mod for powers of two
        return compute_hash(strKey) & (buckets.size()-1);
    }

public:

    Hash_Table()
    {
        // create buckets of Linked_List
        for(int i=0;i < 9;i++)
        {
            // create a unique_ptr to a new Linked_List and
            // add to buckets vector array
            buckets.push_back(unique_ptr<Linked_List<pair<K, V>>>(new Linked_List<pair<K, V>>));
        }
    };

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
            size++;
        }

        pair<K, V> data = {key, value};

        // insert key-value into Hash_Table in either case
        (*ll)->append(data);
    }
};

#endif
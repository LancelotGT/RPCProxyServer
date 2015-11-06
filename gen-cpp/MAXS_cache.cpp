#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <boost/unordered_map.hpp>
#include "cache.h"

/* global data section */
static size_t capacity;
static size_t min_entry_size;
static int memused;
static boost::unordered_map<string, string> lookupTable;

class CompareUrl {
public:
    bool operator() (string& url1, string& url2) {
        return lookupTable[url1].size() <= lookupTable[url2].size();
    }
};
static priority_queue<string, vector<string>, CompareUrl> pq;

void cache_init(size_t c, size_t min_size)
{
    capacity = c;
    min_entry_size = min_size;
    memused = 0;
}

int cache_set(const string& key, string& value)
{
    size_t val_size = value.size();
    if (val_size < min_entry_size || val_size > capacity)
    {
        cout << "Cannot push into cache due to size limit" << endl;
        cout << "size: " << val_size << endl;
        return -1;
    }

    /* evict entry if exceeding capacity */
    while (memused + val_size > capacity)
    {
        if (pq.empty()) break;
        string url = pq.top();
        pq.pop();
        int _size = lookupTable[url].size();
        cout << "url: " << url
            << " is evicted due to capacity limit" << endl; 

        /* remove key pairs in lookup table */
        lookupTable.erase(url);
        memused -= _size;
    }         

    /* set the new entry */
    lookupTable[key] = value;
    pq.push(key);
    memused += val_size;

    for (boost::unordered_map<string, string>::iterator it = lookupTable.begin(); it != lookupTable.end(); it++)
         cout << it->first << " " << it->second.size() << endl;
        
    return 0;
}

int cache_get(const string& key, string& response)
{
    if (lookupTable.count(key) == 0)
        return -1;
    response = lookupTable[key];

    for (boost::unordered_map<string, string>::iterator it = lookupTable.begin(); it != lookupTable.end(); it++)
        cout << it->first << " " << it->second.size() << endl; 
    return 0;
}

int cache_memused()
{
    return memused;
}

void cache_destroy()
{
}

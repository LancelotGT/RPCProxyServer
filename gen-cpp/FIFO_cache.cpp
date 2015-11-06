#include <iostream>
#include <stdlib.h>
#include <deque>
#include <boost/unordered_map.hpp>
#include "cache.h"

/* global data section */
static size_t capacity;
static size_t min_entry_size;
static int memused;
static boost::unordered_map<string, string> lookupTable;
static deque<string> queue;

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
        if (queue.empty()) break;
        string url = queue.front();
        queue.pop_front();
        int _size = lookupTable[url].size();

        /* dealloc entries on urls and contents */
        cout << "url: " << url
            << " is evicted due to capacity limit" << endl; 

        /* remote key pairs in lookup table */
        lookupTable.erase(url);
        memused -= _size;
    }         

    /* set the new entry */
    lookupTable[key] = value;
    queue.push_back(key);
    memused += val_size;

    for (deque<string>::iterator it = queue.begin(); it != queue.end(); it++)
         cout << *it << endl;
        
    return 0;
}

int cache_get(const string& key, string& response)
{
    if (lookupTable.count(key) == 0)
        return -1;
    response = lookupTable[key];

    for (deque<string>::iterator it = queue.begin(); it != queue.end(); it++)
         cout << *it << endl;
    return 0;
}

int cache_memused()
{
    return memused;
}

void cache_destroy()
{
}

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <sys/time.h>
#include "cache.h"

class comparator
{   // this is used by arrange stuff in priority queue
public:
    comparator();
    bool operator() (const pair<double, int>& lhs, const pair<double, int>& rhs) const
    {
        return lhs.first < rhs.first;
    }
};


/* global data section */
static size_t capacity;
static size_t min_entry_size;
static int N; /* maximum number of elements in cache */
static int memused;
static string* entries;
static map<string, int>* lookupTable;
static queue<int>* ids;
static priority_queue<pair<double, int>, vector< pair<double, int> >, comparator>* priority;

void cache_init(size_t c, size_t size)
{
    capacity = c;
    min_entry_size = size;
    size = capacity / min_entry_size;

    /* initialize data structure */
    entries = new string[size];
    lookupTable = new map<string, int>();
    ids = new queue<int>();
    for (int i = 0; i < N; i++)
        ids->push(i);
    priority = new priority_queue<pair<double, int>, vector< pair<double, int> >, comparator>;
}

int set(string key, string value, size_t val_size)
{

    if (val_size < min_entry_size)
    {
        cout << "Cannot push into cache due to minimum entry size" << endl;
        return -1;
    }
        
    /* get a new id */
    int id = ids->front();
    /* place the value in the cache entries */
    new (entries + id) string(value);
    /* update the lookup table */
    (*lookupTable)[key] = id;
    /* evict entry if exceeding capacity */
    while (memused + val_size >= capacity)
    {
        pair<double, int> lru = priority->top();
        priority->pop();
        int _id = lru.second;
        string _key = entries[_id];
        entries[_id].~string();
        lookupTable->erase(_key);
    }
    timeval now;
    gettimeofday(&now, NULL);
    double p = now.tv_sec + now.tv_usec / 1000000;
    priority->push(pair<double, int>(p, id));
    return 0;
}

string get(string key, size_t val_size)
{
    return "";
}

int cache_memused()
{
    return memused;
}

void cache_destroy()
{
    delete[] entries;
    delete lookupTable;
    delete ids;
    delete priority;
}

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include <sys/time.h>
#include <time.h>
#include "cache.h"

/* global data section */
static size_t capacity;
static size_t min_entry_size;
static int N; /* maximum number of elements in cache */
static int memused;
static string* contents;
static string* urls;
static map<string, int> lookupTable;
static stack<int> ids;
static list<int> rndq;

static int get_random_id();

void cache_init(size_t c, size_t min_size)
{
    capacity = c;
    min_entry_size = min_size;
    N = capacity / min_entry_size;
    memused = 0;

    /* initialize data structure */
    contents = new string[N];
    urls = new string[N];
    for (int i = N - 1; i >= 0; i--)
        ids.push(i);

    srand(time(NULL));
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
        int _id = get_random_id();
        int _size = contents[_id].size();

        /* dealloc entries on urls and contents */
        cout << "url: " << urls[_id] 
            << " is evicted due to capacity limit" << endl; 

        /* remote key pairs in lookup table */
        lookupTable.erase(urls[_id]);

        /* push the id to be re-used */
        ids.push(_id);
        memused -= _size;
        contents[_id] = "";
        urls[_id] = "";
    }         

    /* set the new entry */
    int id = ids.top();
    ids.pop();
    contents[id] = string(value);
    urls[id] = string(key); 
    lookupTable[key] = id;
    rndq.push_front(id);
    memused += val_size;

    for (int i = 0; i < 10; i++)
        cout<< urls[i] << endl;
    return 0;
}

int cache_get(const string& key, string& response)
{
    if (lookupTable.count(key) == 0)
        return -1;
    int id = lookupTable[key];
    response = contents[id];
    return 0;
}

int cache_memused()
{
    return memused;
}

void cache_destroy()
{
    delete[] contents;
    delete[] urls;
}

static int get_random_id()
{
    int size = rndq.size();
    int ind = rand() % size;
    list<int>::iterator it = rndq.begin();
    for (int i = 0; i < ind; i++)
        it++;
    int id = int(*it);
    rndq.erase(it);
    return id;
}

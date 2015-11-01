/* Define the cache data structure used by proxy
 * Ning Wang
 */

#ifndef __CACHE_H__
#define __CACHE_H__

#include <string>

using namespace std;

void cache_init(size_t capacity, size_t min_entry_size);
int set(string key, string value, size_t val_size);
void* get(string key, size_t* val_size);
int cache_memused();
void cache_destroy();

#endif

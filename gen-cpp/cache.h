/* Define the cache data structure used by proxy
 * Ning Wang
 */

#ifndef __CACHE_H__
#define __CACHE_H__

#include <string>

using namespace std;

void cache_init(size_t capacity, size_t min_entry_size);
int cache_set(const string& key, string& value);
int cache_get(const string& key, string& response);
int cache_memused();
int cache_get_misses();
void cache_destroy();

#endif

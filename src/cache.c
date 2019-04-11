#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "cache.h"
// #include "llist.h"

/**
 * Allocate a cache entry
 */
struct cache_entry *alloc_entry(char *path, char *content_type, void *content, int content_length)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////

    struct cache_entry *new_entry = malloc(sizeof(struct cache_entry));
    new_entry->path = path;
    new_entry->content_type = content_type;
    new_entry->content = content;
    new_entry->content_length = content_length;

    return new_entry;
}

/**
 * Deallocate a cache entry
 */
void free_entry(struct cache_entry *entry)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////

    free(entry);
}

/**
 * Insert a cache entry at the head of the linked list
 */
void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
{
    // Insert at the head of the list
    if (cache->head == NULL) {
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    } else {
        cache->head->prev = ce;
        ce->next = cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Move a cache entry to the head of the list
 */
void dllist_move_to_head(struct cache *cache, struct cache_entry *ce)
{
    printf("move to head\n");
    if (ce != cache->head) {
        if (ce == cache->tail) {
            // We're the tail
            printf("1\n");
            cache->tail = ce->prev;
            printf("2\n");
            cache->tail->next = NULL;
            printf("3\n");

        } else {
            // We're neither the head nor the tail
            printf("4\n");
            ce->prev->next = ce->next;
            printf("5\n");
            ce->next->prev = ce->prev;
            printf("6\n");
        }
        printf("7\n");
        ce->next = cache->head;
        printf("8\n");
        cache->head->prev = ce;
        printf("9\n");
        ce->prev = NULL;
        printf("10\n");
        cache->head = ce;
        printf("move to head done\n");
    }
}


/**
 * Removes the tail from the list and returns it
 * 
 * NOTE: does not deallocate the tail
 */
struct cache_entry *dllist_remove_tail(struct cache *cache)
{
    struct cache_entry *oldtail = cache->tail;

    cache->tail = oldtail->prev;
    cache->tail->next = NULL;

    cache->cur_size--;

    return oldtail;
}

/**
 * Create a new cache
 * 
 * max_size: maximum number of entries in the cache
 * hashsize: hashtable size (0 for default)
 */
struct cache *cache_create(int max_size, int hashsize)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////

    struct cache *cache = malloc(sizeof(struct cache));
    cache->index = hashtable_create(hashsize, NULL);
    cache->max_size = max_size;
    cache->cur_size = 0;
    cache->head = NULL;
    cache->tail = NULL;

    return cache;
}

void cache_free(struct cache *cache)
{
    struct cache_entry *cur_entry = cache->head;

    hashtable_destroy(cache->index);

    while (cur_entry != NULL) {
        struct cache_entry *next_entry = cur_entry->next;

        free_entry(cur_entry);

        cur_entry = next_entry;
    }

    free(cache);
}

/**
 * Store an entry in the cache
 *
 * This will also remove the least-recently-used items as necessary.
 * 
 * NOTE: doesn't check for duplicate cache entries
 */
void cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    printf("cache put\n");

    struct cache_entry *new_entry = alloc_entry(path, content_type, content, content_length);
    dllist_insert_head(cache, new_entry);
    hashtable_put(cache->index, path, new_entry);
    cache->cur_size++;

    if (cache->cur_size > cache->max_size) {
        hashtable_delete(cache->index, cache->tail->path);
        struct cache_entry *old_tail = dllist_remove_tail(cache);
        cache->tail->prev = old_tail->prev->prev;
        free_entry(old_tail);
    }
}

/**
 * Retrieve an entry from the cache
 */
struct cache_entry *cache_get(struct cache *cache, char *path)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    printf("cache get\n");
    printf("%s\n", path);

    struct cache_entry *entry = hashtable_get(cache->index, path);

    if (entry == NULL) {
        printf("return null\n");
        return NULL;
    }

    printf("%s", entry->content);

    dllist_move_to_head(cache, entry);
    return entry;
}

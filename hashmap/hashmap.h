/* A simple hashmap */
#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#define LOAD_FACTOR 0.75

typedef struct hashmap hashmap_t;

/* the hash function to be used on keys */
int hash(int key);

/* init a hashmap */
hashmap_t* hashmap_new();

/* init a hashmap with a backing array that starts with size */
hashmap_t* hashmap_new_with_size(int size);

/* free a hashmap. return -1 on failure and 0 on success */
int hashmap_destroy(hashmap_t* map);

/* insert with a key of k. return -1 on failure */
int hashmap_insert(hashmap_t* map, int k, void* v);

/* lookup the value at k. return NULL if map is NULL or k was not found */
void* hashmap_lookup(hashmap_t* map, int k);

/* return true if the element is in the hashmap or false if map is NULL */
int hashmap_contains(hashmap_t* map, int);

#endif /*__HASHMAP_H__*/

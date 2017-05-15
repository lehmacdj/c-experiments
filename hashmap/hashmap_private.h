#ifndef __HASHMAP_PRIVATE_H__
#define __HASHMAP_PRIVATE_H__

#include "hashmap.h"

#define LOAD_FACTOR 0.75
#define INITIAL_SIZE_MULTIPLIER 2
#define GROWTH_FACTOR 2

typedef enum {
  VALID, /* properly hashed */
  INVALID, /* empty, or once full bucket */
  DELETED, /* no longer in the hashmap */
} bucket_state_t;

typedef struct {
  int k;
  void* v;
  int hash;
  bucket_state_t state;
} bucket_t;

struct hashmap {
  bucket_t* data; /* an array of buckets that backs the hashmap */
  int size; /* the size of the hashmap */
  int capacity; /* the backing size of the array */
  int filled; /* the number of filled (valid, invalid or deleted) entries */
};

/* one line string representing bucket. must be freed */
char* bucket_string(bucket_t bucket);

/* print a representation of map */
void print_hashmap(hashmap_t* map);

#endif /*__HASHMAP_PRIVATE_H__*/

#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "hashmap.h"
#include "hashmap_private.h"

char* bucket_string(bucket_t bucket) {
  char* state;
  switch (bucket.state) {
  case VALID:
    state = "V";
    break;
  case INVALID:
    state = "I";
    break;
  case DELETED:
    state = "D";
    break;
  }

  char* ret;

  asprintf(&ret, "%s(%d, %p)#%d", state, bucket.k, bucket.v, bucket.hash);
  return ret;
}

void print_hashmap(hashmap_t* map) {
  printf("[\n");
  for (int i = 0; i < map->capacity; i++) {
    char* bstr = bucket_string(map->data[i]);
    printf("  %s,\n", bstr);
    free(bstr);
  }
  printf("]\n");
}

/* https://gist.github.com/badboy/6267743 */
int hash32shift(int key) {
  key = ~key + (key >> 15); // key = (key << 15) - key - 1;
  key = key ^ (key >> 12);
  key = key + (key << 2);
  key = key ^ (key >> 4);
  key = key * 2057; // key = (key + (key << 3)) + (key << 11);
  key = key ^ (key >> 16);
  return key;
}

hashmap_t* hashmap_new() {
  return hashmap_new_with_size(10);
}

hashmap_t* hashmap_new_with_size(int size) {
  hashmap_t* new = malloc(sizeof(hashmap_t));
  if (new) {
    new->capacity = size * INITIAL_SIZE_MULTIPLIER;
    new->data = malloc(new->capacity * sizeof(bucket_t));
    if (! new->data) {
      free(new);
      return NULL;
    }
    new->size = 0;
    new->filled = 0;

    /* set all buckets to unused initially */
    for (int i = 0; i < new->capacity; i++) {
      new->data[i].state = INVALID;
    }
  }
  return new;
}

int hashmap_destroy(hashmap_t* map) {
  if (! map) {
    return -1;
  }
  free(map->data);
  free(map);
  return 0;
}

/* rehash a bucket into map */
int put_bucket(hashmap_t* map, int hash, int k, void* v) {
  int index = hash % map->capacity;
  int try = 1;

  /* if we find a INVALID or DELETED bucket it is safe to overwrite it */
  while (map->data[index].state == VALID) {
    if (map->data[index].k == k) {
      /* already in hashmap + valid */
      return -1;
    }
    index = (index + try * try) % map->capacity;
    try++;
  }

  map->data[index].k = k;
  map->data[index].v = v;
  map->data[index].hash = hash;
  map->data[index].state = VALID;
  return 0;
}

int hashmap_insert(hashmap_t* map, int k, void* v) {
  if (! map) {
    return -1;
  }

  /* check that there is sufficient space in the hashmap */
  if ((double)map->filled / (double)map->capacity > LOAD_FACTOR) {
    int old_capacity = map->capacity;
    map->capacity *= GROWTH_FACTOR;
    map->data = realloc(map->data, sizeof(bucket_t) * map->capacity);

    /* initialize new buckets to empty */
    for (int i = old_capacity; i < map->capacity; i++) {
      map->data[i].state = INVALID;
    }

    /* create a temporary copy of valid buckets */
    bucket_t temp[map->size];
    int temp_index = 0;
    for (int i = 0; i < old_capacity; i++) {
      switch (map->data[i].state) {
      case DELETED:
        map->data[i].state = INVALID;
        break;
      case VALID:
        temp[temp_index] = map->data[i];
        temp_index++;
        map->data[i].state = INVALID;
        break;
      case INVALID:
        /* already invalid so do nothing */
        break;
      }
    }
    /* temp_index should be map->size or we have a problem */

    /* rehash the hashmap */
    for (int i = 0; i < map->size; i++) {
        put_bucket(map, temp[i].hash, temp[i].k, temp[i].v);
    }
  }

  int hash = hash32shift(k);
  if (put_bucket(map, hash, k, v)) {
    return -1;
  } else {
    map->size++;
    map->filled++;
    return 0;
  }
}

void* hashmap_lookup(hashmap_t* map, int k) {
  if (! map) {
    return NULL;
  }

  int hash = hash32shift(k);
  int index = hash % map->capacity;
  int try = 1;

  while (map->data[index].state != INVALID) {
    if (map->data[index].k == k && map->data[index].state == VALID) {
      return map->data[index].v;
    }
    index = (index + try * try) % map->capacity;
    try++;
  }

  /* found an empty bucket before finding a bucket with equal key so
   * not in the hashmap */
  return 0;
}

int hashmap_contains(hashmap_t* map, int k) {
  /* normalize the value to 1 or 0 */
  if (hashmap_lookup(map, k)) {
    return 1;
  } else {
    return 0;
  }
}

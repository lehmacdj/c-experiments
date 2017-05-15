#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "hashmap_private.h"

int main(void) {
  hashmap_t* map = hashmap_new_with_size(20);

  for (int i = 0; i < 15; i++) {
    int* z = malloc(sizeof(int));
    *z = i * 5;
    hashmap_insert(map, i, z);
  }

  printf("expecting `n => n * 5` for n in 0..14:\n");
  for (int i = 0; i < 15; i++) {
    printf("%d => %d\n", i, *(int*)hashmap_lookup(map, i));
  }
  printf("\n");


  printf("expecting 15 zeroes:\n");
  for (int i = 15; i < 30; i++) {
    printf("%d", hashmap_contains(map, i));
  }
  printf("\n\n");

  hashmap_destroy(map);

  map = hashmap_new_with_size(5);
  for (int i = 0; i < 10; i++) {
    double* z = malloc(sizeof(int));
    *z = (double)i * 3.14159;
    hashmap_insert(map, i, z);
  }

  printf("expecting: 10 20 10\n");
  printf("%d %d %d\n\n", map->size, map->capacity, map->filled);

  printf("expecting multiples of pi:\n");
  for (int i = 0; i < 10; i++) {
    printf("%f, ", *(double*)hashmap_lookup(map, i));
  }
  printf("\n");

  return 0;
}

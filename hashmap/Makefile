TARGET = hashmap_test

hashmap_test: hashmap.c hashmap_private.h hashmap_test.c hashmap.h
	gcc -g -Wall -std=c99 -Werror hashmap.c hashmap_test.c -o hashmap_test

.PHONY: clean
clean:
	@rm -rf *.dSYM *.o $(TARGET)

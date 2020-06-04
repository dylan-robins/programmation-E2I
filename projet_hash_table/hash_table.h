#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdint.h>

#define KEY_SIZE 20

typedef struct {
    int value;
    char *key;
} tuple_t;

typedef struct {
    tuple_t **table;
    uint32_t length;
    uint32_t capacity;
} hash_table;

// takes a string and returns it's hash
uint32_t hash(const char* str, uint32_t mod);

// creates a hash table of a given size
hash_table *new_hash_table(uint32_t size);

// deletes a given hash table
void delete_hash_table(hash_table *ht);

void set(hash_table *ht, const char *key, int val);
uint32_t search(hash_table *ht, const char *key);
void delete(hash_table *ht, const char *key);

#endif
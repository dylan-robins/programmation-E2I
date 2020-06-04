#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static tuple_t *new_tuple(const char *key, int value) {
    tuple_t *element = (tuple_t *) malloc(sizeof(tuple_t));
    if (element == NULL) {
        exit(EXIT_FAILURE);
    }
    element->value = value;
    element->key = (char *) malloc(KEY_SIZE * sizeof(char));
    strcpy(element->key, key);
    return element;
}

static void delete_tuple(tuple_t *t) {
    free(t->key);
    free(t);
}

hash_table *new_hash_table(uint32_t size) {
    hash_table *ht = (hash_table*) malloc(sizeof(hash_table));
    ht->table = (tuple_t **) calloc(size, sizeof(tuple_t*));
    if (ht->table == NULL) {
        exit(EXIT_FAILURE);
    }
    ht->capacity = size;
    ht->length = 0;
    return ht;
}

void delete_hash_table(hash_table *ht) {
    for (uint32_t i = 0; i < ht->capacity; i++) {
        if (ht->table[i] != NULL) {
            delete_tuple(ht->table[i]);
        }
    }
    free(ht->table);
    free(ht);
}

void set(hash_table *ht, const char *key, int val) {
    uint32_t index = hash(key, ht->capacity);
    if (ht->table[index] == NULL) {
        // add new item
        ht->table[index] = new_tuple(key, val);
        ht->length++;
    } else {
        // update existing item
        ht->table[index]->value = val;
    }
}

uint32_t search(hash_table *ht, const char *key) {
    uint32_t index = hash(key, ht->capacity);
    return ht->table[index]->value;
}

void delete(hash_table *ht, const char *key) {
    uint32_t index = hash(key, ht->capacity);
    delete_tuple(ht->table[index]);
    ht->table[index] = NULL; // reset NULL so that ht deletion doesn't double free
    ht->length--;
}

static uint32_t rotate5l(uint32_t number) {
    uint8_t lsb5 = (number & 0xF8000000) >> 27;
    number = (number << 5) | lsb5;
    return number;
}

uint32_t hash(const char* str, uint32_t mod) {
    uint32_t hashed = 0;
    for (int i = 0; i < 4 && i < strlen(str); i++) {
        hashed |= (str[i] << 8*i);
    }
    for (int i = 4; i < strlen(str); i++) {
        hashed = rotate5l(hashed);
        hashed ^= str[i];
    }
    return hashed % mod;
}
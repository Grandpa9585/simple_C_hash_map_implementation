/*
 * This hashmap will only take in a string key/ value pairs (up to a certain length) 
 * because I do not hate myself nearly enough to implement a generic implementation
 * 
 * Limitations
 * string key/ value pairs
 * O(n) hash function
 * add_pair does nothing to stop duplicates from being added to the list
 * 
 * Other notes/ To do
 * I am certain I can get away with node not being aligned
 * I could probably easily implement a generic value hash table by doing void *
 * make add_pair do something about duplicates
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <inttypes.h>

#define HASH_ARRAY_LEN 100
#define STRING_LEN 128

struct node {
    char *key;
    char *value;
    struct node *next;
};
typedef struct node list_node;

typedef struct {
    /*
     * Hash map is just infact a pointer pointing to the first element of the thing
     * I have no idea how to do an array of linked lists so I opt to do
     * this absolute dogwater implementation
     */
    list_node *head;
    list_node *tail;
} hash_map;

hash_map *current_hash_array = NULL; 

uint32_t hash_function(char *str) {
    /*
     * multiply all of the string's ascii value to get the hash
     * uint32_t since the worst case scenario would be 34 million z's which 
     * is overkill for the purposes of a simple implementation
     */
    uint32_t hash = 1;

    for (char *c = str; *c != 0; c++) { // O(N) soln but who cares
        hash *= (int)*c;                // im not trying to optimize ts anyway
    }

    return hash;
}

void *make_hash_map(void) {
    /*
     * Function allocates in heap an address for the hash map
     * no idea if the malloc is too large
     * returns a reference to hash_map in heap
     */
    hash_map *new_hash_map = malloc(sizeof(hash_map) * HASH_ARRAY_LEN);
    return (void *)new_hash_map;
}

void add_pair(void *user_hash_map, char *key, char *value) {
    /* 
     * This function just adds a key value pair into the given hashmap
     * Please don't put in garbage pointers, I have no idea how to 
     * vet those :')
     * as it stands, there is absolutely no way to know if a func
     * is adding in duplicates
     */
    current_hash_array = (hash_map *)user_hash_map;
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    hash_map *current = current_hash_array + (index * sizeof(hash_map));
    list_node *tmp;
    char *tmp_key, *tmp_value;
                                            // hash collision stuffs
        
    // char *tmp_value;
    // char *tmp_key;           // im going to have to free everything here later on arent I
    // memcpy(tmp_key, key, STRING_LEN);
    // memcpy(tmp_value, value, STRING_LEN);

    tmp = malloc(sizeof(value) + sizeof(key) + sizeof(list_node *));        // make a list node reference

    tmp->key = key;
    tmp->value = value;
    tmp->next = NULL;

    if (current->head == NULL)              // what the fuck is this
        current->head = tmp;
    else {
        if (current->head->next == NULL) 
            current->head->next = tmp;    
        if (current->tail != NULL)
            current->tail->next = tmp;
        current->tail = tmp;
    }

    current_hash_array = NULL;
}

char *get_value(void *user_hash_map, char *key) {
    /*
     * Takes in a reference to a hash map and a key
     * then returns the value if any
     */
    current_hash_array = (hash_map *)user_hash_map;  // repeated code
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    hash_map *current = current_hash_array + (index * sizeof(hash_map));

    list_node *p = current->head;
    while (p != NULL) {
        // printf("comparing %s and %s -> %d\n", p->s.key, key, strcmp(p->s.key, key));
        if (strcmp(p->key, key) == 0) {
            current_hash_array = NULL;
            return p->value;
        }
        p = p->next;
    }
    current_hash_array = NULL;
    return NULL;
}

int change_value(void *user_hash_map, char *key, char *value){
    /*
     * Takes in a reference to a hash map and a key/ value pair
     * then changes the value found in the key
     * return an error if key not found
     */
    current_hash_array = (hash_map *)user_hash_map;  // repeated code
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    hash_map *current = current_hash_array + (index * sizeof(hash_map));

    list_node *p = current->head;
    while (p != NULL) {
        if (strcmp(p->key, key) == 0) {
            current_hash_array = NULL;
            p->value = value;
            return 1;
        }
        p = p->next;
    }
    current_hash_array = NULL;
    return 0;
}

int remove_pair(void *user_hash_map, char *key) {
    /*
     * Takes in a reference to a hash map and a key
     * then dereferences they key value pair
     * will return an error if no such key is found
     */
    current_hash_array = (hash_map *)user_hash_map;  // repeated code
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    hash_map *current = current_hash_array + (index * sizeof(hash_map));
    
    // time to free my three malloc calls :sob:
    list_node *p = current->head;
    list_node *prev = NULL;
    while (p != NULL) {
        if (strcmp(p->key, key) == 0) {
            if (prev == NULL){
                current->head = p->next;
            } else {
                prev->next = p->next;
            }
            // free(p->key);
            // free(p->value);       // ???????
            free(p);
            current_hash_array = NULL;
            return 1;
        }
        prev = p;
        p = p->next;
    }
    current_hash_array = NULL;
    return 0;

}

int delete_hash_table(void *user_hash_map) {
    /*
     * Takes in a reference to a hash map 
     * then dereference the whole table (slow)
     * No idea how to vet non hash_map inputs
     */
    current_hash_array = (hash_map *)user_hash_map;  // repeated code

    hash_map *start = current_hash_array;
    for (hash_map *bucket = user_hash_map; bucket <= start + (HASH_ARRAY_LEN * sizeof(hash_map)); bucket += sizeof(hash_map)) {
        if (bucket->head != NULL) {
            list_node *head = bucket->head;
            for (list_node *p = head; p != NULL; p = p->next) {
                list_node *tmp = p;
                // free(tmp->key);
                // free(tmp->value);
                free(tmp);
            }
        }
    }
    free(current_hash_array);
    current_hash_array = NULL;
    user_hash_map = NULL;
    return 1;
}
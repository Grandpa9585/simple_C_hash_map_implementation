/*
 * This hashmap will only take in a string key/ value pairs (up to a certain length) 
 * because I do not hate myself nearly enough to implement a generic implementation
 * 
 * Limitations
 * string key/ value pairs
 * O(n) hash function
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HASH_ARRAY_LEN 100
#define STRING_LEN 128

union node{
    struct{
        char *key;
        char *value;
        union node *next;
    } s;
    char alignment[2 * STRING_LEN + sizeof(union node *)];
};
typedef union node list_node;

typedef struct {
    /*
     * I have no idea how to do an array of linked lists so I opt to do
     * this absolute dogwater implementation
     */
    list_node *head;
    list_node *tail;
} list_header;

list_header *current_hash_array = NULL; 

uint32_t hash_function(char *str) {
    /*
     * multiply all of the string's ascii value to get the hash
     * uint32_t since the worst case scenario would be 34 million z's which 
     * is overkill for the purposes of a simple implementation
     */
    uint32_t hash = 0;

    for (char *c = str; *c != 0; c++) { // O(N) soln but who cares
        hash *= (int)*c;                // im not trying to optimize ts anyway
    }

    return hash;
}

void *make_hash_map() {
    /*
     * Function allocates in heap an address for the hash map
     * no idea if the malloc is too large
     * returns a reference to hash_map in heap
     */
    list_header *new_hash_map = malloc(sizeof(list_header) * HASH_ARRAY_LEN);
    return (void *)new_hash_map;
}

void add_pair(void *user_hash_map, char *key, char *value) {
    /* 
     * This function just adds a key value pair into the given hashmap
     * Please don't put in garbage pointers, I have no idea how to 
     * vet those :')
     */
    current_hash_array = (list_header *)user_hash_map;
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    list_header *current = current_hash_array + (index * sizeof(list_header));
    list_node *tmp;
    char *tmp_key, *tmp_value;
                                            // hash collision stuffs
    tmp = malloc(sizeof(list_node));        // make a list node reference
        
    tmp_key = malloc(STRING_LEN);           // im going to have to free everything here later on arent I
    tmp_value = malloc(STRING_LEN);
    memcpy(tmp_key, key, STRING_LEN);
    memcpy(tmp_value, value, STRING_LEN);

    tmp->s.key = tmp_key;
    tmp->s.value = tmp_value;
    tmp->s.next = NULL;

    if (current->head == NULL)              // what the fuck is this
        current->head = tmp;
    else {
        if (current->head->s.next == NULL) 
            current->head->s.next = tmp;    
        if (current->tail != NULL)
            current->tail->s.next = tmp;
        current->tail = tmp;
    }

    current_hash_array = NULL;
}

char *get_value(void *user_hash_map, char *key) {
    /*
     * Takes in a reference to a hash map and a key
     * then returns the value if any
     */
    current_hash_array = (list_header *)user_hash_map;  // repeated code
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    list_header *current = current_hash_array + (index * sizeof(list_header));
}

int change_value(void *user_hash_map, char *key, char *value){
    /*
     * Takes in a reference to a hash map and a key/ value pair
     * then changes the value found in the key
     * return an error if key not found
     */
    current_hash_array = (list_header *)user_hash_map;  // repeated code
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    list_header *current = current_hash_array + (index * sizeof(list_header));
}

int remove_pair(void *user_hash_map, char *key) {
    /*
     * Takes in a reference to a hash map and a key
     * then dereferences they key value pair
     * will return an error if no such key is found
     */
    current_hash_array = (list_header *)user_hash_map;  // repeated code
    
    uint32_t hash = hash_function(key);     // hash table magic
    uint32_t index = hash % HASH_ARRAY_LEN;

    list_header *current = current_hash_array + (index * sizeof(list_header));
}

int delete_hash_table(void *user_hash_map) {
    /*
     * Takes in a reference to a hash map 
     * then dereference the whole table (slow)
     */
    current_hash_array = (list_header *)user_hash_map;  // repeated code
}


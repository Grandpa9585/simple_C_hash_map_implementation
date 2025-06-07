#ifndef CHAINED_HASH_MAP_H

#define CHAINED_HASH_MAP_H

typedef struct {
    void *head;
    void *tail;
} hash_map;


void *make_hash_map(void);
void add_pair(void *user_hash_map, char *key, char *value);
char *get_value(void *user_hash_map, char *key);
int change_value(void *user_hash_map, char *key, char *value);  
int remove_pair(void *user_hash_map, char *key);
int delete_hash_table(void *user_hash_map); 


#endif
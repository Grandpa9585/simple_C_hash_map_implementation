#include <stdio.h>
#include "chained_hash_map.h"

int main() {
    hash_map *my_hash_map = make_hash_map();

    add_pair(my_hash_map, "key1", "value1");
    add_pair(my_hash_map, "1key", "value2");
    add_pair(my_hash_map, "k1ey", "value3");
    add_pair(my_hash_map, "test_key", "test_value");

    printf("key: %s, value: %s\n", "key1", get_value(my_hash_map, "key1"));
    printf("key: %s, value: %s\n", "1key", get_value(my_hash_map, "1key"));
    printf("key: %s, value: %s\n", "k1ey", get_value(my_hash_map, "k1ey"));
    printf("key: %s, value: %s\n\n", "test_key", get_value(my_hash_map, "test_key"));

    change_value(my_hash_map, "key1", "1 value");
    change_value(my_hash_map, "1key", "2 value");
    change_value(my_hash_map, "k1ey", "3 value");
    change_value(my_hash_map, "test_key", "4 value");

    printf("key: %s, value: %s\n", "key1", get_value(my_hash_map, "key1"));
    printf("key: %s, value: %s\n", "1key", get_value(my_hash_map, "1key"));
    printf("key: %s, value: %s\n", "k1ey", get_value(my_hash_map, "k1ey"));
    printf("key: %s, value: %s\n\n", "test_key", get_value(my_hash_map, "test_key"));

    remove_pair(my_hash_map, "1key");

    printf("key: %s, value: %s\n", "key1", get_value(my_hash_map, "key1"));
    printf("key: %s, value: %s\n", "1key", get_value(my_hash_map, "1key"));
    printf("key: %s, value: %s\n\n", "k1ey", get_value(my_hash_map, "k1ey"));

}
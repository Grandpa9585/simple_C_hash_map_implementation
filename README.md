This is just made for trying to learn C, how hash tables work, and how to use linked lists

Hash table
    an array of linked lists
    use a hash function to map a key/value pair
    hash func returns a suggested index to store the pair at

hash = hashfunc(key)            independent of the size of the hash table
index = hash % array_size       index = [0, array_size - 1]
    each index is called a "bucket"

hash collisons
    when an index points to two things
    this WILL happen

    Chaining        will be doing this one
        the linked list approach. if two keys map to one hash key, then just put them in the same linked list

        slower than O(1) since you still need to traverse the linked list

    Open Addressing         might do this later on
        if the hash has a collision, then just keep sliding down the list until you find one that's empty
        can cluster


This hashmap will only take in a string key/ value pairs (up to a certain length)  
because I do not hate myself nearly enough to implement a generic implementation  

Limitations  
string key/ value pairs  
O(n) hash function  
add_pair does nothing to stop duplicates from being added to the list  

Other notes/ To do  
(kind of done) I am certain I can get away with node not being aligned  
I could probably easily implement a generic value hash table by doing void *  
make add_pair do something about duplicates  
all functions has no way to vet if there actually exists a hash_map  
error checking and input checking, in general :sob:




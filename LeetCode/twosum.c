struct hash_elem {
    int key;
    int value;
    UT_hash_handle hh; // this makes our structure `hash_elem` hashable within the table managed by uthash.h...
                       // note: This MUST be named `hh`...
};

struct hash_elem* my_hash_map = NULL;

void add_elem(int key, int value) {
    // printf("hash_map is now: %p.\r\n", my_hash_map);
    // lets declare a hash elem pointer.
    struct hash_elem* elem;

    // lets look in our hash_map constructed to see if the element exists. If so - update value for the key.
    HASH_FIND_INT(my_hash_map, &key, elem);
    if (elem == NULL) {
        printf("Adding: key: %d, value: %d.\r\n", key, value);
        // no elem has been found for key. construct & stash.
        elem = (struct hash_elem*)malloc(sizeof(struct hash_elem));
        elem->key = key;
        elem->value = value;
        HASH_ADD_INT(my_hash_map, key, elem); // It appears
        printf("hash_map is now: %p, elem is %p with key: %d\r\n", my_hash_map, elem, key);
        // printf("There are %d elems in the hash_map.\r\n", HASH_COUNT(my_hash_map));
    } else {
        // update the value at the elem found.
        printf("Updating: key: %d, value: %d.\r\n", key, value);
        elem->value = value;
    }
}

struct hash_elem* find_elem_with_key (int key) {
    struct hash_elem* elem = NULL;
    // looks like in order to lookup an item in the HT, we need its key.
    // there is always a 1:1 mapping between key/value pair. so we use the KEY to find the value.
    HASH_FIND_INT(my_hash_map, &key, elem);
    return elem;
}

void delete_elem(struct hash_elem* elem) {
    // allowing user to pass in a hash_map to delete an elem from...
    HASH_DEL(my_hash_map, elem);
    free(elem);
}

void delete_all_elems() {
    struct hash_elem* current_elem;
    struct hash_elem* temp;

    HASH_ITER(hh, my_hash_map, current_elem, temp) {
        delete_elem(current_elem);
    }
}

void print_hash_map() {
    struct hash_elem* elem;

    elem = my_hash_map;
    while (elem != NULL) {
        printf ("Key: %d, Value: %d.\r\n", elem->key, elem->value);
        elem = elem->hh.next; // It appears we can use `hh` to keep going through the HT....
    }
    printf("There are %d elems in the hash_map.\r\n", HASH_COUNT(my_hash_map));
}

//comparison functions...
int by_value(struct hash_elem* a, struct hash_elem* b){
    if (a->value >= b->value) {
        return 1;
    }
    else if (a->value == b->value) {
        return 0;
    }
    else {
        return -1;
    }
}

int by_key(struct hash_elem* a, struct hash_elem* b){
    if (a->key >= b->key) {
        return 1;
    }
    else if (a->key == b->key) {
        return 0;
    }
    else {
        return -1;
    }
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    //I would first do a pass to stash all the numbers in the hashtable...

    int* return_arr = (int*)malloc(sizeof(int)*2); // need to alloc on heap...
    *returnSize = 0; // init returnSize to 0 at first......

    // stash all data into the map...
    for (int i = 0; i < numsSize; i++) {
        // key: value at the index of the array.
        // value: index of the array for value.
        add_elem(nums[i], i);
    }

    // print_hash_map();

    for (int i = 0; i < numsSize; i++) {
        int key_to_search = target - nums[i];
        struct hash_elem* search_elem = find_elem_with_key(key_to_search);
        if (search_elem != NULL && i != search_elem->value) {
            // if we find a value search elem & the index(value) of the search elem != the index(value) of the current elem...
            return_arr[0] = search_elem->value;
            return_arr[1] = i;
            *returnSize = 2;
            delete_all_elems();
            return return_arr;
        }
    }
    
    delete_all_elems();
    
    return NULL;
}

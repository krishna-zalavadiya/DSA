#include <stdio.h>
#include <stdlib.h>

#define SIZE 10      // Initial size of hash table

/*
 * NODE structure:
 * Each index in the hash table stores:
 *   - data : the integer key
 *   - flag : 0 = empty, 1 = occupied
 *
 * This is used for OPEN ADDRESSING (linear probing).
 */
typedef struct node {
    int data;
    int flag;
} NODE;

/*
 * HASH structure:
 *   - size : current size of hash table
 *   - hashTable : dynamically allocated array of NODEs
 */
typedef struct {
    int size;
    struct node *hashTable;
} HASH;

int count = 0;        // Global count of inserted elements

/******************************************************
 * Function: createHash
 * ---------------------
 * Allocates memory for a new hash table.
 * Initializes all flags to 0 (EMPTY slots).
 ******************************************************/
HASH *createHash(int size) {
    HASH *hash = (HASH *)malloc(sizeof(HASH));
    hash->size = size;

    // Allocate the internal array
    hash->hashTable = (NODE *)malloc(size * sizeof(NODE));

    // Mark all slots empty (flag = 0)
    for (int i = 0; i < size; i++) {
        hash->hashTable[i].flag = 0;
    }

    return hash;
}

/******************************************************
 * Function: destroyHash
 * ----------------------
 * Frees heap memory for both:
 *   1. hash table array
 *   2. hash structure
 ******************************************************/
void destroyHash(HASH *hash) {
    free(hash->hashTable);
    free(hash);
}

/******************************************************
 * Function: rehash
 * -----------------
 * Triggered when load factor > 0.75
 * Steps:
 *   1. Create a larger table (size = old*2 + 2)
 *   2. Reinsert ALL elements using new hash function
 *   3. Destroy the old table
 ******************************************************/
void rehash(HASH *h) {
    int newSize = (h->size * 2) + 2;

    // Create new larger hash table
    HASH *newHash = createHash(newSize);

    // Reinsert all elements from old table
    for (int i = 0; i < h->size; i++) {

        // Only reinsert occupied elements
        if (h->hashTable[i].flag == 1) {

            int key = h->hashTable[i].data;
            int j = 0;

            // Compute new hash index using linear probing
            int hash = ((key % newSize) + j) % newSize;

            while (newHash->hashTable[hash].flag != 0) {
                j++;
                hash = ((key % newSize) + j) % newSize;
            }

            // Insert into new table
            newHash->hashTable[hash].data = key;
            newHash->hashTable[hash].flag = 1;
        }
    }

    // Delete old table memory
    destroyHash(h);

    // Replace old table object contents with the new one
    *h = *newHash;
}

/******************************************************
 * Function: search
 * -----------------
 * Searches for a key using LINEAR PROBING.
 * Stops when:
 *   - Key is found
 *   - An empty slot is encountered (means NOT found)
 ******************************************************/
int search(int key, HASH *h) {
    int hash;
    int i = 0;

    // Try at most 'size' times
    while (i < h->size) {

        hash = ((key % h->size) + i) % h->size;

        // If slot occupied AND data matches → FOUND
        if (h->hashTable[hash].flag == 1 &&
            h->hashTable[hash].data == key) {
            printf("The data %d is found at index %d\n", key, hash);
            return hash;
        }

        // If empty slot → key cannot exist further → NOT FOUND
        if (h->hashTable[hash].flag == 0) {
            printf("The data %d not found\n", key);
            return -1;
        }

        // Check next slot (linear probing)
        i++;
    }

    printf("The data %d not found\n", key);
    return -1;
}

/******************************************************
 * Function: insert_
 * ------------------
 * Inserts a key using:
 *   - Linear probing
 *   - Resizing when load factor > 0.75
 * Steps:
 *   1. Check if key already exists
 *   2. Check load factor and rehash if necessary
 *   3. Find next free slot using linear probing
 *   4. Insert key
 ******************************************************/
void insert_(int key, HASH *h) {

    // If key already exists, do not insert duplicates
    if (search(key, h) != -1) {
        return;
    }

    // Load factor check → rehash
    if ((float)(count + 1) > 0.75 * h->size) {
        rehash(h);
    }

    // Insert using linear probing
    int i = 0;
    int hash = ((key % h->size) + i) % h->size;

    // Find next available slot
    while (h->hashTable[hash].flag != 0) {
        i++;
        hash = ((key % h->size) + i) % h->size;
    }

    // Store the key
    h->hashTable[hash].data = key;
    h->hashTable[hash].flag = 1;

    count++;

    printf("The data %d is inserted\n", key);
}

/******************************************************
 * Function: display
 * ------------------
 * Prints the contents of the hash table.
 ******************************************************/
void display(HASH *h) {
    printf("Hash Table (size %d):\n", h->size);

    for (int i = 0; i < h->size; i++) {
        if (h->hashTable[i].flag == 1)
            printf("Index %d: %d\n", i, h->hashTable[i].data);
        else
            printf("Index %d: EMPTY\n", i);
    }
    printf("\n");
}

/******************************************************
 * MAIN FUNCTION – Demonstrates:
 *   - Insertion
 *   - Searching
 *   - Rehashing
 *   - Displaying hash table
 ******************************************************/
int main() {

    HASH *hashTable = createHash(SIZE);

    insert_(5, hashTable);
    insert_(15, hashTable);
    insert_(25, hashTable);

    display(hashTable);

    search(15, hashTable);
    search(45, hashTable);

    insert_(35, hashTable);
    display(hashTable);

    destroyHash(hashTable);
    return 0;
}

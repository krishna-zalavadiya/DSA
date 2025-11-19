#include <stdio.h>
#include <stdlib.h>

#define SIZE 10     // Size of the hash table (fixed for this example)

/*
 * NODE structure for open addressing:
 * -----------------------------------
 * data → stores the key
 * flag → marks whether the slot is used
 *        0 = EMPTY slot
 *        1 = OCCUPIED slot
 *
 * No linked lists → open addressing handles collisions.
 */
typedef struct node {
    int data;
    int flag;
} NODE;

/*
 * Function: initializeHashTable
 * ------------------------------
 * Sets all hash table entries to EMPTY.
 * This must be done before inserting any element.
 */
void initializeHashTable(NODE *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i].data = 0;   // default meaningless value
        hashTable[i].flag = 0;   // mark slot empty
    }
}

/*
 * Function: search
 * -----------------
 * Searches for a key using DOUBLE HASHING.
 *
 * Double Hashing formula:
 *
 *    h1 = key % SIZE          (primary hash)
 *    h2 = 7 - (key % 7)       (secondary hash)
 *
 * Effective index using probing:
 *
 *    index = (h1 + i * h2) % SIZE
 *
 * i → number of collisions (initially 0)
 *
 * Key points:
 * -----------
 * • If an EMPTY slot is found → stop search (key not present)
 * • If slot matches key → key found
 * • Otherwise → continue probing
 */
int search(int key, NODE *hashTable) {

    int hash  = key % SIZE;           // primary hash
    int hash2 = 7 - (key % 7);        // secondary hash (non-zero)
    int i = 0;                        // number of probes

    // Probe at most SIZE times (entire table)
    while (i < SIZE) {

        // Compute probe index
        int index = (hash + i * hash2) % SIZE;

        // Case 1: Key found
        if (hashTable[index].data == key && hashTable[index].flag == 1) {
            return 1;
        }

        // Case 2: EMPTY slot → key cannot be in table anymore
        if (hashTable[index].flag == 0) {
            return 0;
        }

        // Case 3: Collision → try new index using double hashing
        i++;
    }

    // Table fully searched → not found
    return 0;
}

/*
 * Function: insert
 * -----------------
 * Inserts a key using DOUBLE HASHING collision resolution.
 *
 * Steps:
 *  1. Check if key already exists.
 *  2. Compute primary hash (h1).
 *  3. Compute secondary hash (h2).
 *  4. Probe using index = (h1 + i * h2) % SIZE.
 *  5. Insert at first EMPTY slot.
 *
 * If no empty slot found → table is full.
 */
void insert(int key, NODE *hashTable) {

    // Step 1: Avoid duplicate entries
    if (search(key, hashTable)) {
        printf("The data %d already exists\n", key);
        return;
    }

    int hash  = key % SIZE;        // primary hash
    int hash2 = 7 - (key % 7);     // secondary hash
    int i = 0;

    // Compute first index
    int index = (hash + i * hash2) % SIZE;

    // Step 2: Probe until empty slot found
    while (hashTable[index].flag != 0 && i < SIZE) {
        i++;   // increment probe count
        index = (hash + i * hash2) % SIZE;
    }

    // Step 3: Insert into empty slot
    if (hashTable[index].flag == 0) {
        hashTable[index].data = key;
        hashTable[index].flag = 1;
        printf("The data %d is inserted at %d\n", key, index);
    }
    else {
        // Table is full (rare in this example)
        printf("Data cannot be inserted\n");
    }
}

/*
 * Function: display
 * ------------------
 * Prints the state of the hash table after operations.
 *
 * Shows:
 * • Which indices are occupied
 * • Which slots remain empty
 */
void display(NODE *hashTable) {

    printf("Hash Table:\n");

    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i].flag == 1)
            printf("Index %d: %d\n", i, hashTable[i].data);
        else
            printf("Index %d: EMPTY\n", i);
    }

    printf("\n");
}

/*
 * MAIN FUNCTION
 * --------------
 * Demonstrates:
 *  - Double hashing insertion
 *  - Searching
 *  - Displaying how collisions are resolved
 */
int main() {

    NODE hashTable[SIZE];
    initializeHashTable(hashTable);

    // Insert values (all collide at h1 = key % 10 = 5)
    insert(5, hashTable);     // goes to index 5
    insert(15, hashTable);    // resolves collision → new index
    insert(25, hashTable);
    insert(35, hashTable);
    insert(45, hashTable);

    display(hashTable);

    // Search for values
    if (search(15, hashTable))
        printf("The data %d is found\n", 15);
    else
        printf("The data %d not found\n", 15);

    if (search(35, hashTable))
        printf("The data %d is found\n", 35);
    else
        printf("The data %d not found\n", 35);

    if (search(7, hashTable))
        printf("The data %d is found\n", 7);
    else
        printf("The data %d not found\n", 7);

    return 0;
}

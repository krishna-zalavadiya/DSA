#include <stdio.h>
#include <stdlib.h>

#define SIZE 10   // Size of the hash table (fixed for this example)

/*
 * NODE structure:
 * ----------------
 * Used for open addressing (linear probing).
 *
 * data → stores the key
 * flag → indicates whether the slot is:
 *        0 = EMPTY
 *        1 = OCCUPIED
 */
typedef struct node {
    int data;
    int flag;
} NODE;

/*
 * Function: initializeHashTable
 * ------------------------------
 * Sets all slots in the hash table to EMPTY.
 */
void initializeHashTable(NODE *hashTable) {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i].data = 0;
        hashTable[i].flag = 0;   // Mark slot empty
    }
}

/*
 * Function: search
 * -----------------
 * Searches a key using LINEAR PROBING.
 *
 * Steps:
 *   1. Compute hash = key % SIZE
 *   2. If slot matches key → FOUND
 *   3. If slot is empty → STOP (key cannot be further)
 *   4. Otherwise → move to next index (linear probing)
 *
 * Returns:
 *     1 → Key found
 *     0 → Key not found
 */
int search(int key, NODE *hashTable) {
    int hash, i = 0;

    // Initial hash value
    hash = ((key % SIZE) + i) % SIZE;

    // Probe up to SIZE slots (full table scan)
    while (i < SIZE) {

        // CASE 1: Key found
        if (hashTable[hash].data == key && hashTable[hash].flag == 1) {
            return 1;
        }

        // CASE 2: Empty slot → key NOT present
        // (Linear probing stops once an empty slot appears)
        if (hashTable[hash].flag == 0) {
            return 0;
        }

        // CASE 3: Collision → move to next slot
        i++;
        hash = ((key % SIZE) + i) % SIZE;
    }

    // Full table scanned → key not present
    return 0;
}

/*
 * Function: insert
 * -----------------
 * Inserts a key using LINEAR PROBING.
 *
 * Steps:
 *   1. Check if key already exists → if yes, do not insert
 *   2. Compute initial hash index
 *   3. If slot is occupied → probe (hash+1), (hash+2), ...
 *   4. Insert key into first EMPTY slot
 */
void insert(int key, NODE *hashTable) {

    // Step 1: Do not insert duplicates
    if (search(key, hashTable)) {
        printf("The data %d already exists\n", key);
        return;
    }

    int hash, i = 0;

    // Step 2: Compute initial hash position
    hash = ((key % SIZE) + i) % SIZE;

    // Step 3: Probe until an empty slot is found
    while (hashTable[hash].flag != 0 && i < SIZE) {
        i++;       // count collisions
        hash = ((key % SIZE) + i) % SIZE;// to find the next slot or index in arraya
    }

    // Step 4: Insert in empty space (flag == 0)
    if (hashTable[hash].flag == 0) {
        hashTable[hash].data = key;
        hashTable[hash].flag = 1;     // Mark slot as occupied
        printf("The data %d is inserted at %d\n", key, hash);
    } else {
        // This can occur only when table is full
        printf("Data cannot be inserted\n");
    }
}

/*
 * Function: display
 * ------------------
 * Prints the entire hash table.
 *
 * Shows:
 *     - Index number
 *     - Key stored OR EMPTY
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
 *   - insertion
 *   - searching
 *   - displaying
 *
 * Table size = 10
 */
int main() {

    NODE hashTable[SIZE];
    initializeHashTable(hashTable);

    // Insert 5 keys: all collide at index 5
    insert(5, hashTable);    // goes to index 5
    insert(15, hashTable);   // collision → index 6
    insert(25, hashTable);   // collision → index 7
    insert(35, hashTable);   // collision → index 8
    insert(45, hashTable);   // collision → index 9

    display(hashTable);

    // Search existing key
    if (search(15, hashTable))
        printf("The data %d is found\n", 15);
    else
        printf("The data %d not found\n", 15);

    // Search existing key
    if (search(35, hashTable))
        printf("The data %d is found\n", 35);
    else
        printf("The data %d not found\n", 35);

    // Search non-existing key
    if (search(95, hashTable))
        printf("The data %d is found\n", 95);
    else
        printf("The data %d not found\n", 95);

    return 0;
}

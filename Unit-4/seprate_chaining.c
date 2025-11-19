#include <stdio.h>
#include <stdlib.h>

#define SIZE 10     // Size of the hash table (number of buckets)

/*
 * Node structure for separate chaining.
 * Each node stores:
 *   - an integer key (data)
 *   - a pointer to the next node in the chain
 */
typedef struct node {
    int data;
    struct node *next;
} NODE;

/*
 * Each element of the hash table is a HASHTABLE structure.
 * It stores:
 *   - count : number of elements in this bucket
 *   - head  : pointer to the first node of the linked list in this bucket
 */
typedef struct hashtable {
    int count;
    struct node *head;
} HASHTABLE;

/*
 * Function: createNode
 * ---------------------
 * Allocates memory for a new node, initializes the data with 'key'
 * and sets next pointer to NULL.
 * Used for inserting values into the hash table.
 */
NODE *createNode(int key) {
    NODE *n = (NODE *)malloc(sizeof(NODE));
    if (!n) {   // Always check if malloc failed
        printf("Memory allocation error\n");
        exit(1);
    }
    n->data = key;
    n->next = NULL;
    return n;
}

/*
 * Function: search
 * ----------------
 * Searches for a key inside the hash table.
 * Steps:
 *   1. Compute hash index → key % SIZE
 *   2. Traverse the linked list at that index
 *   3. If a node with the same value is found → return 1
 *   4. If the entire chain is checked and not found → return 0
 */
int search(int key, HASHTABLE HashTable[]) // HASHTABLE HashTable[] this is array of structures and not array of pointers
{
    int hash = key % SIZE;               // Calculate hash index
    NODE *t = HashTable[hash].head;      // Start at head of the linked list

    while (t != NULL) {                  // Traverse chain
        if (t->data == key)              // Key found
            return 1;
        t = t->next;                     // Move to next node
    }
    return 0;                            // Key not found
}

/*
 * Function: insert
 * ----------------
 * Inserts a key into the hash table using separate chaining.
 * Steps:
 *   1. Check if key already exists → if yes, skip insertion.
 *   2. Compute hash index.
 *   3. Create a new node.
 *   4. Insert it at the beginning of the linked list at that index.
 *   5. Increment bucket count.
 */
void insert(int key, HASHTABLE HashTable[]) {
    // Prevent inserting duplicate values
    if (search(key, HashTable)) {
        printf("The data %d already exists\n", key);
        return;
    }

    int hash = key % SIZE;               // Compute hash index
    NODE *nn = createNode(key);          // Create new node

    // Insert at beginning of chain (head insertion)
    nn->next = HashTable[hash].head;
    HashTable[hash].head = nn;            // Update head pointer
    HashTable[hash].count++;             // Increase element count

    printf("The data %d is inserted at index [%d]\n", key, hash);
}

/*
 * Function: deleteData
 * --------------------
 * Deletes a given key from the hash table.
 * Steps:
 *   1. Compute hash index.
 *   2. Traverse the bucket's linked list.
 *   3. Track current and previous nodes to unlink correctly.
 *   4. Adjust pointers and free memory.
 *   5. If key not found → print message.
 */

void deleteData(int key, HASHTABLE HashTable[]) {
    int hash = key % SIZE;
    NODE *t = HashTable[hash].head;
    NODE *prev = NULL;

    while (t != NULL) {
        if (t->data == key) {            // Key found
            if (prev != NULL)
                prev->next = t->next;    // Remove middle node
            else
                HashTable[hash].head = t->next; // Removing first node

            free(t);                      // Free memory
            HashTable[hash].count--;      // Update count
            printf("Data deleted successfully\n");
            return;
        }
        prev = t;                         // Move prev
        t = t->next;                      // Move current node
    }

    printf("Data not found\n");           // Key not found
}

/*
 * Function: display
 * -----------------
 * Displays entire hash table.
 * For each bucket:
 *   - If empty → print "EMPTY"
 *   - If not empty → print all values in linked list format
 */
void display(HASHTABLE HashTable[]) {
    for (int i = 0; i < SIZE; i++) {

        if (HashTable[i].count != 0) {    // If bucket not empty
            printf("Index [%d]: ", i);
            NODE *t = HashTable[i].head;

            while (t != NULL) {
                printf("%d -> ", t->data);
                t = t->next;
            }
            printf("NULL\n");
        }
        else {
            printf("Index [%d]: EMPTY\n", i);
        }
    }
    printf("\n");
}

/*
 * MAIN FUNCTION
 * --------------
 * Demonstrates:
 *   - Inserting elements
 *   - Displaying table
 *   - Searching for elements
 *   - Deleting elements
 */
int main() {
    HASHTABLE HashTable[SIZE] = {0};  // Initialize all buckets to empty

    // Insert sample data
    insert(10, HashTable);
    insert(20, HashTable);
    insert(15, HashTable);
    insert(25, HashTable);
    insert(30, HashTable);

    display(HashTable);   // Show table after insertions

    // Search operations
    if (search(15, HashTable))
        printf("Data 15 is found\n");
    else
        printf("Data 15 not found\n");

    if (search(9, HashTable))
        printf("Data 9 is found\n");
    else
        printf("Data 9 not found\n");

    // Delete operations
    deleteData(10, HashTable);  // Existing key
    deleteData(9, HashTable);   // Non-existing key

    display(HashTable);   // Show table after deletions
    return 0;
}

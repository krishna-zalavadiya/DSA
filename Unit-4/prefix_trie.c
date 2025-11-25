#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 26   // For characters 'a' to 'z'

// ============================ TRIE NODE STRUCT ============================

struct trienode {
    struct trienode *child[MAX];   // 26 child pointers
    int endofword;                 // 1 if a word ends at this node
};

// ============================ STACK STRUCTURE ============================
// Used for deletion to store visited nodes (path of the word)

struct stack {
    struct trienode *m;   // pointer to node
    int index;            // which child index was used
};

// Global stack
struct stack stk[100];
int top = -1;

// Push node and index into stack
void push(struct trienode *t, int index) {
    top++;
    stk[top].m = t;
    stk[top].index = index;
}

// Pop node and index from stack
struct stack pop() {
    return stk[top--];
}

// ============================ GET NEW NODE ============================
// Creates a new empty trie node

struct trienode *getnode() {
    int i;
    struct trienode *temp;

    temp = (struct trienode*)malloc(sizeof(struct trienode));

    // Initialize all children to NULL
    for (i = 0; i < MAX; i++)
        temp->child[i] = NULL;

    temp->endofword = 0;   // Not the end of a word

    return temp;
}

// ============================ INSERT OPERATION ============================
// Insert a string into the TRIE

void insert(struct trienode *root, char *key) {
    struct trienode *curr = root;
    int i, index;

    for (i = 0; key[i] != '\0'; i++) {

        index = key[i] - 'a';    // map char to index 0–25

        // If path does not exist → create new node
        if (curr->child[index] == NULL)
            curr->child[index] = getnode();

        // Move to next node
        curr = curr->child[index];
    }

    curr->endofword = 1;  // Mark end of word
}

// ============================ SEARCH OPERATION ============================
// Returns 1 if word exists, 0 otherwise

int search(struct trienode *root, char *key) {

    struct trienode *curr = root;
    int i, index;

    for (i = 0; key[i] != '\0'; i++) {

        index = key[i] - 'a';

        // If path does not exist → word NOT found
        if (curr->child[index] == NULL)
            return 0;

        curr = curr->child[index];
    }

    // Word found ONLY if endofword is set
    return curr->endofword == 1;
}

// ============================ CHECK FUNCTION ============================
// Checks whether a node has ANY children
// Returns count of children

int check(struct trienode *node) {
    int i, count = 0;

    for (i = 0; i < MAX; i++)
        if (node->child[i] != NULL)
            count++;

    return count;   // number of children
}

// ============================ DISPLAY FUNCTION ============================
// Prints all stored words in TRIE in alphabetical order

char word[100];     // buffer to store word while traversing
int length = 0;

void display(struct trienode *curr) {
    int i, j;

    for (i = 0; i < MAX; i++) {

        // If child exists
        if (curr->child[i] != NULL) {

            word[length++] = i + 'a';   // store character

            // If end of word, print it
            if (curr->child[i]->endofword == 1) {
                printf("\n");
                for (j = 0; j < length; j++)
                    printf("%c", word[j]);
            }

            // Recur deeper
            display(curr->child[i]);
        }
    }

    length--;  // Backtrack
}

// ============================ DELETE OPERATION ============================
// Deletes the given word from TRIE (if exists)

void delete_trie(struct trienode *root, char *key) {

    struct trienode *curr = root;
    int index, i, k;

    // CLEAR stack for safety
    top = -1;

    // Traverse through key characters
    for (i = 0; key[i] != '\0'; i++) {

        index = key[i] - 'a';

        // Word not present
        if (curr->child[index] == NULL) {
            printf("The word not found..\n");
            return;
        }

        // Push current node and index
        push(curr, index);

        curr = curr->child[index];
    }

    // Now curr is pointing to last node of word
    curr->endofword = 0;

    // Push final node
    push(curr, -1);

    // ================= DELETE PROCESS USING STACK =================
    while (1) {

        struct stack x = pop();

        // If child pointer valid
        if (x.index != -1)
            x.m->child[x.index] = NULL;

        // If we reached root → stop
        if (x.m == root)
            break;

        // If node has children OR endofword set → do not delete
        k = check(x.m);
        if (k >= 1 || x.m->endofword == 1)
            break;

        // Otherwise safe to delete
        free(x.m);
    }

    return;
}

// ============================ MAIN ============================

int main() {

    struct trienode *root = getnode();
    int choice;
    char key[50];

    while (1) {

        printf("\n===== TRIE MENU =====\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter word to insert: ");
            scanf("%s", key);
            insert(root, key);
            break;

        case 2:
            printf("Enter word to search: ");
            scanf("%s", key);
            if (search(root, key))
                printf("Word FOUND\n");
            else
                printf("Word NOT found\n");
            break;

        case 3:
            printf("Enter word to delete: ");
            scanf("%s", key);
            delete_trie(root, key);
            break;

        case 4:
            printf("\nWords in TRIE:");
            display(root);
            printf("\n");
            break;

        case 5:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

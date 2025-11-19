#include <stdio.h>      // Standard I/O library
#include <stdlib.h>     // Standard library for exit(), etc.

#define MAX 100         // Maximum heap size

// Function prototypes
void top_down_insert(int *heap, int *size, int value); // Insert using percolate-up
int delete_max(int *heap, int *size);                  // Remove maximum element
void heapify(int *heap, int n);                        // Percolate-down to restore heap
void display(int *heap, int size);                     // Print heap contents

int main() {
    int heap[MAX];     // Array-based heap
    int size = 0;      // Current number of elements in heap
    int choice, value;

    printf("Priority Queue using Top-Down Heap\n");

    do {
        // Menu display
        printf("\nMenu:\n");
        printf("1. Insert element\n");
        printf("2. Delete maximum element\n");
        printf("3. Display heap\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);   // User choice input

        switch(choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);         // Read value
                top_down_insert(heap, &size, value);  // Insert into heap
                break;

            case 2:
                if(size == 0) {              // Check if heap empty
                    printf("Priority queue is empty!\n");
                } else {
                    value = delete_max(heap, &size);  // Remove root (max)
                    printf("Deleted maximum element: %d\n", value);
                }
                break;

            case 3:
                display(heap, size);         // Print heap
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n"); // Wrong menu option
        }
    } while(choice != 4);   // Loop until user chooses exit

    return 0;
}


// =============================================================
// ---------------------- TOP DOWN INSERT -----------------------
// =============================================================
void top_down_insert(int *heap, int *size, int value) {

    if(*size >= MAX) {                    // Check for overflow
        printf("Priority queue is full!\n");
        return;
    }

    int i = *size;                        // New element goes at last index
    heap[i] = value;                      // Put value there
    (*size)++;                            // Increase heap size

    // ----- Percolate UP (bubble up) -----
    while(i > 0) {                        // Repeat until root reached
        int parent = (i - 1) / 2;         // Parent index

        if(heap[parent] < heap[i]) {      // If child > parent → swap
            int temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;

            i = parent;                   // Move to parent index
        }
        else
            break;                        // Correct position found
    }
}


// =============================================================
// -------------------------- DELETE MAX ------------------------
// =============================================================
int delete_max(int *heap, int *size) {

    int max = heap[0];                    // Store max (root element)

    heap[0] = heap[*size - 1];            // Move last element to root
    (*size)--;                            // Reduce size

    heapify(heap, *size - 1);             // Fix heap using percolate down

    return max;                           // Return deleted element
}


// =============================================================
// ---------------------------- HEAPIFY -------------------------
//     Restore max-heap property by percolating DOWN
// =============================================================
void heapify(int *heap, int n) {

    int i = 0;                            // Start from root
    int key = heap[i];                    // Store the root value
    int j = 2 * i + 1;                    // Left child index

    while(j <= n) {                       // While child exists

        // Check if right child exists AND is larger than left child
        if(j + 1 <= n && heap[j + 1] > heap[j])
            j++;                          // Move j to right child

        // If child > key, move child up
        if(key < heap[j]) {
            heap[i] = heap[j];            // Move larger child up
            i = j;                        // Move down to child's index
            j = 2 * i + 1;                // Calculate new left child
        }
        else
            break;                        // Correct position found
    }

    heap[i] = key;                        // Place key in correct location
}


// =============================================================
// ---------------------------- DISPLAY -------------------------
// =============================================================
void display(int *heap, int size) {

    if(size == 0) {                        // Check if empty
        printf("Priority queue is empty!\n");
        return;
    }

    printf("Heap elements (max-heap): ");

    for(int i = 0; i < size; i++)          // Print array elements
        printf("%d ", heap[i]);

    printf("\n");
}

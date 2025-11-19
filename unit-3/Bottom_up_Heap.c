#include <stdio.h>

/*
 Build a max-heap from an array using the bottom-up (heapify) approach.
 Parameters:
   h : array of integers (0-based indexing)
   n : index of the last element in the array (i.e. size-1)
 Example call for array of length N: bot_heap(h, N-1);
*/
void bot_heap(int *h, int n) {
    int i, j, k, key;

    // Start from the last internal node (last parent) and move upwards to root.
    // Last parent index = floor((N/2) - 1) = floor((n-1)/2) when n is last index.
    for (k = (n - 1) / 2; k >= 0; k--) {
        j = k;             // j is the current node index we are "sifting" down
        key = h[j];        // store the value to place in its correct position
        i = 2 * j + 1;     // left child index

        // Sift the key down the subtree rooted at j until it finds the right spot
        while (i <= n) {                          // while left child exists
            // If right child exists and is larger than left child, use right child
            if (i + 1 <= n && h[i + 1] > h[i])    // pick the larger child
                i++;                              // i now indexes the larger child

            // If child is greater than key, move child value up and continue
            if (key < h[i]) {
                h[j] = h[i];  // move larger child up to parent position
                j = i;        // move down to child position
                i = 2 * j + 1;// new left child of j
            } else {
                break;        // key is >= both children, correct position found
            }
        }
        h[j] = key; // place key into its final position in heap
    }
}

int main() {
    int h[100]; // heap array
    int n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &h[i]);

    bot_heap(h, n - 1); // build max-heap; pass last index (n-1)

    printf("Heap after bottom-up construction (max-heap):\n");
    for (i = 0; i < n; i++)
        printf("%d ", h[i]);
    printf("\n");

    return 0;
}

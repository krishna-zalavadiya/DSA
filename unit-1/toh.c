#include <stdio.h>

// Tower of Hanoi recursive function
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {

    // Base case: only one disk → direct move
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", from_rod, to_rod);
        return;
    }

    // Step 1: Move top n-1 disks to auxiliary rod
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);

    // Step 2: Move nth (largest) disk to destination rod
    printf("Move disk %d from rod %c to rod %c\n", n, from_rod, to_rod);

    // Step 3: Move n-1 disks from auxiliary rod to destination rod
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    printf("\nThe moves are:\n");

    // A = source, C = destination, B = auxiliary
    towerOfHanoi(n, 'A', 'C', 'B');

    return 0;
}

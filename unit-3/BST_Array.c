// BST implementation using array
#include <stdio.h>
#include <stdlib.h>

void insert(int *t, int x);
void preorder(int *t, int i);
void inorder(int *t, int i);
void postorder(int *t, int i);

int main()
{
    int t[100];
    int ch, x, i;

    // Initialize all array elements to -1 (means "empty")
    for (i = 0; i < 100; i++)
        t[i] = -1;

    while (1)
    {
        printf("\n1: Insert\n2: Preorder\n3: Inorder\n4: Postorder\n5: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter the value: ");
            scanf("%d", &x);
            insert(t, x);
            break;

        case 2:
            printf("Preorder traversal:\n");
            preorder(t, 0);
            break;

        case 3:
            printf("Inorder traversal:\n");
            inorder(t, 0);
            break;

        case 4:
            printf("Postorder traversal:\n");
            postorder(t, 0);
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
}

// Function to insert an element into BST (array-based)
void insert(int *t, int x)
{
    int i = 0;

    while (t[i] != -1)
    {
        if (x < t[i])
            i = 2 * i + 1; // move to left child
        else
            i = 2 * i + 2; // move to right child
    }

    t[i] = x; // place new node in empty spot
}

// Preorder traversal: Root, Left, Right
void preorder(int *t, int i)
{
    if (t[i] == -1)
        return;

    printf("%d ", t[i]);
    preorder(t, 2 * i + 1);
    preorder(t, 2 * i + 2);
}

// Inorder traversal: Left, Root, Right
void inorder(int *t, int i)
{
    if (t[i] == -1)
        return;

    inorder(t, 2 * i + 1);
    printf("%d ", t[i]);
    inorder(t, 2 * i + 2);
}

// Postorder traversal: Left, Right, Root
void postorder(int *t, int i)
{
    if (t[i] == -1)
        return;

    postorder(t, 2 * i + 1);
    postorder(t, 2 * i + 2);
    printf("%d ", t[i]);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*In a normal BST, many left/right pointers are NULL.
In a Threaded BST, these NULL pointers are replaced with threads:
Left thread → points to inorder predecessor
Right thread → points to inorder successor
This allows inorder traversal without recursion and without stack.
*/


// Node structure of threaded BST
struct node {
    int data;
    struct node *left, *right;
    bool lthread, rthread;
};

// Function prototypes
struct node* insert(struct node *root, int x);
struct node* inorder_successor(struct node *ptr);
void inorder(struct node *root);

// ---------------- MAIN ----------------
int main() {
    struct node *root = NULL;
    int ch, x;

    while(1) {
        printf("\n1: Insert\n2: Inorder Traversal\n3: Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                printf("Enter the number: ");
                scanf("%d", &x);
                root = insert(root, x);
                break;

            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}

// ------------ INSERT into Threaded BST ------------
struct node* insert(struct node *root, int x) {

    struct node *cur = root, *parent = NULL;

    // Create new node
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->data = x;
    temp->lthread = temp->rthread = true;   // both are threads initially
    temp->left = temp->right = NULL;

    // First node becomes root
    if(root == NULL)
        return temp;

    // Find the parent where new node should be inserted
    while(cur != NULL) {
        parent = cur;

        if(x < cur->data) {
            if(!cur->lthread)        // left child exists
                cur = cur->left;
            else
                break;
        } else {
            if(!cur->rthread)        // right child exists
                cur = cur->right;
            else
                break;
        }
    }

    // Insert as left child
    if(x < parent->data) {
        temp->left = parent->left;     // thread to predecessor
        temp->right = parent;          // thread to parent
        parent->lthread = false;       // left is now a real child
        parent->left = temp;           // link new node as left child
    }
    // Insert as right child
    else {
        temp->right = parent->right;   // thread to successor
        temp->left = parent;           // thread to parent
        parent->rthread = false;       // right is now a real child
        parent->right = temp;          // link new node as right child    
    }

    return root;
}

// ------------ FIND INORDER SUCCESSOR ------------
struct node* inorder_successor(struct node *ptr) {

    // If ptr has a thread on right → successor directly
    if(ptr->rthread)
        return ptr->right;

    // Else go to real right subtree → smallest node there
    ptr = ptr->right;
    while(!ptr->lthread)
        ptr = ptr->left;

    return ptr;
}

// ------------ INORDER TRAVERSAL ------------------
void inorder(struct node *root) {

    if(root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    // Go to leftmost node (smallest)
    struct node *cur = root;
    while(!cur->lthread)
        cur = cur->left;

    // Repeatedly print and move to inorder successor
    while(cur != NULL) {
        printf("%d ", cur->data);
        cur = inorder_successor(cur);
    }
}

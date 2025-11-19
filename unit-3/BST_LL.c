#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int info;
    struct node *left, *right;
} node;

typedef struct tree {
    node *root;
} tree;

// Initialize tree
void init(tree *pt) {
    pt->root = NULL;
}

// Insert into BST
void insert(node *t, int x)
{
    node *temp, *prev, *cur;
    temp = (node*)malloc(sizeof(node));
    temp->info = x;
    temp->left = temp->right = NULL;

    if (t == NULL)
        t = temp;
    else
    {
        prev = NULL;//to keep track of parent node
        cur = t;// making a new curent node to traverse the tree
        while (cur != NULL)
        {
            prev = cur;
            if (x < cur->info)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (x < prev->info)
            prev->left = temp;
        else
            prev->right = temp;
    }
}

// Create BST
void create(tree *pt) {
    node *temp, *p, *q;
    printf("Enter the root info: ");
    pt->root = (node*)malloc(sizeof(node));
    scanf("%d", &pt->root->info);
    pt->root->left = NULL;
    pt->root->right = NULL;

    int wish;
    do {
        printf("Enter the element: ");
        temp = (node*)malloc(sizeof(node));
        scanf("%d", &temp->info);
        temp->left = temp->right = NULL;
        
        q = NULL;
        p = pt->root;
        while (p != NULL) {
            q = p;
            if (temp->info < p->info)
                p = p->left;
            else
                p = p->right;
        }

        if (temp->info < q->info)
            q->left = temp;
        else
            q->right = temp;

        printf("Do you want to add another (1/0)? ");
        scanf("%d", &wish);
    } while (wish);
}

//iterative inorder traversal using stack
// void inorder(struct tnode *root) {
//     struct tnode *curr = root;
//     struct tnode *stack[100];
//     int top = -1;

//     while (curr != NULL || top != -1) {

//         while (curr != NULL) {
//             stack[++top] = curr;  // push
//             curr = curr->left;    // go left
//         }

//         curr = stack[top--];      // pop
//         printf("%d ", curr->data);

//         curr = curr->right;       // go right
//     }
// }

// Inorder Traversal (left,root,right)
void inorder(node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->info);
    inorder(root->right);
}

// Preorder Traversal (root,left,right)
void preorder(node *root) {
    if (root == NULL) return;
    printf("%d ", root->info);
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal (left,right,root)
void postorder(node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->info);
}

// Count total nodes
int countNodes(node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeaves(node *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Height of tree (max depth)
int height(node *root) {
    if (root == NULL) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Depth of a node (distance from root)
// returns -1 if not found

int depth(node *root, int key, int level) {
    if (root == NULL) return -1;
    if (root->info == key) return level;

    int left = depth(root->left, key, level + 1);
    if (left != -1) return left;// this is very important

    return depth(root->right, key, level + 1);
}


//                    DELETION OF THE NODE
//case1:Leaf node (no children) → remove directly.

//case 2:One child → replace node with its childc.

//case 3:Two children → replace node with inorder successor (smallest in right subtree) or 
//inorder predecessor (largest in left subtree), then delete that replacement node.

// Find minimum node in a subtree (used for case 3)
//Left subtree < root < Right subtree
node* inorder_succesor(node* root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}
// Delete a node from BST
node* deleteNode(node* root, int key) {
    if (root == NULL) return root;

    if (key < root->info) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->info) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // Found the node to delete

        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        node* temp = inorder_succesor(root->right);   // inorder successor
        root->info = temp->info;             // copy value
        root->right = deleteNode(root->right, temp->info); // delete duplicate
    }
    return root;
}


int main() {
    tree t;
    init(&t);
    create(&t);

    printf("\nInorder traversal: ");
    inorder(t.root);

    printf("\nPreorder traversal: ");
    preorder(t.root);

    printf("\nPostorder traversal: ");
    postorder(t.root);

    printf("\n\nOther Operations:");
    printf("\nTotal number of nodes: %d", countNodes(t.root));
    printf("\nTotal number of leaf nodes: %d", countLeaves(t.root));
    printf("\nHeight of tree: %d", height(t.root));

    int key;
    printf("\nEnter a node value to find its depth: ");
    scanf("%d", &key);
    int d = depth(t.root, key, 0);
    if (d != -1)
        printf("Depth of node %d = %d\n", key, d);
    else
        printf("Node %d not found in tree\n", key);

    // Deletion
    printf("\nEnter a node value to delete: ");
    scanf("%d", &key);
    t.root = deleteNode(t.root, key);

    printf("\nInorder traversal after deletion: ");
    inorder(t.root);

    printf("\nPreorder traversal after deletion: ");
    preorder(t.root);

    printf("\nPostorder traversal after deletion: ");
    postorder(t.root);

    printf("\nTotal number of nodes after deletion: %d", countNodes(t.root));
    printf("\nTotal number of leaf nodes after deletion: %d", countLeaves(t.root));
    printf("\nHeight of tree after deletion: %d", height(t.root));

    printf("\n");
    return 0;
}

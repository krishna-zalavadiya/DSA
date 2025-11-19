#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Simple expression tree node
typedef struct ETNode {
    char *token; // token string (operator or operand)
    struct ETNode *left;
    struct ETNode *right;
} ETNode;

// Create a new node (constructor-like helper)
ETNode *newNode(const char *tok) {
    ETNode *n = (ETNode *)malloc(sizeof(ETNode));
    if (!n) return NULL;
    n->token = strdup(tok);
    n->left = n->right = NULL;
    return n;
}

// Free tree
void freeTree(ETNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root->token);
    free(root);
}

// Utility: check if token is operator
int isOperator(const char *tok) {
    return (strcmp(tok, "+") == 0 || strcmp(tok, "-") == 0 || strcmp(tok, "*") == 0 || strcmp(tok, "/") == 0 || strcmp(tok, "^") == 0);
}

// Construct expression tree from postfix expression tokens (space-separated)
// Returns root of tree or NULL on error.
ETNode *constructTreeFromPostfix(const char *postfix) {
    if (!postfix) return NULL;

    // Simple stack of node pointers
    ETNode **stack = NULL;
    size_t stackCap = 0, stackTop = 0;

    // tokenize input by whitespace
    char *copy = strdup(postfix);
    if (!copy) return NULL;
    char *saveptr = NULL;
    char *tok = strtok_r(copy, " \t\n", &saveptr);

    while (tok) {
        if (!stack) { stackCap = 16; stack = malloc(stackCap * sizeof(ETNode*)); }
        if (stackTop + 2 > stackCap) { stackCap *= 2; stack = realloc(stack, stackCap * sizeof(ETNode*)); }

        if (isOperator(tok)) {
            // need two operands
            if (stackTop < 2) { free(copy); free(stack); return NULL; }
            ETNode *right = stack[--stackTop];
            ETNode *left = stack[--stackTop];
            ETNode *node = newNode(tok);
            if (!node) { free(copy); free(stack); return NULL; }
            node->left = left;
            node->right = right;
            stack[stackTop++] = node;
        } else {
            // operand -> push node
            ETNode *node = newNode(tok);
            if (!node) { free(copy); free(stack); return NULL; }
            stack[stackTop++] = node;
        }

        tok = strtok_r(NULL, " \t\n", &saveptr);
    }

    ETNode *root = NULL;
    if (stackTop == 1) root = stack[0];

    free(copy);
    free(stack);
    return root;
}

// Inorder (with parentheses for clarity)
void inorder(ETNode *root) {
    if (!root) return;
    if (isOperator(root->token)) printf("(");
    inorder(root->left);
    printf("%s", root->token);
    inorder(root->right);
    if (isOperator(root->token)) printf(")");
}

// Postorder
void postorder(ETNode *root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->token);
}

// Evaluate tree (operands are integers)
long evaluate(ETNode *root) {
    if (!root) return 0;
    if (!isOperator(root->token)) {
        return strtol(root->token, NULL, 10);
    }
    long L = evaluate(root->left);
    long R = evaluate(root->right);
    if (strcmp(root->token, "+") == 0) return L + R;
    if (strcmp(root->token, "-") == 0) return L - R;
    if (strcmp(root->token, "*") == 0) return L * R;
    if (strcmp(root->token, "/") == 0) return R != 0 ? L / R : 0;
    if (strcmp(root->token, "^") == 0) { // power (integer)
        long res = 1; for (long i=0;i<R;i++) res *= L; return res;
    }
    return 0;
}

// Small runner: read a postfix expression line from stdin and build tree
int main(int argc, char **argv) {
    const char *expr = NULL;
    char buf[1024];

    if (argc >= 2) {
        // join argv[1..] with spaces
        size_t len = 0;
        for (int i=1;i<argc;i++) len += strlen(argv[i]) + 1;
        char *joined = malloc(len+1);
        joined[0]='\0';
        for (int i=1;i<argc;i++) { strcat(joined, argv[i]); if (i+1<argc) strcat(joined, " "); }
        expr = joined;
    } else {
        // read from stdin
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        // trim newline
        size_t L = strlen(buf); if (L && (buf[L-1]=='\n' || buf[L-1]=='\r')) buf[L-1]='\0';
        expr = buf;
    }

    ETNode *root = constructTreeFromPostfix(expr);
    if (!root) {
        fprintf(stderr, "Failed to construct expression tree (invalid postfix?)\n");
        if (argc>=2) free((char*)expr);
        return 1;
    }

    printf("Infix (with parentheses): "); inorder(root); printf("\n");
    printf("Postfix: "); postorder(root); printf("\n");
    printf("Evaluated value: %ld\n", evaluate(root));

    freeTree(root);
    if (argc>=2) free((char*)expr);
    return 0;
}

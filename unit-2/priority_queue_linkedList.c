// Priority queue using linked list (higher numeric value = higher priority)
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node* next;
};

/* Create a new node */
struct Node* newNode(int d, int p) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    if (!temp) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
    return temp;
}

/* Insert based on priority (higher priority first).
   If priorities are equal, insertion is stable: new node goes after existing nodes
   with the same priority (i.e., FIFO for same priority). */
void push(struct Node** head, int d, int p) {
    struct Node* temp = newNode(d, p);

    /* Special case: empty list or new node has higher priority than head */
    if (*head == NULL || (*head)->priority < p) {
        temp->next = *head;
        *head = temp;
        return;
    }

    /* Locate the node after which the new node is to be inserted.
       We stop when next is NULL or next has strictly lower priority. */
    struct Node* start = *head;
    while (start->next != NULL && start->next->priority >= p) {
        start = start->next;
    }

    temp->next = start->next;
    start->next = temp;
}

/* Remove element with highest priority (head) */
void pop(struct Node** head) {
    if (*head == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct Node* temp = *head;
    printf("Deleted: data=%d priority=%d\n", temp->data, temp->priority);
    *head = (*head)->next;
    free(temp);
}

/* Display queue contents from head to tail */
void display(struct Node* head) {
    if (head == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Priority Queue (data, priority):\n");
    while (head != NULL) {
        printf("(%d, p=%d)\n", head->data, head->priority);
        head = head->next;
    }
}

/* Free entire queue */
void freeQueue(struct Node** head) {
    struct Node* cur = *head;
    while (cur != NULL) {
        struct Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}

int main(void) {
    struct Node* pq = NULL;
    int ch, val, p;

    while (1) {
        printf("\n1. Insert\n2. Remove\n3. Display\n4. Exit\n");
        if (scanf("%d", &ch) != 1) {
            fprintf(stderr, "Invalid input\n");
            break;
        }

        switch (ch) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &val) != 1) { fprintf(stderr, "Invalid input\n"); break; }
                printf("Enter priority: ");
                if (scanf("%d", &p) != 1) { fprintf(stderr, "Invalid input\n"); break; }
                push(&pq, val, p);
                break;

            case 2:
                pop(&pq);
                break;

            case 3:
                display(pq);
                break;

            case 4:
                freeQueue(&pq);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    freeQueue(&pq);
    return 0;
}

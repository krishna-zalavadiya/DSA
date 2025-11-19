#include <stdio.h>
#include <stdlib.h>

// Node structure for Circular Doubly Linked List
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Structure to hold head pointer separately
typedef struct {
    Node *head;
} CircularDoublyList;

// Function prototypes
void insertFront(CircularDoublyList *list, int value);
void deleteFront(CircularDoublyList *list);
void insertEnd(CircularDoublyList *list, int value);
void deleteEnd(CircularDoublyList *list);
void insertAtPos(CircularDoublyList *list, int value, int pos);
void deleteAtPos(CircularDoublyList *list, int pos);
void displayForward(CircularDoublyList *list);
void displayBackward(CircularDoublyList *list);
int getLength(CircularDoublyList *list);

int main() {
    CircularDoublyList list;
    list.head = NULL;

    insertFront(&list, 10);
    insertFront(&list, 20);
    insertEnd(&list, 30);
    insertAtPos(&list, 40, 2);
    displayForward(&list);
    displayBackward(&list);

    deleteFront(&list);
    deleteEnd(&list);
    deleteAtPos(&list, 2);
    displayForward(&list);

    return 0;
}

// Insert at front
void insertFront(CircularDoublyList *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;

    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    } else {
        Node *last = list->head->prev;

        newNode->next = list->head;
        newNode->prev = last;
        last->next = newNode;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

// Delete from front
void deleteFront(CircularDoublyList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = list->head;
    if (temp->next == temp) { // Only one node
        free(temp);
        list->head = NULL;
        return;
    }

    Node *last = temp->prev;
    last->next = temp->next;
    temp->next->prev = last;
    list->head = temp->next;
    free(temp);
}

// Insert at end
void insertEnd(CircularDoublyList *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;

    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    } else {
        Node *last = list->head->prev;

        newNode->next = list->head;
        newNode->prev = last;
        last->next = newNode;
        list->head->prev = newNode;
    }
}

// Delete from end
void deleteEnd(CircularDoublyList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *last = list->head->prev;
    if (last->next == last) { // Only one node
        free(last);
        list->head = NULL;
        return;
    }

    Node *secondLast = last->prev;
    secondLast->next = list->head;
    list->head->prev = secondLast;
    free(last);
}

// Insert at specific position (1-based index)
void insertAtPos(CircularDoublyList *list, int value, int pos) {
    int len = getLength(list);
    if (pos < 1 || pos > len + 1) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        insertFront(list, value);
        return;
    }
    if (pos == len + 1) {
        insertEnd(list, value);
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;

    Node *temp = list->head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;

    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

// Delete at specific position (1-based index)
void deleteAtPos(CircularDoublyList *list, int pos) {
    int len = getLength(list);
    if (pos < 1 || pos > len) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        deleteFront(list);
        return;
    }
    if (pos == len) {
        deleteEnd(list);
        return;
    }

    Node *temp = list->head;
    for (int i = 1; i < pos; i++)
        temp = temp->next;

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
}

// Display list forward
void displayForward(CircularDoublyList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = list->head;
    printf("List (Forward): ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != list->head);
    printf("\n");
}

// Display list backward
void displayBackward(CircularDoublyList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *last = list->head->prev;
    Node *temp = last;
    printf("List (Backward): ");
    do {
        printf("%d ", temp->data);
        temp = temp->prev;
    } while (temp != last);
    printf("\n");
}

// Get length of the list
int getLength(CircularDoublyList *list) {
    if (list->head == NULL) return 0;

    int count = 0;
    Node *temp = list->head;
    do {
        count++;
        temp = temp->next;
    } while (temp != list->head);
    return count;
}
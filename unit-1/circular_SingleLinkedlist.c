#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structure to hold the head pointer (different from Node)
typedef struct {
    Node *head;
} CircularList;

// Function prototypes
void insertFront(CircularList *list, int value);
void deleteFront(CircularList *list);
void insertEnd(CircularList *list, int value);
void deleteEnd(CircularList *list);
void insertAtPos(CircularList *list, int value, int pos);
void deleteAtPos(CircularList *list, int pos);
void display(CircularList *list);
int getLength(CircularList *list);

int main() {
    CircularList list;
    list.head = NULL;

    insertFront(&list, 10);
    insertFront(&list, 20);
    insertEnd(&list, 30);
    insertAtPos(&list, 40, 2);
    display(&list);

    deleteFront(&list);
    deleteEnd(&list);
    deleteAtPos(&list, 2);
    display(&list);

    return 0;
}

// Insert at front
void insertFront(CircularList *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;

    if (list->head == NULL) //empty list
	{
        newNode->next = newNode;
        list->head = newNode;
    } else {
        Node *temp = list->head;
        while (temp->next != list->head)
            temp = temp->next;
        newNode->next = list->head;
        temp->next = newNode;
        list->head = newNode;
    }
}

// Delete from front
void deleteFront(CircularList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = list->head;
    if (temp->next == list->head) //only one node
	{ 
        free(temp);
        list->head = NULL;
        return;
    }

    Node *last = list->head;
    while (last->next != list->head)
        last = last->next;
    last->next = temp->next;
    list->head = temp->next;
    free(temp);
}

// Insert at end
void insertEnd(CircularList *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;

    if (list->head == NULL) {
        newNode->next = newNode;
        list->head = newNode;
    } 
	else {
        Node *temp = list->head;
        while (temp->next != list->head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = list->head;
    }
}

// Delete from end
void deleteEnd(CircularList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = list->head;
    if (temp->next == list->head) {
        free(temp);
        list->head = NULL;
        return;
    }

    Node *prev = NULL;
    while (temp->next != list->head) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = list->head;
    free(temp);
}

// Insert at specific position (1-based index)
void insertAtPos(CircularList *list, int value, int pos) {
    int len = getLength(list);
    if (pos < 1 || pos > len + 1) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        insertFront(list, value);
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;

    Node *temp = list->head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
}

// Delete at specific position (1-based index)
void deleteAtPos(CircularList *list, int pos) {
    int len = getLength(list);
    if (pos < 1 || pos > len) {
        printf("Invalid position.\n");
        return;
    }
    if (pos == 1) {
        deleteFront(list);
        return;
    }

    Node *temp = list->head;
    Node *prev = NULL;
    for (int i = 1; i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    free(temp);
}

// Display the list
void display(CircularList *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *temp = list->head;
    printf("List: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != list->head);
    printf("\n");
}

// Get length of the list
int getLength(CircularList *list) {
    if (list->head == NULL) return 0;

    int count = 0;
    Node *temp = list->head;
    do {
        count++;
        temp = temp->next;
    } while (temp != list->head);
    return count;
}

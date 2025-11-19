// Priority queue using linked list
#include <stdio.h>
#include <stdlib.h>
struct Node {
int data;
int priority;
struct Node* next;
};
// Create a new node
struct Node* newNode (int d, int p) {
struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
temp->data = d;
temp->priority = p;
temp->next = NULL;
return temp;
}
// Insert based on priority (higher priority first)
void push(struct Node** head, int d, int p) {
struct Node* start = *head;
struct Node* temp = newNode (d, p);
// Special case: new node has higher priority than head
if (*head == NULL || (*head)->priority < p) {
temp->next = *head;
*head = temp;
} else {
// Traverse and find position
while (start->next != NULL && start->next->priority >= p)// >= ko yaad rakhna
 {
start = start->next;
temp->next = start->next;
start->next = temp;
}
}
}
// Remove element with highest priority
void pop (struct Node** head) {
if (*head == NULL) {
printf("Queue is empty!\n");
return;
}
struct Node* temp = *head;
printf("Deleted: data=%d priority=%d\n", temp->data, temp->priority);
*head = (*head) ->next;
free (temp);
}
// Display queue
void display (struct Node* head) {
if (head == NULL) {
}
printf("Queue is empty!\n");
return;
printf("Priority Queue:\n");
while (head != NULL) {
printf("data=%d priority=%d\n", head->data, head->priority);
head = head->next;
}
}
int main() {
struct Node* pq = NULL;
int ch, val, p;
while (1) {
printf("\n1. Insert\n2. Remove\n3. Display\n4. Exit\n");
scanf("%d", &ch);
switch (ch) {
    case 1:
printf ("Enter value: ");
scanf("%d", &val);
printf ("Enter priority: ");
scanf("%d", &p);
push (&pq, val, p);
break;
case 2:
pop(&pq);
break;
case 3:
display (pq);
break;
case 4:
exit(0);
default:
printf("Invalid choice!\n");
}
}
return 0;
}
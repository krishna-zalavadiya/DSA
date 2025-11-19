#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data;
    int priority;
} Element;

typedef struct {
    Element arr[MAX];
    int size;
} PriorityQueue;

// Initialize
void init(PriorityQueue *pq) {
    pq->size = 0;
}

// Check if empty
int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

// Enqueue
void enqueue(PriorityQueue *pq, int value, int priority) {
    if (pq->size == MAX) {
        printf("Queue is full!\n");
        return;
    }
    pq->arr[pq->size].data = value;
    pq->arr[pq->size].priority = priority;
    pq->size++;
    printf("Inserted %d with priority %d\n", value, priority);
}

// Dequeue (remove highest priority)
int dequeue(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty!\n");
        return -1;
    }

    // Find index of element with highest priority (lowest priority value)
    int highest = 0;
    for (int i = 1; i < pq->size ; i++) {
        if (pq->arr[i].priority < pq->arr[highest].priority)
            highest = i;
    }

    int value = pq->arr[highest].data;

    // Shift elements to fill the gap
    for (int i = highest; i < pq->size - 1; i++) {
        pq->arr[i] = pq->arr[i + 1];
    }

    pq->size--;
    return value;
}

// Display
void display(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Priority Queue: ");
    for (int i = 0; i < pq->size; i++) {
        printf("(%d,p=%d) ", pq->arr[i].data, pq->arr[i].priority);
    }
    printf("\n");
}

// Main for testing
int main() {
    PriorityQueue pq;
    init(&pq);

    enqueue(&pq, 10, 3);
    enqueue(&pq, 20, 1);
    enqueue(&pq, 30, 2);
    display(&pq);

    printf("Dequeued: %d\n", dequeue(&pq));
    display(&pq);

    return 0;
}





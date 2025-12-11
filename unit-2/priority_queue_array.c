/* priority queues - extension of queue where every item has priority associated to it
2 types = ascending(item with lowest priority is removed) and descending(item with highest priority is removed)
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ priority queues implementation using arrays ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
// descending priority queue

#include <stdio.h>
#include <stdlib.h>
#define max 10
typedef struct priorityq
{
    int data;
    int p;
} PQ;

PQ pq[max];
int size = 0;

void enqueue(int data, int priority);
int dequeue();
void display();
int main()
{
    int ch, data, priority, res;
    while (1)
    {
        printf("\n 1. enqueue\n 2. dequeue\n 3. display\n");
        printf("enter your choice\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("enter element to the queue\n");
            scanf("%d", &data);
            printf("enter the priority of the element\n");
            scanf("%d", &priority);
            enqueue(data, priority);
            break;
        case 2:
            res = dequeue();
            if (res == 0)
                printf("queue is empty\n");
            else
                printf("deleted element is %d\n", res);
            break;
        case 3:
            display();
            break;
        default:
            exit(0);
        }
    }
    return 0;
}

void enqueue(int data, int priority)
{
    if (size == max)
        printf("queue overloaded\n");
    else
    {
        pq[size].data = data;
        pq[size].p = priority;
        size++;

        // sorting the queue based on priority
        for (int i = size - 1; i >0; i--)
        {
            if (pq[i].p > pq[i - 1].p) // if element with index 3 has higher priority than 2...swap them
            {
                PQ temp = pq[i];
                pq[i] = pq[i - 1];
                pq[i - 1] = temp;
            }
        }
    }
}

int dequeue()
{
    if (size == 0)
        return 0;
    else
    {
        int data = pq[0].data;
        for (int i = 0; i < size; i++)
            pq[i] = pq[i + 1];
        size--;
        return data;
    }
}

void display()
{
    if (size == 0)
        printf("empty priority queue\n");
    else
    {
        for (int i = 0; i < size; i++)
            printf("ele = %d and p = %d\n", pq[i].data, pq[i].p);
    }
}
 */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~priority queues with linked list ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <stdio.h>
#include <stdlib.h>
#define max 10
typedef struct priorityq
{
    int data;
    int p;
    struct priorityq *link;
} PQ;

PQ *front = NULL;

PQ *create_node(int data,int priority)
{
    PQ *temp = (PQ *)malloc(sizeof(PQ));
    temp->data = data;
    temp->p = priority;
    temp->link = NULL;
}
void enqueue(int data, int priority);
int dequeue();
void display();
int main()
{
    int ch, data, priority, res;
    while (1)
    {
        printf("\n 1. enqueue\n 2. dequeue\n 3. display\n");
        printf("enter your choice\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("enter element to the queue\n");
            scanf("%d", &data);
            printf("enter the priority of the element\n");
            scanf("%d", &priority);
            enqueue(data, priority);
            break;
        case 2:
            res = dequeue();
            if (res == 0)
                printf("queue is empty\n");
            else
                printf("deleted element is %d\n", res);
            break;
        case 3:
            display();
            break;
        default:
            exit(0);
        }
    }
    return 0;
}

void enqueue(int data, int priority)
{
    PQ *temp = create_node(data,priority);
    if(front == NULL)
        front = temp;
    else
    {
        PQ *pres = front;
        while(pres->link != NULL && pres->link->p > priority)
            pres=pres->link;
        temp->link = pres->link;
        pres->link = temp;  
    }
}

int dequeue()
{
    if(front == NULL)
    {
        printf("the queue is empty\n");
        return 0;
    }
    else
    {
        PQ *p = front;
        int data = p->data;
        front = front->link;
        free(p);
        return data;
    }
}

void display()
{
    if(front == NULL)
    {
        printf("the queue is empty\n");
    }
    else
    {
        PQ *temp  = front;
        while(temp != NULL)
        {
            printf("%d value of priority %d\n",temp->data,temp->p);
            temp = temp->link;
        }
    }
}





void enqueue(int data,int priority)
{
    PQ *temp = create_node(data,priority);
    if(front == NULL)
        front = temp;
    else
    {
        PQ *p = front;
        while(p->link != NULL && p->link->p > priority)
            p = p->link;
        temp->link = p->link;
        p->link = temp;
    }
}
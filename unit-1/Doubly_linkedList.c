#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;//holds the address of next node
    struct node *prev;//holds the address of previous node
};
typedef struct node dll_node;

// Global head pointer instead of dlist structure
dll_node *head = NULL;

void init_list();
void insert_head(int data);
void display();
void insert_tail(int data);
void delete_first();
void delete_last();
void delete_node(int data);
void delete_pos(int pos);
void insert_pos(int data, int pos);

int main()
{
    int ch, data, pos, value;
    init_list();

    while (1)
    {
        display();
        printf("\n1..insert_head");
        printf("\n2..insert_tail");
        printf("\n3..Display");
        printf("\n4.delete first node");
        printf("\n5. Delete Last Node..");
        printf("\n6 .Delete a node given value");
        printf("\n7.Delete at a position");
        printf("\n8.Insert at a Given Position");
        printf("\n9.Exit");

        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("\nEnter the data...");
            scanf("%d", &data);
            insert_head(data);
            break;
        case 2:
            printf("\nEnter the data...");
            scanf("%d", &data);
            insert_tail(data);
            break;
        case 3:
            display();
            break;
        case 4:
            delete_first();
            break;
        case 5:
            delete_last();
            break;
        case 6:
            printf("\nEnter the data...");
            scanf("%d", &data);
            delete_node(data);
            break;
        case 7:
            printf("\nEnter the position");
            scanf("%d", &pos);
            delete_pos(pos);
            break;
        case 8:
            printf("\nEnter the data and position");
            scanf("%d %d", &data, &pos);
            insert_pos(data, pos);
            break;
        case 9:
            exit(0);
        }
    }
}

void init_list()
{
    head = NULL;//making empty list
}

void insert_head(int data)
{
    dll_node *temp=(dll_node *)malloc(sizeof(dll_node));//allocating memory
    temp->data=data;
    temp->next=NULL;
    temp->prev=NULL;
    if(head==NULL)
    {
        head=temp;
    }
    else
    {
        temp->next=head;//assigning the next field to ptr head 
        head->prev=temp;
        head=temp;
    }
}

void display()
{
    dll_node *pres=head;
    while(pres!=NULL)//traversing the present next node until reaches end
    {
        printf("%d<->",pres->data);
        pres=pres->next;
    }
    printf("\n");
}

void insert_tail(int data)
{
    dll_node *temp=(dll_node *)malloc(sizeof(dll_node));//allocating memory
    temp->data=data;
    temp->next=NULL;
    temp->prev=NULL;
    dll_node *pres=head;
    if(head==NULL)//list was empty
    {
        head=temp;
    }
    else{
        while(pres->next!=NULL)
        {
            pres=pres->next;
        }
        pres->next=temp;//linking the last part of present to last node prev field
        temp->prev=pres;//linking the previous part of node to the second last nodes next field
    }
}

void delete_first()
{
    if(head == NULL) {
        printf("\nList is empty\n");
        return;
    }
    
    dll_node *pres=head;
    if(pres->next==NULL)
    {
        head=NULL;
    }
    else{
        head=pres->next;//moving the head to the second node
        head->prev=NULL;//making the second nodes previous field NULL
    }
    free(pres);
}

void delete_last()
{
    if(head == NULL) {
        printf("\nList is empty\n");
        return;
    }
    
    dll_node *pres=head;
    if(pres->next==NULL)
    {
        head=NULL;
    }
    else
    {
        while(pres->next!=NULL)
        {
            pres=pres->next;
        }
        (pres->prev)->next=NULL;//making the second last nodes next field as NULL
    }
    free(pres);
}

//deleting the node on basis of data
void delete_node(int data)
{
    dll_node *pres;

    pres = head;

    // find the node
    while ((pres != NULL) && (pres->data != data))
        pres = pres->next;
    if (pres != NULL) // node found
    {
        // if only one node
        if ((pres->next == NULL) && (pres->prev == NULL))
            head = NULL;
        else if (pres->prev == NULL) // first node
        {
            pres->next->prev = NULL;
            head = pres->next;
        }
        else if (pres->next == NULL) // last node
            (pres->prev)->next = NULL;
        else // somewhere in the middle
        {
            (pres->prev)->next = pres->next;//linking the nodes in bidirectional
            (pres->next)->prev = pres->prev;//linking the nodes in bidirectional
        }
        free(pres);
    }
    else // pres==NULL
        printf("\nNode not found..\n");
}

void delete_pos(int pos)
{
    dll_node *pres;
    int i;
    pres = head;

    // find the node at given position
    i = 1;
    while ((pres != NULL) && (i < pos))
    {
        i++;
        pres = pres->next;
    }
    if (pres != NULL) // position found
    {
        // if only one node
        if ((pres->next == NULL) && (pres->prev == NULL))
            head = NULL;
        else if (pres->prev == NULL) // first node
        {
            (pres->next)->prev = NULL;
            head = pres->next;
        }
        else if (pres->next == NULL) // last node
            (pres->prev)->next = NULL;
        else // somewhere in the middle
        {
            (pres->prev)->next = pres->next;//linking the nodes bidirectional
            (pres->next)->prev = pres->prev;//linking the nodes bidirectional
        }
        free(pres);
    }
    else // pres==NULL
        printf("\nNode not found..Invalid position\n");
}

void insert_pos(int data, int pos)
{
    dll_node *temp, *pres;
    int i;

    temp = (dll_node *)malloc(sizeof(dll_node));
    temp->data = data;
    temp->next = temp->prev = NULL;

    // empty list special case
    if (head == NULL) {
        if (pos == 1) {
            head = temp;
        } else {
            printf("\nInvalid position\n");
            free(temp);
        }
        return;
    }

    // inserting at head
    if (pos == 1) {
        temp->next = head;
        head->prev = temp;
        head = temp;
        return;
    }

    pres = head;
    i = 1;

    // move till (pos-1)th node we aren't doing for entering the data at last position...
    while (pres != NULL && i < pos - 1) {
        pres = pres->next;
        i++;
    }

    if (pres == NULL) {
        printf("\nInvalid position\n");
        free(temp);
        return;
    }

    // if inserting at end
    if (pres->next == NULL) {
        pres->next = temp;
        temp->prev = pres;
    } else {
        // inserting in the middle
        temp->next = pres->next;
        temp->prev = pres;
        pres->next->prev = temp;
        pres->next = temp;
    }
}
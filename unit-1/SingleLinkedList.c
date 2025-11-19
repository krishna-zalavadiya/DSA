#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;//stores the data of the node
    struct node *link;//self referential structure it is pointer to the next node
};
typedef struct node sll_node;

struct list {
    sll_node *head;//pointer to the first node
};

typedef struct list LIST;

void init_list(LIST *ptr_list);//creates an empty list
void insert_front(LIST *ptr_list, int data);
void insert_end(LIST *ptr_list, int data);
void insert_pos(LIST *ptr_list, int data, int pos);
void display(LIST *ptr_list);
int count_node_recur(sll_node *pres);
int count_node(LIST *ptr_list);
void delete_node(LIST *ptr_list, int data);
void delete_pos(LIST *ptr_list, int pos);
void ordered_insert(LIST *ptr_list, int data);


int main() 
{
    LIST l;
    init_list(&l);   // Initialize empty list

    int n, ch, pos;
    while (1)//for multiple execution of the while loop until users enter 10
     {
        printf("\n");
        display(&l);  // Display current list
        printf("\n1..Insert at head\n");
        printf("2..Insert at end\n");
        printf("3..Display\n");
        printf("4..Insert at a given position\n");
        printf("5..Count number of nodes (recursion)\n");
        printf("6..Delete node by value\n");
        printf("7..Delete node at a given position\n");
        printf("8..Exit\n");
        

        scanf("%d", &ch);  // Take user choice

        switch (ch) {
        case 1:
            printf("\nEnter the element to be inserted: ");
            scanf("%d", &n);
            insert_front(&l, n);
            break;

        case 2:
            printf("\nEnter the element to be inserted: ");
            scanf("%d", &n);
            insert_end(&l, n);
            break;

        case 3:
            display(&l);
            break;

        case 4:
            printf("\nEnter the element and position: ");
            scanf("%d %d", &n, &pos);
            insert_pos(&l, n, pos);
            break;

        case 5:
            printf("Counting nodes using recursion...\n");
            int k = count_node(&l);
            printf("The number of nodes = %d\n", k);
            break;

        case 6:
            printf("Enter the element to be deleted: ");
            scanf("%d", &n);
            delete_node(&l, n);
            break;

        case 7:
            printf("\nEnter the position to delete: ");
            scanf("%d", &pos);
            delete_pos(&l, pos);
            break;
        case 8:
            printf("\nEnter the element to be inserted in order: ");
            scanf("%d", &n);
            ordered_insert(&l, n);
            break;
        case 9:
            exit(0);
        }
    }
}

    void init_list(LIST *ptr_list)//empty list
    {
       ptr_list->head=NULL;
    }

    //insesrt at the beginning 
    void insert_front(LIST *ptr_list,int data)
    {
        sll_node *temp=(sll_node *)malloc(sizeof(sll_node));//making a new node
        temp->data=data;
        temp->link=NULL;
        //if the list is empty then the temp is the head and the link will not be affected it will be null
        if(ptr_list->head==NULL)//checking the value of head is null
        {
            ptr_list->head=temp;//storing the value of temp to ptr_list
        }
        else
        {
        temp->link=ptr_list->head;//we are linking the temp to the head 
        ptr_list->head=temp;//changing the pointer to temp
        }
    } 

    void display(LIST *ptr_list)
    {
        sll_node *pres = ptr_list->head;//we are storing the address pf the head
        if(ptr_list->head==NULL)//the data is null
        {
            printf("\n Empty list.\n");
        } 
        else
        {
            while(pres != NULL)
            {
                printf("%d",pres->data);
                pres=pres->link;
            }
        }

    }


    void insert_end(LIST *ptr_list , int data)
    {
        sll_node *pres = ptr_list->head;//we are storing the address of the head
        sll_node *temp = (sll_node*)malloc(sizeof(sll_node));//allocating memory to temp storing the data and setting the link to null
        temp->data = data;
        temp->link = NULL;
        if(ptr_list->head==NULL)//checking whether the list is empty or not
        {
            ptr_list->head=temp;
        }
        else
        {
            while(pres->link!=NULL)
            {
                pres=pres->link;//traverssing till last node
            }
            pres->link=temp;//we put the adress of the new node to the last node
        }
    }


    void insert_pos(LIST *ptr_list,int data,int pos)
    {
        sll_node *pres=ptr_list->head;//adress storing of the head node
        sll_node *temp=(sll_node *)malloc(sizeof(sll_node));//making a temp node to store the data
        temp->data = data;
	    temp->link = NULL;
        int i=1;
        sll_node *prev=NULL;
        while((pres!=NULL) && (i<pos))
        {
            i++;
            prev=pres;
            pres=pres->link;
        }

        if (pres != NULL) //position is found in between first and last node
        {
            if (prev == NULL) 
            {  // inserting at position 1
                temp->link = pres;
                ptr_list->head = temp;
            } 
            else 
            {  // inserting in middle anywhere
                temp->link = pres;
                prev->link = temp;
            }
        } 
        else//pres is null
            {
                if (i == pos)  // inserting at end
                    prev->link = temp;
                else
                    printf("\nInvalid position..\n");
            }
    }
    int count_node(LIST *ptr_list)
    {
        sll_node *pres=ptr_list->head;
        int count=0;
        while(pres!=NULL)
        {
            count++;
            pres=pres->link;
        }
        return count;
    }

    //using recurssion we are counting the nodes
    int count_node_recur(sll_node *pres)
    {
	int count = 0;
	if (pres->link == NULL) // only one node is present so return 1
		return 1;
	count = 1 + count_node_recur(pres->link);
	return count;
    }


    //deleting the node by finding the data
    void delete_node(LIST *ptr_list,int data)
    {
        sll_node *pres=ptr_list->head;
        sll_node *prev=NULL;
        while((pres!=NULL) && (pres->data != data))//traversing the pres until data is found or it points to the last node
        {
            prev=pres;
            pres=pres->link;
        }
        if(pres!=NULL)//node exist with such data
        {
            if(prev==NULL)//it is the the first node
            {
                ptr_list->head=pres->link;//we move the ptr_head to the next node and then free the pres
            }
            else
            {
                prev->link=pres->link;
            }
            free(pres);
        }
        else
            printf("NODE not found");
    }


    //deleting the node with respect to the position
    void delete_pos(LIST *ptr_list, int pos)
    {
	sll_node *pres, *prev;
	pres = ptr_list->head;
	prev = NULL;

	int i = 1;
	// move forward until the postion is found
	while ((pres != NULL) && (i < pos))
	{
		i++;
		prev = pres;
		pres = pres->link;
	}

	if (pres != NULL) // position found
	{
		// if first position
		if (prev == NULL)
			ptr_list->head = pres->link; // make head point to second node
		else							 // not the first node
			prev->link = pres->link;
		free(pres);
	}
	else
		printf("Invalid Position..\n");
    }
    
    void ordered_insert(LIST *ptr_list, int data)
    {
        sll_node *pres = ptr_list->head;
        sll_node *temp = (sll_node *)malloc(sizeof(sll_node));
        temp->data = data;
        temp->link = NULL;
        sll_node *prev = NULL;

        // Traverse to find the correct position to insert
        while ((pres != NULL) && (pres->data < data))
        {
            prev = pres;
            pres = pres->link;
        }

        // Insert at the beginning
        if (prev == NULL)
        {
            temp->link = ptr_list->head;
            ptr_list->head = temp;
        }
        else // Insert in between or at the end
        {
            temp->link = pres;
            prev->link = temp;
        }
    }








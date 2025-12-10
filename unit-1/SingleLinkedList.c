#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *link;
};

typedef struct node NODE;

NODE* create_node(int);
void insert_at_front(int, NODE**);
void insert_at_end(int, NODE**);
void del_from_front(NODE**);
void del_from_end(NODE**);
void ins_at_pos(int ,int, NODE**);
void del_at_pos(int, NODE**);
void display(NODE*);
void insert_in_order(int, NODE**);
int find_key(int, NODE*);
void list_reverse(NODE **);

int main()
{
	int choice,x,x1,pos;
	NODE *start ;
	start=NULL;
	printf("Enter your choice \n1) Insert data at front of the list\n2) Insert data at end of the list\n3) Display the list");
	printf("\n4) Delete data from front of the list\n5) Delete data from end of the list\n6) Insert data at a given position\n7) Delete data at a given position \n");
	printf("8) Insert data in ordered manner \n9) Find the data \n10) Reverse Linked List");
	while(1)
	{
		printf("\nEnter your choice\n");
		scanf("%d", &choice);
		switch(choice)
		{

		case 1: {
			printf("Enter the element");
			scanf("%d", &x);
			insert_at_front(x, &start);
				}
				break;

		case 2: {
			printf("Enter the element");
			scanf("%d", &x);
			insert_at_end(x, &start);
				}
				break;

		case 3: {
			printf("The element in the list are: \t");
			display(start);
				}
				break;
		case 4: {
			del_from_front(&start);
			//printf("The deleted element is  %d\n", x1 );
				}
				break;
		case 5: {
			del_from_end(&start);
			//printf("The deleted element is  %d\n", x1 );
				}
				break;
		case 6: {
			printf("Enter the element and its position to be inserted ");
			scanf("%d%d",&x,&pos);
			ins_at_pos(x,pos, &start);
				}
				break;
		case 7: {
			printf("Enter the position of the node to be deleted ");
			scanf("%d", &pos);
			del_at_pos(pos, &start);
				}
				break;
		case 8: {
			printf("Ordered Insertion\n Enter the element");
			scanf("%d", &x);
			insert_in_order(x, &start);
				}
				break;
		case 9: {
			printf("Search a key element");
			scanf("%d", &x);
			x=find_key(x, start);
			if (x) printf("successful search");
			else  printf("unsuccessful search");
				}
				break;
                case 10: {
                          list_reverse(&start);
                          break;
                         }
                          
		default: {
			printf("Invalid choice \t"); 
			exit(1);
				 }
				 break;
		}
	}
	return(0);
}

NODE* create_node(int x)
{
	NODE *new_node = (NODE *)(malloc(sizeof(NODE)));
	new_node->data=x;
	new_node->link=NULL;
	return new_node;
}

void insert_at_front(int x, NODE **pstart)
{
	NODE *new_node = create_node(x);
	if (*pstart == NULL)
		*pstart = new_node;
	else {
		new_node->link=*pstart;
		*pstart=new_node;
	}
}

void insert_at_end(int x, NODE **pstart)
{
	NODE *dstart;
	NODE *new_node = create_node(x);
	if( *pstart==NULL)
		*pstart=new_node;
	else {
		dstart=*pstart;
		while(dstart->link!=NULL)
			dstart=dstart->link;
		dstart->link=new_node;
	}
}

void display(NODE* start)
{
	
	if(start==NULL) 
		printf("Empty List ");
	else {
		
		printf("The List is.....\n");
		while(start!=NULL)
		{ 
			printf("\t%d", start->data); 
			start=start->link;
		}     
	}
}

void del_from_front(NODE** pstart)
{
	NODE *temp; 
	int x;
	if (*pstart == NULL)
		printf("List is empty");
	else {
		temp=*pstart;
		*pstart = (*pstart)->link;
		printf("deleted element is %d",temp->data);
		free(temp);
		return; 
	}
}

void del_from_end(NODE** pstart)
{
	NODE  *prev,*dstart; 
	int x;
	if (  *pstart == NULL)
		printf("List is empty");
	else if((*pstart)->link==NULL)
	{
		dstart=*pstart;
		*pstart=NULL;
		free(dstart); 
	}
	else {
		dstart=*pstart;
		while(dstart->link!=NULL)
		{
			prev =dstart;
			dstart=dstart->link;
		}
		prev->link=NULL;
		printf(" The deleted element is %d", dstart->data);
		free(dstart);
	}
}


void ins_at_pos(int x,int pos, NODE** pstart)
{
	int i=1;
	NODE *dstart, *prev, *new_node;
	new_node = create_node(x);
	 
	if(pos==1) 
	{
		new_node->link = *pstart;
		*pstart=new_node;
	}
	else  {
		dstart=*pstart;
		while(dstart->link!=NULL && i< pos)
		{
			prev = dstart;
			dstart=dstart->link;i++;
		}
		if(pos == i)
		{
			new_node->link = dstart;
			prev->link = new_node;
		}
		else if(++i==pos)
			dstart->link=new_node;
		else printf("Invalid Position");
	}
}

void del_at_pos(int pos, NODE** pstart)
{
	int i=1; 
	NODE *dstart, *prev;
	if(*pstart==NULL) 
		printf("Empty List");
	else {
		dstart=*pstart;
		if(pos==1) 
		{ 
			*pstart = (*pstart)->link;
			free(dstart);
		}
		else {  
			while(dstart->link!=NULL && i< pos)
			{ prev = dstart;
			dstart=dstart->link; i++;
			}
			if(pos == i)
			{  
				prev->link = dstart->link;
				free(dstart);
			}
			else printf("Invalid Position");
		}
	}
}

void insert_in_order(int x, NODE** pstart)
{ // descending order insert
	NODE *dstart, *prev, *new_node;
	new_node = create_node(x);
	if(*pstart==NULL) 
		*pstart=new_node;
	else if (new_node->data >= (*pstart)->data)
	{
		new_node->link=*pstart;
		*pstart=new_node;
	}

	else  {
		dstart=*pstart;
		while(dstart!=NULL && dstart->data > new_node->data)
		{
			prev = dstart;
			dstart=dstart->link;
		}
		
		new_node->link=dstart;
		prev->link=new_node;
		
	}
}

int find_key(int key, NODE* start)
{
	if(start==NULL)
          return 0;
	while(start!=NULL)
	{
		if(start->data==key)return 1;
		start=start->link;
	}
	return 0;
}
void list_reverse(NODE **pstart){
	NODE *prev=NULL;
	NODE *current;
        current=*pstart;
	NODE *next;
	while (current!=NULL){
		next=current->link;
		current->link=prev;
		prev=current;
		current=next;
	}
	*pstart=prev;
}
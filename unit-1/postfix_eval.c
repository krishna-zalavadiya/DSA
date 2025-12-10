#include<stdio.h>
#include<stdlib.h>
struct stack
{
	int *s;
	int size;
	int top;
};

typedef struct stack stack;

void init_stk(stack *);
void push(stack *, int);
int   pop(stack *);
int postfix_eval(char*);
 
int main()
{

 char postfix[100];
 printf("\nenter the postfix expression\n");
 scanf("%s",postfix);
 int result=postfix_eval(postfix);
 printf("\nthe result=%d\n",result);
 
}

int postfix_eval(char* postfix)
{
	int isoper(char );
	int i,result,op1,op2,a;
	char ch;
	i=0;
	stack st; //stack
	init_stk(&st); //initialise the stack
	while(postfix[i]!='\0')
	{
		ch=postfix[i];
		if(isoper(ch)) // if operator
		{
			 op1=pop(&st);
			 op2=pop(&st);
			 switch(ch)
			 {
				 case '+' : result=op1+op2;
				                  push(&st,result);
								  break;
				case '-':   result=op2-op1;
				                push(&st,result);
								  break;
			   case '*': result = op1*op2;
			                  push(&st,result);
								 break;
	            case '/' : result=op2/op1;
				                 push(&st,result);
								  break ;
			 }
		}			 
       else
	   {
		        printf("%c =",ch);
				scanf("%d",&a);
	            push(&st, a); 
	   }
	  i++;
	}
	 return(pop(&st)); //return the result
} 

//function to check if character is operand or operator
int isoper(char ch)
{
	if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/'))
		return 1;
	return 0;
}
	
//function to initiliaze the stack
void init_stk(stack *st)
{
	st->size=100; 
	st->top=-1;
	
	st->s= (int*)malloc(sizeof(int)*st->size);
}

void push(stack *st, int data)
{
		st->top++; 					//++st->top;
		st->s[st->top]=data;
	
}

int   pop(stack *st)
    {
		int k;
		k=st->s[st->top];//copy the top element into k
		st->top--;
		return k;
	}
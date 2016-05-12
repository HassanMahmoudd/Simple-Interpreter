#include <stdio.h>
#include <stdlib.h>

typedef struct Nodelist
{
    int data;
    char name[100];
    struct Nodelist* next;
} Nodelist;

typedef struct LinkedList
{
    Nodelist* head, *tail;
} LinkedList;

void initializeLinkedList(LinkedList* linkedlist)
{
    linkedlist->head = NULL;
    linkedlist->tail = NULL;
}

LinkedList linkedlist;

Nodelist* newNodelist(int value, char* var)
{
    Nodelist* n = (Nodelist*)malloc(sizeof(Nodelist));
    n->data = value;
    strcpy(n->name, var);
    return n;
}

void addTail(LinkedList* linkedlist, int value, char* var)
{
    Nodelist* n = newNodelist(value, var);
    Nodelist* tail = linkedlist->tail;
    linkedlist->tail = n;
    if(tail != NULL)
        tail->next = n;
    else
        linkedlist->head = n;
}

Nodelist* searchLinkedList(Nodelist* n, char* var)
{
    if(n == NULL)
        return NULL;
    if(strcmp(n->name, var) == 0)
        return n;
    else
        return searchLinkedList(n->next, var);
}

typedef struct Node
{
    int data1;
    struct Node* next;
} Node;

Node* newNode(int value)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->data1 = value;
    n->next = NULL;
    return n;
}

typedef struct
{
    Node* top;
} Stack;

void initialize(Stack* s)
{
    s->top = NULL;
}

int isEmpty(Stack* s)
{
    if(s->top != NULL)
        return 0;
    return 1;
}

void push(Stack* s, int value)
{
    Node* p = newNode(value);
    p->next = s->top;
    s->top = p;
}

int pop(Stack* s)
{
    Node* p = s->top;
    int data1 = p->data1;
    s->top = p->next;
    free(p);
    return data1;
}

int top(Stack* s)
{
    int x = pop(s);
    push(s, x);
    return x;
}

int isDigit(char C)
{
	if(C >= '0' && C <= '9')
        return 1;
	return 0;
}

int isChar(char C)
{
	if((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z'))
		return 1;
	return 0;
}

int priority(char op)
{
	switch(op)
	{
	case '+':
	case '-':
		return 0;
	case '*':
	case '/':
		return 1;
	case '(':
		return 2;
	}
}

char* infixToPostfix(char* exp)
{
    int i;
    int j=0;
    Stack s;
    initialize(&s);
    char* postfix = malloc(100);
    for(i=0; i<strlen(exp); i++)
    {
        if(exp[i] == ' ' || exp[i] == ',')
            continue;
        else if(isDigit(exp[i]))
        {
            while(isDigit(exp[i]))
            {
                postfix[j]= exp[i];
                j++;
                i++;
            }
            postfix[j++]=' ';
            i--;
        }

        else if(exp[i] == ')')
        {
            while(!isEmpty(&s) && top(&s)!='(')
            {
                postfix[j]= pop(&s);
                j++;
                postfix[j++]=' ';
            }
            pop(&s);
        }
        else if(exp[i] == '(')
        {
            push(&s, exp[i]);
        }

        else
        {
            while(!isEmpty(&s) && priority(top(&s)) >= priority(exp[i]) && top(&s) != '(')
            {
                postfix[j]= pop(&s);
                j++;
                postfix[j++]=' ';
            }
            push(&s, exp[i]);
        }
    }
    while(!isEmpty(&s))
    {
        postfix[j]= pop(&s);
        j++;
        postfix[j++]=' ';
    }
    postfix[j++] = '\0';
    char* temp = malloc(j*sizeof(char));
    strcpy(temp, postfix);
    return temp;
}

int evaluate(char x, int op1, int op2)
{
    if(x == '+')
        return(op1 + op2);
    if(x == '-')
        return(op1 - op2);
    if(x == '*')
        return(op1 * op2);
    if(x == '/')
        return(op1 / op2);
}

int evaluatePostfix(char* exp)
{
    Stack s;
    int op1, op2, value, i;
    initialize(&s);
    for(i=0; exp[i]!='\0'; i++)
    {
        if(exp[i] == ' ')
            continue;
        else if(exp[i]>='0' && exp[i]<='9')
        {
            int total = 0;
            while(exp[i]>='0' && exp[i]<='9')
            {
                total = total*10 + (exp[i]-'0');
                i++;
            }
            push(&s, total);
            i--;
        }
        else
        {
            op2 = pop(&s);
            op1 = pop(&s);
            value = evaluate(exp[i],op1,op2);
            push(&s, value);
        }
    }
    value = pop(&s);
    return value;
}


void newVariable(char* var, char* exp)
{
    char* temp = infixToPostfix(exp);
    int value = evaluatePostfix(temp);
    Nodelist* n = searchLinkedList(linkedlist.head, var);
    if(n == NULL)
        addTail(&linkedlist, value, var);
    else
        n->data = value;
}

void printLinkedList(Nodelist* n)
{
    while(n!=NULL)
    {
        printf("Variable name is: %s\n",n->name);
        printf("It's value is: %d\n",n->data);
        n=n->next;
    }
}

int main()
{
    initializeLinkedList(&linkedlist);
    int i;
    for(i=0; i<1; i++)
    {
        char var[100];
        char exp[100];
        printf("Please enter a variable name\n");
        scanf("%s",var);
        printf("Please enter an expression to evaluate\n");
        scanf("%s",exp);
        newVariable(var, exp);
    }
    printLinkedList(linkedlist.head);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main()
{
    char exp[100];
    printf("Please enter an expression\n");
    gets(exp);
    char* temp = infixToPostfix(exp);
    printf("%s\n",temp);
    int value = evaluatePostfix(temp);
    printf("%d",value);
    return 0;
}

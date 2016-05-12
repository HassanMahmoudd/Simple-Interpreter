#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayStruct
{
    char name[100];
    float data;
} ArrayStruct;

ArrayStruct* Collection[100];
int counter = 0;

ArrayStruct* newNodelist(float value, char* var)
{
    ArrayStruct* n = malloc(sizeof(ArrayStruct));
    n->data = value;
    //printf("%s\n",var);
    int i = 0;
    // strcpy(n->name, var);
    while(var[i] != '\0')
    {
        n->name[i] = var[i];
        i++;
    }
    n->name[i] = '\0';
    return n;
}

void addTail(float value, char* var)
{
    ArrayStruct* n = newNodelist(value, var);
    Collection[counter++] = n;
}

int stringCompare(char*x, char*y)
{
    // printf("%d\n",strlen(x));
    // printf("%d\n",strlen(y));
    if(strlen(x) == strlen(y))
    {
        int i;
        for(i=0; i<strlen(x); i++)
            if(x[i] != y[i])
                return 0;
        return 1;
    }
    return 0;
}

ArrayStruct* searchLinkedList(char* var)
{
    int i;
    // printf("%s\n",var);
    for(i=0; i<counter; i++)
    {
        //printf("%s\n",Collection[i]->name);
        //printf("%d\n",stringCompare(Collection[i]->name, var));
        //printf("%d\n",strlen(Collection[i]->name));
        //printf("%d\n",strlen(var));
        if(stringCompare(Collection[i]->name, var) == 1)
            return Collection[i];
    }
    return NULL;
}

typedef struct Node
{
    float data1;
    struct Node* next;
} Node;

Node* newNode(float value)
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

void push(Stack* s, float value)
{
    Node* p = newNode(value);
    p->next = s->top;
    s->top = p;
}

float pop(Stack* s)
{
    if(isEmpty(s))
        return -1000000;
    Node* p = s->top;
    float data1 = p->data1;
    s->top = p->next;
    free(p);
    return data1;
}

float top(Stack* s)
{
    float x = pop(s);
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

int isOperator(char C)
{
    if(C == '+' || C == '-' || C == '*' || C == '/' || C == '(' || C == ')')
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
    //printf("%s\n",exp);
    char postfix[100];
    for(i=0; i<strlen(exp); i++)
    {
        //printf("Test\n");
        //printf("%c\n",exp[i]);
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
            if(exp[i] == '.')
            {
                postfix[j]= exp[i];
                j++;
                i++;
                while(isDigit(exp[i]))
                {
                    postfix[j]= exp[i];
                    j++;
                    i++;
                }
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
            //printf("%c\n",exp[i]);
            while(!isEmpty(&s) && priority(top(&s)) >= priority(exp[i]) && top(&s) != '(')
            {
                //printf("%c\n",exp[i]);
                postfix[j]= pop(&s);
                j++;
                postfix[j++]=' ';
            }
            //printf("%c\n",exp[i]);
            push(&s, exp[i]);
            //printf("%.2f\n",top(&s));
        }
        //printf("Test2\n");
    }
    while(!isEmpty(&s))
    {
        postfix[j]= pop(&s);
        j++;
        postfix[j++]=' ';
    }
    postfix[j++] = '\0';
    //char* temp = malloc(j*sizeof(char));

    //strcpy(temp, postfix);
    //printf("%s\n",postfix);
    return postfix;
}

float evaluate(char x, float op1, float op2)
{
    if(x == '+')
        return(op1 + op2);
    if(x == '-')
        return(op1 - op2);
    if(x == '*')
        return(op1 * op2);
    if(x == '/')
    {
        if(op2 == 0)
            return 921995;
        return(op1 / op2);
    }

}

float evaluatePostfix(char* exp)
{
    Stack s;
    float op1, op2;
    int i, j;
    float value;

    initialize(&s);
    //printf("%s\n",exp);
    for(i=0; exp[i]!='\0'; i++)
    {
        if(exp[i] == ' ')
            continue;
        else if(exp[i]>='0' && exp[i]<='9')
        {
            j=0;
            char temp[100];
            while((exp[i]>='0' && exp[i]<='9') || exp[i] == '.')
            {
                temp[j] = exp[i];
                i++;
                j++;
            }
            i--;
            temp[j] = '\0';
            //printf("%s\n",temp);
            float temp1 = atof(temp);
            //printf("%.2f\n",temp1);
            push(&s, temp1);
        }
        else
        {

            op2 = pop(&s);
            op1 = pop(&s);
            //printf("%.2f\n",op2);
            //printf("%.2f\n",op1);
            if(op1 != -1000000 && op2 != -1000000)
            {
                value = evaluate(exp[i],op1,op2);
                if(value == 921995)
                    return 921995;
                push(&s, value);
            }
            else
                return 921995;

            //printf("%.2f\n",value);
        }
    }
    value = pop(&s);
    //printf("%.2f\n",value);
    return value;
}


void newVariable(char* var, char* exp)
{
    char* temp = infixToPostfix(exp);
    float value = evaluatePostfix(temp);
    ArrayStruct* n = searchLinkedList(var);
    if(n == NULL)
        addTail(value, var);
    else
        n->data = value;
}

void printLinkedList()
{
    int i;
    for(i=0; i<counter; i++)
    {
        printf("The name is: %s\n",Collection[i]->name);
        printf("The value is: %.2f\n",Collection[i]->data);
    }
}

char* convertIntoChar(char* var)
{
    char result[100];
    int i = 0;
    //printf("%s\n",var);
    ArrayStruct* n = searchLinkedList(var);
    //printf("%s\n",n->name);
    if(n == NULL)
    {

        return NULL;
    }

    else
    {
        float value = n->data;
        float temp = value;
        //printf("%.2f\n",temp);

        sprintf(result,"%.2f",temp);
        //result[i] = '\0';
        //printf("%s\n",result);
        //char* temp2 = malloc(i*sizeof(char));
        //strcpy(temp2, result);
        return result;
    }

}

int checkValid(char* exp)
{
    int i=0,j=0,z=0,h=0,k=0;
    char var[100];
    char res[100];
    while(exp[i] != '=')
    {
        if(exp[i] == ' ')
            i++;
        else if(isDigit(exp[i]) || isChar(exp[i]))
        {
            var[j] = exp[i];
            i++;
            j++;
        }
        else
            return 0;
    }
    var[j] = '\0';
    if(isDigit(var[h]))
        return 0;
    while(exp[i] != '\0')
    {
        if(exp[i] == ' ')
                i++;
        else if(exp[i] == '=')
        {
            i++;
            z++;
        }
        else if(isChar(exp[i]))
        {
            char temp[100];
            int x = 0;
            while(isChar(exp[i]) || isDigit(exp[i]))
            {
                        // printf("%c\n",total[i]);
                temp[x]=exp[i];
                x++;
                i++;
            }

            temp[x] = '\0';
            char* tempUsed = malloc(sizeof(j));
            strcpy(tempUsed, temp);
                    //printf("%s\n",tempUsed);
                    // printf("%d\n",strlen(temp));
            char* temp1 = convertIntoChar(tempUsed);
            if(temp1 == NULL)
                return 0;
            int y = 0;
            while(temp1[y] != '\0')
            {
                res[k] = temp1[y];
                k++;
                y++;
            }

        }
        else if(isOperator(exp[i]) || isDigit(exp[i]) || exp[i] == '.')
        {
            if(exp[i] == ' ')
                i++;
            // printf("%c\n",total[i]);
            else
            {
                res[k] = exp[i];
                i++;
                // printf("%c\n",exp[z]);
                k++;
            }
        }
        else
            return 0;
    }
    int w = 0;
    if(res[0] == '-')
    {
        for(w=k; w>0; w--)
        {
            res[w] = res[w-1];
        }
        res[0] = '0';
        //res[k+1] = '\0';
        k++;
    }
    int a;
    w = 0;
    while(res[w] != '\0')
    {
        if(res[w] == '(' && res[w+1] == '-')
        {
            for(a=k; a>w; a--)
            {
                res[a] = res[a-1];
            }
            k++;
            res[w+1] = '0';

        }
        w++;
    }
    res[k] = '\0';
    //printf("%s\n",res);
    char* test = infixToPostfix(res);
    float value = evaluatePostfix(test);
    //printf("%.2f\n",value);
    if(value == 921995)
        return 0;
    if(z == 1)
        return 1;
    return 0;
}

int main()
{

    // int number;
    do
    {
        int i=0;
        int j=0;
        int z=0;
        int flag1=0;
        char total[100];
        char var[100];
        char exp[100];
        printf("Please enter an expression to evaluate or exit\n");
        gets(total);
        if(strcmp(total, "exit") == 0)
            break;
        int flag = checkValid(total);
        //printf("%d\n",flag);
        if(flag == 1)
        {
            while(total[i] != '=')
            {
                if(total[i] == ' ')
                    i++;
                // printf("%c\n",total[i]);
                else
                {
                    var[j] = total[i];
                    i++;
                // printf("%c\n",var[j]);
                    j++;
                }
            }
            //if(var[j] != ' ')
            //{
                //var[j] = ' ';
                //j++;
            //}

            var[j] = '\0';
            //char* tempVar = malloc(sizeof(j));
            //strcpy(tempVar, var);
            //printf("%s\n",var);

            i++;
            while(total[i] != '\0')
            {
                if(isChar(total[i]))
                {
                    char temp[100];
                    int x = 0;
                    while(isChar(total[i]) || isDigit(total[i]))
                    {
                        // printf("%c\n",total[i]);
                        temp[x]=total[i];
                        x++;
                        i++;
                    }

                    temp[x] = '\0';
                    char* tempUsed = malloc(sizeof(j));
                    strcpy(tempUsed, temp);
                    //printf("%s\n",tempUsed);
                    // printf("%d\n",strlen(temp));
                    char* temp1 = convertIntoChar(tempUsed);

                    int y = 0;
                    while(temp1[y] != '\0')
                    {
                        exp[z] = temp1[y];
                        z++;
                        y++;
                    }
                }
                else
                {
                    if(total[i] == ' ')
                    i++;
                    // printf("%c\n",total[i]);
                    else
                    {
                        exp[z] = total[i];
                        i++;
                    // printf("%c\n",exp[z]);
                        z++;
                    }

                }

            }
            int w = 0;
            if(exp[0] == '-')
            {
                for(w=z; w>0; w--)
                {
                    exp[w] = exp[w-1];
                }
                exp[0] = '0';
                z++;
            }
            int a;
            w = 0;
            while(exp[w] != '\0')
            {
                if(exp[w] == '(' && exp[w+1] == '-')
                {
                    for(a=z; a>w; a--)
                    {
                        exp[a] = exp[a-1];
                    }
                    z++;
                    exp[w+1] = '0';

                }
                w++;
            }
            exp[z] = '\0';
            // printf("%s\n",var);
            //printf("%s\n",exp);
            newVariable(var, exp);
        // printLinkedList();

        }
        //printf("%s\n",total);
        if(flag == 0 || flag1 == 1)
            printf("Please enter a valid expression!\n");

    }while(1);
    printLinkedList();

    return 0;
}

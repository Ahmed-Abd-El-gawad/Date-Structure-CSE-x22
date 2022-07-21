/*
    lab4 task: Evaluate Expression
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct node{
    int data;
    struct node *link;
};
struct node *top = NULL;// top of the stack is the first node (header)
void push(int x)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));
    if(top==NULL)
    {
       temp->data = x;
       temp->link = NULL;
       top = temp;
    }
    else
    {
       temp->data = x;
       temp->link = top;
       top = temp;
    }
}
int pop()
{
    int value=0;
    struct node *temp;
    if(top != NULL) // if the stack is not empty
    {
        temp = top;
        value = top->data;
        top = top->link;
        free(temp);
    }
    return value;
}
void postfix_evaluater(char* S)
{
    int result=0;
    int x1=0, x2=0;
    if(S[0] != '0' && S[0] != '1' && S[0] != '2' && S[0] != '3' && S[0] != '4'
        && S[0] != '5' && S[0] != '6' && S[0] != '7' && S[0] != '8' && S[0] != '9')
    {
        printf("Not Valid");
        return;
    }
    else if(S[1] != '0' && S[1] != '1' && S[1] != '2' && S[1] != '3' && S[1] != '4'
            && S[1] != '5' && S[1] != '6' && S[1] != '7' && S[1] != '8' && S[1] != '9')
    {
        printf("Not Valid");
        return;
    }
    for(int i = 0 ; i < strlen(S) ; i++)
    {
        if(S[i] == '0' || S[i] == '1' || S[i] == '2' || S[i] == '3' || S[i] == '4'
            || S[i] == '5' || S[i] == '6' || S[i] == '7' || S[i] == '8' || S[i] == '9')
        {
            push(S[i] - '0');
        }
        else if(S[i] == '*' || S[i] == '/' || S[i] == '%' || S[i] == '+' || S[i] == '-')
        {
            if(top == NULL)
            {
                printf("Not Valid");
                return;
            }
            else if(top->link == NULL)
            {
                printf("Not Valid");
                return;
            }
            else
            {
                x2 = pop();
                x1 = pop();
            }
            switch(S[i])
            {
            case '+':
                result = x1 + x2;
                push(result);
                break;
            case '-':
                result = x1 - x2;
                push(result);
                break;
            case '*':
                result = x1 * x2;
                push(result);
                break;
            case '/':
                if(x2==0)
                {
                    printf("Not Valid");
                    return;
                }
                else
                {
                    result = x1 / x2;
                    push(result);
                }
                break;
            case '%':
                if(x2==0)
                {
                    printf("Not Valid");
                    return;
                }
                else
                {
                    result = x1 % x2;
                    push(result);
                }
                break;
            default:
                printf("Not Valid");
                return;
            }
        }
        else
        {
            printf("Not Valid");
            return;
        }
    }
    if(top == NULL)
    {
        printf("Not Valid");
        return;
    }
    else
    {
        if(top->link == NULL)
        {
            printf("%d",top->data);
        }
        else
        {
            printf("Not Valid");
        }
    }
}
int main()
{
    char S[10000];
    scanf(" %s",S);
    postfix_evaluater(S);
    return 0;
}

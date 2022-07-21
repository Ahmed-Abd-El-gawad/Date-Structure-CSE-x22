/*
    lab3 task: Stack Operations
*/
#include <stdio.h>
#include <stdlib.h>
struct node{
    unsigned int data;
    struct node *link;
};
struct node *top = NULL;// top of the stack is the first node (header)

void push(unsigned int x)
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
void pop()
{
    struct node *temp;
    if(top != NULL) // if the stack is empty
    {
        temp = top;
        top = top->link;
        free(temp);
    }
}
void minimum_element()
{
    struct node *temp = top;
    int min;

    if(top == NULL) // if the stack is empty
    {
        printf("Empty\n");
    }
    else
    {
        min = top->data;
        while (temp != NULL)
        {
            if (min > temp->data)
            {
                min = temp->data;
            }
            temp = temp->link;
        }
        printf("%d\n",min);
    }
}
int main()
{
    unsigned int Q;
    int choice;
    unsigned int E;
    scanf(" %u",&Q);
    if(!(Q<1 || Q>1000000))
    {
        for(unsigned int i = 0 ; i < Q ; i++)
        {
            scanf(" %d",&choice);
            if(choice==1)
            {
                scanf(" %u",&E);
                if(!(E<1 || E>1000000000))
                    push(E);
            }
            else if(choice==2)
            {
                pop();
            }
            else if(choice==3)
            {
                minimum_element();
            }
        }
    }
    return 0;
}

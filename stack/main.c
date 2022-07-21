

/// stack - Array implementation
/*
#include <stdio.h>
#define max_size 101
int a[max_size];
int top = -1;
void push(int x)
{
    top++;
    a[top] = x;
}
void push_overflow(int x)
{
    if(top == max_size-1)
    {
        /// Error: stack overflow
        printf("Error: stack overflow");
        return;
    }
    a[++top] = x;
}
void pop()
{
    if(top == -1)
    {
        /// Error: no element to pop
        printf("Error: no element to pop");
        return;
    }
    top--;
}
void topp()
{
    return a[top];
}
void print_stack()
{
    printf("stack: ");
    for(int i = 0 ; i <= top ; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}
int main()
{
    push_overflow(2);print_stack();
    push_overflow(5);print_stack();
    push_overflow(10);print_stack();
    pop();print_stack();
    push_overflow(12);print_stack();
    return 0;
}
*/


/// stack - Linked List implementation
#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *link;
};
struct node *top = NULL;

void push(int x)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));
    temp->data = x;
    temp->link = top;
    top = temp;
}
void pop()
{
    struct node *temp;
    if(top == NULL) // if the stack is empty
        return;
    temp = top;
    top = top->link;
    free(temp);
}
void minimum_element()
{
    struct node *temp;
    temp = top;
    int min = temp->data;

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

int main()
{
    //unsigned int Q, choice;
    //scanf(" %u");

    push(5);
    pop();
    push(43);
    push(20);
    push(50);
    minimum_element();
    push(84);
    pop();
    push(2);
    minimum_element();

    return 0;
}


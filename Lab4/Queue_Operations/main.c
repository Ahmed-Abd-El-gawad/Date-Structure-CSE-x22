/*
    lab4 task: Queue Operations
*/
#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *link;
};
struct node *front = NULL;
struct node *rear = NULL;
void enqueue(int x)// add from rear (back) side
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));
    temp->data = x;
    temp->link = NULL;
    if(front == NULL && rear == NULL)
    {
        front = temp;
        rear = temp;
        return;
    }
    rear->link = temp;
    rear = temp;
}
void dequeue()// add from rear (back) side
{
    struct node *temp = front;
    if(front == NULL)//queue is empty
    {
        return;
    }
    else if(front == rear)// has only one node to be removed
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        front = front->link;
    }
    free(temp);
}
void display()
{
    struct node *temp = front;
    if(front == NULL)//queue is empty
    {
        printf("Empty\n");
        return;
    }
    while(temp)
    {
        if(temp->link == NULL)
        {
            printf("%d\n", temp->data);
        }
        else
        {
            printf("%d,", temp->data);
        }
        temp = temp->link;
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
                    enqueue(E);
            }
            else if(choice==2)
            {
                dequeue();
            }
            else if(choice==3)
            {
                display();
            }
        }
    }
    return 0;
}

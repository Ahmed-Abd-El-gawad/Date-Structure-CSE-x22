/*
    lab5 task: How many courses should I take?
*/
#include <stdio.h>
#include <stdlib.h>
int end_day = 0;
struct node{
    int data;
    int priority_day;
    struct node *link;
};
struct node *front = NULL;
struct node *rear = NULL;
void enqueue(int x, int y)// add from rear (back) side
{
    struct node *new = (struct node*)malloc(sizeof(struct node*));
    struct node *temp;
    new->data = x;
    new->priority_day = y;
    new->link = NULL;
    if(front == NULL && rear == NULL)
    {
        front = new;
        rear = new;
        return;
    }
    else
    {
        if(y<front->priority_day)
        {
            new->link = front;
            front = new;
        }
        else
        {
            temp = front;
            while(temp->link!=NULL && temp->link->priority_day<=y)
            {
                temp = temp->link;
            }
            new->link = temp->link;
            temp->link = new;
        }
    }
}
void dequeue()
{
    struct node *temp = front;
    if(front == NULL)//queue is empty
    {
        return;
    }
    else
    {
        front = front->link;
    }
    free(temp);
}
int max_courses()
{
    struct node *temp = front;
    if(front == NULL)//queue is empty
    {
        return 0;
    }
    else
    {
        if(end_day+temp->data <= temp->priority_day)
        {
            end_day = end_day + temp->data;
            dequeue();
            return 1 + max_courses();
        }
        else
        {
            dequeue();
            return 0 + max_courses();
        }
    }
    return 0;
}
int main()
{
    unsigned int n;
    scanf(" %u",&n);
    if(n<1)
        return 0;
    unsigned int d, i;
    for(unsigned int j = 0 ; j < n ; j++)
    {
        scanf(" %u",&d);
        scanf(" %u",&i);
        if(i>10000)
            return 0;
        enqueue(d,i);
    }
    printf("%d",max_courses());
    return 0;
}

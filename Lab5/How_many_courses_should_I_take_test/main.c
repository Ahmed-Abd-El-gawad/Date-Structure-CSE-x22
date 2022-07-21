/*
    lab5 task: How many courses should I take?
*/
#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    int priority_day;
    struct node *link;
};
struct node *front = NULL;
struct node *rear = NULL;
void enqueue(int x, int y)// add from rear (back) side
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));
    temp->data = x;
    temp->priority_day = y;
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
int *dequeue_max_piority()
{
    struct node *temp = front;
    struct node *min_node = front;
    struct node *min_temp = front;
    static int arr[2] = {0};
    if(front == NULL)//queue is empty
    {
        printf("%d %d\n",arr[0],arr[1]);
        return arr;
    }
    else if(front == rear)// has only one node to be removed
    {
        front = NULL;
        rear = NULL;
        arr[0] = min_node->data;
        arr[1] = min_node->priority_day;
        free(min_node);
        free(min_temp);
        free(temp);
    }
    else
    {
        min_node = temp;
        min_temp = temp;
        temp = temp->link;
        arr[0] = min_node->data;
        arr[1] = min_node->priority_day;
        while(temp)
        {
            if(min_node->priority_day > temp->priority_day)
            {
                arr[0] = temp->data;
                arr[1] = temp->priority_day;
                min_temp = min_node;
                min_node = temp;
            }
            temp = temp->link;
        }
        min_temp->link = min_node->link;
        //front = front->link;
        free(min_node);
    }
    printf("%d %d\n",arr[0],arr[1]);
    return arr;
}
int max_courses()
{
    int end_day = 0;
    int num_courses = 0;
    int *temp_arr;
    struct node *temp = front;
    if(front == NULL)//queue is empty
    {
        return num_courses;
    }
    while(temp)
    {
        temp_arr = dequeue_max_piority();
        if(end_day+temp_arr[0] <= temp_arr[1])
        {
            end_day = end_day + temp_arr[0];
            if(temp_arr[0]!=0)
                num_courses++;
            return num_courses + max_courses();
        }
        else
        {
            return num_courses + max_courses();
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

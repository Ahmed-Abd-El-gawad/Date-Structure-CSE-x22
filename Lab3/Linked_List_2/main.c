/*
    lab3 task: Linked List 2
*/
#include <stdio.h>
#include <stdlib.h>
struct node{
    unsigned int data;
    struct node *link;
};

void add_node(struct node** head, unsigned int x)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));

    temp->data = x;
    temp->link = *head;
    *head = temp;
}
struct node* reverse_list(struct node *head,struct node *head_reversed)
{
    struct node *temp = head;
    while(temp!=NULL)
    {
        struct node *temp_reversed= (struct node*)malloc(sizeof(struct node));
        if(head_reversed==NULL)
        {
            temp_reversed->data = temp->data;
            temp_reversed->link = NULL;
            head_reversed = temp_reversed;
        }
        else
        {
            temp_reversed->data = temp->data;
            temp_reversed->link = head_reversed;
            head_reversed = temp_reversed;
        }
        temp = temp->link;
    }
    return head_reversed;
}
void cmp_list(struct node *head,struct node *head_reversed)
{
    struct node *temp = head;
    struct node *temp_reversed = head_reversed;

    while(temp!=NULL)
    {
        if(temp->data != temp_reversed->data)
        {
            printf("NO");
            return;
        }
        temp = temp->link;
        temp_reversed = temp_reversed->link;
    }
    printf("YES");
}

int number_counter(int number)
{
    if(number/10 != 0)
        return 1 + number_counter(number/10);
    else
        return 1;
}

int power(int number, int exp)
{
    if(exp==0)
        return 1;
    else
        return number*power(number,exp-1);
}
int main()
{
    int X;
    scanf(" %d",&X);
    struct node* head = NULL;
    struct node* head_reversed = NULL;
    for(int i = 1 ; i <= number_counter(X) ; i++)
    {
        add_node(&head, (X-(X/power(10,i))*power(10,i))/power(10,i-1));
    }
    head_reversed = reverse_list(head,head_reversed);

    cmp_list(head,head_reversed);

    return 0;
}

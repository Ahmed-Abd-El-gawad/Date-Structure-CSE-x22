#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *link;
};
void add_node(struct node** head, unsigned int x)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node*));

    temp->data = x;
    temp->link = *head;
    *head = temp;
}
struct node* reverse_list(struct node *head)
{
    struct node *temp = head;
    struct node *head_reversed = NULL;
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
struct node *concatenate_list( struct node *head_1,struct node *head_2)
{
    struct node *temp;
    if(head_1==NULL)
    {
        head_1=head_2;
        return head_1;
    }
    if(head_2==NULL)
    {
        return head_1;
    }
    temp=head_1;
    while(temp->link!=NULL)
    {
        temp=temp->link;
    }
    temp->link=head_2;
    return head_1;
}
struct node* reverse__part_list(struct node *head,int S,int N)
{
    struct node *temp = head;
   // struct node *ans_temp= NULL;
    struct node *ans= NULL;
    struct node *ans_t= NULL;
    struct node *ans_temp = NULL;
    int flag = 1;

    while(temp!=NULL)
    {
        add_node(&ans_temp,temp->data);

        if(flag)
        {
            for(int i = 0 ; i < N ; i++)
            {
                if(i/N == S/N)
                {
                    ans = concatenate_list(ans,ans_temp);
                }
                if(i>(S/N)*N)
                {
                    flag=0;
                    break;
                }
            }
        }
        //printList(ans_temp);
        printList(ans);
        ans_temp = NULL;
        printList(ans_temp);
        temp = temp->link;
    }
    return ans;
}
void printList(struct node* head)
{
    struct node *temp = head;
    while (temp)
    {
        printf("%d\n", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");
}
int main()
{
    int S, N;
    scanf(" %d %d",&S,&N);
    int element;
    struct node* head = NULL;
    //struct node* reversed_temp = NULL;
    //struct node* head_reversed = NULL;
    for(int i = 0 ; i < S ;i++)
    {
        scanf(" %d",&element);
        add_node(&head,element);
    }
    //printList(head);
    head = reverse_list(head);
    //printList(head);
    head = reverse__part_list(head,S,N);
    printList(head);
    return 0;
}

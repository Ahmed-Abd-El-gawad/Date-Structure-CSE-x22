/*
    lab7 task: Minimum Distinct Elements
*/
#include <stdio.h>
#include <stdlib.h>
struct list_node
{
    unsigned long long int data;
    unsigned long int how_many;
    struct list_node *link;
};

void add_node_at_end_linked_list(struct list_node **list, int data)
{
    struct list_node *new_node = (struct list_node*) malloc(sizeof(struct list_node));
    struct list_node *last = *list;

    new_node->data  = data;
    new_node->how_many  = 1;
    new_node->link = NULL;

    if ((*list) == NULL)
    {
       (*list) = new_node;
       return;
    }
    while(last->link != NULL)
    {
        last = last->link;
    }
    if(new_node->data==last->data)
    {
        last->how_many = last->how_many + new_node->how_many;
        return;
    }
    last->link = new_node;
    return;
}
void remove_first_list(struct list_node **list)
{
    struct list_node *temp;
    if((*list)==NULL)
    {
        return;
    }
    temp = (*list);
    if(temp->how_many > 1)
    {
        temp->how_many = temp->how_many - 1;
    }
    else
    {
        (*list) = (*list)->link;
        free(temp);
    }
}
unsigned long int count_list(struct list_node **list)
{
    struct list_node *node = (*list);
    if((*list)!=NULL)
    {
        while(node)
        {
            node = node->link;
            return 1 + count_list(&node);
        }
    }
    return 0;
}
void printList(struct list_node **node)
{
    while((*node)!=NULL)
    {
        printf("%llu,%lu\n", (*node)->data,(*node)->how_many);
        (*node) = (*node)->link;
    }
}
void merge_array(unsigned long long int *number, unsigned long int start, unsigned long int middle, unsigned long int end, unsigned long int N)
{
    unsigned long int i = start;
    unsigned long int j = middle+1;
    unsigned long int k = 0;
    unsigned long long int temp[end-start+1];
    while(i<=middle && j<=end)
    {
        if(number[i]<=number[j])
        {
            temp[k] = number[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = number[j];
            k++;
            j++;
        }
    }
    while(i<=middle)
    {
        temp[k] = number[i];
        k++;
        i++;
    }
    while(j<=end)
    {
        temp[k] = number[j];
        k++;
        j++;
    }
    for(i=start ; i<=end ; i++)
    {
        number[i] = temp[i-start];
    }
}
void merge_sort_array(unsigned long long int *number, unsigned long int start, unsigned long int end,  unsigned long int N)
{
    if(start<end)
    {
        unsigned long int middle = (start+end)/2;
        merge_sort_array(number,start,middle,N);
        merge_sort_array(number,middle+1,end,N);
        merge_array(number,start,middle,end,N);
    }
}
struct list_node *merge_list(struct list_node *left, struct list_node *right)
{
    if(left==NULL)
    {
        return right;
    }
    if(right==NULL)
    {
        return left;
    }
    if(left->how_many <= right->how_many)
    {
        left->link = merge_list(left->link, right);
        return left;
    }
    else
    {
        right->link = merge_list(left, right->link);
        return right;
    }
}
struct list_node *merge_sort_list(struct list_node *list)
{
    if(list==NULL)
    {
        return NULL;
    }
    if(list->link==NULL)
    {
        return list;
    }
    struct list_node *fast;
    struct list_node *slow;
    struct list_node *pre;
    fast = list;
    slow = list;
    while(fast && fast->link)
    {
        pre = slow;
        fast = fast->link->link;
        slow = slow->link;
    }
    pre->link = NULL;
    return merge_list(merge_sort_list(list),merge_sort_list(slow));
}
unsigned long int minimum_distinct_elements(unsigned long long int *number, int N, unsigned long int r)
{
    merge_sort_array(number,0,N-1,N);
    struct list_node *list = NULL;
    for(int i=0 ; i<N ; i++)
    {
        add_node_at_end_linked_list(&list,number[i]);
    }
    list = merge_sort_list(list);
    for(int i=0 ; i<r ; i++)
    {
        remove_first_list(&list);
    }
    return count_list(&list);
}
int main()
{
    unsigned long int N, r;
    scanf(" %lu",&N);
    if(N<1 && N>100000)
        return 0;
    scanf(" %lu",&r);
    if(r<0 || r>N)
        return 0;
    unsigned long long int *number;
    number = (unsigned long long int*)malloc(N*sizeof(unsigned long long int));
    for(int i=0 ; i<N ; i++)
    {
        scanf(" %llu",number+i);
    }
    printf("%lu",minimum_distinct_elements(number,N,r));
    return 0;
}

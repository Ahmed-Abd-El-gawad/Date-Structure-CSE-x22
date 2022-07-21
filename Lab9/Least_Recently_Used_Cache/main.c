/*
    lab9 task: Least Recently Used Cache
*/
#include <stdio.h>
#include <stdlib.h>
// double linked list to hold key and data
struct cache
{
    unsigned long int key;
    unsigned long int data;
    struct cache *next_link;
    struct cache *prev_link;
};
struct cache *head;
struct cache *tail;
// swap values
void swap(unsigned long int *x, unsigned long int *y)
{
    unsigned long int temp = *x;
    *x = *y;
    *y = temp;
}
// add new keys from the tail
void add_tail(unsigned long int K, unsigned long int E)
{
    struct cache *temp = (struct cache*)malloc(sizeof(struct cache));
    temp->data = E;
    temp->key = K;
    temp->next_link = NULL;
    temp->prev_link = NULL;
    // check if there is any element in the list
    // if there is not just make head and tail same as new node
    if(head==NULL)
    {
        head = temp;
        tail = temp;
    }
    // if there is
    // just link the new node from the tail of the linked list
    else
    {
        tail->next_link = temp;
        temp->prev_link = tail;
        tail = temp;
    }
}
// remove the head node from the linked list
void remove_head()
{
    if(head!=NULL)
    {
        struct cache *temp = head;
        head = temp->next_link;
        if(head==NULL)
        {
            tail = head;
        }
        else
        {
            tail->next_link = NULL;
        }
        // free temp from the memory after edit the links
        free(temp);
        temp = NULL;
    }
}
// insert new key and value to the cache
unsigned long int insert(unsigned long int K, unsigned long int E, unsigned long int C, unsigned long int size)
{
    // if the cache size is 0
    if(C==0)
    {
        printf("Error\n");
        return size;
    }
    // if this is the first node to be added to the cache
    if(size==0)
    {
        add_tail(K,E);
        size++;
        return size;
    }
    // node to hold the key and value if exists
    struct cache *temp = NULL;
    // node to traverse from head
    struct cache *temp_head = head;
    // node to traverse from tail
    struct cache *temp_tail = tail;
    while(temp_head!=NULL && temp_tail!=NULL)
    {
        if(temp_head->key==K)
        {
            temp = temp_head;
            break;
        }
        temp_head = temp_head->next_link;

        if(temp_tail->key==K)
        {
            temp = temp_tail;
            break;
        }
        temp_tail = temp_tail->prev_link;
    }
    // if temp is NULL that means that there is no key matches in the list or new key will be added
    if(temp==NULL)
    {
        if(size<C)
        {
            add_tail(K,E);
            size++;
        }
        else
        {
            remove_head();
            add_tail(K,E);
            size++;
        }
    }
    else
    {
        temp->data = E;
        temp->key = K;
        swap(&(temp->data),&(head->data));
        swap(&(temp->key),&(head->key));
    }
    return size;
}
// print value at key if exists
void print(unsigned long int K, unsigned long int size, unsigned long int C)
{
    if(C==0)
    {
        printf("Not Found\n");
        return;
    }
    // node to traverse from head
    struct cache *temp_head = head;
    // node to traverse from tail
    struct cache *temp_tail = tail;
    while(temp_head!=NULL && temp_tail!=NULL)
    {
        if(temp_head->key==K)
        {
            printf("%lu\n",temp_head->data);
            swap(&(temp_head->data),&(head->data));
            swap(&(temp_head->key),&(head->key));
            return;
        }
        temp_head = temp_head->next_link;

        if(temp_tail->key==K)
        {
            printf("%lu\n",temp_tail->data);
            swap(&(temp_tail->data),&(head->data));
            swap(&(temp_tail->key),&(head->key));
            return;
        }
        temp_tail = temp_tail->prev_link;
    }
    printf("Not Found\n");
    return;
}
int main()
{
    unsigned long int P, C;
    scanf(" %lu",&P);
    if(P<1 || P>1000000)
        return 0;
    scanf(" %lu",&C);
    if(C<0 || C>1000000)
        return 0;
    unsigned long int size = 0;
    for(unsigned long int i=0; i<P; i++)
    {
        int choice = 0;
        unsigned long int K;
        unsigned long int E;
        scanf(" %d",&choice);
        if(choice==1)
        {
            scanf(" %lu",&K);
            scanf(" %lu",&E);
            if(E<1 || E>1000000000)
                return 0;
            size = insert(K,E,C,size);
        }
        else if(choice==2)
        {
            scanf(" %lu",&K);
            print(K,size,C);
        }
    }
    return 0;
}

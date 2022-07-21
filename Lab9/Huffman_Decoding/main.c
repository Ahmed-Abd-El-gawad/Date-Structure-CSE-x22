/*
    lab9 task: Huffman Decoding
*/
#include <stdio.h>
#include <stdlib.h>
unsigned int str_len(const char *s)
{
    unsigned int count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}
void str_descending(char *S)
{
    char temp = S[0];
    for(unsigned int i=0; i<str_len(S); i++)
    {
        for(unsigned int j=0; j<(str_len(S)-1); j++)
        {
            if(S[j]<S[j+1])
            {
                temp = S[j];
                S[j] = S[j+1];
                S[j+1] = temp;
            }
        }
    }
}
struct leave_node{
    char data;
    int frequency;
    struct leave_node *link;
};
struct huffman_root{
    char data;
    int frequency;
    struct huffman_root *left_link;
    struct huffman_root *right_link;
};
void add_node_at_end_list(struct leave_node **list, char data)
{
    struct leave_node *new_node = (struct leave_node*) malloc(sizeof(struct leave_node));
    struct leave_node *last = *list;

    new_node->data  = data;
    new_node->frequency  = 1;
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
        last->frequency = last->frequency + new_node->frequency;
        return;
    }
    last->link = new_node;
    return;
}
void printList(struct leave_node **node)
{
    while((*node)!=NULL)
    {
        printf("%c,%d\n", (*node)->data,(*node)->frequency);
        (*node) = (*node)->link;
    }
}
struct leave_node *merge_list(struct leave_node *left, struct leave_node *right)
{
    if(left==NULL)
    {
        return right;
    }
    if(right==NULL)
    {
        return left;
    }
    if(left->frequency <= right->frequency)
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
struct leave_node *merge_sort_list(struct leave_node *list)
{
    if(list==NULL)
    {
        return NULL;
    }
    if(list->link==NULL)
    {
        return list;
    }
    struct leave_node *fast;
    struct leave_node *slow;
    struct leave_node *pre;
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
int pop(struct Node** headRef)
{
    struct leave_node *new_node = (struct leave_node*) malloc(sizeof(struct leave_node));
    // underflow condition
    if (*headRef == NULL) {
        return -1;
    }

    struct Node* head = *headRef;
    int result = head->data;        // pull out data before the node is deleted

    (*headRef) = (*headRef)->next;  // unlink the head node for the caller
                                    // Note the `*` � uses a reference-pointer
                                    // just like `push()` and `deleteList()`.

    free(head);             // free the head node

    return result;          // don't forget to return the data from the link
}
struct huffman_root *huffman_tree(char *s)
{
    str_descending(S);
    //printf("%s",S);
    struct leave_node *leaves = NULL;
    for(unsigned int i=0; i<str_len(S); i++)
    {
        add_node_at_end_list(&leaves,S[i]);
    }
    //printList(&leaves);
    leaves = merge_sort_list(leaves);
    //printList(&leaves);
    struct huffman_root *root = NULL;
    for(for(unsigned int i=0; i<str_len(S); i++))
    {

    }
    if(huffman_root==NULL)
    {
        return NULL;
    }
    else if(huffman_root->link==NULL)
    {
        return huffman_root;
    }
    else
    {

    }
    return huffman_root;
}
int main()
{
    char S[100000];
    //, E[100000], characters[100000], frequency[100000];
    scanf(" %s",S);
    if(str_len(S) < 2 || str_len(S) > 100000)
    {
        return 0;
    }
    //scanf(" %s",E);
    //if(str_len(E) < 1 || str_len(E) > 100000)
    //{
    //    return 0;
    //}

    return 0;
}

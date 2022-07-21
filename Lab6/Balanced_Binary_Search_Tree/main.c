/*
    lab6 task: Balanced Binary Search Tree
*/
#include <stdio.h>
#include <stdlib.h>
struct tree_node
{
    int data;
    struct tree_node *left_child;
    struct tree_node *right_child;
};
struct tree_node *new_node(int data)
{
    struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node*));
    node->data = data;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}
struct tree_node *insert_sorted_bst(int data[], int start, int end)
{
    if(start>end)
    {
        return NULL;
    }
    struct tree_node *root;
    root = new_node(data[(start+end)/2]);
    root->left_child = insert_sorted_bst(data,start,(start+end)/2-1);
    root->right_child = insert_sorted_bst(data,(start+end)/2+1,end);
    return root;
}
void preorder_traversal(struct tree_node *root, int N)
{
    static int i = 0;
    if(root==NULL)
    {
        return;
    }
    i++;
    if(i==N)
        printf("%d",root->data);
    else
        printf("%d,",root->data);
    preorder_traversal(root->left_child,N);
    preorder_traversal(root->right_child,N);
}
int main()
{
    unsigned int N;
    scanf(" %ul",&N);
    if(!(N>=0 && N<=100000))
        return 0;
    struct tree_node *root = NULL;
    int *data;
    data = (int*)malloc(N*sizeof(int));
    for(int i = 0 ; i < N ; i++)
    {
        scanf(" %d",data+i);
    }
    root = insert_sorted_bst(data,0,N-1);
    preorder_traversal(root,N);
    return 0;
}

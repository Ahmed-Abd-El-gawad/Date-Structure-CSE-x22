/*
    lab6 task: Balanced Binary Search Tree
*/
#include <stdio.h>
#include <stdlib.h>
struct tree_node_avl
{
    int data;
    int height;
    struct tree_node_avl *left_child;
    struct tree_node_avl *right_child;
};
struct tree_node_avl *new_node(int data)
{
    struct tree_node_avl *node = (struct tree_node_avl*)malloc(sizeof(struct tree_node_avl*));
    node->data = data;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}
int height(struct tree_node_avl *node)
{
    if(node==NULL)
        return -1;
    return node->height;
}
int get_balance(struct tree_node_avl *node)
{
    if(node==NULL)
        return -1;
    return height(node->left_child)-height(node->right_child);
}
int max(int i, int j)
{
    if(i>j)
        return i;
    return j;
}
struct tree_node_avl *left_rotate(struct tree_node_avl *node)
{
    struct tree_node_avl *temp = node->right_child;
    struct tree_node_avl *temp2 = temp->left_child;
    temp->right_child = node;
    node->left_child = temp2;
    node->height = max(height(node->left_child),height(node->right_child)+1);
    temp->height = max(height(temp->left_child),height(temp->right_child)+1);
    return temp;
}
struct tree_node_avl *right_rotate(struct tree_node_avl *node)
{
    struct tree_node_avl *temp = node->left_child;
    struct tree_node_avl *temp2 = temp->right_child;
    temp->right_child = node;
    node->left_child = temp2;
    node->height = max(height(node->left_child),height(node->right_child)+1);
    temp->height = max(height(temp->left_child),height(temp->right_child)+1);
    return temp;
}
struct tree_node_avl *insert_sorted_bst_avl(struct tree_node_avl *root, int data)
{
    if(root==NULL)
    {
        return new_node(data);
    }
    if(data<root->data)
        root->left_child = insert_sorted_bst_avl(root->left_child,data);
    else
        root->right_child = insert_sorted_bst_avl(root->right_child,data);
    root->height = 1 +max(height(root->left_child),height(root->right_child));
    int balance = get_balance(root);
    if(balance>1 && data<root->left_child->data)
        return right_rotate(root);
    if(balance<-1 && data>root->right_child->data)
        return left_rotate(root);
    if(balance>1 && data>root->left_child->data)
    {
        root->left_child = left_rotate(root->left_child);
        return right_rotate(root);
    }
    if(balance<-1 && data>root->left_child->data)
    {
        root->right_child = right_rotate(root->right_child);
        return right_rotate(root);
    }
    return root;
}
void preorder_traversal(struct tree_node_avl *root, int N)
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
    struct tree_node_avl *root = NULL;
    int data;
    for(int i = 0 ; i < N ; i++)
    {
        scanf(" %d",&data);
        root = insert_sorted_bst_avl(root,data);
    }
    preorder_traversal(root,N);
    return 0;
}

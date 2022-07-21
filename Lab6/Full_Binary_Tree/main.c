/*
    lab6 task: Full Binary Tree
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
struct tree_node *tree_from_level_order(struct tree_node* root, int data[], int index, int N)
{
    if(index<N)
    {
        struct tree_node* temp = new_node(data[index]);
        root = temp;
        root->left_child = tree_from_level_order(root->left_child,data,2*index + 1,N);
        root->right_child = tree_from_level_order(root->right_child,data,2*index + 2,N);
    }
    return root;
}
bool is_full_binary_tree(struct tree_node* root)
{
    if (root == NULL)//empty
    {
        return true;
    }
    if (root->left_child == NULL && root->right_child == NULL)//one node (one level)
    {
        return true;
    }
    if(root->left_child->data == -1 && root->right_child->data == -1)
    {
        return true;
    }
    else if(root->left_child->data == -1 && root->right_child->data != -1)
    {
        return false;
    }
    else if(root->left_child->data != -1 && root->right_child->data == -1)
    {
        return false;
    }
    else
    {
        if(is_full_binary_tree(root->left_child) && is_full_binary_tree(root->right_child))
        {
            return true;
        }
    }
    return false;
}
int main()
{
    unsigned int N;
    scanf(" %ul",&N);
    if(!(N>=1 && N<=100000))
        return 0;
    int *data;
    data = (int*)malloc(N*sizeof(int));
    for(int i = 0 ; i < N ; i++)
    {
        scanf(" %d",data+i);
    }
    struct tree_node *root;
    root = tree_from_level_order(root,data,0,N);
    if(is_full_binary_tree(root))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }

    return 0;
}

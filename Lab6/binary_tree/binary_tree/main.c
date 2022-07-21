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
struct tree_node *insert_bst(struct tree_node *root, int data)
{
    if(root==NULL)
    {
        return new_node(data);
    }
    if(data<root->data)
    {
        root->left_child = insert_bst(root->left_child,data);
    }
    else
    {
        root->right_child = insert_bst(root->right_child,data);
    }
    return root;
}
struct tree_node *successor_bst(struct tree_node *node)
{
    struct tree_node *current_node = node;
    while(current_node&&current_node->left_child!=NULL)
    {
        current_node = current_node->left_child;
    }
    return current_node;
}
struct tree_node *delete_node_bst(struct tree_node *root, int data)
{
    if(root==NULL)
    {
        return root;
    }
    if(data<root->data)
    {
        root->left_child = delete_node_bst(root->left_child,data);
    }
    else if(data>root->data)
    {
        root->right_child = delete_node_bst(root->right_child,data);
    }
    else
    {
        if(root->left_child==NULL)
        {
            struct tree_node *temp = root->right_child;
            free(root);
            return temp;
        }
        else if(root->right_child==NULL)
        {
            struct tree_node *temp = root->left_child;
            free(root);
            return temp;
        }
        struct tree_node *temp = successor_bst(root->right_child);
        root->data = temp->data;
        root->right_child = delete_node_bst(root->right_child,temp->data);
    }
    return root;
}
/* Print nodes at a given level */
void print_level(struct tree_node *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1)
    {
        print_level(root->left_child, level-1);
        print_level(root->right_child, level-1);
    }
}
/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct tree_node *node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left_child);
        int rheight = height(node->right_child);

        /* use the larger one */
        if (lheight > rheight)
            return(lheight+1);
        else
            return(rheight+1);
    }
}
/* Function to print level order traversal a tree*/
void printLevelOrder(struct tree_node* root)
{
    for (int i=1;i<=height(root);i++)
    {
        print_level(root,i);
        printf("\n");
    }
}
struct tree_node *tree_from_level_oreder(struct tree_node* root, int data[], int index, int N)
{
    if(index<N)
    {
        struct tree_node* temp = new_node(data[index]);
        root = temp;
        root->left_child = tree_from_level_oreder(root->left_child,data,2*index + 1,N);
        root->right_child = tree_from_level_oreder(root->right_child,data,2*index + 2,N);
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
    if(root->left_child->data == -1 || root->right_child->data == -1)
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
    root = tree_from_level_oreder(root,data,0,N);
    if(is_full_binary_tree(root))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    //printLevelOrder(root);

    return 0;
}

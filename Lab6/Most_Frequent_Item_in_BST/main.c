/*
    lab6 task: Most Frequent Item in BST
*/
#include <stdio.h>
#include <stdlib.h>
struct tree_node
{
    int data;
    struct tree_node *left_child;
    struct tree_node *right_child;
};
struct tree_node *new_tree_node(int data)
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
        return new_tree_node(data);
    }
    if(root->data<data)
    {
        root->right_child = insert_bst(root->right_child,data);
    }
    else if(root->data>=data)
    {
        root->left_child = insert_bst(root->left_child,data);
    }
    return root;
}
struct list_node
{
    int data;
    int how_many;
    struct list_node *link;
};
struct list_node *list = NULL;
void add_node_at_end_linked_list(int data)
{
    struct list_node* new_node = (struct list_node*) malloc(sizeof(struct list_node));
    struct list_node *last = list;

    new_node->data  = data;
    new_node->how_many  = 1;
    new_node->link = NULL;

    if (list == NULL)
    {
       list = new_node;
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
void tree_inorder_to_linked_list(struct tree_node *root)
{
    if(root==NULL)
    {
        return;
    }
    tree_inorder_to_linked_list(root->left_child);
    if(root->data!=-1)
    {
        add_node_at_end_linked_list(root->data);
    }
    tree_inorder_to_linked_list(root->right_child);
}
void printList(struct list_node *node)
{
    while(node!=NULL)
    {
        printf("%d\n", node->data);
        node = node->link;
    }
}
void delete_node_linked_list_lesser(int how_many)
{
    struct list_node *temp = list, *last;
    while(temp!=NULL && temp->how_many<how_many)
    {
        list = temp->link;
        free(temp);
        temp = list;
    }
    while(temp!=NULL)
    {
        while(temp!=NULL && temp->how_many >= how_many)
        {
            last = temp;
            temp = temp->link;
        }
        if(temp==NULL)
            return;
        last->link = temp->link;
        free(temp);
        temp = last->link;
    }
}
int max_linked_list()
{
    if(list==NULL)
        return 0;
    int max = list->how_many;
    struct list_node *temp = list;
    temp=temp->link;
    while(temp!=NULL)
    {
        if(max<temp->how_many)
            max = temp->how_many;
        temp=temp->link;
    }
    return max;
}
void most_frequent_item_bst(struct tree_node *root)
{
    tree_inorder_to_linked_list(root);
    if(list==NULL)
    {
        return;
    }
    else
    {
        delete_node_linked_list_lesser(max_linked_list(list));
    }
    printList(list);
}

int main()
{
    unsigned int N;
    scanf(" %ul",&N);
    if(!(N>=1 && N<=100000))
        return 0;
    struct tree_node *root = NULL;
    for(int i = 0 ; i < N ; i++)
    {
        int data;
        scanf(" %d",&data);
        if(data!=-1)
            root = insert_bst(root,data);
    }
    most_frequent_item_bst(root);
    return 0;
}

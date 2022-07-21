/*
    lab10 task: Bipartite Graph
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct adjacent_node
{
    int destination;
    struct adjacent_node* next;
};
struct adjacent_list
{
    struct adjacent_node *head;
};
struct graph
{
    int x;
    struct adjacent_list *array;
};
struct adjacent_node *create_adjacent_node(int destination)
{
    struct adjacent_node *new_node = (struct adjacent_node*)malloc(sizeof(struct adjacent_node*));
    new_node->destination = destination;
    new_node->next = NULL;
    return new_node;
}
struct graph *create_graph(int x)
{
    struct graph *g = (struct graph*)malloc(sizeof(struct graph* ));
    g->x = x;
    g->array = (struct adjacent_list*)malloc(x*sizeof(struct adjacent_list*));
    for(int i=0; i<x; i++)
    {
        g->array[i].head = NULL;
    }
    return g;
}
void add_edge(struct graph *g, int source, int destination)
{
    struct adjacent_node *check = NULL;
    struct adjacent_node *new_node = create_adjacent_node(destination);
    if(g->array[source].head==NULL)
    {
        new_node->next = g->array[source].head;
        g->array[source].head = new_node;
    }
    else
    {
        check = g->array[source].head;
        while(check->next!=NULL)
        {
            check = check->next;
        }
        check->next = new_node;
    }

    new_node = create_adjacent_node(source);
    if(g->array[destination].head==NULL)
    {
        new_node->next = g->array[destination].head;
        g->array[destination].head = new_node;
    }
    else
    {
        check = g->array[destination].head;
        while(check->next!=NULL)
        {
            check = check->next;
        }
        check->next = new_node;
    }
}
void print_graph(struct graph *g)
{
    for(int i=0; i<g->x; i++)
    {
        struct adjacent_node *temp = g->array[i].head;
        printf("\n vertix[%d] : ",i+1);
        while(temp)
        {
            printf("%d -> ",1+temp->destination);
            temp = temp->next;
        }printf("\n");
    }
}
bool dfs(struct graph *g, int *visited, int *color, int x, int c)
{
    visited[x] = 1;
    color[x] = c;
    struct adjacent_node *temp = g->array[x].head;
    while(temp)
    {
        if(visited[temp->destination]==0)
        {
            if(dfs(g,visited,color,temp->destination,c?0:1)==false)
            {
                return false;
            }
        }
        else
        {
            if(color[x]==color[temp->destination])
            {
                return false;
            }
        }
        temp = temp->next;
    }
    return true;
}
bool is_bipartite_graph(struct graph *g, int N)
{
    int visited[N];
    int color[N];
    for(int i=0; i<N; i++)
    {
        visited[i] = 0;
        color[i] = 0;
    }
    return dfs(g,visited,color,0,0);
}
int main()
{

    int N, E, a, b;
    scanf(" %u",&N);
    if(N<0 || N>10000)
        return 0;
    scanf(" %u",&E);
    if(E<0 || E>10000)
        return 0;
    struct graph *g = create_graph(N);
    for(int i=0; i<E; i++)
    {
        scanf(" %u",&a);
        if(a<0 || a>10000)
            return 0;
        scanf(" %u",&b);
        if(b<0 || b>10000)
            return 0;
        add_edge(g,a-1,b-1);
    }
//    print_graph(g);
    is_bipartite_graph(g,N)?printf("Yes"):printf("No");
    return 0;
}

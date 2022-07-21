/*
    lab2 task: Sparse Matrix
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
//function to get the matrix for the user
int read_matrix(int row, int colm, int matrix[row][colm])
{
    int i,j;
    char num_str[100];
    char temp[100];
    for(i=0 ; i<row ; i++)//loop to get each element
    {
        for(j=0 ; j<colm ; j++)
        {
            scanf(" %s",num_str);
            sprintf(temp,"%d",atoi(num_str));
            if((strcmp(num_str,temp)))
            {
                break;
            }
            else
            {
                matrix[i][j] = atoi(num_str);
            }
        }
        if((strcmp(num_str,temp)))
        {
            printf("Not Valid");
            return 0;
            break;
        }
    }
    return 1;
}

//function to show the matrix to the user
void print_matrix(int row, int colm, int matrix[row][colm])
{
    int i,j;
    for(i=0 ; i<row ; i++)//loop to show each element
    {
        for(j=0 ; j<colm ; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}
struct node
{
    int row;
    int colm;
    int value;
    struct node *next; /* pointer*/
};
struct node* head = NULL;

void insertNodeAtEnd(int row, int colm, int value)
{
    struct node *newNode, *temp;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode != NULL)
    {
        newNode->row = row; //Links the data part
        newNode->colm = colm; //Links the data part
        newNode->value = value; //Links the data part
        newNode->next = NULL;
        temp = head;
        while(temp->next != NULL) //Traverse to the last node
        {
             temp = temp->next;
        }
        temp->next = newNode; //Links the address part
        printf("DATA INSERTED SUCCESSFULLY\n");
    }
    else
    {

    }
}

int single_chain(int row, int colm, int matrix[row][colm])
{
    int i, j, turn=0;
    for(i=0 ; i<row ; i++)
    {
        for(j=0 ; j<colm ; j++)
        {
            if(matrix[i][j]!=0)
            {
                if(turn == 0)
                {
                    /* A node is created by allocating memory to a structure */
                    head = (struct node *)malloc(sizeof(struct node));

                    head->row = i; //Links the data field with data
                    head->colm = j; //Links the data field with data
                    head->value = matrix[i][j]; //Links the data field with data

                    head->next = NULL; //Links the address field to NULL
                }
                else
                {
                    insertNodeAtEnd(i,j,matrix[i][j]);
                }
            }
        }
    }
}

void traverseList(struct Node *header)
{
    struct node *temp;
    /* If the list is empty i.e. head = NULL */
    if(header == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        temp = header;
        while(temp != NULL)
        {
            printf("row = %d colm = %d value = %d\n", temp->row, temp->colm, temp->value); //Prints the data of current node
            temp = temp->next; //Advances the position of current node
        }
    }
}

int main()
{
    int valid = 1;
    while(valid)
    {
        int n, m;
        scanf(" %d %d", &n, &m);
        int x[n][m];
        valid = read_matrix(n, m, x);

        if(valid)
        {
            int k, w;
            scanf(" %d %d", &k, &w);
            int y[k][w];
            valid = read_matrix(k, w, y);
        }
    }

    for(int i=0;i<head->row)


    return 0;
}

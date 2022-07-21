/*
    lab1 task 3: matrix addition
*/
#include <stdio.h>
#include <stdlib.h>

void read_matrix(int matrix[3][3],int size);
void print_matrix(int matrix[3][3],int size);
void add_array(int matrix1[3][3],int matrix2[3][3],int matrix3[3][3],int size);

int main()
{
    int matrix1[3][3],matrix2[3][3],matrix3[3][3];
    int size = 3;

    printf("Input matrix1 of size 3x3:\n");
    read_matrix(matrix1,size);//function calling to get the user matrix

    printf("Input matrix2 of size 3x3:\n");
    read_matrix(matrix2,size);//function calling to get the user matrix

    add_array(matrix1,matrix2,matrix3,size);//calling function for matrix addition
    printf("Sum of both matrices:\n");
    print_matrix(matrix3,size);//calling function to show the matrix

    return 0;
}

//function to get the matrix for the user
void read_matrix(int matrix[3][3],int size)
{
    int i,j;
    for(i=0;i<size;i++)//loop to get each element
    {
        for(j=0;j<size;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
}

//function to show the matrix to the user
void print_matrix(int matrix[3][3],int size)
{
    int i,j;
    for(i=0;i<size;i++)//loop to show each element
    {
        for(j=0;j<size;j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}


void add_array(int matrix1[3][3],int matrix2[3][3],int matrix3[3][3],int size)
{
    int i,j;
    for(i=0;i<size;i++)//loop for matrix addition
    {
        for(j=0;j<size;j++)
        {
            *(*(matrix3+i)+j)=*(*(matrix1+i)+j)+*(*(matrix2+i)+j);
        }
    }
}

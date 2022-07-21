/*
    lab1 task 1: Arithmetic Operations
*/
#include <stdio.h>
#include <stdlib.h>

void read_numbers(float numbers[5]);

int count_positive(float numbers[5]);
int count_negetive(float numbers[5]);

float average_positive(float numbers[5]);
float average_negative(float numbers[5]);

int main()
{
    float numbers[5];
    printf("Enter 5 numbers:\n");
    read_numbers(numbers);

    printf("Number of positive numbers: %d\n",count_positive(numbers));
    printf("Number of Negative numbers: %d\n",count_negetive(numbers));

    printf("Average of positive numbers: %.2f\n",average_positive(numbers));
    printf("Average of negative numbers: %.2f\n",average_negative(numbers));

    return 0;
}


void read_numbers(float numbers[5])
{
    for(int i=0;i<5;i++)//loop to get each element
    {
        scanf(" %f",&numbers[i]);
    }
}

/* function to count positive numbers*/
int count_positive(float numbers[5])
{
    int result = 0;
    for(int i=0;i<5;i++)
    {
        if(numbers[i]>0)
        {
            result++;
        }
    }
    return result;
}

/* function to get average of positive numbers*/
float average_positive(float numbers[5])
{
    float result = 0;
    for(int i=0;i<5;i++)
    {
        if(numbers[i]>0)
        {
            result += numbers[i];
        }
    }
    return result/count_positive(numbers);
}

/* function to count negative numbers*/
int count_negetive(float numbers[5])
{
    int result = 0;
    for(int i=0;i<5;i++)
    {
        if(numbers[i]<0)
        {
            result++;
        }
    }
    return result;
}

/* function to get average of negative numbers*/
float average_negative(float numbers[5])
{
    float result = 0;
    for(int i=0;i<5;i++)
    {
        if(numbers[i]<0)
        {
            result += numbers[i];
        }
    }
    return result/count_negetive(numbers);
}

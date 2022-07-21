/*
    lab7 task: Big Integer
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(unsigned long long int *x, unsigned long long int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
unsigned long long int concatenate_numbers(unsigned long long int x, unsigned long long int y)
{
    unsigned long long int temp = 10;
    while(y>=temp)
    {
        temp = temp * 10;
    }
    return x*temp+y;
}
int partition(unsigned long long int *number, int lower_bound, int upper_bound)
{
    unsigned long long int pivot = number[upper_bound];
    int index = lower_bound-1;
    for(int i = lower_bound ; i <= upper_bound ; i++)
    {
        if(concatenate_numbers(number[i],pivot)>concatenate_numbers(pivot,number[i]))
        {
            index++;
            swap(&number[index],&number[i]);
        }
    }
    swap(&number[index+1],&number[upper_bound]);
    return index+1;
}
void quick_sort(unsigned long long int *number, int lower_bound, int upper_bound)
{
    if(lower_bound<upper_bound)
    {
        int location = partition(number,lower_bound,upper_bound);
        quick_sort(number,lower_bound,location-1);
        quick_sort(number,location+1,upper_bound);
    }
}
char *biggest_combined_number(unsigned long long int *number, unsigned int N)
{
    quick_sort(number,0,N-1);
    static char concatenated_number[50];
    char string_2[50];
    sprintf(concatenated_number,"%llu",number[0]);
    int zero_case = N;
    if(number[0]==0)
        zero_case--;
    for(int i = 1 ; i < N ; i++)
    {
        if(number[i]==0)
            zero_case--;
        sprintf(string_2,"%llu",number[i]);
        strcat(concatenated_number,string_2);
    }
    if(zero_case==0)
        return "0";
    return concatenated_number;
}
int main()
{
    unsigned int N;
    unsigned long long int *number;
    scanf(" %ul",&N);
    if(N<1 || N>100000)
        return 0;
    number = (unsigned long long int*)malloc(N*sizeof(unsigned long long int));
    for(int i=0 ; i<N ; i++)
    {
        scanf(" %llu",number+i);
    }
    printf("%s",biggest_combined_number(number,N));
    return 0;
}

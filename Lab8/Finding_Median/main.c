/*
    lab8 task: Finding Median
*/
#include <stdio.h>
#include <stdlib.h>
void swap(long long int *x, long long int *y)
{
    long long int temp = *x;
    *x = *y;
    *y = temp;
}
unsigned int left_heap(int index)
{
    return 2*index+1;
}
int right_heap(int index)
{
    return 2*index+2;
}
void heapify(long long int *number, int N, int index)
{
    int left = left_heap(index);
    int right = right_heap(index);
    int max = index;
    if(left<N)
    {
        if(number[left]>number[max])
        {
            max = left;
        }
    }
    if(right<N)
    {
        if(number[right]>number[max])
        {
            max = right;
        }
    }
    if(max!=index)
    {
        swap(&number[index],&number[max]);
        heapify(number,N,max);
    }
}
void build_heap(long long int *number, int N)
{
    for(int i = N/2 -1 ; i>=0 ; i--)
    {
        heapify(number,N,i);
    }
}
void heap_sort(long long int *number, int N)
{
    build_heap(number,N);
    for(int i=N-1 ; i>=0 ; i--)
    {
        swap(&number[0],&number[i]);
        heapify(number,i,0);
    }
}
void median(long long int *number, int N)
{
    if(N==0)
    {
        printf("Not Exist");
        return;
    }
    heap_sort(number,N);
    if(N%2==0)
    {
        if(number[(N/2)-1]==0 && number[(N/2)]==0)
        {
            printf("%d",0);
            return;
        }
        if(((number[(N/2)-1]+number[(N/2)]))%2==0)
        {
            printf("%.lld",(number[(N/2)-1]+number[(N/2)])/2);
            return;
        }
        printf("%.1lf",(number[(N/2)-1]+number[(N/2)])/(float)2);
        return;
    }
    printf("%lld",number[(N-1)/2]);
}
int main()
{
    int N;
    long long int *number;
    scanf(" %ul",&N);
    if(N<0 || N>100000)
        return 0;
    number = (long long int*)malloc(N*sizeof(long long int));
    for(int i=0 ; i<N ; i++)
    {
        scanf(" %lld",number+i);
    }
    median(number,N);
    return 0;
}

/*
    lab8 task: Largest Possible Interval (BONUS)
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
long long int largest_possible_interval(long long int *number, int N)
{
    heap_sort(number,N);
    long long int answer = 0;
    for(int i=1 ; i<N ; i++)
    {
        if(i==1)
        {
            answer = number[i]-number[i-1];
        }
        else
        {
            if(number[i]-number[i-1]>answer)
            {
                answer = number[i]-number[i-1];
            }
        }
    }
    return answer;
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
    printf("%lld",largest_possible_interval(number,N));
    return 0;
}

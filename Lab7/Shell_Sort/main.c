/*
    lab7 task: Shell Sort

*/
#include <stdio.h>
#include <stdlib.h>
void shell_sort(long long int *number, int gap, unsigned int N)
{
    if(gap>=1)
    {
        int i, j;
        for(j=gap;j<N;j++)
        {
            for(i=j-gap;i>=0;i=i-gap)
            {
                if(number[i+gap]>number[i])
                {
                    break;
                }
                else
                {
                    int temp=number[i+gap];
                    number[i+gap] = number[i];
                    number[i] = temp;
                }
            }
        }
        return shell_sort(number,gap/2,N);
    }
}
long long int Kth_largest_item_sorted(long long int *number, unsigned int K,  unsigned int N)
{
    return number[N-K];
}
int main()
{
    unsigned int N, K;
    long long int *number;
    scanf(" %ul",&N);
    if(N<1 || N>100000)
        return 0;
    scanf(" %ul",&K);
    if(K<1 || K>N)
        return 0;
    number = (long long int*)malloc(N*sizeof(long long int));
    for(int i=0 ; i<N ; i++)
    {
        scanf(" %lld",number+i);
    }
    shell_sort(number,N/2,N);
    printf("%lld",Kth_largest_item_sorted(number,K,N));
    return 0;
}

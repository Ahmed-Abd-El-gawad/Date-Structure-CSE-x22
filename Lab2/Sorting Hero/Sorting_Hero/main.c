/*
    lab2 task: Sorting Hero
*/
#include <stdio.h>
#include <stdlib.h>
// function to sort array in descending order (insertion sort)
void sort_backward(int arr[], int arr_size)
{
    int temp = arr[arr_size-1];
    for(int i = arr_size-1 ; i > 0 ; i--)
    {
        if(arr[i]>arr[i-1])
        {
            temp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = temp;
        }
    }
}

int main()
{
    int N, Q, i, j, max=0;
    scanf(" %d %d", &N, &Q); // takes number of developers in N and number of tasks in Q

    int h[N], t[Q];

    // takes h --> number of minimum hours for each developer
    for(i = 0 ; i < N ; i++ )
    {
        scanf(" %d",h+i);
    }

    // takes t --> time to finish each task
    for(i = 0 ; i < Q ; i++ )
    {
        scanf(" %d",t+i);
    }

    sort_backward(h, N);
    sort_backward(t, Q);


    for(j = 0 ; j < N ; j++)
    {
        for(i = j ; i < Q ; i++)
        {
            if(h[i]>=t[j])
            {
                max++;
                h[i] = h[i] - t[j];
                break;
            }
        }
    }

    printf("%d ",max);

    return 0;
}

/*
    lab4 task: Convert to Base N
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char base[16][2] = {{'0','\0'},{'1','\0'},{'2','\0'},{'3','\0'},{'4','\0'},{'5','\0'},
            {'6','\0'},{'7','\0'},{'8','\0'},{'9','\0'},{'A','\0'},{'B','\0'},
            {'C','\0'},{'D','\0'},{'E','\0'},{'F','\0'}};// need the '\0' for strcat
int number_counter(int number)
{
    if(number/10 != 0)
        return 1 + number_counter(number/10);
    else
        return 1;
}
// i can't use strrev in hacker rank because of the compiler so i will write the function itself
void str_rev(char *str)
{
    char *start, *end, temp;

    start  = str;//address of first element
    end    = &str[strlen(str)-1];//address of last element

    for (int i = 0 ; i < strlen(str)/2 ; i++,start++,end--)
    {
        temp   = *end;
        *end   = *start;
        *start = temp;
    }
}
const char* convert_to_base_n(int X, int N)
{
    int quotient=X/N;
    static char result[50] = {'\0'};// static so i can return it
    if(X>0)
    {
        strcat(result,base[X - quotient*N]);
        return convert_to_base_n(quotient,N);
    }
    str_rev(result);
    return result;// return reversed string as you added elements to right first
}
int main()
{
    int X, N;
    scanf(" %d %d", &X, &N);
    printf("%s",convert_to_base_n(X,N));
    return 0;
}

/*
    lab1 task 1: Sales People
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    float gross;
    float salary;
    char range_count[9] = {0};  //array of zeros
    int employee_counter = 0;  // number of employees

    //salary initial ranges
    int range_initial_start = 200, range_initial_end = 299;

    printf("Enter Employee gross sale (-1 to end) : ");
    scanf(" %f", &gross);

    while(gross != -1)
    {
        salary = 200 + 0.09 * gross;
        printf("Employee salary is $%.0f \n\n", salary);

        // salary ranges
        for(int i = 0 ; i < 8 ; i++)
        {
            if( ( (range_initial_start +100*i) <= salary) && (salary <= (range_initial_end + 100*i) ) )
            {
                range_count[i] += 1;
            }
        }
        if(salary >= 1000)
        {
                range_count[8] += 1;
        }

        employee_counter += 1;

        printf("Enter Employee gross sale (-1 to end) : ");
        scanf("%f", &gross);

    }

    printf("\nTotal %d Employees Reported\n", employee_counter);
    printf("Employees in the range:\n");

    // print number of employees in each range
    for(int i = 0 ; i < 8 ; i++)
    {
        printf("%d  %d: %d\n",range_initial_start+100*i, range_initial_end + 100*i, range_count[i]);
    }
    printf("Over 1000: %d\n", range_count[8]);

    return 0;
}

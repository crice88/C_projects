// Colin Rice 
// Performs Collatz function on user-
// specified integer.
#include <stdio.h>

int get_start(); // Prototype functions
void collatz(int x);

int main()
{
    collatz(get_start());
    return 0;
}

int get_start()
{
    int x = 0;
    while( x <= 0 )
    {
        printf("Enter the starting number: ");
        scanf("%d", &x);
        if( x <= 0 ) // If number outside bounds, throw this message
        {
            printf("The number should be a positive integer.\n");
        }
    }
    return x;
}

void collatz(int x)
{
    int counter = 1; // Starts at 1 to count the initial number
    printf("Collatz sequence: %d, ", x);
    while(x != 1)
    {
        if((x % 2) == 0)
        {
            x = x/2;
            if(x == 1) // Included to account for the absent ',' at the end of sequence
            {
                printf("%d ", x);
                counter++;
            }
            else
            {
                printf("%d, ", x);
                counter++;
            }           
        }
        else
        {
            x = (x*3) + 1;
            printf("%d, ", x);
            counter++;
        }
    }
    printf("\nLength: %d\n", counter);
}

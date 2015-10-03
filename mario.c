#include <stdio.h>

int main()
{
    int h = 0;
    printf("Height: ");
    scanf("%d", &h);
    
    for ( int line = 1; line < (h+1); line++)
    {
        // Print spaces
        for(int sp = 0; sp < (h - line); sp++)
        {
            printf(" ");
        }
        // Print hashes
        for( int hash = 0; hash < line + 1; hash++)
        {
            printf("#");
        } 
        printf("\n");
    }
    return 0;
}

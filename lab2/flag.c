#include <stdio.h>
// Colin Rice September 2nd, 2015
// Display a flag with a height between 3 and 20 using seperate functions

int get_height();
void draw_flag(int height);

int main()
{
    int height = get_height();
    if (!height) // If height returned 0, exit progrm
        return height;
    else
        draw_flag(height);
    return 0;
}   

int get_height()
{
    int height = 0;
    printf("Enter the height of the flag pole: ");
    scanf("%d", &height);
    if ((height <= 20) && (height >= 3))
    {
        return height;

    }
    else
    {
        printf("You did not enter an acceptable height between 3 and 20!!\n");
        return 0;
    }
}

void draw_flag(height)
{
        printf("+------|\n");
        printf("|      |\n+------|\n");
        for( int i = 0; i < (height - 3); i++)
        {
            printf("       |\n");
        }  
}

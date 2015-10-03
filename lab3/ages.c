// Colin Rice
// September 23rd 2015
// CSCI 46 Professor Brown
// Lab 3: Histogram

#include <stdio.h>
#define SIZE 12

int appr_bin(int x);
void print_histogram(int x[]);
void avg_age(int x[], int count);
void max_age(int x[], int count);
void most_age(int x[]);
void empty_bins(int x[]);

int main()
{
    int bins[SIZE];
    int count = -1;
    // Ask for how many ages, and repeat if negative number given
	printf("How many ages? ");
	while(count < 0)
	{
		scanf("%d", &count);
		if(count < 0)
		{
			printf("Please enter a positive number of ages: \n");
		}
	}
    int ages[count];
    
    // Initialize ages and bins arrays to zeroes
    for( int i = 0; i < count; i++)
    {
        ages[i] = 0;
    }
    for( int i = 0; i < SIZE; i++)
    {
        bins[i] = 0;
    }
    
    // Ask user for the ages, and store each age in an array
    printf("Please enter all ages of the people\n");
    for( int i = 0; i < count; i++ )
    {
        int age;
        printf( "%d: ", i );
        scanf("%d", &age);
        while( age <= -1 || age >= 120 )
        {
            printf("Please enter a valid age between 0 and 119\n%d: ", i);
            scanf("%d", &age);
        }
        ages[i] = age;
    }
	
    // Store number of ages in the appropriate bin
    for(int i = 0; i < count; i++)
    {
        int age = appr_bin(ages[i]);
        bins[age]++;
    }
    
    // Print out a histogram of the data
    print_histogram(bins);
    
	// What is the average age?
    avg_age(ages, count);
	
	// What is the maximum age?
	max_age(ages, count);
    
	// Which bin has the most??
    most_age(bins);
    
	// How many bins have no one in them??
	empty_bins(bins);
}

int appr_bin(int x)
{
    int y = (x/10);
    return y;
}

void print_histogram(int x[])  // Pass the bins array
{
	printf("\nHISTOGRAM OF AGES\n");
	int y = 0;  // Initial bin values
	int z = 9;
	for( int i = 0; i < SIZE; i++, y += 10, z += 10)
	{
		int number_of_ages = x[i];
		printf("%d-%d\t\t", y, z);
		for(int i = 0; i < number_of_ages; i++)
		{
			printf("*");
		}
		printf("\n");
	}
}

void avg_age(int x[], int count)  // Pass the ages array
{
	int sum = 0;
	for(int i = 0; i < count; i++)
	{
		sum += x[i];
	}
	int average = (sum/count);
	printf("\nThe average age is %d\n", average);
}

void max_age(int x[], int count)  // Pass the ages array
{
	int max = x[0];
	for( int i = 0; i < count; i++)
	{
		if(x[i] > max)
		{
			max = x[i];
		}
	}
	printf("The maximum age is %d\n", max);
}

void most_age(int x[])  // Pass the bins array
{
	int max = 0;
	for( int i = 0; i < SIZE; i++ )
	{
		if(x[i] > max)
		{
			max = i;
		}
	}
	printf("The bin with the most ages is number %d\n", max);
}

void empty_bins(int x[])  // Pass the bins array
{
	int none = 0;
	for( int i = 0; i < SIZE; i++)
	{
		if(x[i] == 0)
		{
			none++;
		}
	}
	printf("The number of bins that have no one is %d\n", none);
}

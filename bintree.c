#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"
#include "bintree.h"

const int PASS_LEN=50;        // Maximum any password can be
const int HASH_LEN=34;        // Length of MD5 hash string

// Recursively frees all memory in bin tree
void free_tree(node *n)
{
    if(n)
    {
        free_tree(n->left);
        free_tree(n->right);
        free(n);
        return;
    }
}

char **read_hashes(char *filename)
{
    // Open the inputted file for reading, error if NULL
	FILE *in_file = fopen(filename, "r");
	if (in_file == NULL)
	{
	    printf("ERROR file not opened\n");
		exit(1);
    }
    
    // Allocates a pointer to a group of pointers
    int size = 50;
    char **pwds = (char **)malloc(size * sizeof(char *));
    
    char str[HASH_LEN];
    int i = 0;
    
    // Scans in a file line by line, with a new line char
    // If array is too small, realloc to a bigger size array
    while(fgets(str, HASH_LEN, in_file) != NULL)
    {
        str[strlen(str) - 1] = '\0'; // trim off \0
        if ( i == size )
        {
            size += 20;
            char **newarr = (char **)realloc(pwds, size * sizeof(char *));
            if (newarr != NULL )
            { 
                pwds = newarr;
            }
            else
            {
                printf("realloc failed!\n");
                exit(1);
            } 
        }
        
        // Copy the string into an array with it's exact size
        // Assign the string to the allocated pwds
        char *newstr = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(newstr, str);
        pwds[i] = newstr;
        i++;
    }
    pwds[i] = NULL;
    fclose(in_file);
    return pwds;
}

// Read in each plaintext, hash it, put in bin tree
node *read_dict(char *filename)
{
    FILE *in_file = fopen(filename, "r");
    if(in_file == NULL)
    {
        printf("Could not open file in read_dict!\n");
        exit(1);
    }
    
    node *tree = NULL;
    char str[PASS_LEN];
    
    while(fscanf(in_file, "%s\n", str ) != EOF)
    {
        char *hash = md5(str, strlen(str));
        insert(hash, str, &tree);
        // Free the hash
        free(hash);
    }
    fclose(in_file);
    return tree;
}


int main(int argc, char *argv[])
{
    int i = 0;
    int freecount = 0;
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }
    
    char **hashes = read_hashes(argv[1]);
    node *dict = read_dict(argv[2]);
    node *results;
    
    // Looks at random hashes and compares them to bin tree
    // if a match is found, the hash and plaintext is printed
    // to console
    while( hashes[i] != NULL )
    {
        results = search(hashes[i], dict);
        if(results != NULL)
        {
            printf("%s %s\n", results->hash, results->plain);
        }
        i++;
    }
    
    // Frees all memory allocated in main
    free_tree(dict);
    while(hashes[freecount] != NULL)
    {
        free(hashes[freecount]);
        freecount++;
    }
    free(hashes);  
}

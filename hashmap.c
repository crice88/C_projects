#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define P printf

#include "md5.h"
#include "entry.h"

const int PASS_LEN=20;        // Maximum any password can be
const int HASH_LEN=33;        // Length of MD5 hash strings

// Take a hashed value, converts it to an unsigned char and uses bit shifting to 
// create a 24 bit number.
int locate_file(char *h)
{
    unsigned char *hash = hex2digest(h);
    int idx = hash[0] * 65536 + hash[1] * 256 + hash[2];
    idx *= sizeof(entry);
    return idx;  
} 

int main(int argc, char *argv[])
{
    char hash[HASH_LEN];
    
    if (argc < 3) 
    {
        printf("Usage: %s hash_file rainbow_file\n", argv[0]);
        exit(1);
    }
    
    // Open both hash and rainbow.bow file for reading
    FILE *hf = fopen(argv[1], "r");
    if (!hf) {
        printf("Hash file could not be opened!\n");
        exit(1);
    }

    FILE *rf = fopen(argv[2], "rb");
    if (!rf) {
        printf("Binary file could not be opened!\n");
        exit(1);
    }
    
    // Takes the hash file and hashes each value
    // Seeks to the appropriate mem location and returns password found
    while ( fscanf(hf, "%s\n", hash) != EOF ) 
    {
        entry e;
        int file_location = locate_file(hash);
        
        if (fseek(rf, file_location, SEEK_SET) < 0)
        {
            P("Error! %s\n", strerror(errno));
        }
        
        // Loops while password is not found
        while(fread(&e, sizeof(entry), 1, rf) == 1)
        {
            // Convert the raw data to hex
            char *new_hash = digest2hex(e.hash);
            
            // Compare raw hashes, if equal, print
            // the hash and plain text password, break
            if (memcmp(new_hash, hash, 16) == 0)
            {
                P("%s %s\n", hash, e.pass);
                break;  
            }
        }
    }
    fclose(rf);
    fclose(hf); 
}

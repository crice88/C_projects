// Colin Rice
// October 1st 2015
// CSCI 46 Professor Brown
// Lab 4: CSI

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

unsigned char * read_card(char fname[], int *size);
void save_jpeg(unsigned char data[], int size, char fname[]);
void recover(unsigned char data[], int size);

int main()
{
    int card_length;
    unsigned char *card = read_card("card.raw", &card_length);
    recover(card, card_length);
}

unsigned char * read_card(char fname[], int *size)
{

    struct stat st;
    if (stat(fname, &st) == -1)
    {
        fprintf(stderr, "Can't get info about %s\n", fname);
        exit(1);
    }
    int len = st.st_size;
    unsigned char *raw = (unsigned char *)malloc(len * sizeof(int));
    
    FILE *fp = fopen(fname, "rb");
    if (!fp)
    {
        fprintf(stderr, "Can't open %s for reading\n", fname);
        exit(1);
    }
    
    char buf[512];
    int r = 0;
    while (fread(buf, 1, 512, fp))
    {
        for (int i = 0; i < 512; i++)
        {
            raw[r] = buf[i];
            r++;
        }
    }
    fclose(fp);
    
    *size = len;
    return raw;
}

void save_jpeg(unsigned char data[], int size, char fname[])
{
    FILE *fp = fopen(fname, "wb");
    if (!fp)
    {
        fprintf(stderr, "Can't write to %s\n", fname);
        exit(1);
    }
    
    fwrite(data, 1, size, fp);
    fclose(fp);   
}

void recover(unsigned char data[], int size)
{  
    int picture_count = 0;  // Total number of pictures
    
    for ( int datacount = 0; datacount + 3 < size; datacount++ )
    {
        if ( data[datacount] == 0xff && data[datacount+1] == 0xd8 && data[datacount+2] == 0xff &&  data[datacount+3] == 0xe1 )
        {  
            // Could be valid!! Mark position of Array 
            int start = datacount;
            int searcharray = datacount;
            int done = 0;
            do
            {
                if(data[searcharray] == 0xff && data[searcharray + 1] == 0xd9 && data[searcharray + 2] == 0x00)
                {
                    // If it looks like the end, check to see if it eventually leads to a new file
                    // if so, you found the right breakpoint!
                    int end = searcharray + 1;
                    int done = 1;
                    int endcounter = searcharray + 2;
                    int finished = 0;
                    while(!finished)
                    {
                        if (endcounter < size)
                        {
                            if(data[endcounter] == 0x00)
                            {
                            }
                            else if (data[endcounter] == 0xff && data[endcounter + 1] == 0xd8 && data[endcounter + 2] == 0xff && data[endcounter + 3] == 0xe1)
                            {
                                finished = 1;
                            }
                            else
                            {
                                finished = 1;
                                done = 0;
                            }
                        }
                        else
                        {
                            finished = 1;
                        }
                        endcounter++;
                    }
                }
                searcharray++;
                if ( searcharray > size )
                {
                    break;
                }
            } while (!done);
            // Creates the jpg array from data array, creates file name and passes it to save_jpeg
            unsigned char *jpg = (unsigned char *)malloc(sizeof(unsigned char*) * searcharray);
            for ( int i = 0; i < (searcharray - start); i++)
            {
                jpg[i] = data[start];
                start++;
            }
            char jpg_name[6];
            sprintf(jpg_name, "%d.jpg", picture_count);
            save_jpeg(jpg, (searcharray-start), jpg_name);
            
            picture_count++;
            free(jpg);
        } 
    }
}

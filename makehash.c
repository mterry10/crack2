#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

const int LINE_LEN = 256;  // Maximum length for any line

int main(int argc, char *argv[]) 
{
    // Check command line arguments
    if (argc < 3) 
    {
        // If user doesn't supply source and destination filenames, display error
        fprintf(stderr, "Usage: %s source_file dest_file\n", argv[0]);
        return 1;
    }

    // Open the source file for reading
    FILE *source = fopen(argv[1], "r");
    if (!source) 
    {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file for writing
    FILE *dest = fopen(argv[2], "w");
    if (!dest) 
    {
        perror("Error opening destination file");
        fclose(source);
        return 1;
    }

    // Buffer to hold each line from the source file
    char line[LINE_LEN];

    // Loop through each line of the source file
    while (fgets(line, sizeof(line), source)) 
    {
        // Remove the newline character from the line, if present
        line[strcspn(line, "\n")] = '\0';

        // Generate the MD5 hash for the line
        char *hash = md5(line, strlen(line));

        // Write the hash to the destination file
        fprintf(dest, "%s\n", hash);

        // Free the memory allocated by md5
        free(hash);
    }

    // Close the source file
    fclose(source);

    // Close the destination file
    fclose(dest);

    // Program ends successfully
    return 0;
}
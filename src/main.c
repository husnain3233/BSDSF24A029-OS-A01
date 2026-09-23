#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main()
{
    printf("--- Testing String Functions ---\n");

    char buffer[100];
    char src[] = "Hello, OS Assignment!";

    int len = mystrlen(src);
    printf("mystrlen(\"%s\") = %d\n", src, len);

    int copied = mystrcpy(buffer, src);
    printf("mystrcpy -> \"%s\" (copied %d chars)\n", buffer, copied);

    char partial[20];
    int ncopied = mystrncpy(partial, src, 5);
    printf("mystrncpy(5 chars) -> \"%s\" (copied %d chars)\n", partial, ncopied);

    char catBuffer[100] = "Hello";
    int newLen = mystrcat(catBuffer, ", World!");
    printf("mystrcat -> \"%s\" (new length %d)\n", catBuffer, newLen);

    printf("\n--- Testing File Functions ---\n");

    // Create a small sample file to test with
    const char* filename = "sample.txt";
    FILE* out = fopen(filename, "w");
    if (out == NULL)
    {
        printf("Failed to create sample file.\n");
        return 1;
    }
    fprintf(out, "This is line one.\n");
    fprintf(out, "This line has the word error in it.\n");
    fprintf(out, "Another normal line.\n");
    fprintf(out, "Another line with an error mentioned.\n");
    fclose(out);

    FILE* in = fopen(filename, "r");
    if (in == NULL)
    {
        printf("Failed to open sample file.\n");
        return 1;
    }

    int lines, words, chars;
    if (wordCount(in, &lines, &words, &chars) == 0)
    {
        printf("wordCount -> lines: %d, words: %d, chars: %d\n", lines, words, chars);
    }
    else
    {
        printf("wordCount failed.\n");
    }

    char** matches = NULL;
    int matchCount = mygrep(in, "error", &matches);
    if (matchCount >= 0)
    {
        printf("mygrep found %d matching line(s) containing \"error\":\n", matchCount);
        for (int i = 0; i < matchCount; i++)
        {
            printf("  %s\n", matches[i]);
            free(matches[i]);
        }
        free(matches);
    }
    else
    {
        printf("mygrep failed.\n");
    }

    fclose(in);
    remove(filename);

    return 0;
}

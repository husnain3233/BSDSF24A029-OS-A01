#include "../include/mystrfunctions.h"

// Returns the number of characters in s, not counting the
// terminating null byte. Returns -1 if s is NULL.
int mystrlen(const char* s)
{
    if (s == NULL)
        return -1;

    int len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

// Copies the string pointed to by src (including the terminating
// null byte) into dest. Returns the number of characters copied
// (not counting the null byte), or -1 on failure.
int mystrcpy(char* dest, const char* src)
{
    if (dest == NULL || src == NULL)
        return -1;

    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return i;
}

// Copies at most n characters from src into dest. If src is shorter
// than n, the remainder of dest is padded with null bytes (same
// behaviour as the standard strncpy). Returns the number of
// characters copied from src, or -1 on failure.
int mystrncpy(char* dest, const char* src, int n)
{
    if (dest == NULL || src == NULL || n < 0)
        return -1;

    int i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    int copied = i;

    // Pad the rest with null bytes, like the standard library version
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }

    return copied;
}

// Appends the string src to the end of string dest. dest must have
// enough allocated space to hold the result. Returns the new total
// length of dest, or -1 on failure.
int mystrcat(char* dest, const char* src)
{
    if (dest == NULL || src == NULL)
        return -1;

    int destLen = mystrlen(dest);
    int i = 0;

    while (src[i] != '\0')
    {
        dest[destLen + i] = src[i];
        i++;
    }
    dest[destLen + i] = '\0';

    return destLen + i;
}

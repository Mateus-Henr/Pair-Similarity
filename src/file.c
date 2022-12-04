#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "file.h"

#define FILES_FOLDER "../files/"


void readFileIntoVector(char *filename, int n, char vector[n])
{
    char filepath[strlen(FILES_FOLDER) + strlen(filename) + 1];

    strcpy(filepath, FILES_FOLDER);
    strcat(filepath, filename);

    FILE *file = fopen(filepath, "r");

    if (!file)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        vector[n] = fgetc(file);
    }
}
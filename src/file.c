#include <stdio.h>
#include <string.h>

#include "file.h"

#define FILES_FOLDER "files/"


bool readFileIntoArray(int n, char vector[n], char *filename)
{
    char filepath[strlen(FILES_FOLDER) + strlen(filename) + 1];

    strcpy(filepath, FILES_FOLDER);
    strcat(filepath, filename);

    FILE *file = fopen(filepath, "r");

    if (!file)
    {
        return false;
    }

    for (int i = 0; i < n; i++)
    {
        vector[i] = fgetc(file);
    }

    return true;
}
#include <stdio.h>
#include <stdlib.h>
#include "similarity.h"

#include "file.h"

#define HUMANO_FILENAME "humano.txt"
#define CHIMP_FILENAME "chimp.txt"
#define CACHORRO_FILENAME "cachorro.txt"

#define HUMANO_SIZE 4320
#define CHIMP_SIZE 1682
#define CACHORRO_SIZE 820

#define ERROR_FILE "ERROR: Couldn't read file '%s'"


// Functions prototype

void flushIn(void);

void clearConsole(void);


/**
 * Project's startup point.
 *
 * @return whether the operation was successful or not.
 */
int main()
{
    printf("Welcome to the similarity calculator!\n");

    char humano[HUMANO_SIZE];

    if (!readFileIntoArray(HUMANO_SIZE, humano, HUMANO_FILENAME))
    {
        printf(ERROR_FILE, HUMANO_FILENAME);
        flushIn();
    }

    char chimp[CHIMP_SIZE];

    if (!readFileIntoArray(CHIMP_SIZE, chimp, CHIMP_FILENAME))
    {
        printf(ERROR_FILE, CHIMP_FILENAME);
        flushIn();
    }

    char cachorro[CACHORRO_SIZE];

    if (!readFileIntoArray(CACHORRO_SIZE, cachorro, CACHORRO_FILENAME))
    {
        printf(ERROR_FILE, CACHORRO_FILENAME);
        flushIn();
    }

    int stringSize = 2;
    int qtyCombinations = getVectorSizeForCartesianProduct(stringSize);

    char matrix[qtyCombinations][stringSize];

    initializeCartesianProductMatrix(qtyCombinations, stringSize, matrix);

    for (int i = 0; i < qtyCombinations; i++)
    {
        for (int j = 0; j < stringSize; j++)
        {
            printf("%c", matrix[i][j]);
        }

        printf("\n");
    }

    return 0;
}


/**
 *  Clears the input buffer.
 */
void flushIn(void)
{
    long long int ch;

    do
    {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}


/**
 *  Clears console based on user's OS.
 */
void clearConsole(void)
{
#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif
}
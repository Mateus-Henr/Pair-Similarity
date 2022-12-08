#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "patternMatching.h"
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

    /// ------------------------------- Initializing arrays from files ------------------------------- ///

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

    /// ---------------------------------------------------------------------------------------------- ///



    /// --------------------------- Initializing cartesian product matrix --------------------------- ///

    int numberOfCharacters = 2;
    int qtyOfCombinations = getVectorSizeForCartesianProduct(numberOfCharacters);

    char matrix[qtyOfCombinations][numberOfCharacters + 1];

    initializeCartesianProductMatrix(qtyOfCombinations, numberOfCharacters + 1, matrix);

    /// ---------------------------------------------------------------------------------------------- ///


    /// ------------------------------- Get random pattern from matrix ------------------------------- ///

    int numberOfElementsToChoose = 4;

    char pattern[numberOfElementsToChoose][numberOfCharacters + 1];

    srand(time(NULL));

    for (int i = 0; i < numberOfElementsToChoose; i++)
    {
        strcpy(pattern[i], matrix[rand() % (qtyOfCombinations + 1)]);
    }

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Searching for patterns on strings ----------------------------- ///

    int patternMatchesA[numberOfElementsToChoose];
    int patternMatchesB[numberOfElementsToChoose];

    for (int i = 0; i < numberOfElementsToChoose; i++)
    {
        patternMatchesA[i] = getNumberOfPatternMatching(humano,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingBoyerMooreAlgorithm);
        patternMatchesB[i] = getNumberOfPatternMatching(chimp,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingBoyerMooreAlgorithm);

        printf("Human pattern '%s' matches: %d\n", pattern[i], patternMatchesA[i]);
        printf("Chimp pattern '%s' matches: %d\n\n", pattern[i], patternMatchesB[i]);
    }

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Calculating similarity between vectors ------------------------- ///

    double similarity = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);

    printf("Similarity: %f\n", similarity);

    /// ---------------------------------------------------------------------------------------------- ///


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
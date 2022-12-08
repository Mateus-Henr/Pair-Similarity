/*
    * main.c
    *
    * Using Shift-And algorithm to find the number of pattern matching.
*/

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
#define SIMULATION_SIZE 1000

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
    clearConsole();
    printf("Welcome to the similarity calculator, using Shift-And algorithm!\n\n");

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
    printf("Number of characters: %d \n", numberOfCharacters);
    int qtyOfCombinations = getVectorSizeForCartesianProduct(numberOfCharacters);

    char matrix[qtyOfCombinations][numberOfCharacters + 1];

    initializeCartesianProductMatrix(qtyOfCombinations, numberOfCharacters + 1, matrix);


    /// ---------------------------------------------------------------------------------------------- ///


    /// ------------------------------- Get random pattern from matrix ------------------------------- ///

    srand(time(NULL));
    printf("Quantity of combinations: %d\n", qtyOfCombinations);

    int numberOfElementsToChoose = rand() % (qtyOfCombinations - 1) + 1;
    printf("Number of elements to choose: %d\n\n", numberOfElementsToChoose);

    char pattern[numberOfElementsToChoose][numberOfCharacters + 1];


    for (int i = 0; i < numberOfElementsToChoose; i++)
    {
        strcpy(pattern[i], matrix[rand() % (qtyOfCombinations)]);
    }

    

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Searching for patterns on strings |Human and Chimp| ----------------------------- ///

    int patternMatchesA[numberOfElementsToChoose];
    int patternMatchesB[numberOfElementsToChoose];

    for (int i = 0; i < numberOfElementsToChoose; i++)
    {
        patternMatchesA[i] = getNumberOfPatternMatching(humano,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingShiftAndAlgorithm);
        patternMatchesB[i] = getNumberOfPatternMatching(chimp,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingShiftAndAlgorithm);

        /* 
        printf("Human pattern '%s' matches: %d\n", pattern[i], patternMatchesA[i]);
        printf("Chimp pattern '%s' matches: %d\n\n", pattern[i], patternMatchesB[i]); 
        */
    }

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Calculating similarity between vectors ------------------------- ///

    double similarity = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);

    printf("Similarity between human and chimp: %lf\n", similarity);

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Searching for patterns on strings |Human and Dog| ------------------------------ ///

    for (int i = 0; i < numberOfElementsToChoose; i++)
    {
        patternMatchesA[i] = getNumberOfPatternMatching(humano,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingShiftAndAlgorithm);
        patternMatchesB[i] = getNumberOfPatternMatching(cachorro,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingShiftAndAlgorithm);

        /*
        printf("Human pattern '%s' matches: %d\n", pattern[i], patternMatchesA[i]);
        printf("Dog pattern '%s' matches: %d\n\n", pattern[i], patternMatchesB[i]); 
        */
        
    }

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Calculating similarity between vectors ------------------------- ///

    similarity = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);

    printf("Similarity between human and dog: %lf\n", similarity);

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Searching for patterns on strings |Chimp and Dog| ------------------------------ ///



    for (int i = 0; i < numberOfElementsToChoose; i++)
    {
        patternMatchesA[i] = getNumberOfPatternMatching(chimp,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingShiftAndAlgorithm);
        patternMatchesB[i] = getNumberOfPatternMatching(cachorro,
                                                        pattern[i],
                                                        getNumberOfPatternMatchingShiftAndAlgorithm);

        /* 
        printf("Chimp pattern '%s' matches: %d\n", pattern[i], patternMatchesA[i]);
        printf("Dog pattern '%s' matches: %d\n\n", pattern[i], patternMatchesB[i]); 
        */
    }

    /// ---------------------------------------------------------------------------------------------- ///



    /// ------------------------------ Calculating similarity between vectors ------------------------- ///

    similarity = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);

    printf("Similarity between chimp and dog: %lf\n", similarity);

    /// ---------------------------------------------------------------------------------------------- ///



    /// ----------------------------------- Simulation ----------------------------------------------- ///

    printf("\nDo you want to run the simulation? (y/n)\n");
    char answer = getchar(); flushIn();

    if (answer != 'y')
    {
        printf("Ok... Bye! :D\n");
        return 0;
    }

    double results[SIMULATION_SIZE];
    double average;
    clock_t begin = clock();

    /// ------------------------------ |Human and Chimp| ----------------------------------------------- ///

    average = 0;

    for (int i = 0; i < SIMULATION_SIZE; i++)
    {
        for (int i = 0; i < numberOfElementsToChoose; i++)
        {
            for (int i = 0; i < numberOfElementsToChoose; i++)
            {
                strcpy(pattern[i], matrix[rand() % (qtyOfCombinations)]);
            }

            patternMatchesA[i] = getNumberOfPatternMatching(humano,
                                                            pattern[i],
                                                            getNumberOfPatternMatchingShiftAndAlgorithm);
            patternMatchesB[i] = getNumberOfPatternMatching(chimp,
                                                            pattern[i],
                                                            getNumberOfPatternMatchingShiftAndAlgorithm);
        }

    
        results[i] = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);
        //printf("Similarity between human and chimp: %lf\n", results[i]);
        
        
    }

    for (int i = 0; i < SIMULATION_SIZE; i++) average += results[i];
    
    printf("\nAverage similarity between human and chimp: %lf\n", average /= SIMULATION_SIZE);

    /// ------------------------------ |Human and Dog| ----------------------------------------------- ///

    average = 0;

    for (int i = 0; i < SIMULATION_SIZE; i++)
    {

        for (int i = 0; i < numberOfElementsToChoose; i++)
        {
            for (int i = 0; i < numberOfElementsToChoose; i++)
            {
                strcpy(pattern[i], matrix[rand() % (qtyOfCombinations)]);
            }

            patternMatchesA[i] = getNumberOfPatternMatching(humano,
                                                            pattern[i],
                                                            getNumberOfPatternMatchingShiftAndAlgorithm);
            patternMatchesB[i] = getNumberOfPatternMatching(cachorro,
                                                            pattern[i],
                                                            getNumberOfPatternMatchingShiftAndAlgorithm);
        }
    
        results[i] = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);
        //printf("Similarity between human and dog: %lf\n", results[i]);
    }

    for (int i = 0; i < SIMULATION_SIZE; i++) average += results[i];

    printf("Average similarity between human and dog: %lf\n", average /= SIMULATION_SIZE);

    /// ------------------------------ |Chimp and Dog| ----------------------------------------------- ///

    average = 0;

    for (int i = 0; i < SIMULATION_SIZE; i++)
    {
        for (int i = 0; i < numberOfElementsToChoose; i++)
        {
            for (int i = 0; i < numberOfElementsToChoose; i++)
            {
                strcpy(pattern[i], matrix[rand() % (qtyOfCombinations)]);
            }

            patternMatchesA[i] = getNumberOfPatternMatching(chimp,
                                                            pattern[i],
                                                            getNumberOfPatternMatchingShiftAndAlgorithm);
            patternMatchesB[i] = getNumberOfPatternMatching(cachorro,
                                                            pattern[i],
                                                            getNumberOfPatternMatchingShiftAndAlgorithm);
        }
    
        results[i] = calculateSimilarity(patternMatchesA, patternMatchesB, numberOfElementsToChoose);
        //printf("Similarity between chimp and dog: %lf\n", results[i]);
    }

    for (int i = 0; i < SIMULATION_SIZE; i++) average += results[i];

    printf("Average similarity between chimp and dog: %lf\n\n", average /= SIMULATION_SIZE);

    /// ---------------------------------------------------------------------------------------------- ///

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Simulation size: %d\n", SIMULATION_SIZE);
    printf("Time spent: %lf seconds\n\n", time_spent);

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
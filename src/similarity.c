#include <math.h>
#include <string.h>
#include <stdio.h>

#include "similarity.h"


const char DNA[] = "ACGT";

/**
 * Calculates similarity between two vectors using cosines similarity formula.
 *
 * @param vectorA pointer to first vector.
 * @param vectorB pointer to second vector.
 * @param n vectors' size.
 * @return value of the calculated similarity.
 */
double calculateSimilarity(const int *vectorA, const int *vectorB, int n)
{
    double sumATimesB = 0;
    double sumASquared = 0;
    double sumBSquared = 0;

    for (int i = 1; i <= n; i++)
    {
        sumATimesB += vectorA[i - 1] * vectorB[i - 1];
        sumASquared += pow(vectorA[i - 1], 2);
        sumBSquared += pow(vectorA[i - 1], 2);
    }

    return sumATimesB / (sqrt(sumASquared) * sqrt(sumBSquared));
}


/**
 * Sets the cartesian product matrix with all possible combinations of the given size.
 *
 * @param qtyOfCombinations quantity of combinations.
 * @param size size of the combinations.
 * @param matrix matrix to be filled.
 * @see https://www.geeksforgeeks.org/print-all-combinations-of-given-length/
 */
void setCartesianProductMatrix(int qtyOfCombinations, int k, char matrix[qtyOfCombinations][k])
{
    // Store all possible strings of length k in vector that can be formed from a set of n character using DNA vector
    int n = (int) strlen(DNA);
    int vector[k];

    // Initialize vector with first k character of DNA
    for (int i = 0; i < k; i++)
    {
        vector[i] = 0;
    }

    // One by one print all sequences
    for (int i = 0; i < qtyOfCombinations; i++)
    {
        // Print current combination
        for (int j = 0; j < k; j++)
        {
            matrix[i][j] = DNA[vector[j]];
        }

        // Find the rightmost character which is not DNA.length - 1 and increment its value
        int next = k - 1;

        while (next >= 0 && (vector[next] + 1 >= n))
        {
            next--;
        }

        // If there is no such character, all are DNA.length - 1, then there are no more combinations
        if (next < 0)
        {
            return;
        }

        // If there is such a character, then increment it
        vector[next]++;

        // Fill all the characters to the right of this character with the first character of DNA
        for (int j = next + 1; j < k; j++)
        {
            vector[j] = 0;
        }
    }
}


/**
 * Gets the size for the cartesian product vector.
 *
 * @param  size variable.
 * @return the size for the cartesian product vector.
 */
int getVectorSizeForCartesianProduct(int n)
{
    return (int) pow(4, n);
}
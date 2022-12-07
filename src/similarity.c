#include <math.h>

#include "similarity.h"

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
#include <string.h>
#include <stdlib.h>


/**
 * Returns the max value between two integers.
 *
 * @param a first integer.
 * @param b second integer.
 * @return the max value between a and b.
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}


/**
 * Gets number of pattern matching using Boyer-Moore algorithm.
 *
 * @param text pointer to text.
 * @param pattern pointer to pattern.
 * @return number of pattern matching.
 * @see https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
 */
int getNumberOfPatternMatchingBoyerMooreAlgorithm(char *text, char *pattern)
{
    int M = (int) strlen(pattern);
    int N = (int) strlen(text);
    int numberOfMatches = 0;

    int badChar[256];

    for (int i = 0; i < 256; i++)
    {
        badChar[i] = -1;
    }

    for (int i = 0; i < M; i++)
    {
        badChar[(int) pattern[i]] = i;
    }

    int s = 0;

    while (s <= N - M)
    {
        int j = M - 1;

        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0)
        {
            numberOfMatches++;
            s += (s + M < N) ? M - badChar[text[s + M]] : 1;
        }
        else
        {
            s += max(1, j - badChar[text[s + j]]);
        }
    }

    return numberOfMatches;
}


/**
 *  Gets number of pattern matching using Shift-And algorithm.
 *
 *  @param text pointer to text.
 *  @param pattern pointer to pattern.
 *  @return number of pattern matching.
 *  @see https://www.geeksforgeeks.org/shift-and-algorithm-for-pattern-searching/
 */
int getNumberOfPatternMatchingShiftAndAlgorithm(char *text, char *pattern)
{
    int n = (int) strlen(text);
    int m = (int) strlen(pattern);
    int numberOfMatches = 0;

    int D[256];
    int A = 0;

    for (int i = 0; i < 256; i++)
    {
        D[i] = 0;
    }

    for (int i = 0; i < m; i++)
    {
        D[(int) pattern[i]] |= 1 << i;
    }

    for (int i = 0; i < n; i++)
    {
        A = (A << 1 | 1) & D[(int) text[i]];

        if (A & (1 << (m - 1)))
        {
            numberOfMatches++;
        }
    }

    return numberOfMatches;
}


/**
 * Gets number of pattern matching using Knuth-Morris-Pratt algorithm.
 *
 * @param text pointer to text.
 * @param pattern pointer to pattern.
 * @return number of pattern matching.
 * @see https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
 */
int getNumberOfPatternMatchingKnuthMorrisPrattAlgorithm(char *text, char *pattern)
{
    int n = (int) strlen(text);
    int m = (int) strlen(pattern);
    int *prefix = (int *) malloc(m * sizeof(int));
    int numberOfMatches = 0;

    // Calculate prefix function
    prefix[0] = 0;

    for (int i = 1; i < m; i++)
    {
        int j = prefix[i - 1];

        while (j > 0 && pattern[i] != pattern[j])
        {
            j = prefix[j - 1];
        }

        if (pattern[i] == pattern[j])
        {
            j++;
        }

        prefix[i] = j;
    }

    // Find pattern matching
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = prefix[j - 1];
        }

        if (text[i] == pattern[j])
        {
            j++;
        }
        if (j == m)
        {
            numberOfMatches++;
            j = prefix[j - 1];
        }
    }

    free(prefix);

    return numberOfMatches;
}


/**
 * Gets number of pattern matching using passed in algorithm.
 *
 * @param text pointer to text.
 * @param pattern pointer to pattern.
 * @param algorithm algorithm to use.
 * @return number of pattern matching.
 */
int getNumberOfPatternMatching(char *text, char *pattern, int (*algorithm)(char *, char *))
{
    return (*algorithm)(text, pattern);
}
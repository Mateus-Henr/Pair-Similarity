#ifndef PAIRSIMILARITY_PATTERNMATCHING_H
#define PAIRSIMILARITY_PATTERNMATCHING_H
#endif

int getNumberOfPatternMatchingBoyerMooreAlgorithm(char *text, char *pattern);

int getNumberOfPatternMatchingShiftAndAlgorithm(char *text, char *pattern);

int getNumberOfPatternMatchingKnuthMorrisPrattAlgorithm(char *text, char *pattern);

int getNumberOfPatternMatching(char *text, char *pattern, int (*algorithm)(char *, char *));
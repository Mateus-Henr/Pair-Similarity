#ifndef PAIRSIMILARITY_SIMILARITY_H
#define PAIRSIMILARITY_SIMILARITY_H
#endif

double calculateSimilarity(const int *vectorA, const int *vectorB, int n);

void initializeCartesianProductMatrix(int qtyOfCombinations, int size, char matrix[qtyOfCombinations][size]);

int getVectorSizeForCartesianProduct(int n);
#include "readData.h"
#include "exponentialtsp.h"


double ** matrizAdj; // matriz de adjacencia
int dimension; // quantidade total de vertices

int main(int argc, char** argv) {
    readData(argc, argv, &dimension, &matrizAdj);
    exponential_tsp(dimension, matrizAdj);
    return 0;
}
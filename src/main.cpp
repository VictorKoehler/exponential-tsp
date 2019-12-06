#include "readData.h"
#include "exponentialtsp.h"
#include <ctime>
#include <chrono>
#include <iostream>

std::string CurrentDate()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    char buf[100] = {0};
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
    return buf;
}

double ** matrizAdj; // matriz de adjacencia
int dimension; // quantidade total de vertices

void printData() {
    std::cout << "dimension: " << dimension << std::endl;
    for (size_t i = 0; i < dimension; i++) {
        for (size_t j = 0; j < dimension; j++) {
            std::cout << matrizAdj[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void fixTheGodamnData() {
    for (size_t i = 0; i < dimension; i++) {
        for (size_t j = 0; j < dimension; j++) {
            matrizAdj[i][j] = matrizAdj[i+1][j+1];
        }
    }
}

int main(int argc, char** argv) {
    std::cout << CurrentDate() << std::endl;
    readData(argc, argv, &dimension, &matrizAdj);
    fixTheGodamnData();
    exponential_tsp(dimension, matrizAdj);
    return 0;
}
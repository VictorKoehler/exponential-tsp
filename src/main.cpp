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

int main(int argc, char** argv) {
    std::cout << CurrentDate() << std::endl;
    readData(argc, argv, &dimension, &matrizAdj);
    exponential_tsp(dimension, matrizAdj);
    return 0;
}
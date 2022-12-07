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
    if (argc != 3 || std::string(argv[1]) == "-h" || std::string(argv[2]) == "-h") {
        std::cout << "Usage: " << argv[0] << " <e[dges]|s[toerwagner]|m[axback]|b[oth]|a[rcs]> <input name>\n";
        std::cout << "  Strategies:\n";
        std::cout << "      e[dges]: Uses symmetric formulation\n";
        std::cout << "      a[acs]: Uses assymmetric formulation\n";
        std::cout << "      s[toerwagner]: Uses symmetric formulation with cuts provided by Stoer-Wagner Mincut algorithm\n";
        std::cout << "      m[axback]: Uses symmetric formulation with cuts provided by Nadef Maxback algorithm\n";
        std::cout << "      b[oth]: Uses symmetric formulation with cuts provided by both Nadef Maxback and Stoer-Wagner algorithms\n";
        exit(1);
    }
    readData(argv[2], &dimension, &matrizAdj);
    fixTheGodamnData();
    if (argv[1][0] == 'a') exponential_tsp(dimension, matrizAdj);
    else exponential_tsp_edges(dimension, matrizAdj, argv[1][0] == 's' || argv[1][0] == 'b', argv[1][0] == 'm' || argv[1][0] == 'b');
    std::cout << CurrentDate() << std::endl;
    return 0;
}
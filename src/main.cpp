#include "readData.h"
#include "exponentialtsp.h"
#include <tclap/CmdLine.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <regex>

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

template<typename T, typename V>
void conflict_flags(const T& t, const V& v, const std::string& error_msg="The --$t and --$v flags cannot appear together\n") {
    if (t.isSet() && v.isSet()) {
        auto tmp = regex_replace(error_msg, std::regex("\\$t"), t.getName());
        std::cout << std::regex_replace(tmp, std::regex("\\$v"), v.getName());
        exit(1);
    }
}

struct scoutClass {
    template <typename T>
    scoutClass& operator<<(const T& v) {
        std::cout << " " << v;
        return *this;
    }
} scout;

int main(int argc, char** argv) {
    std::cout << CurrentDate() << std::endl;
    using namespace TCLAP;

	try {
        CmdLine cmd("Solves TSP instances to optimality", ' ', "0.2");
        UnlabeledValueArg<std::string> inputf("input", "TSP Input file", true, "", "input_file.tsp", cmd);
        
        SwitchArg symmetric("s", "symmetric", "Uses symmetric (edges) formulation", cmd);

        TCLAP::ValueArg<int> depth("d", "depth", "Max depth to add user cuts", false, 8, "integer", cmd);
        SwitchArg maxback_usercuts("N", "disable-nadef-maxback-usercuts", "Disables Nadef maxback algorithm on user cuts", cmd, true);
        SwitchArg mincut_usercuts("S", "disable-stoerwagner-mincut-usercuts", "Disables Stoer-Wagner mincut algorithm on user cuts", cmd, true);
        SwitchArg mincut_lazies("L", "disable-stoerwagner-mincut-lazies", "Disables Stoer-Wagner mincut algorithm on lazy cuts", cmd, true);

        cmd.parse(argc, argv);
        conflict_flags(symmetric, depth);
        conflict_flags(symmetric, maxback_usercuts);
        conflict_flags(symmetric, mincut_usercuts);
        conflict_flags(symmetric, mincut_lazies);

        std::cout << "SOLVER PARAMETERS:";
        scout << symmetric.getValue() << depth.getValue() << maxback_usercuts.getValue() << mincut_usercuts.getValue() << mincut_lazies.getValue() << "\n";

        readData(inputf.getValue().c_str(), &dimension, &matrizAdj);
        fixTheGodamnData();
        if (symmetric.getValue()) exponential_tsp(dimension, matrizAdj);
        else exponential_tsp_edges(dimension, matrizAdj, maxback_usercuts.getValue(), mincut_usercuts.getValue(), mincut_lazies.getValue(), depth.getValue());
	} catch (TCLAP::ArgException &e) {
        std::cerr << "Error: " << e.error() << " for arg " << e.argId() << std::endl;
    }
    std::cout << CurrentDate() << std::endl;
    return 0;
}
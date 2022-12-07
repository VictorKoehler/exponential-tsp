#ifndef NADEF_MAXBACK_H_
#define NADEF_MAXBACK_H_

#include <numeric>
#include <vector>
#include <list>
#include "cplex_utils.h"

template<typename T>
std::tuple<std::vector<int>, std::vector<int>, double> nadef_maxback(const T& X_) {
    std::vector<int> s = {0}, smin = {0}; // s0 = {0}
    const int numVertices = getSizeOf(X_);
    s.reserve(numVertices);

    std::list<int> v_minus_s; // s0 = {0}
    std::vector<double> b = {0}; // s0 = {0}
    
    double cutmin = 0, cutval;
    for (int i = 1; i < numVertices; i++) { // s0 = {0}
        v_minus_s.push_back(i); // s0 = {0}
        cutmin += X_[0][i]; // s0 = {0}
        b.push_back(X_[0][i]); // s0 = {0}
    }
    cutval = cutmin;

    while (!v_minus_s.empty()) {
        auto v = v_minus_s.begin();
        for (auto vms_i = ++v_minus_s.begin(); vms_i != v_minus_s.end(); vms_i++) {
            if (b[*vms_i] > b[*v]) v = vms_i;
        }
        int v_value = *v;

        s.push_back(v_value);
        v_minus_s.erase(v);
        cutval += 2 - 2*b[v_value];
        for (const auto t : v_minus_s) {
            b[t] += X_[v_value][t];
        }

        if (cutval < cutmin) {
            cutmin = cutval;
            smin = s;
        }
    }

    std::vector<bool> smin_mask(numVertices, false);
    std::vector<int> not_in_smin;
    not_in_smin.reserve(size_t(numVertices) - s.size());
    
    for (const auto si : smin) smin_mask[si] = true;
    for (size_t i = 0; i < smin_mask.size(); i++) {
        if (!smin_mask[i]) not_in_smin.push_back(int(i));
    }

    // std::cout << "NADEF S: {";
    // std::copy(smin.begin(), smin.end(), std::ostream_iterator<double>(std::cout, " "));
    // std::cout << "} V\\S: {";
    // std::copy(not_in_smin.begin(), not_in_smin.end(), std::ostream_iterator<double>(std::cout, " "));
    // std::cout << "} cutmin=" << cutmin << "\n";
    return {smin, not_in_smin, cutmin};
}

#endif

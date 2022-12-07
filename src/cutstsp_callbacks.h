#ifndef EXPTSP_CUTCALLBACK_H_
#define EXPTSP_CUTCALLBACK_H_

#include "cplex_utils.h"
#include "stoer_wagner_mincut.hpp"
#include "nadef_maxback.hpp"


ILOUSERCUTCALLBACK4(MINCUTTSPCALLBACK, IloArray<IloBoolVarArray> &, x, bool, mincut, bool, maxback, int, maxdepth) {
    assert(mincut || maxback);
    if (getCurrentNodeDepth() > maxdepth) return;
    const int numVertices = x.getSize();
    IloArray<IloNumArray> X_(getEnv(), numVertices);
    for(IloInt i = 0; i < numVertices; i++) {
        X_[i] = IloNumArray(getEnv(), numVertices);
        getValues(X_[i], x[i]);
    }
    
    GraphPartition c;
    if (maxback) c = nadef_maxback(X_);
    if (mincut && (std::get<2>(c) >= 2 || std::get<0>(c).empty() || std::get<1>(c).empty())) c = stoer_wagner_mincut(X_);
    if (std::get<2>(c) >= 2 || std::get<0>(c).empty() || std::get<1>(c).empty()) return;
    IloExpr expr(getEnv());
    for (const auto& i : std::get<0>(c)) {
        for (const auto& j : std::get<1>(c)) {
            expr += x[i][j];
        }
    }
    add(expr >= 2);
}

#endif

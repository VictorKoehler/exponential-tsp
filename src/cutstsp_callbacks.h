#ifndef EXPTSP_CUTCALLBACK_H_
#define EXPTSP_CUTCALLBACK_H_

#include "cplex_utils.h"
#include <boost/heap/fibonacci_heap.hpp>
#include <boost/tti/has_member_data.hpp>
#include <numeric>
#include <vector>
#include <list>

template<typename T>
std::tuple<std::vector<int>, std::vector<int>, double> stoer_wagner_mincut(T& X_, const int numVertices) {
    using boost::heap::fibonacci_heap;
    struct heap_data;
    typedef typename fibonacci_heap<heap_data>::handle_type fibohandle;
    struct heap_data {
        fibohandle handle;
        double value;
        IloInt index;

        heap_data(double p, IloInt i) : value(p), index(i) {}

        bool operator<(heap_data const & rhs) const {
            return value < rhs.value;
        }
    };

    std::vector<int> best_gs, best_gt, group(numVertices);
    best_gs.reserve(numVertices);
    best_gt.reserve(numVertices);
    std::iota(std::begin(group), std::end(group), 0);
    double best_cut_weight = INFINITY;

    for (int iter = 1; iter < numVertices; iter++) {
        fibonacci_heap<heap_data> q;
        std::list<fibohandle> handles;
        
        for(IloInt i = 1; i < numVertices; i++) {
            if (group[i] == i) {
                handles.push_back(q.emplace(X_[1][i], i));
                (*handles.back()).handle = handles.back();
            }
        }

        IloInt g;
        while (q.size() > 2) {
            const auto& g_h = q.top();
            g = g_h.index;
            // std::cout << "Adding " << g+1 << " to A (" << g_h.value << "). Increasing";
            q.pop();
            
            for (auto hi = handles.begin(); hi != handles.end(); ) {
                const auto h = (*(*hi)).index;
                if ((*(*hi)).index != g) {
                    if (X_[g][h] > (*(*hi)).value) {
                        // std::cout << " " << h+1 << "<{" << (*(*hi)).value << "->" << X_[g][h] << "}";
                        (*(*hi)).value = X_[g][h];
                        q.increase((*(*hi)).handle);
                    }
                    hi++;
                } else {
                    hi = handles.erase(hi);
                }
            }
            // std::cout << "\n";
        }
        g = q.top().index;
        q.pop();
        auto t = q.empty() ? 0 : q.top().index;
        double w = 0;
        // std::cout << "== Picked s=" << g+1 << " t=" << t+1 << " w=sum([ ";
        for(IloInt k = 0; k < numVertices; k++) {
            if (group[k] != k) continue;
            w += X_[k][t];
            // std::cout << X_[k][t] << " ";
        }

        const auto st_v = std::min(g, t), st_w = std::max(g, t);
        for(IloInt k = 0; k < numVertices; k++) {
            if (group[k] != k || k == st_v || k == st_w) continue;
            X_[st_v][k] += X_[st_w][k];
            X_[k][st_v] += X_[k][st_w];
        }
        // std::cout << "])=" << w << " ==\n\n";

        if (w < best_cut_weight) {
            best_cut_weight = w;
            best_gt.clear();
            best_gs.clear();
            bool vert_is_in_t[numVertices];
            for (int i = 0; i < numVertices; i++) {
                if (group[i] == i) vert_is_in_t[i] = i == t;
                else vert_is_in_t[i] = vert_is_in_t[group[i]];

                if (vert_is_in_t[i]) best_gt.push_back(i);
                else best_gs.push_back(i);
            }
        }
        group[st_w] = st_v;
    }
    // std::cout << "BEST CUT: w=" << best_cut_weight << "; T={ ";
    // for (const auto& i : best_gt) std::cout << i+1 << " ";
    // std::cout << "} S={ ";
    // for (const auto& i : best_gs) std::cout << i+1 << " ";
    // std::cout << "}\n";
    return {best_gs, best_gt, best_cut_weight};
}

std::tuple<std::vector<int>, std::vector<int>, double> stoer_wagner_mincut(std::vector<std::vector<double>>& X_) {
    return stoer_wagner_mincut(X_, int(X_.size()));
}

std::tuple<std::vector<int>, std::vector<int>, double> stoer_wagner_mincut(IloArray<IloNumArray>& X_) {
    return stoer_wagner_mincut(X_, int(X_.getSize()));
}


ILOUSERCUTCALLBACK1(MINCUTTSPCALLBACK, IloArray<IloBoolVarArray> &, x) {
    const int numVertices = x.getSize();
    IloArray<IloNumArray> X_(getEnv(), numVertices);
    for(IloInt i = 0; i < numVertices; i++) {
        X_[i] = IloNumArray(getEnv(), numVertices);
        getValues(X_[i], x[i]);
    }
    
    const auto c = stoer_wagner_mincut(X_);
    if (std::get<2>(c) >= 2) return;
    IloExpr expr(getEnv());
    for (const auto& i : std::get<0>(c)) {
        for (const auto& j : std::get<1>(c)) {
            expr += x[i][j];
        }
    }
    add(expr >= 2);
}

#endif

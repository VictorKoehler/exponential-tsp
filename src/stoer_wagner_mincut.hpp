#ifndef STOER_WAGNER_MINCUT_H_
#define STOER_WAGNER_MINCUT_H_

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/tti/has_member_data.hpp>
#include <numeric>
#include <vector>
#include <list>
#include "utils.hpp"

template<typename T>
GraphPartition stoer_wagner_mincut(T& X_) {
    using boost::heap::fibonacci_heap;
    struct heap_data;
    typedef typename fibonacci_heap<heap_data>::handle_type fibohandle;
    struct heap_data {
        fibohandle handle;
        double value;
        int index;

        heap_data(double p, int i) : value(p), index(i) {}

        // ~heap_data() {
        //     std::cout << "Deallocating heap_data of index " << index << " value " << value << " and handle " << &handle << std::endl; 
        // }

        bool operator<(heap_data const & rhs) const {
            return value < rhs.value;
        }
    };

    const int numVertices = getSizeOf(X_);
    std::vector<int> best_gs, best_gt, group(numVertices);
    best_gs.reserve(numVertices);
    best_gt.reserve(numVertices);
    std::iota(std::begin(group), std::end(group), 0);
    double best_cut_weight = INFINITY;

    for (int iter = 1; iter < numVertices; iter++) {
        fibonacci_heap<heap_data> q;
        std::list<std::pair<int, fibohandle>> handles;
        
        for(int i = 1; i < numVertices; i++) {
            if (group[i] == i) {
                handles.emplace_back(i, q.emplace(X_[0][i], i));
                (*handles.back().second).handle = handles.back().second;
            }
        }

        int g;
        while (q.size() > 2) {
            const auto& g_h = q.top();
            g = g_h.index;

            // if (verbose) std::cout << "Adding " << g << " to A (" << g_h.value << "). Increasing";
            // auto _tmp = q.top().index;
            q.pop();
            // std::cout << "\nPopping (I) out " << _tmp << " leaving " << q.top().index << "\n";
            
            // int ccc = 0;
            for (auto hi = handles.begin(); hi != handles.end(); ) {
                // std::cout << "  " << ccc++;
                const auto h = hi->first;
                if (h != g) {
                    if (X_[g][h] > (*hi->second).value) {
                        // if (verbose) std::cout << " " << h << "<{" << (*hi->second).value << "->" << X_[g][h] << "}";
                        (*hi->second).value = X_[g][h];
                        q.increase((*hi->second).handle);
                    }
                    hi++;
                } else {
                    hi = handles.erase(hi);
                }
            }
            // if (verbose) std::cout << "\n";
        }
        g = q.top().index;
        q.pop();
        // std::cout << "\nPopping (II) out " << g << " leaving " << (q.empty() ? 0 : q.top().index) << "\n";
        auto t = q.empty() ? 0 : q.top().index;
        double w = 0;
        // if (verbose) std::cout << "== Picked s=" << g+1 << " t=" << t+1 << " w=sum([ ";
        for(int k = 0; k < numVertices; k++) {
            if (group[k] != k) continue;
            w += X_[k][t];
            // if (verbose) std::cout << X_[k][t] << " ";
        }

        const auto st_v = std::min(g, t), st_w = std::max(g, t);
        for(int k = 0; k < numVertices; k++) {
            if (group[k] != k || k == st_v || k == st_w) continue;
            X_[st_v][k] += X_[st_w][k];
            X_[k][st_v] += X_[k][st_w];
        }
        // if (verbose) std::cout << "])=" << w << " ==\n\n";

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

#endif

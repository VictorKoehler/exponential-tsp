#ifndef EXPTSP_CALLBACK_H_
#define EXPTSP_CALLBACK_H_

#include "cplex_utils.h"
#include "stoer_wagner_mincut.hpp"
#include <vector>

/**
 * Eliminação Simples de Ciclos.
 * Para um ciclo C=(a, b, c, d), impõe uma restrição do tipo:
 * A(a, b) + A(b, a) + A(b, c) + A(c, b) + A(c, d) + A(d, c) + A(d, a) + A(a, d) <= #C - 1 = 3
 * Ou seja, para cada dois vértices adjacentes no ciclo, impõe duas somas na restrição.
 * Isso não é o mesmo do modelo proposto, mas funciona: um ciclo é eliminado,
 * mas não todos os ciclos possíveis com esses vértices. Ainda assim o algoritmo garante a
 * otimalidade, já que a Lazy sempre detecta ciclos e elimina-os.
 */
ILOLAZYCONSTRAINTCALLBACK3(CYCLELC_SIMPLE, IloArray<IloBoolVarArray> &, x, int, numVertices, const bool, edges)
{
    bool visited[numVertices] = {false};
    int start = 0, cycles_cc = 0;

    // Enquanto não achamos todos os vértices.
    while (cycles_cc != numVertices) {

        // Para cada ciclo encontrado.
        int atual = start, vert_cc = 0, anterior=-1;
        IloExpr subCycle(getEnv());
        //std::cout << std::endl << "Imposing:";

        do {
            IloNumArray X_(getEnv(), numVertices);
            getValues(X_, x[atual]); // copia o array de fluxos (x)

            for (int i = 0; i < numVertices; i++) {
                if (edges && anterior == i) continue;
                if (X_[i] >= 0.98 && i != atual) {

                    if (i != start || vert_cc != 1) { // ANTI-BUG
                        subCycle += x[atual][i]; // Restrições Simples: Elimina o ciclo da vez,
                        if (!edges) subCycle += x[i][atual]; // mas não todos os ciclos possíveis do conjunto.
                        // std::cout << " " << atual << ":" << i;
                    }

                    vert_cc++; // Incrementa o contador
                    visited[i] = true; // Marca como visitado.
                    anterior = atual;
                    atual = i; // Passa para o próximo vértice.
                    break;
                }
            }
        } while (atual != start);
        cycles_cc += vert_cc;

        if (vert_cc == numVertices) {
            // std::cout << "*****" << std::endl;
            return; // Se houve apenas uma iteração, então o ciclo é hamiltoniano.
        }

        // std::cout << " <= " << (vert_cc-1) << std::endl;
        add(subCycle <= (vert_cc-1));

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                start = i;
                break;
            }
        }
    }
    //std::cout << std::endl << "----" << std::endl;
}




/**
 * Eliminação Completa de Conjunto de Ciclos.
 * Para um ciclo C=(a, b, c, d), impõe uma restrição do tipo:
 * A(a, b) + A(a, c) + A(a, d) + A(b, a) + A(b, c) + A(b, d) +
 * A(c, a) + A(c, b) + A(c, d) + A(d, a) + A(d, b) + A(d, c) <= #C - 1 = 3
 * Essa é a restrição completa como descrita no algoritmo clássico.
 * Isto é, a restrição impede que quaisquer ciclos no conjunto dos vértices de C seja formando.
 */
ILOLAZYCONSTRAINTCALLBACK3(CYCLELC_CONJCOMPL, IloArray<IloBoolVarArray> &, x, int, numVertices, const bool, edges)
{
    bool visited[numVertices] = {false};
    int start = 0, cycles_cc = 0;

    // Enquanto não achamos todos os vértices.
    while (cycles_cc != numVertices) {

        // Para cada ciclo encontrado.
        int atual = start, vert_cc = 0, anterior=-1;
        IloExpr subCycle(getEnv());
        // std::cout << std::endl << "Imposing:";
        std::vector<int> subcycle_vertexs;

        do {
            IloNumArray X_(getEnv(), numVertices);
            getValues(X_, x[atual]); // copia o array de fluxos (x)
            subcycle_vertexs.push_back(atual);

            for (int i = 0; i < numVertices; i++) {
                if (edges && anterior == i) continue;
                if (X_[i] >= 0.98 && i != atual) {

                    if (i != start) { // ANTI-BUG
                        for (int m : subcycle_vertexs) {
                            subCycle += x[m][i]; // Restrições Completas: Elimina o ciclo da vez,
                            if (!edges) subCycle += x[i][m]; // e todos os ciclos desse subconjunto de vértices
                            // std::cout << " " << i << ":" << m;
                        }
                    }
                    // std::cout << ".(" << start << "," << i << ")";

                    vert_cc++; // Incrementa o contador
                    visited[i] = true; // Marca como visitado.
                    anterior = atual;
                    atual = i; // Passa para o próximo vértice.
                    break;
                }
            }
        } while (atual != start);
        cycles_cc += vert_cc;

        if (vert_cc == numVertices) {
            // std::cout << "*****" << std::endl;
            return; // Se houve apenas uma iteração, então o ciclo é hamiltoniano.
        }

        // std::cout << " <= " << (vert_cc-1) << std::endl;
        add(subCycle <= (vert_cc-1));

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                start = i;
                break;
            }
        }
    }
    // std::cout << std::endl << "----" << std::endl;
}



ILOLAZYCONSTRAINTCALLBACK1(SWMINCUTLAZYCALLBACK, IloArray<IloBoolVarArray> &, x) {
    const int numVertices = x.getSize();
    IloArray<IloNumArray> X_(getEnv(), numVertices);
    for(IloInt i = 0; i < numVertices; i++) {
        X_[i] = IloNumArray(getEnv(), numVertices);
        getValues(X_[i], x[i]);
    }
    
    const auto c = stoer_wagner_mincut(X_);
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

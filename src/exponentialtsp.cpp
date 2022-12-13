#include "cplex_utils.h"
#include "exptsp_callbacks.h"
#include "cutstsp_callbacks.h"
#include <iostream>
#include <cassert>

template<bool edges>
int counting_descendent(IloEnv &env, IloCplex &model, IloArray<IloBoolVarArray> &x, int numVertices, double **mdist, int start = 0) {
    int atual = start, cc = 0, anterior = -1;
    //std::cout << "SEQUENCE:";
    bool visited[numVertices]={false};
    do {
        int na = atual;
        if (visited[atual]) std::cout << " " << atual << "!!!";
        visited[atual] = true;
        IloNumArray X_(env, numVertices);
        model.getValues(X_, x[atual]);
        for (int i = 0; i < numVertices; i++) {
            if (edges && i == anterior) continue;
            if (i != atual && X_[i] >= 0.98) {
                // std::cout << " " << atual << "->" << i << "(" << mdist[atual][i] << ")";
                na = i;
                cc++;
            }
        }
        if constexpr (edges) {
            if (atual == start && cc == 2) cc--;
            anterior = atual;
        }
        atual = na;
    } while (atual != start);
    //std::cout << std::endl;
    if (cc != numVertices) {
        std::cout << "\nWARNING: Visited vertices (" << cc << ") is different than total number of vertices (" << numVertices << ")!\n";
        std::cerr << "\nWARNING: Visited vertices (" << cc << ") is different than total number of vertices (" << numVertices << ")!\n";
    }
    return cc;
}

double exponential_tsp(int numVertices, double **mdist) {
    // Ambiente
    IloEnv env;

    // Criando um modelo
    IloModel modelo(env);
    // CPLEX_MUTE(env);



    // Variáveis de decisão

    ////////////////////////////////////////////////////////
    // Variável Xij
    // Se o arco i-j está ativo
    ////////////////////////////////////////////////////////
    IloArray<IloBoolVarArray> x(env, numVertices); // 5.26
    for (int i = 0; i < numVertices; ++i) {
        IloBoolVarArray vetor(env, numVertices);
        x[i] = vetor;
    }

    // Adicao da variável x ao modelo
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            char var[100];
            sprintf(var, "x(%d,%d)", i, j);
            x[i][j].setName(var);
            modelo.add(x[i][j]);
        }
    }



    // Função Objetivo
    IloExpr SumDX(env);
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++)
            SumDX += mdist[i][j]*x[i][j]; // 5.22
    }

    // Adicionando a FO
    modelo.add(IloMinimize(env, SumDX));



    // Restrição: Quantidade de arcos que entram/saem = 1
    for (int i = 0; i < numVertices; ++i) {
        IloExpr temp(env);
        for (int j = 0; j < numVertices; j++) {
            if (j != i)
                temp += x[i][j];
        }
        modelo.add(temp == 1); // 5.24
        temp.end();

        IloExpr temp2(env);
        for (int j = 0; j < numVertices; j++) {
            if (j != i)
                temp2 += x[j][i];
        }
        modelo.add(temp2 == 1); // 5.24
        temp2.end();
    }



    // Let the games begin
    IloCplex exptspModel(modelo);
    exptspModel.use(CYCLELC_CONJCOMPL(env, x, numVertices, false));
    exptspModel.exportModel("results/exptsp.lp");
    exptspModel.setParam(IloCplex::TiLim,60*10);

    IloNum startTime;
    startTime = exptspModel.getTime();
    exptspModel.solve();

    std::cout << "STATUS: " <<  exptspModel.getCplexStatus() << std::endl;
    std::cout << "BEST: " <<  exptspModel.getBestObjValue() << std::endl;
    std::cout << "OBJ VALUE: " <<  exptspModel.getObjValue() << std::endl;
    std::cout << "VISITED: " <<  counting_descendent<false>(env, exptspModel, x, numVertices, mdist) << std::endl;
    std::cout << "TIME ELAPSED: " << (exptspModel.getTime()-startTime) << std::endl << std::endl << "-----" << std::endl;

    double thereturnis = exptspModel.getBestObjValue();
    env.end();
    return thereturnis;
}



double exponential_tsp_edges(int numVertices, double **mdist, bool maxback_cut, bool stoer_wagner_cut, bool stoer_wagner_lazy, int maxdepth) {
    // Ambiente
    IloEnv env;

    // Criando um modelo
    IloModel modelo(env);
    // CPLEX_MUTE(env);



    // Variáveis de decisão

    ////////////////////////////////////////////////////////
    // Variável Xij
    // Se o arco i-j está ativo
    ////////////////////////////////////////////////////////
    IloArray<IloBoolVarArray> x(env, numVertices); // 5.26
    for (int i = 0; i < numVertices; ++i) {
        IloBoolVarArray vetor(env, numVertices);
        x[i] = vetor;
    }

    // Adicao da variável x ao modelo
    for (int i = 0; i < numVertices; i++) {
        for (int j = i+1; j < numVertices; j++) {
            char var[100];
            sprintf(var, "x(%d,%d)", i, j);
            x[i][j].setName(var);
            modelo.add(x[i][j]);
            x[j][i] = x[i][j];
        }
        x[i][i] = x[i][(i+1)%numVertices];
    }



    // Função Objetivo
    IloExpr SumDX(env);
    for (int i = 0; i < numVertices; i++) {
        for (int j = i+1; j < numVertices; j++) {
            SumDX += mdist[i][j]*x[i][j]; // 5.22
            assert(mdist[i][j] == mdist[j][i]);
        }
    }

    // Adicionando a FO
    modelo.add(IloMinimize(env, SumDX));



    // Restrição: Quantidade de arcos que entram/saem = 2
    for (int i = 0; i < numVertices; ++i) {
        IloExpr temp(env);
        for (int j = 0; j < numVertices; j++) {
            if (j != i)
                temp += x[i][j];
        }
        modelo.add(temp == 2);
        temp.end();
    }



    // Let the games begin
    IloCplex exptspModel(modelo);
    if (stoer_wagner_lazy) exptspModel.use(SWMINCUTLAZYCALLBACK(env, x));
    else exptspModel.use(CYCLELC_CONJCOMPL(env, x, numVertices, true));
    if (stoer_wagner_cut || maxback_cut) exptspModel.use(MINCUTTSPCALLBACK(env, x, stoer_wagner_cut, maxback_cut, maxdepth));
    exptspModel.exportModel("results/exptsp.lp");
    exptspModel.setParam(IloCplex::TiLim,60*10);

    IloNum startTime;
    startTime = exptspModel.getTime();
    exptspModel.solve();

    std::cout << "STATUS: " <<  exptspModel.getCplexStatus() << std::endl;
    std::cout << "BEST: " <<  exptspModel.getBestObjValue() << std::endl;
    std::cout << "OBJ VALUE: " <<  exptspModel.getObjValue() << std::endl;
    std::cout << "VISITED: " <<  counting_descendent<true>(env, exptspModel, x, numVertices, mdist) << std::endl;
    std::cout << "TIME ELAPSED: " << (exptspModel.getTime()-startTime) << std::endl << std::endl << "-----" << std::endl;

    double thereturnis = exptspModel.getBestObjValue();
    env.end();
    return thereturnis;
}

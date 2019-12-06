#include "cplex_utils.h"

int counting_descendent(IloEnv &env, IloCplex &model, IloArray<IloBoolVarArray> &x, int numVertices, int start = 0) {
    int atual = start, cc = 0;
    do {
        std::cout << atual << " ";
        IloNumArray X_(env, numVertices);
        model.getValues(X_, x[atual]);
        for (int i = 0; i < numVertices; i++) {
            if (X_[i] >= 0.98) {
                atual = i;
                cc++;
                break;
            }
        }
    } while (atual != start);
    std::cout << std::endl;
    return cc;
}

double exponential_tsp(int numVertices, double **mdist) {
    // Ambiente
    IloEnv env;

    // Criando um modelo
    IloModel modelo(env);
    // env.setOut(env.getNullStream());
    // env.setWarning(env.getNullStream());



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
        modelo.add(IloSum(x[i]) == 1); // 5.23

        IloExpr temp(env);
        for (int j = 0; j < numVertices; j++) {
            temp += x[j][i];
        }
        modelo.add(temp == 1); // 5.24
        temp.end();
    }



    // Let the games begin
    IloCplex exptspModel(modelo);
    exptspModel.exportModel("exptsp.lp");
    exptspModel.solve();

    std::cout << "BEST: " <<  exptspModel.getBestObjValue() << std::endl;
    std::cout << "OBJ VALUE: " <<  exptspModel.getObjValue() << std::endl;
    std::cout << "STATUS: " <<  exptspModel.getCplexStatus() << std::endl;
    std::cout << "VISITED: " <<  counting_descendent(env, exptspModel, x, numVertices) << std::endl;

    return exptspModel.getBestObjValue();
}
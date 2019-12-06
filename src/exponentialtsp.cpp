#include "cplex_utils.h"
#include "exptsp_callbacks.h"

int counting_descendent(IloEnv &env, IloCplex &model, IloArray<IloBoolVarArray> &x, int numVertices, int start = 0) {
    int atual = start, cc = 0;
    do {
        // std::cout << atual << " ";
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
    // std::cout << std::endl;
    return cc;
}

double exponential_tsp(int numVertices, double **mdist) {
    // Ambiente
    IloEnv env;

    // Criando um modelo
    IloModel modelo(env);
    CPLEX_MUTE(env);



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
    exptspModel.use(CYCLELC_SIMPLE(env, x, numVertices));
    exptspModel.exportModel("results/exptsp.lp");
    exptspModel.setParam(IloCplex::TiLim,60*30);

    IloNum startTime;
    startTime = exptspModel.getTime();
    exptspModel.solve();

    std::cout << "BEST: " <<  exptspModel.getBestObjValue() << std::endl;
    std::cout << "OBJ VALUE: " <<  exptspModel.getObjValue() << std::endl;
    std::cout << "STATUS: " <<  exptspModel.getCplexStatus() << std::endl;
    std::cout << "VISITED: " <<  counting_descendent(env, exptspModel, x, numVertices) << std::endl;
    std::cout << "TIME ELAPSED: " << (exptspModel.getTime()-startTime) << std::endl << std::endl << "-----" << std::endl;

    double thereturnis = exptspModel.getBestObjValue();
    env.end();
    return thereturnis;
}
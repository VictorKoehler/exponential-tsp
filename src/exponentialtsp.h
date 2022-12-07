#ifndef EXPTSP_H_INCLUDED
#define EXPTSP_H_INCLUDED

double exponential_tsp(int numVertices, double **mdist);
double exponential_tsp_edges(int numVertices, double **mdist, bool stoer_wagner_cut, bool maxback_cut);

#endif
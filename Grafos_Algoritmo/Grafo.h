#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"
#include "Aresta.h"

class Aresta;
class Vertice;

class Grafo
{
public:
    Grafo();
    ~Grafo();
    void adicionaVertice(string nome);
    void adicionaAresta(string nome1, string nome2);
    void removeVertice(string nome);
    void removeAresta(string nome1, string nome2);
    void listaAdjacencia();
    int grauVertice(string nome);
    bool K_Regularidade(int k);
    int ordemDoGrafo();

private:
    Vertice *primeiro;
    bool existeVertice(string nome);
    Vertice *getVertice(string nome);
};

#endif // GRAFO_H

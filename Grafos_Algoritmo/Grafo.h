#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"
#include "Aresta.h"
#include <stack>

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
    int getOrdemDoGrafo();
    void vizinhancaAberta(string nome);
    void vizinhancaFechada(string nome);
    bool grafoCompleto();
    bool grafoBipartido();

private:
    Vertice *primeiro;
    bool existeVertice(string nome);
    Vertice *getVertice(string nome);
    int ordemGrafo;
    void aumentaOrdem();
    void diminuiOrdem();
    bool grafoVazio();
    int getIndex(string *nomes, string nome);
    bool auxGrafoBipartido(Vertice *auxVertice, stack<string>pilha, int *vizitado, int *coloracao, string *nomes, int cor);
};

#endif // GRAFO_H

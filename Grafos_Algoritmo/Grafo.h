#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"
#include "Aresta.h"
#include <stack>
#include <list>

class Aresta;
class Vertice;

class Grafo
{
public:
    Grafo();
    ~Grafo();
    void adicionaVertice(string nome);
    void adicionaAresta(string nome1, string nome2, bool direcionado);
    void adicionaAresta(string nome1, string nome2, float peso, bool direcionado);
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
    void sequenciaGraus();
    void arvoreGeradoraMinimaKruskal();
    bool existeCiclo();
    void arvoreGeradoraMinimaPrim();
    void caminhoMinimoDijkstra(string vertice1, string vertice2);
    void caminhoMinimoFloyd();
    void fechoTransitivoDireto(string nome, bool direcionado);
    void fechoTransitivoIndireto(string nomes, bool direcionado);

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
    bool contemAresta(string origem, string destino, list<Aresta> *arestas);
    list<Aresta> *ordernarArestasPorPeso(list<Aresta> *arestas);
    bool formaCiclo(list<Aresta> *solucao, Aresta *aresta);
    int distanciaMinima(int dist[], bool sptSet[]);
};

#endif // GRAFO_H

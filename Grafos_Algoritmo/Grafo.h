#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"
#include "Aresta.h"
#include <fstream>
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


//Funcoes com IDs
    void adicionaVertice(int id);
    void adicionaAresta(int id1, int id2, float peso, bool direcionado);
    void adicionaAresta(int id1, int id2, bool direcionado);
    void removeAresta(int id1, int id2, bool direcionado);
    void removeVertice(int id, bool direcionado);
    void vizinhancaAberta(int id);
    void vizinhancaFechada(int id);

    void construirIds();



//Funcoes com strgin nome
    void removeVertice(string nome, bool direcionado);
    void removeAresta(string nome1, string nome2, bool direcionado);
    void listaAdjacencia();
    void grauVertice(string nome, bool direcionado);
    bool K_Regularidade(int k);
    int getOrdemDoGrafo();
    void vizinhancaAberta(string nome);
    void vizinhancaFechada(string nome);
    bool grafoCompleto();
    bool grafoBipartido();
    void sequenciaGraus(bool direcionado);
    void arvoreGeradoraMinimaKruskal();
    bool existeCiclo();
    void arvoreGeradoraMinimaPrim();
    void caminhoMinimoDijkstra(string vertice1);
    void caminhoMinimoFloyd(string vertice);
    void fechoTransitivoDireto(string nome, bool direcionado);
    void fechoTransitivoIndireto(string nome, bool direcionado);
    void apagarGrafo();

    void conjuntoMaximoIndependenteGuloso();
    void conjuntoMaximoIndependenteGulosoRandomizado(int intMax);
    void conjuntoMaximoIndependenteGulosoRandomizadoReativo(int intMax);

    void numeroVertices(int n);

private:
    bool usaId;
    bool *verticesNoGrafo;
    bool existeVertice(int id);
    Vertice *getVertice(int id);





    list<string> *nomes;

    Vertice *primeiro;
    bool existeVertice(string nome);
    Vertice *getVertice(string nome);
    int ordemGrafo;
    void aumentaOrdem();
    void diminuiOrdem();
    bool grafoVazio();
    int getIndex(list<string> *nomes, string nome);
    int getIndex(string *nomes, string nome);
    bool auxGrafoBipartido(Vertice *auxVertice, stack<string>pilha, int *vizitado, int *coloracao, string *nomes, int cor);
    bool contemAresta(string origem, string destino, list<Aresta> *arestas);
    list<Aresta> *ordernarArestasPorPesoCrescente(list<Aresta> *arestas);
    bool formaCiclo(list<Aresta> *solucao, Aresta *aresta);
    int distanciaMinima(int dist[], bool sptSet[]);
    list<Vertice> *ordenaGrauDecrescente(list<Vertice> *vertices);
    bool verticesVizinhos(list<Vertice> *solucao, Vertice *v);
    list<Vertice> *possiveisAdicionarIndependente(list<Vertice> *conjuntoSolucao, bool *verticesNaSolucao);
    Aresta *getMelhorAresta(list<string> *verticesNaSolucao, bool *visitados, list<Aresta> *solucao);
    int Find(int *parent, int n, int tamanho);
    void Union(int *parent, int x, int y);
    int minKey(float *key, bool *verticesNaArvore);
    void imprimirSolucao(list<Vertice> *solucao, ofstream *file);


    void removeVerticesAdjacentes(list<Vertice> *candidatos, string verticeAdicionado, int vizinhos);
};

#endif // GRAFO_H

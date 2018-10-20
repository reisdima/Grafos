#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include "Vertice.h"
using namespace std;

class Vertice;

class Aresta
{
public:
    Aresta();
    Aresta(float peso1);
    ~Aresta();

    void setPeso(float p);
    void setProx(Aresta *p);
    void setVerticeAdj(string nome);
    void setEnderecoVerticeAdj(Vertice *adjacente);

    float getPeso();
    string getVerticeAdj();
    Aresta *getProx();
    Vertice *getEnderecoVerticeAdj();

private:
    float peso;
    Aresta *prox;
    string verticeAdj;
    Vertice *adj;
};

#endif // ARESTA_H

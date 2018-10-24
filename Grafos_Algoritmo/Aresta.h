#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include "Vertice.h"
using namespace std;

class Vertice;

class Aresta
{
public:
    Aresta(); //contrutor para aresta
    Aresta(float peso1); //contrutor para aresta com peso
    ~Aresta();

    void setPeso(float p); //definir peso para aresta sem peso
    void setProx(Aresta *p); //define para onde vai a aresta, ou seja o "nó final"
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

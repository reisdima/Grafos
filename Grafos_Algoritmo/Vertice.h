#ifndef VERTICE_H
#define VERTICE_H
#include <iostream>
#include "Aresta.h"
using namespace std;

class Aresta;

class Vertice
{
public:
    Vertice();
    ~Vertice();
    void setNome(string nome1);
    void setProx(Vertice *p);
    void setArestaAdj(Aresta *adj);

    string getNome();
    int getGrau();
    Vertice *getProx();
    Aresta *getArestaAdj();

    void aumentaGrau();
    void diminuiGrau();

private:
    string nome;
    int grau;
    Vertice *prox;
    Aresta *arestaAdj;

};

#endif // VERTICE_H

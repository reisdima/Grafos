#include "Vertice.h"

Vertice::Vertice()
{
    arestaAdj = NULL;
    prox = NULL;
    grau = 0;
}

Vertice::~Vertice()
{
    //dtor
}

void Vertice::setNome(string nome1)
{
    this->nome = nome1;
}

void Vertice::setArestaAdj(Aresta *adj)
{
    this->arestaAdj = adj;
}

void Vertice::setProx(Vertice *p)
{
    this->prox = p;
}

int Vertice::getGrau()
{
    return grau;
}

string Vertice::getNome()
{
    return this->nome;
}

Aresta *Vertice::getArestaAdj()
{
    return this->arestaAdj;
}

Vertice *Vertice::getProx()
{
    return prox;
}

void Vertice::aumentaGrau()
{
    grau++;
}

void Vertice::diminuiGrau()
{
    grau--;
}

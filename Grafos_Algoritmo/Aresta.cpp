#include "Aresta.h"

Aresta::Aresta()
{
}

Aresta::Aresta(float peso1)
{
    this->peso = peso1;
    this->prox = NULL;
}

Aresta::~Aresta()
{
    //dtor
}

void Aresta::setPeso(float p)
{
    this->peso = p;
}

void Aresta::setProx(Aresta *p)
{
    this->prox = p;
}

void Aresta::setVerticeAdj(string nome)
{
    this->verticeAdj = nome;
}


float Aresta::getPeso()
{
    return this->peso;
}

Aresta *Aresta::getProx()
{
    return this->prox;
}

string Aresta::getVerticeAdj()
{
    return this->verticeAdj;
}

void Aresta::setEnderecoVerticeAdj(Vertice *adjacente)
{
    this->adj = adjacente;
}

Vertice *Aresta::getEnderecoVerticeAdj()
{
    return adj;
}

void Aresta::setNomeOrigem(string nome)
{
    this->verticeOrigem = nome;
}

string Aresta::getNomeOrigem()
{
    return this->verticeOrigem;
}

#include "Vertice.h"

Vertice::Vertice() //contrutor, define a aresta adjascente como full e define seu grau como 0 por ser um novo vertice
{
    arestaAdj = NULL;
    prox = NULL;
    grauEntrada = 0;
    grauSaida = 0;
}

Vertice::~Vertice()
{
    //dtor
}

void Vertice::setNome(string nome1)  //define um nome pro vertice que foi passado como referencia
{
    this->nome = nome1;
}

void Vertice::setArestaAdj(Aresta *adj) //define uma aresta adjascente (passada por referecia) para o vertice selecionado
{
    this->arestaAdj = adj;
}

void Vertice::setProx(Vertice *p)   //define um proximo vertice para o vertice atual(no caso seria como uma aresta entre este dois vertices)
{
    this->prox = p;
}

int Vertice::getGrauEntrada()  //retorna o grau do vertice
{
    return grauEntrada;
}

int Vertice::getGrauSaida()
{
    return grauSaida;
}

string Vertice::getNome() //retorna o grau do vertice
{
    return this->nome;
}

Aresta *Vertice::getArestaAdj() //retorna a aresta adjascente
{
    return this->arestaAdj;
}

Vertice *Vertice::getProx()
{
    return prox;
}
/*
void Vertice::aumentaGrau() //utilizado para aumentar o grau do vertice quando é adicionada uma nova aresta
{
    grauEntrada++;
}

void Vertice::diminuiGrau() //utilizada para diminuir o grau do vertice quando uma aresta é removida
{
    grau--;
}
*/
void Vertice::aumentaGrauEntrada()
{
    grauEntrada++;
}

void Vertice::aumentaGrauSaida()
{
    grauSaida++;
}

void Vertice::diminuiGrauEntrada()
{
    grauEntrada--;
}


void Vertice::diminuiGrauSaida()
{
    grauSaida--;
}











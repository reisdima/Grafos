#ifndef VERTICE_H
#define VERTICE_H
#include <iostream>
#include "Aresta.h"
using namespace std;

class Aresta;

class Vertice
{
public:
    Vertice();                          //contrutor

    ~Vertice();                         //Get do nome do vertice
    void setNome(string nome1);         //Get do grau do vertice
    void setProx(Vertice *p);           //Get do proximo vertice
    void setArestaAdj(Aresta *adj);     //Set da Aresta Adjascente ao vertice

    string getNome();                   //Get do nome do vertice
    int getGrauEntrada();                      //Get do grau do vertice
    int getGrauSaida();                      //Get do grau do vertice
    Vertice *getProx();                 //Get do proximo vertice
    Aresta *getArestaAdj();             //Get da Aresta Adjascente ao vertice

    void aumentaGrauEntrada();                 //Aumenta o grau do vertice
    void aumentaGrauSaida();                 //Aumenta o grau do vertice
    void diminuiGrauEntrada();                 //Diminui o grau do vertice
    void diminuiGrauSaida();                 //Diminui o grau do vertice

private:
    string nome;                        //nome do vertice
    int grau;
    int grauEntrada;                    //grau de entrada do vertice
    int grauSaida;                      //grau de saida do vertice
    Vertice *prox;                      //proximo vertice
    Aresta *arestaAdj;                  //aresta entre o vertice e o proximo

};

#endif // VERTICE_H

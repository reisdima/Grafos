#include "Grafo.h"
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <queue>
#include <string>
#include <time.h>
#include <math.h>
#include <fstream>
#define INF 99999

Grafo::Grafo()
{
    primeiro = NULL;
    ordemGrafo = 0;
    nomes = new list<string>;

}

Grafo::~Grafo()
{
    Vertice *auxVertice = this->primeiro;
    Vertice *auxVertice2 = NULL;
    while(auxVertice!=NULL){
        Aresta *auxAresta = auxVertice->getArestaAdj();
        Aresta *auxAresta2 = NULL;
        while(auxAresta!=NULL){
            auxAresta2 = auxAresta->getProx();
            delete auxAresta;
            auxAresta = auxAresta2;
        }
        auxVertice->setArestaAdj(NULL);
        auxVertice2 = auxVertice->getProx();
        delete auxVertice;
        auxVertice = auxVertice2;
    }
    this->primeiro = NULL;
}

void Grafo::apagarGrafo()
{
    //cout << "Apagando grafo" << endl;
    Vertice *auxVertice = primeiro;
    Vertice *auxVertice2 = NULL;
    while(auxVertice!=NULL){
        Aresta *auxAresta = auxVertice->getArestaAdj();
        Aresta *auxAresta2 = NULL;
        while(auxAresta!=NULL){
            auxAresta2 = auxAresta->getProx();
            delete auxAresta;
            auxAresta = auxAresta2;
        }
        auxVertice->setArestaAdj(NULL);
        auxVertice2 = auxVertice->getProx();
        delete auxVertice;
        auxVertice = auxVertice2;
    }
    //cout << "teste" << primeiro->getNome() << endl;
    primeiro = NULL;
}

bool Grafo::existeVertice(string nome)
{
    Vertice *aux = primeiro;
    while(aux!=NULL && aux->getNome()!=nome)
        aux = aux->getProx();
    if(aux==NULL)
        return false;
    return true;
}

Vertice *Grafo::getVertice(string nome)
{
    Vertice *aux = primeiro;
    if(aux!=NULL){
        while(aux->getNome()!=nome && aux!=NULL)
            aux=aux->getProx();
        if(aux==NULL){
            //vertice não existe
        }
    }
    else{
        //grafo vazio
    }
    return aux;
}

void Grafo::adicionaVertice(string nome)
{
    if(!existeVertice(nome)){
        Vertice *novo = new Vertice();
        novo->setNome(nome);
        novo->setArestaAdj(NULL);
        if(primeiro == NULL){
            primeiro = novo;
        }
        else{
            Vertice *aux = primeiro;
            while(aux->getProx()!=NULL)
                aux = aux->getProx();
            aux->setProx(novo);
        }
        aumentaOrdem();
        nomes->push_back(nome);
    }
}

void Grafo::adicionaAresta(string nome1, string nome2, bool direcionado)
{
    if(!existeVertice(nome1))
        adicionaVertice(nome1);
    if(!existeVertice(nome2))
        adicionaVertice(nome2);
    Vertice *no1 = getVertice(nome1);
    Vertice *no2 = getVertice(nome2);


    Aresta *nova1 = new Aresta();
    nova1->setVerticeAdj(nome2);
    nova1->setNomeOrigem(nome1);
    nova1->setEnderecoVerticeAdj(no2);
    nova1->setProx(NULL);


    Aresta *aux = no1->getArestaAdj();
    if(aux == NULL){
        no1->setArestaAdj(nova1);

    }
    else{
        while(aux->getProx()!=NULL)
            aux = aux->getProx();
        aux->setProx(nova1);
    }

    if(!direcionado){
        Aresta *nova2 = new Aresta();
        nova2->setVerticeAdj(nome1);
        nova2->setNomeOrigem(nome2);
        nova2->setEnderecoVerticeAdj(no1);
        nova2->setProx(NULL);

        aux = no2->getArestaAdj();
        if(aux == NULL){
            no2->setArestaAdj(nova2);
        }
        else{
            while(aux->getProx() != NULL)
                aux = aux->getProx();
            aux->setProx(nova2);
        }
    }
    if(direcionado){
        no1->aumentaGrauSaida();
        no2->aumentaGrauEntrada();
    }
    else{
        no1->aumentaGrauSaida();
        no1->aumentaGrauEntrada();
        no2->aumentaGrauSaida();
        no2->aumentaGrauEntrada();
    }
}

void Grafo::adicionaAresta(string nome1, string nome2, float peso, bool direcionado)
{
    if(!existeVertice(nome1))
        adicionaVertice(nome1);
    if(!existeVertice(nome2))
        adicionaVertice(nome2);
    Vertice *no1 = getVertice(nome1);
    Vertice *no2 = getVertice(nome2);


    Aresta *nova1 = new Aresta();
    nova1->setVerticeAdj(nome2);
    nova1->setNomeOrigem(nome1);
    nova1->setEnderecoVerticeAdj(no2);
    nova1->setProx(NULL);
    nova1->setPeso(peso);


    Aresta *aux = no1->getArestaAdj();
    if(aux == NULL){
        no1->setArestaAdj(nova1);

    }
    else{
        while(aux->getProx()!=NULL)
            aux = aux->getProx();
        aux->setProx(nova1);
    }

    if(!direcionado){
        Aresta *nova2 = new Aresta();
        nova2->setVerticeAdj(nome1);
        nova2->setNomeOrigem(nome2);
        nova2->setEnderecoVerticeAdj(no1);
        nova2->setProx(NULL);
        nova2->setPeso(peso);

        aux = no2->getArestaAdj();
        if(aux == NULL){
            no2->setArestaAdj(nova2);
        }
        else{
            while(aux->getProx() != NULL)
                aux = aux->getProx();
            aux->setProx(nova2);
        }
    }

    if(direcionado){
        no1->aumentaGrauSaida();
        no2->aumentaGrauEntrada();
    }
    else{
        no1->aumentaGrauSaida();
        no1->aumentaGrauEntrada();
        no2->aumentaGrauSaida();
        no2->aumentaGrauEntrada();
    }
}


void Grafo::removeAresta(string nome1, string nome2, bool direcionado)
{
    if(existeVertice(nome1) && existeVertice(nome2)){
        Vertice *auxVertice1 = getVertice(nome1);
        Aresta *atual;
        Aresta *anterior;
        atual = auxVertice1->getArestaAdj();
        if(atual!=NULL){
            anterior = NULL;
            while(atual!=NULL && atual->getVerticeAdj()!=nome2){
                anterior = atual;
                atual = atual->getProx();
            }
            if(atual!=NULL){
                if(anterior!=NULL){
                    anterior->setProx(atual->getProx());
                }
                else{
                    auxVertice1->setArestaAdj(atual->getProx());
                }
                delete atual;
            }
            else{
                //erro nao existe essa aresta
            }
        }
        else{
            //erro vertice nao tem aresta
        }
        Vertice *auxVertice2 = getVertice(nome2);
        atual = auxVertice2->getArestaAdj();
        if(atual!=NULL){
            anterior = NULL;
            while(atual!=NULL && atual->getVerticeAdj()!=nome1){
                anterior = atual;
                atual = atual->getProx();
            }
            if(atual!=NULL){
                if(anterior!=NULL){
                    anterior->setProx(atual->getProx());
                }
                else
                    auxVertice2->setArestaAdj(atual->getProx());
                delete atual;
            }
            else{
                //erro aresta nao existe
            }
        }
        else{
            //erro vertice nao tem aresta
        }
        if(direcionado){
            auxVertice1->diminuiGrauSaida();
            auxVertice2->diminuiGrauEntrada();
        }
        else{
            auxVertice1->diminuiGrauSaida();
            auxVertice2->diminuiGrauEntrada();
            auxVertice1->diminuiGrauEntrada();
            auxVertice2->diminuiGrauSaida();
        }
    }
    else{
        //pelo menos algum vertice não existe
    }
}

void Grafo::removeVertice(string nome, bool direcionado)
{
    if(existeVertice(nome)){
        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                if(auxAresta->getVerticeAdj()==nome){
                    removeAresta(auxVertice->getNome(), nome, direcionado);
                    break;
                }
                auxAresta = auxAresta->getProx();
            }
            auxVertice = auxVertice->getProx();
        }
        Vertice *anterior = NULL;
        auxVertice = primeiro;
        while(auxVertice->getNome()!=nome){
            anterior = auxVertice;
            auxVertice = auxVertice->getProx();
        }
        if(anterior==NULL)
            primeiro = primeiro->getProx();
        else
            anterior->setProx(auxVertice->getProx());
        delete auxVertice;
        diminuiOrdem();
        nomes->remove(nome);
    }
    else{
        //vertice não existe
    }
}


void Grafo::listaAdjacencia()
{
    Vertice *auxVertice = primeiro;
    while(auxVertice!=NULL){
        Aresta *auxAresta = auxVertice->getArestaAdj();
        cout << auxVertice->getNome() << " -> ";
        while(auxAresta!=NULL){
            cout << auxAresta->getVerticeAdj() << " -> ";
            auxAresta = auxAresta->getProx();
        }
        cout << "||" << endl;
        auxVertice = auxVertice->getProx();
    }
}


void Grafo::grauVertice(string nome, bool direcionado)
{
    if(existeVertice(nome)){
        Vertice *auxVertice = getVertice(nome);
        if(direcionado){
            cout << "Grau de entrada: [" << auxVertice->getGrauEntrada() << "]" << endl;
            cout << "Grau de saida: [" << auxVertice->getGrauSaida() << "]" << endl;
        }
        else{
            cout << "Grau do vertice " << nome << ": " << auxVertice->getGrauEntrada() << endl;
        }
    }
    else{
        //erro vertice nao existe

    }
}


bool Grafo::K_Regularidade(int k)
{
    if(!grafoVazio()){
        if(primeiro==NULL){
            return false;
        }
        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            if(auxVertice->getGrauEntrada() != k)
                return false;
            auxVertice = auxVertice->getProx();
        }
        return true;
    }
    else{
        cout << "Grafo vazio" << endl;
        return false;
    }
    /*Vertice *aux = primeiro;
    if(primeiro==NULL)
        return false;
    while(aux!=NULL){
        if(aux->getGrauSaida()!=k)
            return false;
        aux = aux->getProx();
    }
    return true;
*/
}

void Grafo::aumentaOrdem(){
    ordemGrafo++;
}

void Grafo::diminuiOrdem(){
    ordemGrafo--;
}

int Grafo::getOrdemDoGrafo(){
    return ordemGrafo;
}



void Grafo::vizinhancaAberta(string nome)
{
    if(existeVertice(nome)){
        Vertice *auxVertice = getVertice(nome);
        Aresta *auxAresta = auxVertice->getArestaAdj();
        cout << "[ ";
        while(auxAresta!=NULL){
            cout << auxAresta->getVerticeAdj() << ", ";
            auxAresta = auxAresta->getProx();
        }
        cout << "]" << endl;
    }
    else{
        //erro vertice nao existe
    }
}

void Grafo::vizinhancaFechada(string nome)
{
    if(existeVertice(nome)){
        Vertice *auxVertice = getVertice(nome);
        Aresta *auxAresta = auxVertice->getArestaAdj();
        cout << "[ " << auxVertice->getNome() << ", ";
        while(auxAresta!=NULL){
            cout << auxAresta->getVerticeAdj() << ", ";
            auxAresta = auxAresta->getProx();
        }
        cout << "]" << endl;
    }
    else{
        //erro vertice nao existe
    }
}


bool Grafo::grafoCompleto()
{
    if(!grafoVazio()){
        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            if(auxVertice->getGrauSaida()!=ordemGrafo-1){
                return false;
            }
            auxVertice = auxVertice->getProx();
        }
        return true;
    }
    return false;





    /*
    Vertice *aux = primeiro;
    while(aux!=NULL){
        if(aux->getGrau() != ordemGrafo-1)
            return false;
        aux = aux->getProx();
    }
    return true;*/
}


bool Grafo::grafoBipartido()
{
    if(!grafoVazio()){



        stack<string> pilha;
        int cont;
        int *vizitado = new int[ordemGrafo];
        string *nomes = new string[ordemGrafo];
        int *coloracao = new int[ordemGrafo];
        Vertice *verticeAux = primeiro;
        int i=0;
        while (verticeAux!=NULL){
            nomes[i] = verticeAux->getNome();
            i++;
            verticeAux = verticeAux->getProx();
        }
        verticeAux = primeiro;
        for(int i=0; i<ordemGrafo; i++){
            vizitado[i] = 0;
            coloracao[i] = 0;
        }
        int cor = 1;
        return auxGrafoBipartido(verticeAux, pilha, vizitado, coloracao, nomes, cor);
        /*
        pilha.push(verticeAux->getNome());
        int index;
        while(!pilha.empty()){
            index = getIndex(nomes, verticeAux->getNome());
            if(verificado[index]==0){
                verificado[index] = 1;
                coloracao[index]  = cor;
                cor = 2;
                Aresta *auxAresta = verticeAux->getArestaAdj();
                while(auxAresta!=NULL){

                }
            }
            else{

            }

        }*/
/*
    stack<string> *pilha = new <string>stack;
    int *vizitado = new int[ordemGrafo];
    string *nomes = new string[ordemGrafo];
    int *coloracao = new int[ordemGrafo];
    Vertice *verticeAux = primeiro;
    while (verticeAux!=NULL){
        nomes[i] = verticeAux->getNome();
    }
    verticeAux = primeiro;
    for(int i=0; i<ordemGrafo; i++){
        verificado[i] = 0;
        coloracao[i] = 0;
    }
    int cor = 1;
*/
    }
}


bool Grafo::auxGrafoBipartido(Vertice *auxVertice, stack<string>pilha, int *vizitado, int *coloracao, string *nomes, int cor)
{
    /*cout <<endl <<  "Cor: " << cor<<endl;
    if(!pilha.empty())
        cout << "Topo da pilha: "<< pilha.top() << endl;
    else
        cout << "Pilha vazia" << endl;*/
    if(auxVertice==NULL)
        return true;
    int index = getIndex(nomes, auxVertice->getNome());
    if(vizitado[index] == 0){
        //cout << "Adicionando na pilha: " << auxVertice->getNome() << endl;
        pilha.push(auxVertice->getNome());
        vizitado[index] = 1;
        coloracao[index] = cor;
        if(cor==1)
            cor = 2;
        else
            cor = 1;
        Aresta *auxAresta = auxVertice->getArestaAdj();
        while(auxAresta!=NULL){
            bool a = auxGrafoBipartido(getVertice(auxAresta->getVerticeAdj()), pilha, vizitado, coloracao, nomes, cor);
            if(a==false)
                return false;
            auxAresta = auxAresta->getProx();
        }
        pilha.pop();
        return true;
    }
    else{
        //cout << "Vertice " << auxVertice->getNome() << " ja vizitado" << endl << endl;
        if(coloracao[index]!=cor)
            return false;
        else
            return true;

    }
}

int Grafo::getIndex(string *nomes, string nome)
{
    for(int i=0; i<ordemGrafo; i++){
        if(nomes[i] == nome)
            return i;
    }
}

int Grafo::getIndex(list<string> *nomes, string nome)
{
    list<string>::iterator it;
    int i=0;
    for(it=nomes->begin(); it!=nomes->end(); it++){
        if(*it==nome)
            return i;
        i++;
    }

}

bool Grafo::grafoVazio()
{
    return (primeiro==NULL);
}

void Grafo::sequenciaGraus(bool direcionado)
{
    if(!grafoVazio()){
        Vertice *auxVertice = primeiro;
        if(direcionado){
            int *grausEntrada = new int[ordemGrafo];
            int *grausSaida = new int[ordemGrafo];
            int i=0;
            while(auxVertice!=NULL){
                grausEntrada[i] = auxVertice->getGrauEntrada();
                grausSaida[i] = auxVertice->getGrauSaida();
                i++;
                auxVertice = auxVertice->getProx();
            }
            for(i=0; i<ordemGrafo; i++){
                for(int j=0; j<ordemGrafo; j++){
                    if(grausEntrada[i] > grausEntrada[j]){
                        int aux = grausEntrada[i];
                        grausEntrada[i] = grausEntrada[j];
                        grausEntrada[j] = aux;
                        aux = grausSaida[i];
                        grausSaida[i] = grausSaida[j];
                        grausSaida[j] = aux;
                    }
                    else if(grausEntrada[i]==grausEntrada[j]){
                        if(grausSaida[i] > grausSaida[j]){
                            int aux = grausEntrada[i];
                            grausEntrada[i] = grausEntrada[j];
                            grausEntrada[j] = aux;
                            aux = grausSaida[i];
                            grausSaida[i] = grausSaida[j];
                            grausSaida[j] = aux;
                        }
                    }
                }

            }
            cout << "< ";
            for(int i=0; i<ordemGrafo; i++){
                cout << "(" << grausEntrada[i] << ", " << grausSaida[i] << ")";
                if(i<ordemGrafo-1)
                    cout << ", ";
            }
            cout << " >" << endl;
        }
        else{
            int *graus = new int[ordemGrafo];
            int i=0;
            while(auxVertice!=NULL){
                graus[i] = auxVertice->getGrauSaida();
                i++;
                auxVertice = auxVertice->getProx();
            }
            for(i =0; i<ordemGrafo; i++){
                for(int j=0; j<ordemGrafo; j++){
                    if(graus[i]>graus[j]){
                        int aux = graus[i];
                        graus[i] = graus[j];
                        graus[j] = aux;
                    }
                }
            }
            cout << "< ";
            for(int i=0; i<ordemGrafo; i++){
                cout << graus[i];
                if(i<ordemGrafo-1)
                    cout << ", ";
            }
            cout << " >" << endl;
        }
    }




    /*if(!grafoVazio()){
        Vertice *auxVertice = primeiro;
        int *vet = new int[ordemGrafo];
        int i=0;
        while(auxVertice!=NULL){
            vet[i] = auxVertice->getGrau();
            auxVertice = auxVertice->getProx();
            i++;
        }
        for(i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++){
                if(vet[i]>vet[j]){
                    int aux = vet[i];
                    vet[i] = vet[j];
                    vet[j] = aux;
                }
            }
        }

        cout << "< ";
        for(int i=0; i<ordemGrafo; i++){
            cout << vet[i] << ", ";
        }
        cout << " >" << endl;
    }
    else{
        //grafo vazio
    }*/
}



void Grafo::arvoreGeradoraMinimaKruskal()
{

    if(!grafoVazio()){
        Vertice *auxVertice = primeiro;
        list<Aresta> *arestas = new list<Aresta>;
        while(auxVertice!=NULL){
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                arestas->push_back(*auxAresta);
                auxAresta = auxAresta->getProx();
            }
            auxVertice = auxVertice->getProx();
        }

        arestas = ordernarArestasPorPesoDecrescente(arestas);
        int *parent = new int[ordemGrafo];
        auxVertice = primeiro;
        for(int i=0; i<ordemGrafo; i++){
            parent[i] = -1;
            auxVertice = auxVertice->getProx();
        }
        list<Aresta>::iterator it;

        list<Aresta> solucao;

        int e = 0;


        while(e<ordemGrafo-1){

            it = arestas->begin();
            //cout << "Verificando aresta " << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
            int index1 = getIndex(nomes, it->getNomeOrigem());
            int index2 = getIndex(nomes, it->getVerticeAdj());
            //cout << "Indexes: " << index1 << "  " << index2 << endl;
            int x = Find(parent, index1, 0);
            int y = Find(parent, index2, 0);
            //cout << "X: " << x << "  Y: " << y << endl;
            if(x!=y){
                //cout << "Adicionando aresta " << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
                solucao.push_back(*it);
                Union(parent, x, y);
                e++;
            }
            //cout << endl;
            arestas->pop_front();
        }
        float peso = 0;
        for(it=solucao.begin(); it!=solucao.end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << "  (" << it->getPeso() << ")"  << endl;
            peso += it->getPeso();
        }
        cout << endl << "Soma dos pesos: " << peso << endl;


    }





if(false){
/*
    if(!grafoVazio()){
        int contador = 0;
        bool *visitados = new bool[ordemGrafo];
        list<Aresta> *arestas = new list<Aresta>;
        Vertice *auxVertice = primeiro;
        int i=0;
        while(auxVertice!=NULL){
            visitados[i] = false;
            i++;
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                if(!contemAresta(auxAresta->getNomeOrigem(), auxAresta->getVerticeAdj(), arestas)){
                    arestas->push_back(*auxAresta);
                }
                auxAresta = auxAresta->getProx();
            }
            auxVertice = auxVertice->getProx();
        }
        arestas = ordernarArestasPorPesoDecrescente(arestas);
        list<Aresta>::iterator it;
        int index1;
        int index2;
        list<Aresta> *solucao = new list<Aresta>;
        it = arestas->begin();
        while(it!=arestas->end()){
            Aresta auxAresta = *it;
            index1 = getIndex(nomes, auxAresta.getVerticeAdj());
            index2 = getIndex(nomes, auxAresta.getNomeOrigem());
            if(!formaCiclo(solucao, &auxAresta)){
                contador++;
                visitados[index1] = true;
                visitados[index2] = true;
                solucao->push_back(auxAresta);
            }
            it++;
        }
        float soma = 0;
        for(it = solucao->begin(); it!=solucao->end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << "  (" << it->getPeso() << ")" << endl;
            soma += it->getPeso();
        }
        cout << endl << contador;
        cout << "\n\n";
        cout << "Somatorio dos pesos: " << soma << endl;

    }*/
}

}

bool Grafo::contemAresta(string origem, string destino, list<Aresta> *arestas)
{
    list<Aresta>::iterator it;

    for(it = arestas->begin(); it!=arestas->end(); it++){
        if((it->getNomeOrigem()==origem && it->getVerticeAdj()==destino) || (it->getNomeOrigem()==destino && it->getVerticeAdj()==origem))
            return true;

    }
    return false;
}

list<Aresta> *Grafo::ordernarArestasPorPesoDecrescente(list<Aresta> *arestas)
{

    list<Aresta>::iterator it1;
    list<Aresta>::iterator it2;

    for(it1 = arestas->begin(); it1!=arestas->end(); it1++){
        for(it2 = arestas->begin(); it2!=arestas->end(); it2++){
            if(it2->getPeso()>it1->getPeso()){
                Aresta auxAresta = *it2;
                //cout << auxAresta.getPeso() << " ";
                *it2 = *it1;
                *it1 = auxAresta;
            }
        }
    }

    return arestas;
}

bool Grafo::formaCiclo(list<Aresta> *solucao, Aresta *aresta)
{
    if(solucao->empty())
        return false;
    Grafo *G1 = new Grafo();
    list<Aresta>::iterator it1;
    for(it1 = solucao->begin(); it1!=solucao->end(); it1++){
        //cout << "Adicionando aresta: " << it1->getNomeOrigem() << " -> " << it1->getVerticeAdj() << endl;
        G1->adicionaAresta(it1->getNomeOrigem(), it1->getVerticeAdj(), 0);
    }
    //cout << "Adicionando aresta: " << aresta->getNomeOrigem() << " -> " << aresta->getVerticeAdj() << endl;
    G1->adicionaAresta(aresta->getNomeOrigem(), aresta->getVerticeAdj(), 0);
    //G1->listaAdjacencia();
    //cout << endl;
    queue<string> fila;

    bool *visitado = new bool [G1->ordemGrafo];
    string *parent = new string[G1->ordemGrafo];
    Vertice *auxVertice = G1->primeiro;
    for(int i=0; i<G1->ordemGrafo; i++){
        parent[i] = "-1";
        visitado[i] = false;
    }

    fila.push(auxVertice->getNome());
    int index = G1->getIndex(G1->nomes, auxVertice->getNome());
    visitado[index] = true;
    while(!fila.empty()){
        auxVertice = G1->getVertice(fila.front());
        fila.pop();
        Aresta *auxAresta = auxVertice->getArestaAdj();
        while(auxAresta!=NULL){
            index = G1->getIndex(G1->nomes, auxAresta->getVerticeAdj());
            if(!visitado[index]){
                visitado[index] = true;
                fila.push(auxAresta->getVerticeAdj());
                parent[index] = auxVertice->getNome();
            }
            else{
                index = G1->getIndex(G1->nomes, auxVertice->getNome());
                if(parent[index] != auxAresta->getVerticeAdj())
                    return true;
            }
            auxAresta = auxAresta->getProx();
        }
    }
    G1->apagarGrafo();
    //cout << "teste" << endl;
    return false;






    if(false){
            /*
    if(solucao->empty())
        return false;
    //cout << endl;

    Grafo *G1 = new Grafo;
    list<Aresta>::iterator it;
    for(it=solucao->begin(); it!=solucao->end(); it++){
        //cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
        G1->adicionaAresta(it->getNomeOrigem(), it->getVerticeAdj(), 0);
    }
    G1->adicionaAresta(aresta->getNomeOrigem(), aresta->getVerticeAdj(), 0);

    int tamanho = G1->ordemGrafo;
    int *parent = new int[tamanho];
    for(int i=0; i<tamanho; i++)
        parent[i] = -1;
    it = solucao->begin();
    Aresta *auxAresta;
    Vertice *auxVertice = G1->primeiro;
    G1->listaAdjacencia();

    while(auxVertice!=NULL){
        cout << "Vertice atual:  " << auxVertice->getNome() << endl;
        auxAresta = auxVertice->getArestaAdj();
        while(auxAresta!=NULL){
            cout << "Verificando se tem ciclo: " << endl;
            cout << auxAresta->getNomeOrigem() << " -> " << auxAresta->getVerticeAdj() << endl;
            //cout << getIndex(G1->nomes, auxAresta->getNomeOrigem()) << endl;
            //cout << getIndex(G1->nomes, auxAresta->getVerticeAdj()) << endl;
            int x = Find(parent, getIndex(G1->nomes, auxAresta->getNomeOrigem()), tamanho);
            int y = Find(parent, getIndex(G1->nomes, auxAresta->getVerticeAdj()), tamanho);
            cout << x << "  " << y << endl << endl;
            if(x==y){
                cout << "TEEESSSTEE" << endl;
                cout << x << "  " << y << endl;
                return true;
            }
            else
                Union(parent, x, y);
            auxAresta = auxAresta->getProx();
        }
        auxVertice = auxVertice->getProx();
    }

    return false;



/*    while(auxVertice!=NULL){
        Aresta *auxAresta = auxVertice->getArestaAdj();
        while(auxAresta!=NULL){
            int x = Find(parent, ->getIndex(G1->nomes, auxAresta->getNomeOrigem()));
            int y = Find(parent, ->getIndex(G1->nomes, auxAresta->getVerticeAdj()));
            if(a==0)
                cout << x << "  " << y << endl;
            if(x==y){

                return true;
            }
            else
                Union(parent, x, y);
            cout << parent[0] << "  " << parent[1] << endl;
            auxAresta = auxAresta->getProx();
        }
        auxVertice = auxVertice->getProx();
    }
    return false;

    //G1->listaAdjacencia();
    //cout << endl;
    //return G1->existeCiclo();*/
    }
}

void Grafo::Union(int *parent, int x, int y)
{
    int xset = Find(parent, x, 0);
    int yset = Find(parent, y, 0);
    if(xset!=yset){
       parent[xset] = (yset);
    }

}

int Grafo::Find(int *parent, int i, int tamanho)
{
    if(parent[i]==-1)
        return i;
    return Find(parent, parent[i], tamanho);
}

bool Grafo::formaCiclo(bool *visitados, Aresta *aresta, int tamanho, int index1, int index2)
{
    if(tamanho==0)
        return false;

    if(!visitados[index1] || !visitados[index2])
        return false;
    return true;





/*

    if(solucao->empty())
        return false;
    //cout << endl;
    Grafo G1;
    list<Aresta>::iterator it;
    it = solucao->begin();


    while(it!=solucao->end()){

        Aresta auxAresta = *it;
        G1.adicionaAresta(it->getNomeOrigem(), it->getVerticeAdj(), 0);
        it++;

    }
    G1.adicionaAresta(aresta->getNomeOrigem(), aresta->getVerticeAdj(), 0);


    //G1.listaAdjacencia();
    //cout << endl;
    return G1.existeCiclo();*/
}


bool Grafo::existeCiclo()
{
    if(!grafoVazio()){
        queue<string> fila;
        string *parents = new string[ordemGrafo];
        string *nomes = new string[ordemGrafo];
        int *visitados = new int[ordemGrafo];
        int index;
        Vertice *auxVertice = primeiro;
        int i = 0;
        while(auxVertice!=NULL){
            visitados[i] = 0;
            parents[i] = "0";
            nomes[i] = auxVertice->getNome();
            i++;
            auxVertice = auxVertice->getProx();
        }
        auxVertice = primeiro;
        fila.push(auxVertice->getNome());
        index = getIndex(nomes, auxVertice->getNome());
        visitados[index] = 1;
        while(!fila.empty()){
            string atual = fila.front();
            fila.pop();
            auxVertice = getVertice(atual);
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                index = getIndex(nomes, auxAresta->getVerticeAdj());
                if(visitados[index]==0){
                    visitados[index] = 1;
                    fila.push(auxAresta->getVerticeAdj());
                    parents[index] = atual;
                }
                else{
                    index = getIndex(nomes, atual);
                    if(parents[index] != auxAresta->getVerticeAdj()){
                        return true;
                    }
                }
                auxAresta = auxAresta->getProx();
            }
        }
        return false;
    }
}

Aresta *Grafo::getMelhorAresta(list<string> *verticesNaSolucao, bool *visitados, list<Aresta> *solucao)
{
    Vertice *auxVertice;
    list<Aresta> *arestasCandidatas = new list<Aresta>;
    list<string>::iterator it;



    int index1;
    int a = 0;
    int index2;
    int menor = INF;
    Aresta *arestaMenor = NULL;



    for(it=verticesNaSolucao->begin(); it!=verticesNaSolucao->end(); it++){
        auxVertice = getVertice(*it);
        Aresta *auxAresta = auxVertice->getArestaAdj();
        while(auxAresta!=NULL){
            //index1 = getIndex(nomes, auxAresta->getNomeOrigem());
            //index2 = getIndex(nomes, auxAresta->getVerticeAdj());
            /*
            if(auxAresta->getPeso()<menor && (!visitados[index1] || !visitados[index2])){
                arestaMenor = auxAresta;
                menor = auxAresta->getPeso();
            }*/
            if(!contemAresta(auxAresta->getNomeOrigem(), auxAresta->getVerticeAdj(), solucao) && !formaCiclo(solucao, auxAresta)){
                //cout << "Teste1" << endl;
                arestasCandidatas->push_back(*auxAresta);
            }
            a++;
            auxAresta = auxAresta->getProx();
        }
    }
    arestasCandidatas = ordernarArestasPorPesoDecrescente(arestasCandidatas);
    list<Aresta>::iterator it2;
    it2 = arestasCandidatas->begin();
    //cout << endl << "Arestas candidatas: " << endl;
    /*for(it2=arestasCandidatas->begin(); it2!=arestasCandidatas->end(); it2++){
        cout << it2->getNomeOrigem() << " -> " << it2->getVerticeAdj() << endl;
    }*/
    //cout << endl;
    it2 = arestasCandidatas->begin();
    if(it2==arestasCandidatas->end())
        return NULL;
    //cout << "teste1" << endl;
    Aresta *auxAresta = &(*it2);
    return auxAresta;
}

int Grafo::minKey(float *key, bool *verticesNaArvore)
{
    float menor = INT_MAX;
    int menorIndex;
    for(int i=0; i<ordemGrafo; i++){
        if(!verticesNaArvore[i] && key[i]<menor){
            menor = key[i];
            menorIndex = i;
        }
    }
    return menorIndex;
}

void Grafo::arvoreGeradoraMinimaPrim()
{
    /*
    if(!grafoVazio()){
        bool visitados[ordemGrafo];
        list<string> verticesNaSolucao;
        list<Aresta>::iterator it;
        list<string>::iterator itString;
        int index;
        int index2;
        list<Aresta> solucao;
        Vertice *auxVertice = primeiro;
        list<Aresta> *candidatos = new list<Aresta>;
        Aresta *auxAresta = auxVertice->getArestaAdj();
        while(auxAresta!=NULL){
            candidatos->push_back(*auxAresta);
            auxAresta = auxAresta->getProx();
        }
        index = getIndex(nomes, auxVertice->getNome());
        candidatos = ordernarArestasPorPesoDecrescente(candidatos);
        it = candidatos->begin();
        solucao.push_back(*it);
        visitados[index] = true;
        verticesNaSolucao.push_back(auxVertice->getNome());
        candidatos->clear();
        while(verticesNaSolucao.size()<ordemGrafo-1){
            itString = verticesNaSolucao.begin();
            while(itString!=verticesNaSolucao.end()){
                auxVertice = getVertice(*itString);
                auxAresta = auxVertice->getArestaAdj();
                while(auxAresta!=NULL){
                    /*
                    index = getIndex(nomes, auxAresta->getNomeOrigem());
                    index2 = getIndex(nomes, auxAresta->getVerticeAdj());
                    if(!visitados[index] || !visitados[index2]){
                        candidatos->push_back(*auxAresta);
                    }

                    if(!contemAresta(auxAresta->getNomeOrigem(), auxAresta->getVerticeAdj(), &solucao))
                        candidatos->push_back(*auxAresta);
                    auxAresta = auxAresta->getProx();
                }
                itString++;
            }
            candidatos = ordernarArestasPorPesoDecrescente(candidatos);
            it = candidatos->begin();
            index = getIndex(nomes, it->getNomeOrigem());
            index2 = getIndex(nomes, it->getVerticeAdj());
            visitados[index] = true;
            visitados[index2] = true;
            verticesNaSolucao.push_back(it->getVerticeAdj());
            solucao.push_back(*it);
            candidatos->clear();
        }
        int contador = 0;
        float pesos = 0;
        for(it=solucao.begin(); it!=solucao.end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << "  " << it->getPeso() << endl;
            pesos += it->getPeso();
            contador++;
        }
        cout << "Contador: " << contador << endl;
        cout << "Pesos: " << pesos << endl;
    }
*/
if(true){

    if(!grafoVazio()){
        string *parent = new string[ordemGrafo];
        float *key = new float[ordemGrafo];
        bool *verticesNaArvore = new bool[ordemGrafo];

        for(int i=0; i<ordemGrafo;i++){
            key[i] = INF;
            verticesNaArvore[i] = false;
        }

        Vertice *auxVertice = primeiro;
        int index = getIndex(nomes, auxVertice->getNome());
        parent[index] = "-1";
        key[index] = 0;
        for(int i=0; i<ordemGrafo-1; i++){
            int u = minKey(key, verticesNaArvore);
            verticesNaArvore[u] = true;
            Vertice *verticeEscolhido = primeiro;
            for(int j=0; j<ordemGrafo; j++){
                if(j==u)
                    break;
                verticeEscolhido = verticeEscolhido->getProx();
            }
            auxVertice = primeiro;
            Aresta *auxAresta = verticeEscolhido->getArestaAdj();
            while(auxAresta!=NULL){
                index = getIndex(nomes, auxAresta->getVerticeAdj());
                if(!verticesNaArvore[index] && auxAresta->getPeso()<key[index]){
                    parent[index] = verticeEscolhido->getNome();
                    key[index] = auxAresta->getPeso();
                }
                auxAresta = auxAresta->getProx();
            }
        }
        float soma = 0;
        for(int i=1; i<ordemGrafo; i++){
            auxVertice = primeiro;
            for(int j=0; j<ordemGrafo; j++){
                if(i==j)
                    break;
                auxVertice = auxVertice->getProx();
            }
            cout << parent[i] << " -> " << auxVertice->getNome() << " (" << key[i] << ")" << endl;
            soma += key[i];
        }
        cout << endl << "somatorio dos pesos: " << soma << endl;
    }
}
        if(false){/*
        int contador = 0;
        list<string> verticesNaSolucao;
        bool *visitados = new bool[ordemGrafo];
        list<Aresta> solucao;
        Vertice *auxVertice = primeiro;
        verticesNaSolucao.push_back(auxVertice->getNome());
        int index = getIndex(nomes, auxVertice->getNome());
        for(int i=0; i<ordemGrafo; i++){
            visitados[i] = false;
        }
        visitados[index] = true;
        while(solucao.size()<ordemGrafo-1){
            Aresta *auxAresta;
            Aresta *melhorAresta = getMelhorAresta(&verticesNaSolucao, visitados, &solucao);
            if(melhorAresta!=NULL){
                contador++;
                //cout << endl <<  "Melhor aresta, escolhida: " << endl;
                //cout << melhorAresta->getNomeOrigem() << " -> " << melhorAresta->getVerticeAdj() << endl << endl;
                index = getIndex(nomes, melhorAresta->getVerticeAdj());
                visitados[index] = true;
                verticesNaSolucao.push_back(melhorAresta->getVerticeAdj());
                solucao.push_back(*melhorAresta);
            }
            cout << "Tamanho da solucao: " << solucao.size() << endl;
        }
        list<Aresta>::iterator it;
        for(it=solucao.begin(); it!=solucao.end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
        }
        cout << contador << endl;
        cout << "\n\n";
    }*/
    }

    if(false){
/*
    if(!grafoVazio()){
        string *nomes = new string[ordemGrafo];
        int *inseridosNaArvore = new int[ordemGrafo];
        list<string> *verticesNaSolucao = new list<string>;
        list<string> *verticesForaDaSolucao= new list<string>;
        bool *arvore = new bool[ordemGrafo];
        Vertice *auxVertice = primeiro;
        int i=0;
        while(auxVertice!=NULL){
            nomes[i] = auxVertice->getNome();
            arvore[i] = false;
            verticesForaDaSolucao->push_back(auxVertice->getNome());
            auxVertice = auxVertice->getProx();
            i++;
        }

        srand(time(NULL));
        i = rand()%ordemGrafo;
        arvore[i] = true;
        auxVertice = primeiro;

        for(int j=0; j<i; j++){
            auxVertice = auxVertice->getProx();
        }


        verticesNaSolucao->push_back(auxVertice->getNome());
        verticesForaDaSolucao->remove(auxVertice->getNome());

        list<Aresta> *solucao = new list<Aresta>;
        list<Aresta> *arestasCandidatas = new list<Aresta>;
        list<Aresta>::iterator it2;
        list<string>::iterator it1;
        Aresta *auxAresta;
        int index1;
        int index2;
        while(!verticesForaDaSolucao->empty()){
            for(it1=verticesNaSolucao->begin(); it1!=verticesNaSolucao->end(); it1++){
                auxAresta = getVertice(*it1)->getArestaAdj();
                index1 = getIndex(nomes, auxAresta->getNomeOrigem());
                index2 = getIndex(nomes, auxAresta->getVerticeAdj());
                while(auxAresta!=NULL){
                   // cout << "teste" << endl;
                    if(!contemAresta(getVertice(*it1)->getNome(), auxAresta->getVerticeAdj(), arestasCandidatas) && !formaCiclo(solucao, auxAresta)){
                        arestasCandidatas->push_back(*auxAresta);
                        //cout << "Aresta candidata: " << auxAresta->getNomeOrigem() << " -> " << auxAresta->getVerticeAdj() << endl;
                    }
                    auxAresta = auxAresta->getProx();
                }
            }
            arestasCandidatas = ordernarArestasPorPesoDecrescente(arestasCandidatas);
            it2 = arestasCandidatas->begin();
            solucao->push_back(*it2);
            index1 = getIndex(nomes, it2->getNomeOrigem());
            index2 = getIndex(nomes, it2->getVerticeAdj());
            arvore[index1] = true;
            arvore[index2] = true;

            verticesNaSolucao->push_back(it2->getVerticeAdj());
            verticesForaDaSolucao->remove(it2->getVerticeAdj());
            arestasCandidatas->clear();
        }
        //cout << "Teste" << endl;
        list<Aresta>::iterator it;
        for(it=solucao->begin(); it!=solucao->end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
        }
        cout << "\n\n";

    }*/}
}

void Grafo::caminhoMinimoDijkstra(string vertice1)
{
    string *nomes = new string[ordemGrafo];
    int index;
    int *dist = new int[ordemGrafo];
    bool *sptSet = new bool[ordemGrafo];
    list<string> verticesNaSolucao;
    Vertice *auxVertice = primeiro;
    for(int i=0; i<ordemGrafo; i++){
        dist[i] = INF;
        sptSet[i] = false;
        nomes[i] = auxVertice->getNome();
        auxVertice = auxVertice->getProx();
    }
    index = getIndex(nomes, vertice1);
    dist[index] = 0;

    for(int count=0; count<ordemGrafo-1; count++){
        index = distanciaMinima(dist, sptSet);
        sptSet[index] = true;
        verticesNaSolucao.push_back(nomes[index]);
        list<string> verticesCandidatos;
        list<string>::iterator it;
        for(it=verticesNaSolucao.begin(); it!=verticesNaSolucao.end(); it++){
            auxVertice = getVertice(*it);
            int index2 = getIndex(nomes, *it);
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                index2 = getIndex(nomes, auxAresta->getVerticeAdj());
                if(!sptSet[index2] && (dist[index]+auxAresta->getPeso()<dist[index2])){
                    dist[index2] = dist[index] + auxAresta->getPeso();
                    verticesCandidatos.push_back(auxAresta->getVerticeAdj());
                }
                auxAresta = auxAresta->getProx();
            }
        }

    }
    cout << "Vertice \tDistancia do vertice origem" << endl;
    for(int i=0; i<ordemGrafo; i++){
        index = getIndex(nomes, nomes[i]);
        cout << nomes[i] << " \t\t" << dist[index] << endl;
    }



}


int Grafo::distanciaMinima(int dist[], bool sptSet[])
{
    int menor = INF;
    int indexMenor;
    for(int i=0; i<ordemGrafo; i++){
        if(sptSet[i]==false && dist[i]<menor){
            indexMenor = i;
            menor = dist[i];
        }
    }

    return indexMenor;
}

void Grafo::caminhoMinimoFloyd(string vertice)
{
    if(!grafoVazio()){
        string *nomes = new string[ordemGrafo];
        int **dist = new int*[ordemGrafo];
        for(int i=0; i<ordemGrafo; i++){
            dist[i] = new int[ordemGrafo];
        }
        Vertice *auxVertice = primeiro;

        for(int i=0; i<ordemGrafo; i++){
            nomes[i] = auxVertice->getNome();
            auxVertice = auxVertice->getProx();
        }

        auxVertice = primeiro;
        for(int i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++){
                if(i==j)
                    dist[i][j] = 0;
                else
                    dist[i][j] = INF;
            }
        }
        Aresta *auxAresta;
        while(auxVertice!=NULL){
            int index1 = getIndex(nomes, auxVertice->getNome());
            auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                int index2 = getIndex(nomes, auxAresta->getVerticeAdj());
                dist[index1][index2] = auxAresta->getPeso();
                auxAresta = auxAresta->getProx();
            }
            auxVertice = auxVertice->getProx();
        }/*
        for(int i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++)
                cout << dist[i][j] << "  ";
            cout << endl;
        }*/
        cout << endl;
        auxVertice = primeiro;
        Vertice *intermediario = primeiro;
        for(int k=0; k<ordemGrafo; k++){
            Vertice *atual = primeiro;
            int index1 = getIndex(nomes, intermediario->getNome());
            for(int i=0; i<ordemGrafo; i++){
                Vertice *destino = primeiro;
                int index2 = getIndex(nomes, atual->getNome());
                for(int j=0; j<ordemGrafo; j++){
                    int index3 = getIndex(nomes, destino->getNome());
                    if(dist[index2][index1] + dist[index1][index3] < dist[index2][index3]){

                        dist[index2][index3] = dist[index2][index1] + dist[index1][index3];

                    }
                    destino = destino->getProx();
                    //cout << index1 << "  " << index2 << "  " << index3 << "  " << endl;
                }
                atual = atual->getProx();
            }
            intermediario = intermediario->getProx();
        }


        int index = getIndex(nomes, vertice);
        auxVertice = primeiro;
        for(int i=0; i<ordemGrafo; i++){
            if(dist[index][i]==INF)
                cout << vertice << " -> " << auxVertice->getNome() << " (INF)" << endl;
            else
                cout << vertice << " -> " << auxVertice->getNome() << " (" << dist[index][i] << ")" << endl;
            cout << i << endl;
            auxVertice = auxVertice->getProx();
        }
    }
}

void Grafo::fechoTransitivoDireto(string nome, bool direcionado)
{
    if(direcionado && !grafoVazio()){
        Vertice *origem = getVertice(nome);
        list<string> alcancaveis;
        bool *verticesNaSolucao = new bool[ordemGrafo];
        bool *visitados = new bool[ordemGrafo];
        string *nomes = new string[ordemGrafo];
        Vertice *auxVertice = primeiro;
        for(int i=0; i<ordemGrafo; i++){
            visitados[i] = false;
            nomes[i] = auxVertice->getNome();
            auxVertice = auxVertice->getProx();
        }
        stack<string> pilha;
        auxVertice = origem;
        Aresta *auxAresta = origem->getArestaAdj();
        pilha.push(origem->getNome());
        while(!pilha.empty()){
            int index = getIndex(nomes, pilha.top());
            auxVertice = getVertice(pilha.top());

            auxAresta = auxVertice->getArestaAdj();
            bool achou = false;
            while(auxAresta!=NULL){
                index = getIndex(nomes, auxAresta->getVerticeAdj());
                if(!visitados[index]){
                    //cout << "Visitando vertice  " << auxAresta->getVerticeAdj() << endl;
                    visitados[index] = true;
                    alcancaveis.push_back(auxAresta->getVerticeAdj());
                    auxVertice = getVertice(auxAresta->getVerticeAdj());
                    pilha.push(auxVertice->getNome());
                     achou = true;
                    break;
                }
                auxAresta = auxAresta->getProx();
            }
            if(!achou){
                pilha.pop();
            }
        }

        list<string>::iterator it;
        for(it=alcancaveis.begin(); it!=alcancaveis.end(); it++){
            cout << *it << "  ";
        }
    }
}

void Grafo::fechoTransitivoIndireto(string nome, bool direcionado)
{
    if(direcionado && !grafoVazio()){
        list<string> solucao;
        bool **alcansaveis = new bool*[ordemGrafo];
        bool *verticeNaSolucao = new bool[ordemGrafo];
        string *nomes = new string[ordemGrafo];
        Vertice *auxVertice = primeiro;
        for(int i=0; i<ordemGrafo; i++){
            alcansaveis[i] = new bool[ordemGrafo];
            nomes[i] = auxVertice->getNome();
            auxVertice = auxVertice->getProx();
            verticeNaSolucao[i] = false;
        }
        for(int i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++){
                alcansaveis[i][j] = 0;
            }
        }
        auxVertice = primeiro;
        int index1;
        while(auxVertice!=NULL){
            index1 = getIndex(nomes, auxVertice->getNome());
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                int index2 = getIndex(nomes, auxAresta->getVerticeAdj());
                alcansaveis[index1][index2] = 1;
                auxAresta = auxAresta->getProx();
            }
            auxVertice = auxVertice->getProx();
        }

        auxVertice = primeiro;
        Vertice *intermediario = primeiro;

        for(int i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++){
                cout << alcansaveis[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl << endl;


        for(int k=0; k<ordemGrafo; k++){
            Vertice *atual = primeiro;
            index1 = getIndex(nomes, intermediario->getNome());
            for(int i=0; i<ordemGrafo; i++){
                Vertice *destino = primeiro;
                int index2 = getIndex(nomes, atual->getNome());
                for(int j=0; j<ordemGrafo; j++){
                    int index3 = getIndex(nomes, destino->getNome());
                    alcansaveis[i][j] = alcansaveis[i][j] || (alcansaveis[i][k] && alcansaveis[k][j]);
                    if(destino->getNome()==nome && alcansaveis[i][j] && !verticeNaSolucao[index2]){
                        verticeNaSolucao[index2] = true;
                        solucao.push_back(atual->getNome());
                    }
                    destino = destino->getProx();

                    //cout << index1 << "  " << index2 << "  " << index3 << endl;
                }
                atual = atual->getProx();
            }
            intermediario = intermediario->getProx();
        }
        for(int i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++){
                cout << alcansaveis[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl;
        list<string>::iterator it;
        for(it=solucao.begin(); it!=solucao.end(); it++){
            cout << *it << "  ";
        }



    }
}


void Grafo::conjuntoMaximoIndependenteGuloso()
{
    if(!grafoVazio()){
        list<Vertice> *vertices = new list<Vertice>;
        list<Vertice> *solucao = new list<Vertice>;
        list<Vertice>::iterator it;
        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            vertices->push_back(*auxVertice);
            auxVertice = auxVertice->getProx();
        }
        vertices = ordenaGrauDecrescente(vertices);
        while(!vertices->empty()){
            it = vertices->begin();
            auxVertice = &(*it);
            vertices->pop_front();
            if(!verticesVizinhos(solucao, auxVertice)){
                solucao->push_back(*auxVertice);
            }
        }
        cout << endl;
        list<string>::iterator it2;
        for(it=solucao->begin(); it!=solucao->end(); it++)
            cout << it->getNome() << "  ";
        cout << endl << endl;
    }
}

list<Vertice> *Grafo::ordenaGrauDecrescente(list<Vertice> *vertices)
{
    list<Vertice>::iterator it1;
    list<Vertice>::iterator it2;
    for(it1=vertices->begin(); it1!=vertices->end(); it1++){
        for(it2=vertices->begin(); it2!=vertices->end(); it2++){
            if(it1->getGrauSaida() < it2->getGrauSaida()){
                Vertice auxVertice = *it1;
                *it1 = *it2;
                *it2 = auxVertice;
            }
        }
    }
    return vertices;
}

bool Grafo::verticesVizinhos(list<Vertice> *solucao, Vertice *v)
{
    list<Vertice>::iterator it;
    for(it=solucao->begin(); it!=solucao->end(); it++){
        Aresta *auxAresta = it->getArestaAdj();
        while(auxAresta!=NULL){
            if(auxAresta->getVerticeAdj()==v->getNome() || auxAresta->getNomeOrigem()==v->getNome()){
                return true;
            }
            auxAresta = auxAresta->getProx();
        }
    }
    return false;
}


void Grafo::conjuntoMaximoIndependenteGulosoRandomizado(int intMax, float alpha)
{
    if(!grafoVazio()){
        ofstream file;
        file.open("gulosoRandomizado.txt");
        srand (time(NULL));
        list<Vertice> *solucao = new list<Vertice>;
        list<Vertice> *candidatos = new list<Vertice>;
        Vertice *auxVertice;
        float alfa[3] = {0.1, 0.2, 0.3};
        list<Vertice>::iterator it;
        for(int p=0;p<3; p++){
            file << "ALFA " << alfa[p] << "\n\n";
            for(int m=0; m<20; m++){
                candidatos = possiveisAdicionarIndependente(solucao);
                candidatos = ordenaGrauDecrescente(candidatos);
                int contador = 0;
                while(contador<intMax && !candidatos->empty()){
                    int n = ceil(candidatos->size()*alfa[p]);
                    int random = rand()%n;
                    it = candidatos->begin();
                    for(int i=0; i<random; i++)
                        it++;
                    auxVertice = &(*it);

                    solucao->push_back(*auxVertice);
                    candidatos = possiveisAdicionarIndependente(solucao);
                    candidatos = ordenaGrauDecrescente(candidatos);
                    contador++;

                }

                file << "Execucao " << m+1 << "\n\t";
                this->imprimirSolucao(solucao, &file);
                solucao->clear();
                candidatos->clear();
            }
        }
        delete solucao;
    }
}

void Grafo::imprimirSolucao(list<Vertice> *solucao, ofstream *file)
{
    if(!solucao->empty()){
        list<Vertice>::iterator it;


        for(it=solucao->begin(); it!=solucao->end(); it++){
            *file << it->getNome() << "  ";
        }
        *file << "\n\n";
    }
}

list<Vertice> *Grafo::possiveisAdicionarIndependente(list<Vertice> *conjuntoSolucao)
{
    list<Vertice> *candidatos = new list<Vertice>;
    list<Vertice>::iterator it1;
    list<Vertice>::iterator it2;
    Vertice *auxVertice = primeiro;
    while(auxVertice!=NULL){
        if(!verticesVizinhos(conjuntoSolucao, auxVertice))
            candidatos->push_back(*auxVertice);
        auxVertice = auxVertice->getProx();
    }
    return candidatos;

}

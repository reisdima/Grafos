#include "Grafo.h"
#include <stack>
#include <list>


Grafo::Grafo()
{
    primeiro = NULL;
    ordemGrafo = 0;

}

Grafo::~Grafo()
{
    //dtor
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
    }
    aumentaOrdem();
}

void Grafo::adicionaAresta(string nome1, string nome2)
{
    if(!existeVertice(nome1))
        adicionaVertice(nome1);
    if(!existeVertice(nome2))
        adicionaVertice(nome2);
    Vertice *no1 = getVertice(nome1);
    Vertice *no2 = getVertice(nome2);

    Aresta *nova1 = new Aresta();
    Aresta *nova2 = new Aresta();
    nova1->setVerticeAdj(nome2);
    nova2->setVerticeAdj(nome1);


    nova1->setEnderecoVerticeAdj(no2);
    nova2->setEnderecoVerticeAdj(no1);

    Aresta *aux = no1->getArestaAdj();
    if(aux == NULL){
        no1->setArestaAdj(nova1);
        nova1->setProx(NULL);
    }
    else{
        while(aux->getProx()!=NULL)
            aux = aux->getProx();
        aux->setProx(nova1);
        nova1->setProx(NULL);
    }
    aux = no2->getArestaAdj();
    if(aux == NULL){
        no2->setArestaAdj(nova2);
        nova2->setProx(NULL);
    }
    else{
        while(aux->getProx() != NULL)
            aux = aux->getProx();
        aux->setProx(nova2);
        nova2->setProx(NULL);
    }
    no1->aumentaGrau();
    no2->aumentaGrau();
}


void Grafo::removeAresta(string nome1, string nome2)
{
    if(existeVertice(nome1) && existeVertice(nome2)){
        Vertice *aux = getVertice(nome1);
        Aresta *atual;
        Aresta *anterior;
        atual = aux->getArestaAdj();
        if(atual!=NULL){
            anterior = NULL;
            while(atual->getVerticeAdj()!=nome2 && atual!=NULL){
                anterior = atual;
                atual = atual->getProx();
            }
            if(atual!=NULL){
                if(anterior!=NULL){
                    anterior->setProx(atual->getProx());
                }
                else{
                    aux->setArestaAdj(atual->getProx());
                }
                aux = atual->getEnderecoVerticeAdj();
                delete atual;
            }
            else{
                //erro nao existe essa aresta
            }
        }
        else{
            //erro vertice nao tem aresta
        }
        aux = getVertice(nome2);
        atual = aux->getArestaAdj();
        if(atual!=NULL){
            anterior = NULL;
            while(atual->getVerticeAdj()!=nome1 && atual!=NULL){
                anterior = atual;
                atual = atual->getProx();
            }
            if(atual!=NULL){
                if(anterior!=NULL){
                    anterior->setProx(atual->getProx());
                }
                else
                    aux->setArestaAdj(atual->getProx());
                delete atual;
            }
            else{
                //erro aresta nao existe
            }
        }
        else{
            //erro vertice nao tem aresta
        }
        aux = getVertice(nome1);
        aux->diminuiGrau();
        aux = getVertice(nome2);
        aux->diminuiGrau();
    }
    else{
        //pelo menos algum vertice não existe
    }
}

void Grafo::removeVertice(string nome)
{
    if(existeVertice(nome)){
        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                if(auxAresta->getVerticeAdj()==nome){
                    removeAresta(auxVertice->getNome(), nome);
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
    }
    else{
        //vertice não existe
    }
    diminuiOrdem();
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


int Grafo::grauVertice(string nome)
{
    if(existeVertice(nome)){
        Vertice *aux = getVertice(nome);
        return aux->getGrau();
    }
    else{
        //erro vertice nao existe
        return -1;
    }
}


bool Grafo::K_Regularidade(int k)
{
    Vertice *aux = primeiro;
    if(primeiro==NULL)
        return false;
    while(aux!=NULL){
        if(aux->getGrau()!=k)
            return false;
        aux = aux->getProx();
    }
    return true;

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
    Vertice *aux = primeiro;
    while(aux!=NULL){
        if(aux->getGrau() != ordemGrafo-1)
            return false;
        aux = aux->getProx();
    }
    return true;
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

bool Grafo::grafoVazio()
{
    return (primeiro==NULL);
}

void Grafo::sequenciaGraus()
{
    if(!grafoVazio()){
        Vertice *auxVertice = primeiro;
        int *vet = new int[ordemGrafo];
        int i=0;
        while(auxVertice!=NULL){
            vet[i] = auxVertice->getGrau();
            auxVertice = auxVertice->getProx();
            i++;
        }
        for(int i=0; i<ordemGrafo; i++){
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
    }
}

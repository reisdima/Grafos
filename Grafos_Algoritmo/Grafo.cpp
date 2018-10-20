#include "Grafo.h"



Grafo::Grafo()
{
    primeiro = NULL;

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
    nova1->setEnderecoVerticeAdj(no1);
    nova2->setEnderecoVerticeAdj(no2);
    Aresta *aux = no1->getArestaAdj();
    if(aux == NULL)
        no1->setArestaAdj(nova1);
    else{
        while(aux->getProx()!=NULL)
            aux = aux->getProx();
        aux->setProx(nova1);
    }
    aux = no2->getArestaAdj();
    if(aux == NULL)
        no2->setArestaAdj(nova2);
    else{
        while(aux->getProx() != NULL)
            aux = aux->getProx();
        aux->setProx(nova2);
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
    Vertice *aux = getVertice(nome);
    return aux->getGrau();
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

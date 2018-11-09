#include "Grafo.h"
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <queue>
#include <time.h>
#define INF 99999

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
    no1->aumentaGrau();

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
        no2->aumentaGrau();
    }

    no2->aumentaGrau();
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
    no1->aumentaGrau();

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
        no2->aumentaGrau();
    }

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



void Grafo::arvoreGeradoraMinimaKruskal()
{
    if(!grafoVazio()){
        list<Aresta> *arestas = new list<Aresta>;
        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            Aresta *auxAresta = auxVertice->getArestaAdj();
            while(auxAresta!=NULL){
                if(!contemAresta(auxAresta->getNomeOrigem(), auxAresta->getVerticeAdj(), arestas)){
                    arestas->push_back(*auxAresta);
                }
                auxAresta = auxAresta->getProx();
            }
            auxVertice = auxVertice->getProx();
        }
        arestas = ordernarArestasPorPeso(arestas);
        list<Aresta>::iterator it;
        for(it=arestas->begin(); it!=arestas->end(); it++){
            cout << it->getPeso() << " ";
        }
        cout << endl << endl;
        list<Aresta> *solucao = new list<Aresta>;
        it = arestas->begin();
        while(it!=arestas->end()){
            Aresta auxAresta = *it;
            cout << "Aresta sendo observada: " << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
            if(!formaCiclo(solucao, &auxAresta)){
                solucao->push_back(auxAresta);
            }
            it++;
        }
        for(it = solucao->begin(); it!=solucao->end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << "  (" << it->getPeso() << ")" << endl;
        }
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

list<Aresta> *Grafo::ordernarArestasPorPeso(list<Aresta> *arestas)
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
    return G1.existeCiclo();
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


void Grafo::arvoreGeradoraMinimaPrim()
{
    if(!grafoVazio()){
        int *inseridosNaArvore = new int[ordemGrafo];
        list<string> *verticesNaSolucao = new list<string>;
        list<string> *verticesForaDaSolucao= new list<string>;

        Vertice *auxVertice = primeiro;
        while(auxVertice!=NULL){
            verticesForaDaSolucao->push_back(auxVertice->getNome());
            auxVertice = auxVertice->getProx();
        }

        srand(time(NULL));
        int verticeAleatorio = rand()%ordemGrafo;
        auxVertice = primeiro;
        for(int i=0; i<verticeAleatorio; i++){
            auxVertice = auxVertice->getProx();
        }


        verticesNaSolucao->push_back(auxVertice->getNome());
        verticesForaDaSolucao->remove(auxVertice->getNome());

        list<Aresta> *solucao = new list<Aresta>;
        while(!verticesForaDaSolucao->empty()){
            list<Aresta> *arestasCandidatas = new list<Aresta>;
            list<string>::iterator it1;
            for(it1=verticesNaSolucao->begin(); it1!=verticesNaSolucao->end(); it1++){
                Aresta *auxAresta = getVertice(*it1)->getArestaAdj();
                while(auxAresta!=NULL){
                    if(!contemAresta(getVertice(*it1)->getNome(), auxAresta->getVerticeAdj(), arestasCandidatas) && !formaCiclo(solucao, auxAresta)){
                        arestasCandidatas->push_back(*auxAresta);
                    }
                    auxAresta = auxAresta->getProx();
                }
            }
            arestasCandidatas = ordernarArestasPorPeso(arestasCandidatas);
            list<Aresta>::iterator it2;
            it2 = arestasCandidatas->begin();
            solucao->push_back(*it2);
            verticesNaSolucao->push_back(it2->getVerticeAdj());
            verticesForaDaSolucao->remove(it2->getVerticeAdj());
        }
        list<Aresta>::iterator it;
        for(it=solucao->begin(); it!=solucao->end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << endl;
        }
        cout << "Teste";

    }
}

void Grafo::caminhoMinimoDijkstra(string vertice1, string vertice2)
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

void Grafo::caminhoMinimoFloyd()
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



        for(int i=0; i<ordemGrafo; i++){
            for(int j=0; j<ordemGrafo; j++){
                if(dist[i][j] == INF)
                    cout << "INF  ";
                else
                    cout << dist[i][j] << "    ";
            }
            cout << endl;
        }



    }
}





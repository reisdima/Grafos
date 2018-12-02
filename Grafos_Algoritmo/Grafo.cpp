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
//#include <chrono>
#define INF 99999

Grafo::Grafo()
{
    primeiro = NULL;
    ordemGrafo = 0;
    nomes = new list<string>;
    usaId = false;

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


/*************************************
*Verifica se um vertice com o nome   *
*passado como parametro existe no    *
*grafo                               *
**************************************/


bool Grafo::existeVertice(string nome)
{
    Vertice *aux = primeiro;
    while(aux!=NULL && aux->getNome()!=nome)
        aux = aux->getProx();
    if(aux==NULL)
        return false;
    return true;
}


/*************************************
*retorna o Vertice, se existir,      *
*passado como parametro uma string   *
*que representa o nome               *
**************************************/
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


/*************************************
*Adiciona um vertice ao grafo,       *
*passando como parametro uma string  *
*que representa seu nome             *
**************************************/
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


/*************************************
*A função adicionaAresta recebe como *
*parâmetro os nomes dos vertices da  *
* aresta desejada                    *
*Se esta aresta não existir ela é    *
*adicionada.                         *
**************************************/
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

/*************************************
*A função adicionaAresta recebe como *
*parâmetro os nomes dos vertices da  *
* aresta desejada e um float peso    *
*Se esta aresta não existir ela é    *
*adicionada.                         *
**************************************/
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

/*************************************
*A função removeAresta recebe como   *
*parâmetro o nome dos vértices que   *
*formam a aresta a ser removida.     *
*Se estes vértices existirem, é 	 *
*então verificado se existe aresta 	 *
*entre esses vértices. Então a aresta*
*é removida.                         *
**************************************/
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


/*************************************
*A função removeVertice recebe como  *
*parâmetro o nome do vértice que     *
*quer ser removido ser removida.     *
*Se este vértice existire, o mesmo é *
*removido.                  		 *
**************************************/
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

/*************************************
*imprime o grafo no formato de lista *
*de adjascencia                		 *
**************************************/
void Grafo::listaAdjacencia()
{
    Vertice *auxVertice = primeiro;
    if(!usaId){
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
    else{
        while(auxVertice!=NULL){
            Aresta *auxAresta = auxVertice->getArestaAdj();
            cout << auxVertice->getId() << " -> ";
            while(auxAresta!=NULL){
                cout << auxAresta->getIdVerticeAdj() << " -> ";
                auxAresta = auxAresta->getProx();
            }
            cout << "||" << endl;
            auxVertice = auxVertice->getProx();
        }
    }
}

/*************************************
*imprime o grau do vertice passado	 *
*por referência						 *
**************************************/
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

/*************************************
*Verifica a K regularidade do grafo  *
*Recebe como parametro um inteiro k  *
*retorna TRUE caso o grafo seja      *
*K-regular e FALSE caso contrario    *
**************************************/
bool Grafo::K_Regularidade(int k)
{
    if(!grafoVazio()){
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

/***************************************
*Utilizada por outras funções a 	   *
*função aumentaOrdem aumenta a ordem do*
*grafo.								   *
****************************************/
void Grafo::aumentaOrdem(){
    ordemGrafo++;
}

/***************************************
*Utilizada por outras funções a 	   *
*função diminuiOrdem diminui a ordem do*
*grafo.								   *
****************************************/
void Grafo::diminuiOrdem(){
    ordemGrafo--;
}

/*************************************
*Utilizada por outras funções a 	 *
*função getOrdemGrafo retorna a ordem*
do grafo.							 *
**************************************/
int Grafo::getOrdemDoGrafo(){
    return ordemGrafo;
}


/*************************************
*A função vizinhancaAberta recebe o  *
*nome do vértice como parâmetro e 	 *
*imprime a sua vizinhança aberta	 *
**************************************/
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

/*************************************
*A função vizinhancaFechada recebe o *
*nome do vértice como parâmetro e 	 *
*imprime a sua vizinhança fechada	 *
**************************************/
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


/******************************************
*A função grafoCompleto verifica se o     *
*grafo desejado é completo. Retorna TRUE  *
*caso seja completoe  FALSE caso não seja *
*completo. 		                          *
*******************************************/
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
}


/*********************************************
*A função grafoBipartido verifica se o grafo  *
*desejado é bipartido e utiliza uma função    *
*auxiliar (auxGrafoBipartido) para verificar a*
*bipartição.								  *
**********************************************/
bool Grafo::grafoBipartido()
{
    if(!grafoVazio()){
        stack<string> pilha;
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
    }
    return false;
}

/*********************************************
*auxGrafoBipartido recebe como parametro uma *
*pilha de vertices visitados, um inteiro que *
*representa o vertice que esta visitando, e  *
*um inteiro cor                              *
**********************************************/
bool Grafo::auxGrafoBipartido(Vertice *auxVertice, stack<string>pilha, int *vizitado, int *coloracao, string *nomes, int cor)
{
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
        if(coloracao[index]!=cor)
            return false;
        else
            return true;
    }
}


/*********************************************
*recebe um vetor de string com os nomes dos  *
*vertices, e uma string do nome do vertice   *
*desejado e retorna o valor da posicao dele  *
**********************************************/
int Grafo::getIndex(string *nomes, string nome)
{
    for(int i=0; i<ordemGrafo; i++){
        if(nomes[i] == nome)
            return i;
    }
    return 0;
}

/*********************************************
*recebe uma lista de string com os nomes dos *
*vertices, e uma string do nome do vertice   *
*desejado e retorna o valor da posicao dele  *
**********************************************/
int Grafo::getIndex(list<string> *nomes, string nome)
{
    list<string>::iterator it;
    int i=0;
    for(it=nomes->begin(); it!=nomes->end(); it++){
        if(*it==nome)
            return i;
        i++;
    }
    return 0;
}

/*********************************************
*retorna um boolean se o grafo esta ou nao   *
*vazio                                       *
**********************************************/
bool Grafo::grafoVazio()
{
    return (primeiro==NULL);
}


/*********************************************
*imprime a sequancia de graus do grafo       *
**********************************************/
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
}


/*********************************************
*Algoritmo da Arvore Geradora Minima de      *
*Kruskal                                     *
**********************************************/
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
        arestas = ordernarArestasPorPesoCrescente(arestas);
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
            int index1 = getIndex(nomes, it->getNomeOrigem());
            int index2 = getIndex(nomes, it->getVerticeAdj());
            int x = Find(parent, index1, 0);
            int y = Find(parent, index2, 0);
            if(x!=y){
                solucao.push_back(*it);
                Union(parent, x, y);
                e++;
            }
            arestas->pop_front();
        }
        float peso = 0;
        for(it=solucao.begin(); it!=solucao.end(); it++){
            cout << it->getNomeOrigem() << " -> " << it->getVerticeAdj() << "  (" << it->getPeso() << ")"  << endl;
            peso += it->getPeso();
        }
        cout << endl << "Soma dos pesos: " << peso << "  numero de vertices na solucao: " << solucao.size() << endl;

    }
}

/*********************************************
*retorna se existe uma aresta. É passado como*
*parametro os nomes dos vertices da aresta, e*
*uma lista de arestas, que deseja-se saber se*
*ela esta inserida                           *
**********************************************/
bool Grafo::contemAresta(string origem, string destino, list<Aresta> *arestas)
{
    list<Aresta>::iterator it;

    for(it = arestas->begin(); it!=arestas->end(); it++){
        if((it->getNomeOrigem()==origem && it->getVerticeAdj()==destino) || (it->getNomeOrigem()==destino && it->getVerticeAdj()==origem))
            return true;

    }
    return false;
}

/*********************************************
*retorna uma lista de arestas ordenadas      *
*crescentemente por peso e recebe como       *
*parametro uma lista de arestas              *
**********************************************/
list<Aresta> *Grafo::ordernarArestasPorPesoCrescente(list<Aresta> *arestas)
{

    list<Aresta>::iterator it1;
    list<Aresta>::iterator it2;

    for(it1 = arestas->begin(); it1!=arestas->end(); it1++){
        for(it2 = arestas->begin(); it2!=arestas->end(); it2++){
            if(it2->getPeso()>it1->getPeso()){
                Aresta auxAresta = *it2;
                //cout << it2->getPeso() << " ";
                *it2 = *it1;
                *it1 = auxAresta;
            }
        }
    }

    return arestas;
}


/*************************************
*Recebe como parametro uma lista     *
*de arestas e uma arestas.Retorna    *
*um boolean indicando se a aresta    *
*forma ciclo com as arestas da lista.*
*************************************/
bool Grafo::formaCiclo(list<Aresta> *solucao, Aresta *aresta)
{
    if(solucao->empty())
        return false;
    Grafo *G1 = new Grafo();
    list<Aresta>::iterator it1;
    for(it1 = solucao->begin(); it1!=solucao->end(); it1++){
        G1->adicionaAresta(it1->getNomeOrigem(), it1->getVerticeAdj(), 0);
    }
    G1->adicionaAresta(aresta->getNomeOrigem(), aresta->getVerticeAdj(), 0);
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
    return false;
}

/*********************************************
*Função auxiliar para Kruskal                *
**********************************************/
void Grafo::Union(int *parent, int x, int y)
{
    int xset = Find(parent, x, 0);
    int yset = Find(parent, y, 0);
    if(xset!=yset){
       parent[xset] = (yset);
    }

}

/*********************************************
*Função auxiliar para Kruskal                *
**********************************************/
int Grafo::Find(int *parent, int i, int tamanho)
{
    if(parent[i]==-1)
        return i;
    return Find(parent, parent[i], tamanho);
}



/*******************************
*Retorna um boolean, indicando *
*se existe ciclo no grafo      *
*******************************/
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
    return false;
}


/*******************************
*Função auxiliar de Prim       *
*******************************/
int Grafo::minKey(float *key, bool *verticesNaArvore)
{
    float menor = INT_MAX;
    int menorIndex = 0;
    for(int i=0; i<ordemGrafo; i++){
        if(!verticesNaArvore[i] && key[i]<menor){
            menor = key[i];
            menorIndex = i;
        }
    }
    return menorIndex;
}

/*******************************
*Algoritmo da arvore geradora  *
*minima de Prim                *
*******************************/
void Grafo::arvoreGeradoraMinimaPrim()
{
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

/*********************************
*Algoritmo do caminho minimo de  *
*Dijkstra. Exibe na tela o       *
*caminho minimo de um vertice    *
*passado como parametro ate todos*
*os outros vertice               *
*********************************/
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

/*******************************
*Função auxiliar de Dijkstra   *
*******************************/
int Grafo::distanciaMinima(int dist[], bool sptSet[])
{
    int menor = INF;
    int indexMenor = 0;
    for(int i=0; i<ordemGrafo; i++){
        if(sptSet[i]==false && dist[i]<menor){
            indexMenor = i;
            menor = dist[i];
        }
    }

    return indexMenor;
}

/*********************************
*Algoritmo do caminho minimo de  *
*Floyd. Exibe na tela o          *
*caminho minimo de um vertice    *
*passado como parametro ate todos*
*os outros vertice               *
*********************************/
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
        }
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

/*********************************
*Exibe na tela o fecho transitivo*
*direto de um vertice passado    *
*como parametro, e um boolean    *
*dizendo se é ou nao direcionado *
*********************************/
void Grafo::fechoTransitivoDireto(string nome, bool direcionado)
{
    if(direcionado && !grafoVazio()){
        Vertice *origem = getVertice(nome);
        list<string> alcancaveis;
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

/*********************************
*Exibe na tela o fecho transitivo*
*indireto de um vertice passado  *
*como parametro, e um boolean    *
*dizendo se é ou nao direcionado *
*********************************/
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
                    alcansaveis[i][j] = alcansaveis[i][j] || (alcansaveis[i][k] && alcansaveis[k][j]);
                    if(destino->getNome()==nome && alcansaveis[i][j] && !verticeNaSolucao[index2]){
                        verticeNaSolucao[index2] = true;
                        solucao.push_back(atual->getNome());
                    }
                    destino = destino->getProx();

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

/*********************************
*Algoritmo guloso para achar     *
*conjunto maximo independente    *
*********************************/
void Grafo::conjuntoMaximoIndependenteGuloso()
{
    if(!grafoVazio()){
        double tInicio = clock();
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
        double tFinal = clock();
        double tDecorrido = ((double)(tFinal - tInicio))/CLOCKS_PER_SEC;
        cout << "Tempo decorrido: " << tDecorrido << endl;
        for(it=solucao->begin(); it!=solucao->end(); it++)
            cout << it->getNome() << "  ";
        cout << endl << "Tamanho da solucao: " << solucao->size() << endl;
        delete solucao;
        delete vertices;
        auxVertice = NULL;
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


/*****************************************
*Algoritmo guloso randomizado            *
*para achar conjunto maximo independente *
*Recebe como parametro o numero maximo de*
*iterações                               *
*****************************************/
void Grafo::conjuntoMaximoIndependenteGulosoRandomizado(int intMax)
{
    if(!grafoVazio()){
        clock_t tempoInicialSolucao;
        clock_t tempoFinalSolucao;
        clock_t tempoInicialAlgoritmo;
        clock_t tempoFinalAlgoritmo;
        tempoInicialAlgoritmo = clock();


        ofstream file;
        file.open("gulosoRandomizado.txt");
        srand (time(NULL));

        bool *verticesNaSolucao = new bool[ordemGrafo];
        for(int i=0; i<ordemGrafo; i++){
            verticesNaSolucao[i] = false;
        }

        list<Vertice> *solucao = new list<Vertice>;
        list<Vertice> *candidatos = new list<Vertice>;

        list<Vertice> *verticesOrdenados = new list<Vertice>;
        verticesOrdenados = possiveisAdicionarIndependente(solucao, verticesNaSolucao);
        verticesOrdenados = ordenaGrauDecrescente(verticesOrdenados);

        Vertice *auxVertice;
        float alfa[3] = {0.1, 0.2, 0.3};
        list<Vertice>::iterator it;
        int melhor = 0;
        for(int p=0;p<3; p++){
            file << "ALFA " << alfa[p] << "\n\n";
            int contador = 0;
            while(contador<intMax){
                tempoInicialSolucao = clock();
                *candidatos = *verticesOrdenados;
                while(candidatos->size() != 0){
                    int n = ceil(candidatos->size()*alfa[p]);
                    int random = rand()%n;
                    it = candidatos->begin();
                    for(int i=0; i<random; i++)
                        it++;
                    auxVertice = &(*it);


                    solucao->push_back(*auxVertice);




                    removeVerticesAdjacentes(candidatos, auxVertice->getNome(), auxVertice->getGrauEntrada());


                }
                contador++;
                cout << endl << "Tamanho da solucao encontrada: " << solucao->size() << endl;
                if(solucao->size() > melhor){
                    melhor = solucao->size();
                }
                tempoFinalSolucao = clock();
                cout << "contador: " << contador << endl;
                this->imprimirSolucao(solucao, &file);
                file << "\tTamanho da solucao encontrada; " << solucao->size() << endl;
                file << "\tTempo decorrido: " << (double)(tempoFinalSolucao-tempoInicialSolucao)/CLOCKS_PER_SEC<< "\n\n";
                cout << "Tempo decorrido para achar solucao: " << (double)(tempoFinalSolucao-tempoInicialSolucao)/CLOCKS_PER_SEC << endl;
                solucao->clear();
                candidatos->clear();
            }



        }
        tempoFinalAlgoritmo = clock();
        cout << "Melhor:  " << melhor << endl;
        cout << "Tempo decorrido para algoritmo: " << (double)(tempoFinalAlgoritmo - tempoInicialAlgoritmo)/CLOCKS_PER_SEC << endl;
        file << "Tamanho do melhor conjunto independente achado: " << melhor;
        file << "\nTempo para execucao do algoritmo: " << (double)(tempoFinalAlgoritmo - tempoInicialAlgoritmo)/CLOCKS_PER_SEC;
        delete solucao;
    }
}


/*********************************************
*Escreve no arquivo recebido como parametro  *
*os vertices da lista recebida como parametro*
*********************************************/
void Grafo::imprimirSolucao(list<Vertice> *solucao, ofstream *file)
{
    if(!solucao->empty()){
        list<Vertice>::iterator it;
        *file << "\t";

        for(it=solucao->begin(); it!=solucao->end(); it++){
            *file << it->getNome() << "  ";
        }
        *file << "\n";
    }
}


/*****************************************
*Função que remove todos os vertices da  *
*lista de vertices recebida como         *
*parametros que sao adjacente ao vertice *
*adicionado                              *
*****************************************/
void Grafo::removeVerticesAdjacentes(list<Vertice> *candidatos, string verticeAdicionado, int vizinhos)
{

    string *verticesParaExcluir = new string[vizinhos+1];


    Aresta *auxAresta = getVertice(verticeAdicionado)->getArestaAdj();
    int n=0;
    while(auxAresta!=NULL){
        verticesParaExcluir[n] = auxAresta->getVerticeAdj();
        auxAresta = auxAresta->getProx();
        n++;
    }
    verticesParaExcluir[n] = verticeAdicionado;
    n++;
    int a = 0;
    list<Vertice>::iterator it = candidatos->begin();
    while(it!=candidatos->end()){
        for(int i=0; i<n; i++){
            if(it->getNome()==verticesParaExcluir[i]){
                it = candidatos->erase(it);
                it--;
                a++;
                break;
            }
        }
        it++;
    }
    delete []verticesParaExcluir;

}

/*****************************************
*Algoritmo retorna uma lista de vertices *
*possiveis de se adicionar em um conjunto*
*independente. Recebe uma lista de       *
*vertices e um array de boolean          *
*****************************************/
list<Vertice> *Grafo::possiveisAdicionarIndependente(list<Vertice> *conjuntoSolucao, bool *verticesNaSolucao)
{
    list<Vertice> *candidatos = new list<Vertice>;
    list<Vertice>::iterator it1;
    list<Vertice>::iterator it2;
    int index;
    Vertice *auxVertice = primeiro;
    while(auxVertice!=NULL){
        index = getIndex(nomes, auxVertice->getNome());
        if(!verticesNaSolucao[index]){
            if(!verticesVizinhos(conjuntoSolucao, auxVertice))
                candidatos->push_back(*auxVertice);
        }
        auxVertice = auxVertice->getProx();
    }
    return candidatos;

}


/*****************************************
*Algoritmo guloso randomizado reativo    *
*para achar conjunto maximo independente *
*Recebe como parametro o numero maximo de*
*iterações                               *
*****************************************/
void Grafo::conjuntoMaximoIndependenteGulosoRandomizadoReativo(int intMax)
{
    clock_t tempoInicialSolucao;
    clock_t tempoInicialAlgoritmo;
    clock_t tempoFinalSolucao;
    clock_t tempoFinalAlgoritmo;
    tempoInicialAlgoritmo = clock();

    clock_t tInicial;
    clock_t tFinal;

    ofstream file;
    file.open("gulosoRandomizadoReativo.txt");


    srand(time(NULL));
    float *alfa = new float[10];
    float *probabilidades = new float[10];
    bool *verticesNaSolucao = new bool[ordemGrafo];
    for(int i=0; i<10; i++){
        probabilidades[i] = 1/10.0;
        alfa[i] = i*0.05 +0.05;
        cout << alfa[i] << "  ";
    }
    cout << endl;
    for(int i=0; i<10; i++){
        cout << probabilidades[i] << "  ";
    }
    for(int i=0; i<ordemGrafo; i++){
        verticesNaSolucao[i] = false;
    }
    cout << endl;
    list<Vertice> *solucao = new list<Vertice>;
    list<Vertice> *candidatos = new list<Vertice>;
    list<Vertice>::iterator it;
    int contador = 0;

    list<Vertice> *verticesOrdenados = new list<Vertice>;
    verticesOrdenados = possiveisAdicionarIndependente(solucao, verticesNaSolucao);
    verticesOrdenados = ordenaGrauDecrescente(verticesOrdenados);



    int contadorAlfa[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float mediaAlfa[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int melhor = 0;
    while(contador<intMax){
        tempoInicialSolucao = clock();
        int x = rand()%1000;
        float c = probabilidades[0]*1000.0;
        int i = 0;
        while(c<=x){
            i++;
            c += probabilidades[i]*1000;
        }

        contadorAlfa[i] = contadorAlfa[i] +1;
        int y = 0;
        while(candidatos->size()!=0){
            int n = ceil(candidatos->size()*alfa[i]);
            x = rand()%n;
            it = candidatos->begin();
            for(int j=0; j<x; j++)
                it++;
            Vertice *auxVertice = &(*it);
            solucao->push_back(*auxVertice);
            tInicial = clock();
            removeVerticesAdjacentes(candidatos, auxVertice->getNome(), auxVertice->getGrauEntrada());
            tFinal = clock();
            cout << "remove adjacentes tempo: " << (double)(tFinal-tInicial)/CLOCKS_PER_SEC << endl;
            y++;
        }
        cout << "Y: " << y << endl;
        for(it=solucao->begin(); it!=solucao->end(); it++){
        }
        contador++;
        cout << "Contador: " << contador << endl;
        mediaAlfa[i] = mediaAlfa[i]+solucao->size();

        if(contador%50==0){
            float q[10];
            float somatorioQ = 0.0;
            for(int i=0; i<10; i++){
                if(contadorAlfa[i]==0){
                    mediaAlfa[i] = 0;
                    q[i] = 0;
                }
                else{
                    mediaAlfa[i] = mediaAlfa[i]/contadorAlfa[i];
                    q[i] = pow((melhor/mediaAlfa[i]), 10);
                }
                somatorioQ += q[i];
            }
            for(int i=0; i<10; i++){
                probabilidades[i] = q[i]/somatorioQ;
                mediaAlfa[i] = 0;
                contadorAlfa[i] = 0;
            }



        }
        //Fim contador
        if(solucao->size()>melhor){
            melhor = solucao->size();
        }
        tempoFinalSolucao = clock();
        cout << "Tamanho da solucao encontrada: " << solucao->size() << endl;
        cout << "Tempo de execucao da solucao: " << (double)(tempoFinalSolucao- tempoInicialSolucao)/CLOCKS_PER_SEC << endl << endl;
        imprimirSolucao(solucao, &file);
        file << "\tTamanho da solucao encontrada: " << solucao->size() << endl;
        file << "\tTempo decorrido: " << (double)(tempoFinalSolucao-tempoInicialSolucao)/CLOCKS_PER_SEC<< "\n\n";
        solucao->clear();
        candidatos->clear();
    }
    tempoFinalAlgoritmo = clock();
    cout << "Melhor: " << melhor << endl ;
    cout << "Tempo de execucao do algoritmo: " << (double)(tempoFinalAlgoritmo - tempoInicialAlgoritmo)/CLOCKS_PER_SEC << endl << endl;
    file << "Tamanho do melhor conjunto independente achado: " << melhor;
    file << "\nTempo para execucao do algoritmo: " << (double)(tempoFinalAlgoritmo - tempoInicialAlgoritmo)/CLOCKS_PER_SEC;
}

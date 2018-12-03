#include <iostream>
#include <string>
#include "Grafo.h"
#include <fstream>
#include <sstream>
#include <time.h>




using namespace std;

void leituraDeArquivoSemPeso(string arquivoEntrada, Grafo *G, bool direcionado)
{
    string filename = "Instancias\\"+arquivoEntrada;
    ifstream file(filename.c_str());
    int n;
    string nome1, nome2;
    double tempoInicio = clock();
    double tempoFinal;
    if(file.is_open()){
        file >> n;
        while(file >> nome1 >> nome2){
            G->adicionaAresta(nome1, nome2, direcionado);
        }
        tempoFinal = clock();
    }
    cout << "Tempo decorrido na leitura de arquivo: " << (double)(tempoFinal - tempoInicio)/CLOCKS_PER_SEC << endl << endl;
}

void leituraDeArquivoComPeso(string arquivoEntrada, Grafo *G, bool direcionado)
{
    string filename = "Instancias\\"+arquivoEntrada;
    ifstream file(filename.c_str());
    int n;
    string nome1, nome2;
    float peso;
    double tempoInicio = clock();
    double tempoFinal;
    if(file.is_open()){
        file >> n;
        while(file >> nome1 >> nome2 >> peso){
            G->adicionaAresta(nome1, nome2, peso, direcionado);
        }
        tempoFinal = clock();
    }
    cout << "Tempo decorrido na leitura de arquivo: " << (double)(tempoFinal - tempoInicio)/CLOCKS_PER_SEC << endl << endl;
}

void Menu()
{
    cout << "[1]  Adicionar Vertice" << endl;
    cout << "[2]  Adicionar Aresta" << endl;
    cout << "[3]  Exibir Grafo por Lista de Adjacencia" << endl;
    cout << "[4]  Remover Vertice" << endl;
    cout << "[5]  Remover Aresta" << endl;
    cout << "[6]  Grau de um Vertice" << endl;
    cout << "[7]  Verifiar a K regularidade do grafo" << endl;
    cout << "[8]  Ordem do Grafo" << endl;
    cout << "[9]  Vizinhanca aberta de um vertice" << endl;
    cout << "[10] Vizinhanca fechada de um vertice" << endl;
    cout << "[11] Verificar se o grafo e completo" << endl;
    cout << "[12] Verificar se o grafo e bipartido" << endl;
    cout << "[13] Imprimir sequencia de graus" << endl;
    cout << "[14] Arvore geradora minima por Kruskal" << endl;
    cout << "[15] Arvore geradora minima por Prim" << endl;
    cout << "[16] Caminho minimo por Dijkstra" << endl;
    cout << "[17] Caminho minimo por Floyd" << endl;
    cout << "[18] Fecho transitivo direto" << endl;
    cout << "[19] Fecho transitivo indireto" << endl;
    cout << "[20] Verifica se o grafo forma ciclo" << endl << endl;
    cout << "[21] Conjunto maximo independente guloso" << endl;
    cout << "[22] Conjunto maximo independente guloso randomizado" << endl;
    cout << "[23] Conjunto maximo independente guloso randomizado reativo" << endl;
    cout << "[0]  Sair" << endl;
}


int main(int args, char *arqv[])
{

    Grafo G;
    string arquivoEntrada;
    string arquivoSaida;
    bool direcionado = false;
    bool ponderadoAresta = false;
    //arquivoEntrada = arqv[1];
    //arquivoSaida = arqv[2];
    //ponderadoAresta = argv[3];
    arquivoEntrada = "grafo_125.txt";
    leituraDeArquivoSemPeso(arquivoEntrada, &G, direcionado);
    G.setArquivoSaida(arquivoSaida);




    int escolha;
        while(true){
            Menu();
            cin >> escolha;
            if(escolha==1){
                string nome;
                cout << "Digite o nome do vertice: ";
                cin >> nome;
                G.adicionaVertice(nome);
            }
            else if(escolha==2){
                string nome1, nome2;
                float peso;
                cout << "Digite os nomes dos vertices da aresta:" << endl;
                cin >> nome1;
                cin >> nome2;
                if(ponderadoAresta){
                    cin >> peso;
                    G.adicionaAresta(nome1, nome2, peso, direcionado);
                }
                else
                    G.adicionaAresta(nome1, nome2, direcionado);
            }
            else if(escolha==3){
                G.listaAdjacencia();
            }
            else if(escolha==4){
                string nome;
                cout << "Digite o nome do verice que deseja remover: ";
                cin >> nome;
                G.removeVertice(nome, direcionado);
            }
            else if(escolha==5){
                string nome1, nome2;
                cout << "Digite o nome dos verices da aresta: ";
                cin >> nome1;
                cin >> nome2;
                G.removeAresta(nome1, nome2, direcionado);
            }
            else if(escolha==6){
                string nome;
                cout << "Digite o nome do vertice que deseja saber o grau: ";
                cin >> nome;
                G.grauVertice(nome, direcionado);
            }
            else if(escolha==7){
                int k;
                cout << "Digite o valor de k para verificar sua regularidade: ";
                cin >> k;
                if(G.K_Regularidade(k))
                    cout << "O grafo e " << k << "-regular"<< endl;
                else
                    cout << "O grafo nao e " << k << "-regular"<< endl;
            }
            else if(escolha==8){
                cout<<endl<<"O grafo tem ordem: "<<G.getOrdemDoGrafo()<<endl;
            }
            else if(escolha == 9){
                string nome;
                cout << "Digite o nome do vertice que voce deseja ver a vizinhanca aberta: ";
                cin >> nome;
                G.vizinhancaAberta(nome);
            }
            else if(escolha == 10){
                string nome;
                cout << "Digite o nome do vertice que voce deseja ver a vizinhanca fechada: ";
                cin >> nome;
                G.vizinhancaFechada(nome);
            }
            else if(escolha==11){
                if(G.grafoCompleto())
                    cout << "O grafo e completo" << endl;
                else
                    cout << "O grafo nao e completo" << endl;
            }
            else if(escolha==12){
                if(G.grafoBipartido())
                    cout << "O grafo e bipartido" << endl;
                else
                    cout << "O grafo nao e bipartido" << endl;
            }
            else if(escolha == 13){
                G.sequenciaGraus(direcionado);
            }
            else if(escolha==14){
                G.arvoreGeradoraMinimaKruskal();
            }
            else if(escolha==15){
                G.arvoreGeradoraMinimaPrim();
            }
            else if(escolha==16){
                cout << "Digite o vertice que deseja saber o caminho minimo: ";
                string nome;
                cin >> nome;
                G.caminhoMinimoDijkstra(nome);
            }
            else if(escolha==17){
                cout << "Digite o vertice que deseja saber o caminho minimo: ";
                string nome;
                cin >> nome;
                G.caminhoMinimoFloyd(nome);
            }
            else if(escolha==18){
                cout << "Digite o vertice que deseja saber o fecho transitivo: ";
                string nome;
                cin >> nome;
                G.fechoTransitivoDireto(nome, direcionado);
            }
            else if(escolha==19){
                cout << "Digite o vertice que deseja saber o fecho transitivo: ";
                string nome;
                cin >> nome;
                G.fechoTransitivoIndireto(nome, direcionado);
            }
            else if(escolha==20){
                if(G.existeCiclo())
                    cout << "O grafo tem ciclo" << endl;
                else
                    cout << "O grafo nao tem ciclo" << endl;
            }
            else if(escolha==21){
                G.conjuntoMaximoIndependenteGuloso();
            }
            else if(escolha==22){
                G.conjuntoMaximoIndependenteGulosoRandomizado(500);
            }
            else if(escolha==23){
                G.conjuntoMaximoIndependenteGulosoRandomizadoReativo(500);
            }
            else if(escolha==0)
                break;
        }
        return 0;
}

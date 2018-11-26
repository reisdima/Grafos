#include <iostream>
#include <string>
#include "Grafo.h"
#include <fstream>




using namespace std;

void leituraDeArquivo(string nomeArquivo, Grafo *G, bool direcionado)
{
    //ifstream file("grafo_1000_1.txt");
    ifstream file("grafo_125.txt");
    int n;
    string nome1, nome2;
    float peso;
    if(file.is_open()){
        file >> n;
        while(file >> nome1 >> nome2 >> peso){
            G->adicionaAresta(nome1, nome2, peso, direcionado);
            //cout << "a";
        }
    }
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
    cout << "[14] Arvore geradore minima por Kruskal" << endl;
    cout << "[15] Arvore geradore minima por Prim" << endl;
    cout << "[16] Caminho minimo por Dijkstra" << endl;
    cout << "[17] Caminho minimo por Floyd" << endl;
    cout << "[18] Fecho transitivo direto" << endl;
    cout << "[19] Fecho transitivo indireto" << endl;
    cout << "[20] Conjunto maximo independente guloso" << endl;
    cout << "[21] Conjunto maximo independente guloso randomizado" << endl;
    cout << "[22] Verifica se o grafo forma ciclo" << endl;
    cout << "[0]  Sair" << endl;
}


int main()
{
    Grafo G;
    bool direcionado = false;
    //string nomeArquivo = "grafo_1000_1.txt";
    string nomeArquivo = "grafo_125.txt";
    leituraDeArquivo(nomeArquivo, &G, direcionado);
    ofstream fileWrite;
    fileWrite.open("test.txt");
    fileWrite << "Teste";
    fileWrite.close();

/*
    cout << "O grafo sera direcionado?" << endl << endl;
    cout << "[0] Nao" << endl << "[1] Sim" << endl;
    cin >> direcionado;
*/


    int escolha;/*
    cout << endl << "Como voce ira montar o grafo?" << endl;
    cout << endl << "[1] Manualmente" << endl << "[2] Leitura de arquivo" << endl;
    cin >> escolha;*/
    escolha=1;
    if(escolha==1){
        bool ponderadoAresta;
       /* cout << "O grafo sera ponderado nas arestas?" << endl;
        cout << "[0] Nao" << endl << "[1] Sim" << endl;
        cin >> ponderadoAresta;*/
        ponderadoAresta=true;
/*
        G.adicionaAresta("A", "B", 7, direcionado);
        G.adicionaAresta("A", "D", 5, direcionado);
        G.adicionaAresta("D", "B", 9, direcionado);
        G.adicionaAresta("D", "E", 15, direcionado);
        G.adicionaAresta("D", "F", 6, direcionado);
        G.adicionaAresta("F", "G", 11, direcionado);
        G.adicionaAresta("F", "E", 8, direcionado);
        G.adicionaAresta("B", "C", 8, direcionado);
        G.adicionaAresta("C", "E", 5, direcionado);
        G.adicionaAresta("E", "G", 9, direcionado);
        G.adicionaAresta("B", "E", 7, direcionado);*/
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
                G.conjuntoMaximoIndependenteGuloso();
            }
            else if(escolha==21){
                G.conjuntoMaximoIndependenteGulosoRandomizado(500, 0.5);
            }
            else if(escolha==22){
                if(G.existeCiclo())
                    cout << "O grafo tem ciclo" << endl;
                else
                    cout << "O grafo nao tem ciclo" << endl;
            }
            else if(escolha==0)
                break;
        }
    }
    else{

    }

    G.adicionaAresta("A", "B", 7, true);
    G.adicionaAresta("A", "D", 5, true);
    G.adicionaAresta("D", "B", 97, true);
    G.adicionaAresta("D", "E", 15, true);
    G.adicionaAresta("D", "F", 6, true);
    G.adicionaAresta("F", "G", 11, true);
    G.adicionaAresta("F", "E", 8, true);
    G.adicionaAresta("B", "C", 8, true);
    G.adicionaAresta("C", "E", 5, true);
    G.adicionaAresta("E", "G", 9, true);


    //G.grauVertice("A", direcionado);
    //cout << G.K_Regularidade(2) << endl;



    return 0;
}

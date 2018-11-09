#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

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
    cout << "[0]  Sair" << endl;
}


int main()
{
    Grafo G;
    bool direcionado;

    /*
    cout << "O grafo sera direcionado?" << endl;
    cout << "[0] Nao" << endl << "[1] Sim" << endl;
    cin >> direcionado;
    */

    direcionado = true;

    /*
    int escolha;
    cout << "Como voce ira montar o grafo?" << endl;
    cout << endl << "[1] Manualmente" << endl << "[2] Leitura de arquivo" << endl;
    cin >> escolha;
    if(escolha==1){
        int ponderadoAresta;
        cout << "O grafo sera ponderado nas arestas?" << endl;
        cout << "[1] Sim" << endl << "[2] Nao" << endl;
        cin >> ponderadoAresta;
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
                cout << "Digite os nomes dos vertices da aresta:" << endl;
                cin >> nome1;
                cin >> nome2;
                G.adicionaAresta(nome1, nome2, ponderadoAresta);
            }
            else if(escolha==3){
                G.listaAdjacencia();
            }
            else if(escolha==4){
                string nome;
                cout << "Digite o nome do verice que deseja remover: ";
                cin >> nome;
                G.removeVertice(nome);
            }
            else if(escolha==5){
                string nome1, nome2;
                cout << "Digite o nome dos verices da aresta: ";
                cin >> nome1;
                cin >> nome2;
                G.removeAresta(nome1, nome2);
            }
            else if(escolha==6){
                string nome;
                cout << "Digite o nome do vertice que deseja saber o grau: ";
                cin >> nome;
                int grau = G.grauVertice(nome);
                cout << "Grau do vertice " << nome << ": " <<grau << endl;
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
                G.sequenciaGraus();
            }
            else if(escolha==14){
                G.arvoreGeradoraMinimaKruskal();
            }
            else if(escolha==0)
                break;
        }
    }
    else{

    }
*/

/*
    G.adicionaVertice("A");
    G.adicionaVertice("B");
    G.adicionaVertice("C");
    G.adicionaVertice("D");
    G.adicionaVertice("E");
    G.adicionaVertice("F");
    G.adicionaVertice("G");
    G.adicionaVertice("H");
    G.adicionaVertice("I");
*/
    G.adicionaVertice("A");
    G.adicionaVertice("B");
    G.adicionaVertice("C");
    G.adicionaVertice("D");
    G.adicionaVertice("E");
    G.adicionaVertice("F");
    G.adicionaVertice("G");

/*
    G.adicionaAresta("A", "B");
    G.adicionaAresta("A", "C");
    G.adicionaAresta("B", "D");
    G.adicionaAresta("B", "E");
    G.adicionaAresta("C", "F");
  */
    G.adicionaAresta("A", "B", 1, direcionado);
    G.adicionaAresta("B", "E", 1, direcionado);
    G.adicionaAresta("E", "D", 1, direcionado);
    G.adicionaAresta("G", "D", 1, direcionado);
    G.adicionaAresta("G", "E", 1, direcionado);
    G.adicionaAresta("G", "F", 1, direcionado);
    G.adicionaAresta("C", "F", 1, direcionado);
    G.adicionaAresta("F", "C", 1, direcionado);
    G.adicionaAresta("B", "C", 1, direcionado);
    G.adicionaAresta("D", "A", 1, direcionado);
  /*
    G.adicionaAresta("A", "B", 0);
    G.adicionaAresta("A", "H", 0);
    G.adicionaAresta("B", "H", 0);
    G.adicionaAresta("B", "C", 0);
    G.adicionaAresta("C", "D", 0);
    G.adicionaAresta("C", "I", 0);
    G.adicionaAresta("H", "I", 0);
    G.adicionaAresta("G", "H", 0);
    G.adicionaAresta("G", "I", 0);
    G.adicionaAresta("D", "E", 0);
    G.adicionaAresta("F", "E", 0);
    G.adicionaAresta("C", "F", 0);
    G.adicionaAresta("G", "F", 0);
    G.adicionaAresta("D", "F", 0);
*/

    G.listaAdjacencia();
    cout << endl;
    //G.arvoreGeradoraMinimaPrim();
    //G.caminhoMinimoDijkstra("A", "B");
    //G.caminhoMinimoFloyd();
    //G.fechoTransitivoDireto("G", 1);
    G.fechoTransitivoIndireto("G", direcionado);

    return 0;
}

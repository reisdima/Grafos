#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

void Menu()
{
    cout << "[1] Adicionar Vertice" << endl;
    cout << "[2] Adicionar Aresta" << endl;
    cout << "[3] Exibir Grafo por Lista de Adjacencia" << endl;
    cout << "[4] Remover Vertice" << endl;
    cout << "[5] Remover Aresta" << endl;
    cout << "[6] Grau de um Vertice" << endl;
    cout << "[7] Verifiar a K regularidade do grafo" << endl;
    cout << "[8] Ordem do Grafo" << endl;
    cout << "[9] Vizinhanca aberta de um vertice" << endl;
    cout << "[10] Vizinhanca fechada de um vertice" << endl;
    cout << "[0] Sair" << endl;
}


int main()
{
    Grafo G;
    while(true){
        Menu();
        int escolha;
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
            G.adicionaAresta(nome1, nome2);
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
        else if(escolha==0)
            break;
    }
/*
    G.adicionaVertice("1");
    G.adicionaVertice("2");
    G.adicionaVertice("3");
    G.adicionaVertice("4");
    G.adicionaAresta("1", "2");
    G.adicionaAresta("1", "3");
    G.adicionaAresta("1", "4");
    G.adicionaAresta("2", "3");
    G.listaAdjacencia();
    G.removeAresta("1", "2");

    cout << endl;
    G.listaAdjacencia();

    cout << endl;
    G.listaAdjacencia();
    G.adicionaAresta("1", "2");
    cout << endl;
    G.listaAdjacencia();
    G.removeVertice("2");
    cout << endl;
    G.listaAdjacencia();*/
    return 0;
}

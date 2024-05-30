#include <iostream>
#include <queue>
#include <utility>
#include <map>

std::vector<std::pair<int,std::pair<int,int>>> AGM; //arbol generador minimal
int n = 9; //numero de nodos;

void insertar_arista(std::vector<std::vector<std::pair<int,int>>>& grafo, int nodo_origen, int nodo_destino, int costo_arista){
  if(nodo_origen<0 || nodo_origen>n-1 || nodo_destino<0 || nodo_destino>n-1){
    std::cout << "Inserción fallida: Alguno de los nodos ingresados no existe\n";
    return;
  }
  grafo[nodo_origen].push_back({nodo_destino,costo_arista});
  grafo[nodo_destino].push_back({nodo_origen,costo_arista});
}

int prim(std::vector<std::vector<std::pair<int,int>>>& grafo, int nodo){
  std::vector<bool> S(n); //S[i] == 1 significa que el nodo ya esta en el arbol;
  int peso_total = 0;
  
  // {-1*peso, {nodo origen, nodo destino}}
  std::priority_queue<std::pair<int, std::pair<int,int>>> cola; 
  
  cola.push({0,{nodo,nodo}}); 
  while(!cola.empty()){
    std::pair<int,std::pair<int,int>> actual = cola.top();
    cola.pop();
    if(S[actual.second.first] == true){
      continue;
    }
    AGM.push_back(actual);
    S[actual.second.first] = true;
    peso_total += -actual.first;
    for(int i = 0; i<grafo[actual.second.first].size(); i++){
      cola.push({-grafo[actual.second.first][i].second,{grafo[actual.second.first][i].first,actual.second.first}});
    }
  }
  return peso_total;
}

int main() {
  std::vector<std::vector<std::pair<int,int>>> grafo(n);

  insertar_arista(grafo,0,1,12);
  insertar_arista(grafo,0,2,5);
  insertar_arista(grafo,0,3,7);
  insertar_arista(grafo,1,4,5);
  insertar_arista(grafo,1,5,5);
  insertar_arista(grafo,1,8,11);
  insertar_arista(grafo,2,3,6);
  insertar_arista(grafo,2,6,4);
  insertar_arista(grafo,3,4,3);
  insertar_arista(grafo,3,5,4);
  insertar_arista(grafo,3,6,8);
  insertar_arista(grafo,5,7,7);
  insertar_arista(grafo,5,8,6);
  insertar_arista(grafo,6,7,9);
  insertar_arista(grafo,7,8,10);
  
  int peso_total = prim(grafo,0);

  std::cout << "Las aristas del árbol generador minimal son:\nFormato: {peso, {nodo origen, nodo destino}}\n\n";

  for(int i = 1; i<AGM.size(); i++){
    std::cout << "{" << -AGM[i].first << ", {" << AGM[i].second.second << ", " << AGM[i].second.first << "} }\n"; 
  }

  std::cout << "\nEl peso total es: " << peso_total;
}
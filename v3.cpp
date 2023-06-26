#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <list>

using namespace std;

typedef pair<int, int> pii;  // par (nodo, peso)


int costoBarco(int pi, int qj, vector<vector<int>> costos) {

    return costos[pi][qj];
}

void dijkstraDirigido(const vector<vector<pii>>& graph, int source, vector<int>& distances, vector<int>& parents) {
    int n = graph.size();
    distances.resize(n, numeric_limits<int>::max());
    parents.resize(n, -1);
    
    priority_queue<pii, vector<pii>, greater<pii>> pq;  // cola mínima
    
    distances[source] = 0;
    pq.push(make_pair(0, source));
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            int new_distance = distances[u] + weight;
            
            if (new_distance < distances[v]) {
                distances[v] = new_distance;
                parents[v] = u;
                pq.push(make_pair(new_distance, v));
            }
        }
    }
}

void dijkstraNoDirigido(const vector<vector<pii>>& graph, int source, vector<int>& distances, vector<int>& parents) {
    int n = graph.size();
    distances.resize(n, numeric_limits<int>::max());
    parents.resize(n, -1);

    priority_queue<pii, vector<pii>, greater<pii>> pq;  // cola mínima

    distances[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            int new_distance = distances[u] + weight;

            if (new_distance < distances[v]) {
                distances[v] = new_distance;
                parents[v] = u;
                pq.push(make_pair(new_distance, v));
            }
        }

        for (int v = 0; v < n; ++v) {
            for (const auto& neighbor : graph[v]) {
                if (neighbor.first == u) {
                    int weight = neighbor.second;
                    int new_distance = distances[v] + weight;

                    if (new_distance < distances[u]) {
                        distances[u] = new_distance;
                        parents[u] = v;
                        pq.push(make_pair(new_distance, u));
                    }
                }
            }
        }
    }
}

void printShortestPathsDirigido(const vector<int>& distances, const vector<int>& parents, int source, const vector<int>& ports) {
    int n = distances.size();
    cout << "Shortest paths from node " << source << ":\n";
    
    for (int port : ports) {
        cout << "Port " << port << ": distance = " << distances[port] << ", path = ";
        
        vector<int> path;
        int curr = port;
        
        while (curr != -1) {
            path.push_back(curr);
            curr = parents[curr];
        }
        
        for (int j = path.size() - 1; j >= 0; --j) {
            cout << path[j];
            if (j > 0) cout << " -> ";
        }
        
        cout << endl;
    }
}

void printShortestPathsNoDirigido(const vector<int>& distances, const vector<int>& parents, int source, const vector<int>& ports) {
    int n = distances.size();
    cout << "Shortest paths from node " << source << ":\n";

    for (int i = 0; i < n; ++i) {
        if (i != source && find(ports.begin(), ports.end(), i) != ports.end()) {
            cout << "Node " << i << ": distance = " << distances[i] << ", path = ";

            vector<int> path;
            int curr = i;

            while (curr != -1) {
                path.push_back(curr);
                curr = parents[curr];
            }

            for (int j = path.size() - 1; j >= 0; --j) {
                cout << path[j];
                if (j > 0) cout << " -> ";
            }

            cout << endl;
        }
    }
}

int main() {
    int n = 5;  // número de nodos
    int m = 9;
    vector<vector<pii>> pais(n);
    vector<vector<pii>> archipielago(m);
    
    int c;
      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            c=rand()%21;//genera numero aleatoria entre 0 y 20
            if(c!=0){
                pais[i].push_back(make_pair(j,c));
            }
        }
       
    }
    vector<int> portsDirigido;
    int lN=log2(n);
    for(int i=0;i<lN;i++){
        c=rand()%n;//Escoge un numero alazar para que este sea el puerto
        portsDirigido.push_back(c);
    }



/*     pais[0].push_back(make_pair(1,2));
    pais[0].push_back(make_pair(4,8));
    pais[1].push_back(make_pair(0,3));
    pais[1].push_back(make_pair(4,3));
    pais[1].push_back(make_pair(2,1));
    pais[2].push_back(make_pair(0,4));
    pais[2].push_back(make_pair(3,6));
    pais[3].push_back(make_pair(2,5));
    pais[3].push_back(make_pair(4,9));
    pais[4].push_back(make_pair(2,2));
    pais[4].push_back(make_pair(3,2)); */

    
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            c=rand()%21;//genera numero aleatoria entre 0 y 20
            if(c!=0){
                archipielago[i].push_back(make_pair(j, c));
                archipielago[j].push_back(make_pair(i, c));
            }
        }
       
    }

    vector<int> portsNoDirigido;
    c=rand()%m;
    int lM=log2(m);
    while(c<lM){
        c=rand()%m;//Escoge la isla destino al azar
    }
    portsNoDirigido.push_back(c);
   /*  archipielago[0].push_back(make_pair(1, 1));
    archipielago[1].push_back(make_pair(0, 1));
    archipielago[0].push_back(make_pair(3, 2));
    archipielago[3].push_back(make_pair(0, 2));
    archipielago[1].push_back(make_pair(3, 3));
    archipielago[3].push_back(make_pair(1, 3));
    archipielago[1].push_back(make_pair(2, 5));
    archipielago[2].push_back(make_pair(1, 5));
    archipielago[1].push_back(make_pair(8, 12));
    archipielago[8].push_back(make_pair(1, 12));
    archipielago[3].push_back(make_pair(4, 1));
    archipielago[4].push_back(make_pair(3, 1));
    archipielago[3].push_back(make_pair(6, 4));
    archipielago[6].push_back(make_pair(3, 4));
    archipielago[4].push_back(make_pair(8, 2));
    archipielago[8].push_back(make_pair(4, 2));
    archipielago[2].push_back(make_pair(8, 5));
    archipielago[8].push_back(make_pair(2, 5));
    archipielago[2].push_back(make_pair(7, 4));
    archipielago[7].push_back(make_pair(2, 4));
    archipielago[6].push_back(make_pair(5, 3));
    archipielago[5].push_back(make_pair(6, 3));
    archipielago[6].push_back(make_pair(8, 2));
    archipielago[8].push_back(make_pair(6, 2));
    archipielago[5].push_back(make_pair(7, 7));
    archipielago[7].push_back(make_pair(5, 7));
    archipielago[7].push_back(make_pair(8, 3));
    archipielago[8].push_back(make_pair(7, 3)); */
    
    vector<vector<int>> costos(lN,vector<int>(lM));
    for(int i=0;i<lN;i++){
        for(int j=0;j<lM;j++){
            c = 1 + rand()%21; // Generar valor aleatorio en el rango 0 y 20
            if (rand() % 2 == 0) { // Multiplicar por -1 con probabilidad del 50%
                c *= -1;
            }
            costos[i][j]=c;
        }
    }
    
    int source = 0;  // nodo fuente
    vector<int> distancesDirigido;
    vector<int> parentsDirigido;

    
    dijkstraDirigido(pais, source, distancesDirigido, parentsDirigido);
    
    list<int> distancesFinalesNoDirigidos;
    for (int i = 0; i < lM; i++)
    {
        vector<int> distancesNoDirigido;
        vector<int> parentsNoDirigidos;
        dijkstraNoDirigido(archipielago, i, distancesNoDirigido, parentsNoDirigidos);
        printShortestPathsNoDirigido(distancesNoDirigido, parentsNoDirigidos, i, portsNoDirigido);
        int tam = distancesNoDirigido.size();
        for (int i = 0; i < tam; ++i) {
            if (i != source && find(portsNoDirigido.begin(), portsNoDirigido.end(), i) != portsNoDirigido.end()) {
                
                distancesFinalesNoDirigidos.push_back(distancesNoDirigido[i]);
                
            }
        }
    }

    
    cout << "--------------------------------------------------------------------------" << endl;
    printShortestPathsDirigido(distancesDirigido, parentsDirigido, source, portsDirigido);

    cout << "--------------------------------------------------------------------------" << endl;

    int costo;
    int minCosto = 9999999999999;
    int i = 0;
    int j = 0;
    int besti = 0;
    int bestj = 0;
    for (int port : portsDirigido)
    {
        j = 0;
        for (const auto& elemento : distancesFinalesNoDirigidos)
        {
            costo = distancesDirigido[port] + costoBarco(i,j,costos) + elemento;
            cout << distancesDirigido[port] << " + " << costoBarco(i,j,costos) << " + " << elemento <<  endl;
            if (costo < minCosto){
                minCosto = costo;
                besti = i;
                bestj = j;
                //cout << minCosto << endl;
            }
            j++;
        }
        i++;        
    }

    



    cout << "minCosto = " << minCosto << " -> besti = " << besti << " -> bestj = " << bestj << endl;
    
    
    return 0;
}

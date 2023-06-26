#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef vector<vector<pii>> Graph;

const int INF = numeric_limits<int>::max();

// Función costoBarco
int costoBarco(int port, int island) {
    // Asignamos un costo específico para cada combinación de puerto e isla
    if (port == 0 && island == 1) {
        return 10; // Costo de viaje desde puerto 0 (A) hasta isla 1
    } else if (port == 1 && island == 3) {
        return 2; // Costo de viaje desde puerto 1 (1) hasta isla 3
    } else if (port == 3 && island == 4) {
        return 6; // Costo de viaje desde puerto 3 (3) hasta isla 4
    } else {
        return 0; // No hay conexión directa entre el puerto y la isla
    }
}



vector<int> dijkstraModified(const Graph& graph, const vector<int>& ports, const vector<int>& enabledIslands, int start, int destination) {
    int n = graph.size();
    vector<int> distance(n, INF);
    vector<int> previous(n, -1);
    distance[start] = 0;
    
    priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
    pq.push(make_pair(0, make_pair(start, -1)));  // (-cost, (node, previousPort))
    
    while (!pq.empty()) {
        int currNode = pq.top().second.first;
        int currPort = pq.top().second.second;
        pq.pop();
        
        if (currNode == destination) {
            break;
        }
        
        for (const auto& neighbor : graph[currNode]) {
            int nextNode = neighbor.first;
            int cost = neighbor.second;
            int totalCost;
            
            if (find(enabledIslands.begin(), enabledIslands.end(), nextNode) != enabledIslands.end()) {
                int nextPort = nextNode;
                if (currPort != -1) {
                    totalCost = distance[currNode] + cost + costoBarco(currPort, nextPort); // Modify costoBarco() as needed
                } else {
                    totalCost = distance[currNode] + cost;
                }
            } else {
                totalCost = distance[currNode] + cost;
            }
            
            if (totalCost < distance[nextNode]) {
                distance[nextNode] = totalCost;
                previous[nextNode] = currNode;
                pq.push(make_pair(totalCost, make_pair(nextNode, currPort)));
            }
        }
    }
    
    vector<int> path;
    int curr = destination;
    while (curr != -1) {
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    
    return path;
}

int main() {
    int n = 5, m = 9; // Number of cities and islands
    //cin >> n >> m;
    
    Graph graph(n);
    // Grafo de ciudades y rutas terrestres
    Graph landGraph = {
        {{1, 4}, {2, 2}},  // A
        {{3, 5}},         // B
        {{3, 1}, {4, 6}},  // C
        {{4, 3}, {5, 8}},  // D
        {{6, 9}},         // E
        {{6, 7}, {7, 1}},  // F
        {{7, 4}},         // G
        {}                // H
    };
    vector<int> ports = {0};
    vector<int> enabledIslands = {4};
    
    // Read the graph, ports, and enabled islands from input
    
    int s=2, z=3; // Starting city and destination island
    //cin >> s >> z;
    
    vector<int> path = dijkstraModified(landGraph, ports, enabledIslands, 0, 4);
    
    if (path.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    return 0;
}

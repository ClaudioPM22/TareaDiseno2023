#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

typedef vector<vector<pair<int, int>>> Graph;

int costoBarco(int city, int island) {
    // Implementa la lógica para calcular el costo de viajar desde una ciudad a una isla
    // Puedes agregar tus propias reglas y condiciones aquí
    // Retorna el costo de viaje

    // Ejemplo de implementación (costoBarco ficticio)
    if (city == 0 && island == 1)
        return 10;
    else if (city == 1 && island == 2)
        return 5;
    else if (city == 2 && island == 3)
        return -5;
    else if (city == 3 && island == 4)
        return 3;
    else
        return 0;
}

vector<int> dijkstraModified(const Graph& landGraph, const Graph& islandGraph, const vector<int>& ports, const vector<int>& enabledIslands, int startCity, int destinationIsland) {
    int numCities = landGraph.size();
    vector<int> distances(numCities, numeric_limits<int>::max());
    vector<int> path(numCities, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distances[startCity] = 0;
    pq.push(make_pair(0, startCity));

    while (!pq.empty()) {
        int currentCity = pq.top().second;
        int currentCost = pq.top().first;
        pq.pop();

        if (currentCity == destinationIsland)
            break;

        if (currentCost > distances[currentCity])
            continue;

        for (const auto& neighbor : landGraph[currentCity]) {
            int nextCity = neighbor.first;
            int cost = neighbor.second;

            int newCost = currentCost + cost;

            if (newCost < distances[nextCity]) {
                distances[nextCity] = newCost;
                path[nextCity] = currentCity;
                pq.push(make_pair(newCost, nextCity));
            }
        }

        if (find(ports.begin(), ports.end(), currentCity) != ports.end()) {
            for (const auto& neighbor : islandGraph[currentCity]) {
                int nextIsland = neighbor.first;
                int cost = neighbor.second;

                int newCost = currentCost + costoBarco(currentCity, nextIsland);

                if (newCost < distances[nextIsland]) {
                    distances[nextIsland] = newCost;
                    path[nextIsland] = currentCity;
                    pq.push(make_pair(newCost, nextIsland));
                }
            }
        }
    }

    vector<int> shortestPath;
    int currentNode = destinationIsland;
    while (currentNode != -1) {
        shortestPath.push_back(currentNode);
        currentNode = path[currentNode];
    }
    reverse(shortestPath.begin(), shortestPath.end());

    return shortestPath;
}



int main() {
    // Grafo de ciudades y rutas terrestres
    Graph landGraph = {
        {{1, 4}, {2, 2}},  // A
        {{3, 5}},         // B
        {{3, 1}, {4, 6}},  // C
        {{4, 3}, {5, 8}},  // D
        {{6, 9}},         // E
        {{6, 7}, {7, 1}},  // F
        {{7, 0}},         // G
        {{}}              // H
    };

    // Grafo de islas y rutas marítimas
    Graph islandGraph = {
        {{1, 10}},         // Isla 1
        {{2, 5}, {3, -5}}, // Isla 2
        {{3, 3}, {4, 2}},  // Isla 3
        {{5, 4}},          // Isla 4
    };

    // Puertos marítimos
    vector<int> ports = {0};

    // Islas habilitadas
    vector<int> enabledIslands = {1, 2, 3, 4};

    // Punto de partida (capital continental) y destino (capital regional del archipiélago)
    int startCity = 0;  // A
    int destinationIsland = 4;  // Isla 4

    vector<int> shortestPath = dijkstraModified(landGraph, islandGraph, ports, enabledIslands, startCity, destinationIsland);

    // Imprimir la ruta más económica
    for (int city : shortestPath) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}

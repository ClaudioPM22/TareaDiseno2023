#include <iostream>
#include <vector>

using namespace std;

void algoritmo_exhaustivo(vector<int>& escalones, int escalon_actual, vector<int>& saltos_posibles, vector<int>& camino_actual) {
    int n = escalones.size();
    
    if (escalon_actual == n) {
        // Imprimir el camino_actual
        for (int i = 0; i < camino_actual.size(); i++) {
            cout << camino_actual[i] << " ";
        }
        cout << endl;
    } else {
        for (int i = 0; i < saltos_posibles.size(); i++) {
            int salto = saltos_posibles[i];
            
            if (escalon_actual + salto <= n && escalones[escalon_actual + salto - 1] != 1) {
                // Añadir el salto al escalón actual
                escalon_actual += salto;
                // Añadir el escalón actual al camino_actual
                camino_actual.push_back(escalon_actual);
                
                algoritmo_exhaustivo(escalones, escalon_actual, saltos_posibles, camino_actual);
                
                // Eliminar el último salto del escalón actual
                escalon_actual -= salto;
                // Eliminar el último escalón del camino_actual
                camino_actual.pop_back();
            }
        }
    }
}

int main() {
    vector<int> escalones = {0, 0, 1, 0, 1, 0, 0, 1, 0, 0};  // Ejemplo de escalera con escalones rotos
    int n = escalones.size();
    vector<int> saltos_posibles = {1, 2, 4, 8};  // Saltos permitidos (potencias de 2)
    vector<int> camino_actual;
    
    algoritmo_exhaustivo(escalones, 0, saltos_posibles, camino_actual);
    
    return 0;
}
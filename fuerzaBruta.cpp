#include <iostream>
#include <vector>
#include <set>
#include <chrono>

using namespace std;

set<vector<int>> posiblesSecuencias;

void Secuencias(vector<int> escalera, vector<int> secuencia, vector<int> p){
    if (escalera.size() == 0){
        posiblesSecuencias.insert(secuencia);
    }
    else{
        for(int salto : p){
            if(salto <= escalera.size() && escalera[salto-1] != 0){
                vector<int> nuevaEscalera(escalera.begin() + salto, escalera.end());
                vector<int> nuevaSecuencia = secuencia;
                nuevaSecuencia.push_back(salto);
                Secuencias(nuevaEscalera, nuevaSecuencia, p);
            }
        }
    }
}

set<vector<int>> fuerzaBruta(vector<int> E, vector<int> p){
    posiblesSecuencias.clear();
    vector<int> secuenciaVacia;
    Secuencias(E, secuenciaVacia, p);
    return posiblesSecuencias;
}

int main(int argc, char **argv){
	if(argc != 4){
		cout << "Error. debe ejecutarse como ./SuperMario n r p" << endl;
		exit(EXIT_FAILURE);}

	int n = atoi(argv[1]);//tranformar un entero del segundo argumento de la llamada
	int r= atoi(argv[2]);
    int p= atoi(argv[3]);
    
    vector<int> E;
    for(int i=0;i<n;i++){
        E.push_back(1);
    }

    int roto;
      for(int i=0;i<r;i++){
        roto=rand()%n;//genera numero aleatoria entre 1 y n-1
        E[roto]=0;
    } 

    
    int aux=1;
    int pot=0;
    vector<int> potencias;
    potencias.push_back(1);
    while(aux<n){
        aux=aux*p;
        if (aux < n){
            potencias.push_back(aux);
            //cout << aux << endl;
        }
        
        
        pot+=1;
    }
    auto start = chrono::high_resolution_clock::now();
    set<vector<int>> resultado = fuerzaBruta(E, potencias);
    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración en segundos
    chrono::duration<double> duration = end - start;
    double tiempoEjecucion = duration.count();

    // Imprimir el tiempo de ejecución
    cout << "El tiempo de ejecución fue: " << tiempoEjecucion << " segundos." << endl;

/*     for(auto secuencia : resultado){
        for(int salto : secuencia){
            cout << salto << ' ';
        }
        cout << endl;
    } */

    return 0;
}

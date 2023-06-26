#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

pair<int, vector<vector<int>>> combinaciones(vector<int> E, vector<int> p) {
    int n = E.size();
    vector<int> dp(n+1, 0);
    vector<vector<vector<int>>> comb(n+1);

    dp[0] = 1;
    comb[0] = {{}};

    for(int i = 1; i <= n; i++) {
        if(E[i-1] == 0)
            continue;
        for(int j : p) {
            if(j <= i) {
                dp[i] += dp[i-j];
                for(auto &c : comb[i-j]) {
                    vector<int> temp = c;
                    temp.push_back(j);
                    comb[i].push_back(temp);
                }
            }
        }
    }

    return {dp[n], comb[n]};
}

int main(int argc, char **argv) {
	if(argc != 4){
		cout << "Error. debe ejecutarse como ./SuperMario n r p" << endl;
		exit(EXIT_FAILURE);}

	int n = atoi(argv[1]);//tranformar un entero del segundo argumento de la llamada
	int r= atoi(argv[2]);
    int p= atoi(argv[3]);
    //0: Roto, 1:Bueno
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
    pair<int, vector<vector<int>>> result = combinaciones(E, potencias);
    auto end = chrono::high_resolution_clock::now();

    // Calcular la duración en segundos
    chrono::duration<double> duration = end - start;
    double tiempoEjecucion = duration.count();

    // Imprimir el tiempo de ejecución
    cout << "El tiempo de ejecución fue: " << tiempoEjecucion << " segundos." << endl;

 /*    cout << "Number of ways: " << result.first << endl;
    cout << "Ways:" << endl;
    for(auto &way : result.second) {
        for(int j : way)
            cout << j << ' ';
        cout << '\n';
    } */

    return 0;
}

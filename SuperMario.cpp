#include<iostream>
#include <cmath>
using namespace std;

int main(int argc, char **argv){
	int a,b;
	if(argc != 4){
		cout << "Error. debe ejecutarse como ./SuperMario n r p" << endl;
		exit(EXIT_FAILURE);}
	int n = atoi(argv[1]);//tranformar un entero del segundo argumento de la llamada
	int r= atoi(argv[2]);
    int p= atoi(argv[3]);

    //Crea el arreglo con los escalones y settea los todos los escalos como 1
    int *E= new int[n];
    for(int i=0;i<n;i++){
        E[i]=1;
    }

    int roto;
    int *R =new int[r];
    for(int i=0;i<r;i++){
        roto=1+rand()%n;//genera numero aleatoria entre 1 y n-1
        R[i]=roto;
        E[roto]=0;
    }

    //generador de los saltos de super mario
    int aux=1;
    int pot=0;
    while(aux<n){
        aux=aux*p;
        pot+=1;
    }
    int *Saltos=new int[pot];
    for(int i=0;i<pot;i++){
        Saltos[i]=pow(p,i);
    }

    cout<<"Escalosnes: "<<endl;
    cout<<"E[n] = ";
    for(int i=0;i<n;i++){
        cout<<E[i] <<" ";
    }
    cout<<""<<endl;

    cout<<"Saltos de Super mario: "<<endl;
    cout<<"p = ";
    for(int i=0;i<pot;i++){
        cout<<Saltos[i] <<" ";
    }
    cout<<""<<endl;

return 0;
}
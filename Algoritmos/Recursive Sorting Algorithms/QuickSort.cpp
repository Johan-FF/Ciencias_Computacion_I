#include <iostream>
#include <chrono>
#include <cstdlib>


using namespace std;

void ordenRapido(int a[], int izq, int der){
	int i, j , v ;
	
	if(der>izq){
		v=a[der]; i =izq -1; j=der;
		for(;;){
			while(a[++i]<v);
			while(a[--j]>v);
			if(i>=j)break;
			swap(a[i],a[j]);
		}
		swap(a[i],a[der]);
		ordenRapido(a,izq,i-1);
		ordenRapido(a,i+1,der);
	}
}

int main(){
	
	int tamano = 10;
	
	while(tamano <= 6000){
		
		//Declaracion del array
		int a[tamano];
		int size = sizeof(a) / sizeof(a[0]);
		
		//Llenado del array con el peor caso
		
		for(int i =0; i<= tamano; i++){
			a[i] = tamano - i;
		}
		
		//Llamado del metodo orden rapido y las variables de tiempo en nanosegundos
		
		auto start = chrono::high_resolution_clock::now();
		
		ordenRapido(a,0,tamano);
		
		auto stop = chrono::high_resolution_clock::now();
	    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	    cout << duration.count() << endl;
		
		tamano += 10;
	}
	
	return 0;
}

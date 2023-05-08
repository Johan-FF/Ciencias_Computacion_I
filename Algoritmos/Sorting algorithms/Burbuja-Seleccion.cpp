#include <iostream>
#include <chrono>
#include <cstdlib>


using namespace std;

// Algoritmo de Selección
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    int s=0;
    while(n<=200){
    	s=0;
    	/*Llenar el arreglo*/
    	for(i=n;i>=0;i--){
    		arr[s] = n - s;
    		s++;
		}
		
	    //Obtiene el tiempo inicial
	    auto start = chrono::steady_clock::now();
		// Code to execute
	    for (i = 0; i < n-1; i++) {
	        min_idx = i;
	        for (j = i+1; j < n; j++)
	            if (arr[j] < arr[min_idx])
	                min_idx = j;
	        swap(arr[min_idx], arr[i]);
	    }
	    
	    // Obtiene el tiempo Final
	   	auto end = chrono::steady_clock::now();
		// Muestra el tiempo final en nanosegundos
	    cout <<chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
	    n +=10;
	}
	cout << "Arreglo ordenado con algoritmo de selección: ";
	for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Algoritmo de Burbuja
void bubbleSort(int arr[], int n) {
    int i, j;
    int s = 0;
    bool swapped;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
    
    while(n<=200){
    	/*Llenar el arreglo*/
    	s=0;
    	/*Llenar el arreglo*/
    	for(i=n;i>=0;i--){
    		arr[s] = n - s;
    		s++;
		}
		//Obtiene el tiempo inicial
	    start = chrono::steady_clock::now();
	    
	    for (i = 0; i < n-1; i++) {
	        for (j = 0; j < n-i-1; j++) {
	            if (arr[j] > arr[j+1]) {
	                swap(arr[j], arr[j+1]);
	            }
	        }
	    }
		
		// Obtiene el tiempo Final
	   	end = chrono::steady_clock::now();
		// Muestra el tiempo final en microsegundos
	    cout <<chrono::duration_cast<chrono::microseconds>(end - start).count()<<endl;
	    n +=10; 
	}
	cout << "Arreglo ordenado con algoritmo de burbuja: ";
	for (int i = 0; i < n; i++)
	    cout << arr[i] << " ";
	cout << endl;		
}

// Función para imprimir el arreglo ordenado
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {};
    
    // Ordenar con algoritmo de selección
    bubbleSort(arr, 10);

    return 0;
}


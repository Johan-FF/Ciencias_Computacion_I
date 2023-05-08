#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}

int main() {
    int *arr;
    int n = 5;
    
    int x = 0;
    
    while(n <= 200){
    	/*Llena el arreglo descendentemente*/
    	arr = new int[n];
    	for(int i=0; i < n; i++){
    		arr[i]= n-(i+1);
		}
			
		/*Inicia la cuenta de tiempo de ejecución*/
		auto start = steady_clock::now();
	    //Invoca al metodo de busqueda binaria
	    int result = binarySearch(arr, 0, n - 1, x);
	    //Finaliza la cuenta del tiempo de ejecución y la muestra
	    auto end = steady_clock::now();
	    cout<<duration_cast<nanoseconds>(end - start).count()<<endl;
	    
	    n += 5;
	}
    
    return 0;
}


#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void insercion(int a[], int n);

int main() {
    int i, j, *a;
    ofstream archivo;

    archivo.open("DataSetInsercion",ios::out);
    for (i=1; i<21; i++) {

        a = new int[i*10]; //creación de la lista
        for (j=0; j<i*10; j++) {
            a[j]= j;
        } //termina el relleno en el peor caso de insercion
        
        auto start = steady_clock::now();
        insercion(a, i*10); //algoritmo de ordenamiento
        auto end = steady_clock::now();
        //medicion y captura del tiempo 
        archivo<<duration_cast<microseconds>(end - start).count()<<endl;
        
        delete a;
    }

    archivo.close();
    return 0;
}

void insercion(int a[], int n) {
    int k, l, v;
    for (k=2; k<=n; k++) {
        l=k;
        v=a[l];
        while (a[l-1]>v && l>1) {
            a[l] = a[l-1];
            l--;
        }
        a[l]=v;
    }
}

#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void shell(int a[], int n, int &cont);

int main() {
    int k, l, *a, cont=0;
    ofstream archivo;

    archivo.open("DataSetShell",ios::out);
    for (k=1; k<41; k++) {
        cout<<k;
        a = new int[k*50]; //creación de la lista
        for (l=0; l<k*50; l++) {
            a[l]=(k*50)-l;
        } //termina el relleno en el peor caso de insercion
        
        auto start = steady_clock::now();
        shell(a, k*50, cont); //algoritmo de ordenamiento
        auto end = steady_clock::now();
        //medicion y captura del tiempo 
        archivo<<k*50<<","<<duration_cast<microseconds>(end - start).count()<<","<<cont<<endl;
        
        cont=0;
        delete[] a;
    }

    archivo.close();
    return 0;
}

void shell(int a[], int n, int &cont) {
    int i, j, h, v;
    for (h=1; h<=n/9; h=3*h+1);
    for (; h>0; h/=3){
        for (i=h+1; i<=n; i++) {
            v=a[i];
            j=i;
            while (j>h && a[j-h]>v) {
                a[j]=a[j-h];
                j-=h;
                cont+=2;
            }
            a[j]=v;
            cont+=3;
        }
    }
}
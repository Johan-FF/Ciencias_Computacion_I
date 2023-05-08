#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <chrono>

using namespace std;


inline unsigned bits (int x, int k, int j)
{
    return (x >> k) & ~(~ 0 << j) ;
}

inline void swap(char& x, char& y)
{
    std::swap(x, y);
}

void cambioresiduos(char a[], int izq, int der, int b)
{
    if (izq >= der) {
        return;
    }

    int i = izq;
    int j = der;
    
    while(j != i)
    {
        while(!bits(a[i],b,1) && i < j) {
            i++;
        }
        while(bits(a[j],b,1) && j > i) {
            j--;
        }
        swap(a[i], a[j]);
    }
    if (bits(a[j],b,1)) {
        j++;
    }
    cambioresiduos(a, izq, j-1, b-1);
    cambioresiduos(a, j, der, b-1);
}
 
int main(){
	
    int tamanoArreglo = 10;
    
    srand(time(NULL));

    while(tamanoArreglo <= 6000){
        
        char arreglo[tamanoArreglo] = {};

        // Generamos las letras del abecedario utilizando la tabla ASCII
    
        for (int i = 0; i < tamanoArreglo; i++) {
            arreglo[i] = 'A' + rand() % 26; ; // La letra 'a' tiene el código ASCII 97
        }

	
        int n = sizeof(arreglo) / sizeof(arreglo[0]);

        /* Inicia la cuenta del reloj*/
        auto start = chrono::high_resolution_clock::now();

        cambioresiduos(arreglo, 0, n-1, 2);

        /* Finaliza la cuenta del reloj*/
        auto end = chrono::high_resolution_clock::now();

        /*Muestra  la cuenta del reloj*/
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << duration.count() << endl;

        tamanoArreglo += 10;
    }


	
	return 0;
}

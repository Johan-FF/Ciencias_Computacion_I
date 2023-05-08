#include <iostream>
#include <chrono>

void radixsort(int arr[], int n, int exp) {
    int output[n]; // arreglo para guardar los elementos ordenados
    int count[10] = {0}; // arreglo para contar la cantidad de elementos en cada "bucket"

    // contar la cantidad de elementos en cada "bucket"
    for (int i = 0; i < n; i++) {
        count[(arr[i]/exp) % 10]++;
    }

    // ajustar los contadores para que indiquen la posición de cada elemento en el arreglo de salida
    for (int i = 1; i < 10; i++) {
        count[i] += count[i-1];
    }

    // colocar cada elemento en su posición correspondiente en el arreglo de salida
    for (int i = n-1; i >= 0; i--) {
        output[count[(arr[i]/exp) % 10]-1] = arr[i];
        count[(arr[i]/exp) % 10]--;
    }

    // copiar el arreglo de salida al arreglo original
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixsort(int arr[], int n) {
    // encontrar el número más grande del arreglo
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // aplicar radixsort para cada dígito decimal, empezando por el menos significativo
    for (int exp = 1; max/exp > 0; exp *= 10) {
        radixsort(arr, n, exp);
    }
}

int main() {
    // semilla para la generación de números aleatorios
    srand(time(NULL));

    // iterar por diferentes tamaños de arreglo
    for (int n = 10; n <= 2000; n += 10) {
        // generar arreglo aleatorio de tamaño n
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

        // medir tiempo de ejecución de radixsort
        auto start = std::chrono::high_resolution_clock::now();
        radixsort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();


        // imprimir información de tiempo y tamaño de arreglo
        std::cout << "Radixsort ordenando " << n << " datos en " << duration << " microsegundos" << std::endl;
    
    }

    return 0;
}

#include <iostream>
#include <chrono>

using namespace std;

// Función merge para fusionar dos sub-listas
void merge(int arr[], int left[], int right[], int leftSize, int rightSize) {
    int i = 0, j = 0, k = 0;

    // Fusionar elementos en orden ascendente
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de la sub-lista izquierda, si hay alguno
    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de la sub-lista derecha, si hay alguno
    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Función recursiva para dividir la lista en sub-listas y fusionarlas usando la función merge
void mergeSort(int arr[], int size) {
    if (size < 2) { // Lista de tamaño 1 o vacía ya está ordenada
        return;
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    // Copiar los elementos de la lista en las sub-listas izquierda y derecha
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    // Llamadas recursivas para ordenar las sub-listas izquierda y derecha
    mergeSort(left, mid);
    mergeSort(right, size - mid);

    // Fusionar las sub-listas ordenadas
    merge(arr, left, right, mid, size - mid);
}

int main() {
    for (int i=1; i<=200; i++) {
        int n = 10*i; // Inicializar tamaño de la lista a 10
        int arr[n];

        // Generar lista aleatoria de enteros y ordenarla usando mergesort
        srand(time(0)); // Semilla para la función de números aleatorios
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
        }

        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        cout << "Numero de elementos: " << n << " Tiempo de ejecucion: " << duration << " microsegundos." << endl;
    }

}
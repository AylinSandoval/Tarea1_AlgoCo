#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Biblioteca para medir el tiempo

#define MIN_SIZE 1000  // Tamaño mínimo del arreglo
#define MAX_SIZE 100000 // Tamaño máximo del arreglo
#define NUM_CASES 10    // Número de casos de prueba a generar

// Función para leer el archivo de casos de prueba
int** leerCasosPrueba(int *numCasos, int **tamanos) {
    FILE *fptr = fopen("casospruebas.txt", "r");  

    if (fptr == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    int **arreglos = (int **)malloc(NUM_CASES * sizeof(int *));
    *tamanos = (int *)malloc(NUM_CASES * sizeof(int));
    *numCasos = 0;

    while (*numCasos < NUM_CASES) {
        int size;
        if (fscanf(fptr, "%d", &size) != 1) break; 

        arreglos[*numCasos] = (int *)malloc(size * sizeof(int));
        (*tamanos)[*numCasos] = size;

        for (int i = 0; i < size; i++) {
            if (fscanf(fptr, "%d", &arreglos[*numCasos][i]) != 1) {
                printf("Error al leer los datos del archivo!\n");
                exit(1);
            }
        }

        (*numCasos)++;
    }

    fclose(fptr);
    return arreglos;
}



void swap(int a[], int b, int c) {
    int aux = a[b];
    a[b] = a[c];
    a[c] = aux;
}

// Función de partición para QuickSort
int particionar(int a[], int l, int r, int p) {
    swap(a, l, p);  // Coloca el pivote en la primera posición
    int i = l + 1;
    for (int j = l + 1; j <= r; j++) {
        if (a[j] <= a[l]) {
            swap(a, i, j);
            i++;
        }
    }
    swap(a, l, i - 1);
    return i - 1;
}

// Función de QuickSort con diferentes estrategias de pivote
void quicksort(int a[], int l, int r, int estrategia) {
    if (l < r) {
        int p; // Pivote

        switch (estrategia) {
            case 1: // Pivote en el inicio
                p = l;
                break;
            case 2: // Pivote en el final
                p = r;
                break;
            case 3: // Pivote en la mitad
                p = (l + r) / 2;
                break;
            case 4: // Pivote aleatorio
                p = l + rand() % (r - l + 1);
                break;
            default:
                p = l;
        }

        p = particionar(a, l, r, p);  // Particiona el arreglo con el pivote seleccionado
        quicksort(a, l, p - 1, estrategia);  // Parte izquierda
        quicksort(a, p + 1, r, estrategia);  // Parte derecha
    }
}

// Función para realizar QuickSort sobre los casos de prueba leídos
void ejecutarQuickSort(int **arreglos, int *tamanos, int numCasos) {
    for (int estrategia = 1; estrategia <= 4; estrategia++) {
        printf("Probando QuickSort con estrategia %d:\n", estrategia);

        for (int i = 0; i < numCasos; i++) {
            int *copia = (int *)malloc(tamanos[i] * sizeof(int));
            
            // Copia el arreglo original
            for (int j = 0; j < tamanos[i]; j++) {
                copia[j] = arreglos[i][j];
            }

            clock_t start = clock();
            quicksort(copia, 0, tamanos[i] - 1, estrategia);  // Aplica QuickSort
            clock_t end = clock();

            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Caso %d - Tamaño %d - Tiempo de ejecución: %f segundos\n", i + 1, tamanos[i], time_spent);

            free(copia);
        }
        printf("\n");
    }
}

int main() {

    int numCasos;
    int *tamanos;
    int **arreglos = leerCasosPrueba(&numCasos, &tamanos);  // Lee los casos de prueba

    ejecutarQuickSort(arreglos, tamanos, numCasos);  // Ejecuta QuickSort en los casos de prueba

    // Libera la memoria
    for (int i = 0; i < numCasos; i++) {
        free(arreglos[i]);
    }
    free(arreglos);
    free(tamanos);

    return 0;
}

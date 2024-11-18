#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Biblioteca para medir el tiempo

#define NUM_CASES 10    // Número máximo de casos de prueba

// Función para leer el archivo de casos de prueba
int** leerCasosPrueba(int *numCasos, int **tamanos) {
    FILE *fptr = fopen("casospruebas.txt", "r");  // Abre el archivo para lectura

    if (fptr == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    // Leer el archivo y cargar los casos de prueba
    int **arreglos = (int **)malloc(NUM_CASES * sizeof(int *));
    *tamanos = (int *)malloc(NUM_CASES * sizeof(int));
    *numCasos = 0;

    while (*numCasos < NUM_CASES) {
        int size;
        if (fscanf(fptr, "%d", &size) != 1) break;  // Lee el tamaño del arreglo

        // Reserva memoria para el arreglo
        arreglos[*numCasos] = (int *)malloc(size * sizeof(int));
        (*tamanos)[*numCasos] = size;

        // Lee el arreglo
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

// Función de ordenamiento por selección
void selectionSort(int a[], int n) {
    int m, f, aux;
    for (int e = 0; e < n - 1; e++) {
        m = e;
        for (f = e + 1; f < n; f++) {
            if (a[f] < a[m]) {
                m = f;
            }
        }
        aux = a[e];
        a[e] = a[m];
        a[m] = aux;
    }
}

// Función para imprimir un arreglo
void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int numCasos;
    int *tamanos;
    int **arreglos = leerCasosPrueba(&numCasos, &tamanos);

    for (int i = 0; i < numCasos; i++) {
        printf("Caso de prueba %d (tamaño %d):\n", i + 1, tamanos[i]);

        clock_t start = clock();
        selectionSort(arreglos[i], tamanos[i]);
        clock_t end = clock();

        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Tiempo de ejecución: %f segundos\n", time_spent);
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < numCasos; i++) {
        free(arreglos[i]);
    }
    free(arreglos);
    free(tamanos);

    return 0;
}

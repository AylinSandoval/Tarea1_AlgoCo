#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CASES 10    // Número de casos de prueba

// Función para leer el archivo de casos de prueba
int** leerCasosPrueba(int *numCasos, int **tamanos) {
    FILE *fptr;
    fptr = fopen("casospruebas.txt", "r");  // Abre el archivo para lectura

    if (fptr == NULL) {
        printf("Error al abrir el archivo!\n");
        exit(1);
    }

    // Leer el archivo y cargar los casos de prueba
    int **arreglos = (int **)malloc(NUM_CASES * sizeof(int *));
    *tamanos = (int *)malloc(NUM_CASES * sizeof(int));
    *numCasos = 0;

    while (1) {
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

// Funciones auxiliares para mergeSort
void copiar(int an[], int av[], int n2, int n, int f){
    if(f == 0){
        for (int i = 0; i < n2; i++) {
            an[i] = av[i];
        }
    } else if(f == 1){
        for (int i = n2; i < n; i++) {
            an[i - n2] = av[i];
        }
    }
}

void merge(int a[], int a1[], int m, int a2[], int n_m) {
    int i = 0, j = 0, k = 0;
    while (i < m && j < n_m) {
        if (a1[i] < a2[j]) {
            a[k++] = a1[i++];
        } else {
            a[k++] = a2[j++];
        }
    }
    while (i < m) {
        a[k++] = a1[i++];
    }
    while (j < n_m) {
        a[k++] = a2[j++];
    }
}

void mergeSort(int a[], int n){
    if(n <= 1) return;
    int m = n / 2;
    int *a1 = (int *)malloc(m * sizeof(int));
    int *a2 = (int *)malloc((n - m) * sizeof(int));
    copiar(a1, a, m, n, 0);
    copiar(a2, a, m, n, 1);
    mergeSort(a1, m);
    mergeSort(a2, n - m);
    merge(a, a1, m, a2, n - m);
    free(a1);
    free(a2);
}

void printArray(int a[], int n) {
    for(int i = 0; i < n; i++) {
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
        mergeSort(arreglos[i], tamanos[i]);
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

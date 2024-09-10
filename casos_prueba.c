#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 1000  // Tamaño mínimo del arreglo
#define MAX_SIZE 100000 // Tamaño máximo del arreglo
#define NUM_CASES 10    // Número de casos de prueba a generar

int main() {
    FILE *fptr;
    fptr = fopen("casospruebas.txt", "w");  // Abre el archivo para escritura

    if (fptr == NULL) {
        printf("Error al abrir el archivo!\n");
        return 1;
    }

    srand(time(NULL));  // Inicializa la semilla de números aleatorios

    // Genera varios casos de prueba
    for (int i = 0; i < NUM_CASES; i++) {
        // Genera un tamaño aleatorio para el arreglo entre MIN_SIZE y MAX_SIZE
        int size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE + 1);
        
        // Escribe el tamaño del arreglo en el archivo
        fprintf(fptr, "%d\n", size);
        
        // Genera y escribe los números aleatorios del arreglo
        for (int j = 0; j < size; j++) {
            int random_num = rand();  // Número aleatorio
            fprintf(fptr, "%d ", random_num);
        }
        fprintf(fptr, "\n");  // Salto de línea después de cada arreglo
    }

    fclose(fptr);  // Cierra el archivo
    printf("Archivo 'casospruebas.txt' generado correctamente.\n");

    return 0;
}

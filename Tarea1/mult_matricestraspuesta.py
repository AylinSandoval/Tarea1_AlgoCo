import time

def leer_matrices(filename):
    matrices = []
    with open(filename, "r") as f:
        contenido = f.read().strip().split("\n\n")
        for matriz_str in contenido:
            lines = matriz_str.strip().split("\n")
            if not lines:
                continue
            header = lines[0]
            size = int(header.split("x")[0].split(" ")[-1])
            matriz = [list(map(int, line.split())) for line in lines[1:]]
            matrices.append(matriz)
    return matrices

def transponer_matriz(matriz):
    return [list(fila) for fila in zip(*matriz)]

def multiplicar_matrices_filas(A, B_T):
    filas_A = len(A)
    columnas_A = len(A[0])
    filas_B_T = len(B_T)
    columnas_B_T = len(B_T[0])
    
    if columnas_A != filas_B_T:
        raise ValueError("El número de columnas de A debe ser igual al número de filas de B^T.")
    
    C = [[0] * columnas_B_T for _ in range(filas_A)]
    
    for i in range(filas_A):
        for j in range(columnas_B_T):
            for k in range(columnas_A):
                C[i][j] += A[i][k] * B_T[j][k]
    
    return C

def main():
    matrices = leer_matrices("casosprueba_matrices.txt")
    
    for i in range(0, len(matrices) - 1, 2):
        A = matrices[i]
        B = matrices[i + 1]
        B_transpuesta = transponer_matriz(B)
        print(f"Multiplicando matriz A de tamaño {len(A)}x{len(A[0])} con la transpuesta de B ({len(B_transpuesta)}x{len(B_transpuesta[0])})")
        
        try:
            inicio = time.time()
            resultado = multiplicar_matrices_filas(A, B_transpuesta)
            fin = time.time()
            
            tiempo_total = fin - inicio
            print(f"Resultado de la multiplicación de A con B transpuesta ({i//2 + 1}):")
            print(f"Tiempo de ejecución: {tiempo_total:.4f} segundos")
        except ValueError as e:
            print(f"Error: {e}")
        print("\n")

if __name__ == "__main__":
    main()

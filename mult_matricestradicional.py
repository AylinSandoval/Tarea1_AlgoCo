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

def multiplicar_matrices(A, B):
    filas_A = len(A)
    columnas_A = len(A[0])
    filas_B = len(B)
    columnas_B = len(B[0])
    
    if columnas_A != filas_B:
        raise ValueError("El número de columnas de A debe ser igual al número de filas de B.")
    
    C = [[0] * columnas_B for _ in range(filas_A)]
    
    for i in range(filas_A):
        for j in range(columnas_B):
            for k in range(columnas_A):
                C[i][j] += A[i][k] * B[k][j]
    
    return C

def main():
    matrices = leer_matrices("casosprueba_matrices.txt")
    
    for i in range(0, len(matrices) - 1, 2):
        A = matrices[i]
        B = matrices[i + 1]
        print(f"Multiplicando matrices de tamaño {len(A)}x{len(A[0])} y {len(B)}x{len(B[0])}")
        
        try:
            inicio = time.time()
            resultado = multiplicar_matrices(A, B)
            fin = time.time()
            
            tiempo_total = fin - inicio
            print(f"Resultado de la multiplicación de las matrices {i//2 + 1}:")
            print(f"Tiempo de ejecución: {tiempo_total:.4f} segundos")
        except ValueError as e:
            print(f"Error: {e}")
        print("\n")

if __name__ == "__main__":
    main()

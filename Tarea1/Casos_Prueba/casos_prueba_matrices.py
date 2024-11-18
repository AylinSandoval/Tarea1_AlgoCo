import random

MIN_SIZE = 512 # Tamaño mínimo de la matriz
NUM_CASES = 10   # Número de matrices a generar

def generar_matrices():
    with open("casosprueba_matrices.txt", "w") as f:
        # Genera varias matrices de prueba
        for i in range(NUM_CASES):
            size = MIN_SIZE
            
            f.write(f"Matriz {size}x{size}:\n")
            
            for _ in range(size):
                row = " ".join(str(random.randint(0, 1000000)) for _ in range(size))
                f.write(row + "\n")
            
            f.write("\n")

    print("Archivo 'casosprueba_matrices.txt' generado correctamente.")

if __name__ == "__main__":
    generar_matrices()

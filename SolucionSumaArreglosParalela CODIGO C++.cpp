#include <iostream>
#include <omp.h>

#define N 1000  
#define MOSTRAR 10

void imprimeArreglo(int *arreglo, int cantidad);

int main()
{
    std::cout << "=== SUMA PARALELA DE ARREGLOS CON OpenMP ===\n\n";
    
    // Declaración de los tres arreglos
    int A[N], B[N], R[N];
    
    // PASO 1: Inicializar arreglos A y B
    std::cout << "Inicializando arreglos...\n";
    for (int i = 0; i < N; i++)
    {
        A[i] = i + 1;        // A = {1, 2, 3, 4, 5, ...}
        B[i] = i + 11;       // B = {11, 12, 13, 14, 15, ...}
    }
    
    // PASO 2: Realizar suma paralela
    std::cout << "Realizando suma paralela...\n";
    
    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        R[i] = A[i] + B[i];
        
        // Opcional: mostrar qué hilo está trabajando
        #pragma omp critical
        {
            if (i < 10) // Solo mostrar los primeros 10 para no saturar la salida
            {
                std::cout << "Hilo " << omp_get_thread_num() 
                         << " procesando índice " << i 
                         << ": " << A[i] << " + " << B[i] 
                         << " = " << R[i] << "\n";
            }
        }
    }
    
    // PASO 3: Imprimir resultados
    std::cout << "\n=== RESULTADOS ===\n";
    std::cout << "\nArreglo A (primeros " << MOSTRAR << " elementos):\n";
    imprimeArreglo(A, MOSTRAR);
    
    std::cout << "\nArreglo B (primeros " << MOSTRAR << " elementos):\n";
    imprimeArreglo(B, MOSTRAR);
    
    std::cout << "\nArreglo R (resultado - primeros " << MOSTRAR << " elementos):\n";
    imprimeArreglo(R, MOSTRAR);
    
    // Información de hilos utilizados
    std::cout << "\n=== INFORMACIÓN DE EJECUCIÓN ===\n";
    #pragma omp parallel
    {
        #pragma omp master
        {
            std::cout << "Número total de hilos utilizados: " << omp_get_num_threads() << "\n";
        }
    }
    
    return 0;
}

void imprimeArreglo(int *arreglo, int cantidad)
{
    std::cout << "[";
    for (int i = 0; i < cantidad; i++)
    {
        std::cout << arreglo[i];
        if (i < cantidad - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}
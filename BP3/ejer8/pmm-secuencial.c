#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define VECTOR_DYNAMIC  //Como se nos ha indicado en clase, hacemos uso de este tipo de vectores


int main(int argc, char** argv)
{
    int i, j, k;
    double t_ini, t_fin, t_total;

    //Leemos si el numero de datos introducidos es correcto
    if (argc<2){
        printf("Falta el tamaño de la matriz y e el tamaño del vector\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]); //MAXIMO N = 2^32

    double **A, **B, **C;
    A = (double**) malloc(N*sizeof(double *));
    B = (double**) malloc(N*sizeof(double *));
    C = (double**) malloc(N*sizeof(double *));

//Comprobamos que la reserva de memoria se ha realizado correctamente
//MATRIZ M1
    if ((A==NULL) || (B==NULL) || (C==NULL)){
        printf("Error al reservar el espacio de la matriz\n");
        exit(-2);
    }

    for(i=0; i<N; i++){
        A[i] = (double*) malloc(N*sizeof(double));
        B[i] = (double*) malloc(N*sizeof(double));
        C[i] = (double*) malloc(N*sizeof(double));

        if(A[i]==NULL || B[i]==NULL || C[i]==NULL){
            printf("Error al reservar el espacio de la matriz\n");
            exit(-2);
        }
    }
//******************************************************+


//Inicializamos las matriz 
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            A[i][j]=0;
            B[i][j]=1;
            C[i][j]=1;
        }
    }

    //Calculamos A = B*C y lo que se tarda en realizar esta operación
    t_ini = omp_get_wtime();

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            for(k=0; k<N; k++){
                A[i][j] = A[i][j] + (B[i][j]*C[i][j]);
            }
        }
    }

    t_fin = omp_get_wtime();
    t_total = t_fin-t_ini;

    //Mostramos el resultado y su tiempo de ejecución;
    printf("Tiempo(seg.): %11.9f\t / Tamaño:%u\t/ A[0][0]=%8.6f A[%d][%d]=%8.6f\n", t_total, N, A[0][0], N-1, A[N-1][N-1]);

    //Liberamos el espacio reservado de las matrices A, B y C
    for(i=0; i<N; i++) {free(A[i]); free(B[i]); free(C[i]);}

    free(A);
    free(B);
    free(C);

    return 0;
}
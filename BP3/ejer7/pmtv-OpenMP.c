#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define VECTOR_DYNAMIC  //Como se nos ha indicado en clase, hacemos uso de este tipo de vectores


int main(int argc, char** argv)
{
    int i, j, *chunk_size;
    double t_ini, t_fin, t_total, res;
    omp_sched_t kind;

    //Leemos si el numero de datos introducidos es correcto
    if (argc<2){
        printf("Falta el tamaño de la matriz y e el tamaño del vector\n");
        exit(-1);
    }

    unsigned int N = atoi(argv[1]); //MAXIMO N = 2^32-1

    double *v1, *v2, **M;
    v1 = (double*) malloc(N*sizeof(double));
    v2 = (double*) malloc(N*sizeof(double));
    M = (double**) malloc(N*sizeof(double *));

    //Comprobamos que la reserva de memoria se ha realizado correctamente
    if ((v1==NULL) || (v2==NULL) || (M==NULL)){
        printf("Error al reservar el espacio de la matriz\n");
        exit(-2);
    }

    for(i=0; i<N; i++){
        M[i] = (double*) malloc(N*sizeof(double));
        if(M[i]==NULL){
            printf("Error al reservar el espacio de la matriz\n");
            exit(-2);
        }
    }

    //Inicializamos la matriz 
    for(i=0; i<N; i++){
        v1[i]=1;
    }

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(i<=j){
                M[i][j]=1;
            }else{
                M[i][j]=0;
            }
            
        }
    }

    //Calculamos v2 = M * v1 y lo que se tarda en realizar esta operación
    #pragma omp parallel shared(v1,v2,M) 
    {
        #pragma omp single
        {
            omp_get_schedule(&kind,&chunk_size);
            printf("run-sched-var --> Kind: %d, Modifier: %d\n",kind,chunk_size);
            t_ini = omp_get_wtime();
        }
        #pragma omp for schedule(runtime)
            for(i=0; i<N; i++){
                v2[i]=0;
                for(j=0; j<N; j++){
                    if(i<=j){
                        v2[i]=v2[i]+(M[i][j]*v1[j]);
                    }
                }
            }
        
        #pragma omp single
        {
            t_fin = omp_get_wtime();
        }
    }
    
    t_total = t_fin-t_ini;

    //Mostramos el resultado y su tiempo de ejecución;
    printf("Tiempo(seg.): %11.9f\t / Tamaño:%u\t/ V2[0]=%8.6f v2[%d]=%8.6f\n", t_total, N, v2[0], N-1, v2[N-1]);
    if(N<30){
        printf("%f ", v2[i]);
    printf("\n");
    }

    //Liberamos el espacio reservado
    free(v1);
    free(v2);
    for(i=0; i<N; i++)
        free(M[i]);

    free(M);

    return 0;
}
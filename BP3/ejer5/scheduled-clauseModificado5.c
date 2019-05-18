#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()0
#endif

int main (int argc, char **argv){
    int i, n=200,chunk, a[n], suma=0, *chunk_size;
    omp_sched_t *kind;

    if(argc<2){
        printf(stderr,"\nFalta chunk\n");
        exit(-1);
    }
    n=atoi(argv[1]);
    if(n>200) n=200; chunk = atoi(argv[2]);

    for(i=0; i<n; i++) a[i]=i;

    #pragma omp parallel 
    {
        #pragma omp single
        {
            printf("VALORES DE LAS VARIABLES DENTRO DE PARALLEL\n");
            printf("dyn-var: %d\n", omp_get_dynamic());
            //Modificamos la variable dyn y la mostramos por pantalla
            omp_set_dynamic(2);
            printf("Variable dyn-var modificada: %d\n",omp_get_dynamic);
            printf("nthreads-var: %d\n",omp_get_max_threads());
            //Modificamos la variable nthreads y la mostramos por pantalla
            omp_set_num_threads(4);
            printf("Variable nthreads-var modificada: %d\n",omp_get_max_threads());
            
            omp_get_schedule(&kind,&chunk_size);
            printf("run-sched-var --> Kind: %d, Modifier: %d\n",kind, chunk_size);
            //Modificamos la variable run-sched y la mostramos por pantalla
            omp_set_schedule(2,4);
            omp_get_schedule(&kind,&chunk_size);
            printf("Variable run-sched-var modificada --> Kind: %d, Modifier: %d\n",kind,chunk_size);
        }

    #pragma omp for firstprivate(suma) \
            lastprivate(suma)schedule(dynamic,chunk)
    for(i=0; i<n; i++)
    {
        suma=suma+a[i];
        printf("thread %d suma a[%d]suma=%d\n",
            omp_get_thread_num(),i,a[i],suma);
    }

    }

    //Imprimimos fuera de la region parallel todas las variables y la suma
    printf("VALOR DE LAS VARIABLES FUERA DE PARALLEL");
    printf("dyn-var Fuera de parallel: %d\n", omp_get_dynamic());
    printf("nthreads-var Fuera de parallel: %d\n",omp_get_max_threads());

    omp_get_schedule(&kind,&chunk_size);

    printf("run-sched-var Fuera de parallel --> Kind: %d, Modifier: %d\n",kind, chunk_size);
  
    printf("Fuera de 'parallel for' suma=%d\n", suma);
}
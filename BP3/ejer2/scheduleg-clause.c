#include <stdio.h>
#include <stdlib.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num()0
#endif

int main (int argc, char **argv){
    int i, n=15,chunk, a[n], suma=0;

    if(argc<3){
        printf(stderr,"\nFalta chunk\n");
        exit(-1);
    }
    chunk = atoi(argv[1]);

    for(i=0; i<n; i++) a[i]=i;

    #pragma omp parallel for num_threads(4) firstprivate(suma) \
            lastprivate(suma)schedule(guided,chunk)
    for(i=0; i<n; i++)
    {
        suma=suma+a[i];
        printf("thread %d suma a[%d]suma=%d\n",
            omp_get_thread_num(),i,a[i],suma);
    }

    printf("Fuera de 'parallel for' suma=%d\n", suma);
}
#include <stdio.h>
#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int main(int argc, char **argv)
{
    int i, n=7;
    int a[n], suma;

    for(i=0; i<n; i++) a[i]=i;

    suma = 0;
    #pragma omp parallel for
      for (i=0; i<n; i++)
      {
          suma = suma + a[i];
          printf("thread%d suma a[%d] suma=%d \n",
                omp_get_thread_num(),i,suma);
      }
      printf("\n Thread %d suma= %d", omp_get_thread_num(), suma);
    

    

    printf("\nFuera de la region parallel Thread suma=%d\n",omp_get_thread_num(), suma);
}
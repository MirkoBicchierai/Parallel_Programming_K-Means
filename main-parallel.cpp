#include <cstdio>
#include <omp.h>


int main(){
    int a = omp_get_max_threads();
    printf("%d",a);
#pragma omp parallel for default(none)
    for(int i=0;i<10;i++){
        printf("Thread n:%d print:%i\n",omp_get_thread_num(), i);
    }
    return 0;
}
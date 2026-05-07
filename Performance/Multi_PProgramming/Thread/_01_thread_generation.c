#define _GNU_SOURCE // Required for CPU_SET and other affinity functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>


pthread_mutex_t lock ;

void *thread_fun(void *y){
	int *x = (int *)y ;
	printf("Print Jay Shree Ram : %d ",*x) ;
	
	free(y) ;
	return NULL ;
}

int main(){
	pthread_t thread[3]  ;           //structure of the 3 threads  ;
	pthread_attr_t attr[3] ;     //structre of the the 3 attributes array ;
	struct sched_param para[3] ;
	
	for(int i=0 ; i<3 ; i++){
		pthread_attr_init(&attr[i]) ;
		
		para[i].sched_priority = 3-i ;
		pthread_attr_setschedparam(&attr[i], &para[i]) ;

		int *x= (int *)malloc(sizeof(int));
		*x = i ;
	
		pthread_create(&thread[i], &attr[i], thread_fun, x); 
	}
	
	for(int i=0  ;i<3 ; i++){
		pthread_join(thread[i],NULL) ;
		pthread_attr_destroy(&attr[i]) ;
	}
	
	printf("\n"); 

    return 0; // This line is not reached due to pthread_exit()
}

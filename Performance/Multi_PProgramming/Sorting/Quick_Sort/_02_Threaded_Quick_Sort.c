#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <pthread.h>
#include <unistd.h>
#define MAX_INPUT 1000001

struct args{
	int *arr ;
	int left ;
	int right ;
};

int MAX_THREAD ;
pthread_mutex_t lock ;
int active_thread= 0 ; 


int partition(int *arr, int low, int high) ;
void *Threaded_Quick_Sort(void *args) ;

int partition(int *arr, int strt, int end){
/*
//lomuto partition :
int pivot  = arr[high] ;
int i=low-1 ;

int j=low ;
for(j=low; j<high; j++){
	if(arr[j] <= pivot){
		i++ ;
		int temp = arr[j] ;
		arr[j] = arr[i] ;
		arr[i] = temp ;
	}
}
int temp = arr[high] ;
arr[high]= arr[i+1] ;
arr[i+1] = temp ;
return i+1;
}
*/

//hoares partition : 	
	int pivot = arr[strt] ;

	
		while(strt < end){
			while(arr[strt]< pivot  ){
				strt++ ;
			}
			while(arr[end] > pivot){
				end-- ;
			}
			int temp = arr[end] ;
			arr[end] = arr[strt] ;
			arr[strt] = temp ;
	}
	if(strt >end) {
		int temp = arr[end] ;
		arr[end] = pivot ;
		arr[strt] = temp ;
	} 
	return end ;
}

void *Threaded_Quick_Sort(void *arg_t){
struct args *arg = (struct args *)arg_t ;

	if(arg->left < arg->right){
	//1. if the input for the threads are greater than the 1000 then fform a thread 
		
			int index = partition(arg->arr, arg->left, arg->right) ;
			int create_left = 0 ;
			int create_right = 0 ;
			pthread_t left_thread ;
			pthread_t right_thread ;


			struct args *thread_to_left = (struct args *)malloc(sizeof(struct args)) ;
			thread_to_left->arr = arg->arr; 
			thread_to_left->left = arg->left ;
			thread_to_left->right = index-1  ;
				
	
			struct args *thread_to_right = (struct args *)malloc(sizeof(struct args)) ;
			thread_to_right -> arr = arg->arr ;
			thread_to_right -> left = index+1 ;
			thread_to_right -> right = arg->right ;

			if(active_thread < MAX_THREAD && ((thread_to_left->right-thread_to_left->left) > 35000)){
				pthread_create(&left_thread, NULL, Threaded_Quick_Sort, thread_to_left) ;
				create_left = 1 ;
				active_thread++ ;
			}else{
				Threaded_Quick_Sort(thread_to_left) ;
			}		
			if(active_thread < MAX_THREAD && (thread_to_right->right-thread_to_right->left > 35000)){
				pthread_create(&right_thread, NULL, Threaded_Quick_Sort, thread_to_right) ;
				create_right=1 ;
				active_thread++ ;
			}else{
				Threaded_Quick_Sort(thread_to_right) ;
			}
			
			if(create_left){
				pthread_join(left_thread, NULL) ;
				pthread_mutex_lock(&lock) ;
				active_thread-- ;
				pthread_mutex_unlock(&lock) ;
			}
			if(create_right){
				pthread_join(right_thread, NULL) ;
				pthread_mutex_lock(&lock) ;
				active_thread-- ;
				pthread_mutex_unlock(&lock) ;
			} 
			free(thread_to_left) ;
			free(thread_to_right) ;
			//also go witht the number of the core that number of the threads 
	}
	return NULL ;
}





int main(){
	int *array  ;
	array= (int *)malloc(sizeof(int)*MAX_INPUT) ;
	MAX_THREAD= sysconf(_SC_NPROCESSORS_ONLN) ;
	pthread_mutex_init(&lock, NULL) ;

	//read_file 
	FILE *read_int ;
	read_int = fopen("integers_100k.txt","r") ;

	int count=0 ;
	char buff[10] ;

	while(fgets(buff, sizeof(buff), read_int)){
		int num = atoi(buff) ;
		array[count] = num ;
		count++ ;
		if(count >= MAX_INPUT-1) break ;
	}

	printf("TOTAL INT READ FROM FILE  : %d\n", count) ;
	printf("TOTAL CORES IN CPU ARE : %d\n", MAX_THREAD);
	
	struct args *arg = (struct args *)malloc(sizeof(struct args)) ;
	arg ->arr = array ;
	arg->left = 0 ;
	arg->right = count-1 ;

	Threaded_Quick_Sort(arg) ;
	int k=0 ; 
	for(int i=0 ; i<count ; i++){
		printf("%d ", array[i] ) ;
		k++ ;
	}
	printf("\n%d ",k);
	printf("\n") ;

	free(arg) ;

	return 0 ;
}


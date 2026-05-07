#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 100000



int partition(int *arr, int lb, int ub) ;
void Quick_Sort(int *arr, int lb, int ub) ;


int partition(int *arr, int lb, int ub){
	int pivot = arr[lb] ;
	int strt = lb ;
	int end = ub ;

	while(strt < end) {
		//cond 1 : srt will inc only if the arr[srt] <= arr[pivot] ;
		while(arr[strt] <= pivot) {
			strt++ ;
		}

		//cond 2 :decrm of end only if the arr[end] > arr[pivot] ;
		while(arr[end] > pivot ) {
			end-- ;
		}

		if(strt < end){
			int temp = arr[strt] ;
			arr[strt] = arr[end] ;
			arr[end] = temp ;
		}
	}

		//cond 3 : strt > end so came out from the loop ;
		int temp = pivot ;
		arr[lb] = arr[end] ;
		arr[end] = temp ;
		
		//return ;
		return end ;
}


void Thread_Quick_Sort(int *arr, int lb, int ub){
	//using the pivot as the first element // 
	if(lb < ub) {
		int index = partition(arr, lb, ub) ;
		Thread_Quick_Sort(arr, lb, index-1) ;
		Thread_Quick_Sort(arr, index+1, ub) ;
	}
}


int main(){
	/* int *arr ;
	int n ;

	puts("Enter the size of the array") ;
	scanf(" %d",&n) ;


	arr = (int *)malloc(sizeof(int) * n) ;
	
	puts("Enter the array element one by one"); 

	for(int i=0 ; i<n ; i++){
		scanf(" %d",(arr+i)) ;
	}
	*/
	//int arr[59] = {9,8,7,6,5,4,3,2,1,11,12,13,14,15,19,18,171,16,20,21,22,23,24,25,26,29,28,27,30,39//	//	,38,37,36,35,34,33,32,31,40,41,42,43,49,48,47,46,45,44,50,59,58,57,56,55,54,51,53//***,52,60} ;*
	
	int *arr = (int *) malloc(sizeof(int)*MAX_CHAR) ;
	FILE *read = fopen("integers_100k.txt","r") ;
	char str[10] ; 
	int k=0 ;
	
	while(fgets(str, sizeof(str), read)){
		int num = atoi(str) ;
		arr[k] = num ;
		k++ ;
		if(k>=100000) break ;
	}
	
	
	Thread_Quick_Sort(arr, 0, k-1) ;

	printf("Number of the elements sorted out :%d\nArray after the Quick_Sort:\n",k) ;


	for(int i=0 ; i<k ; i++){
		printf("%d ",arr[i]) ; 
	}
	printf("\n");
	return 0 ;
      }

			

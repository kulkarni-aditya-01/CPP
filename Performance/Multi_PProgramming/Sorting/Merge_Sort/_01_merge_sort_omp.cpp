#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define MAX_INPUT 1000001


void merge(int *arr, int left, int mid, int right){
	
	int *temp = (int *)malloc(sizeof(int)*(right-left+1));
	int k=0 ;	
	int i=left; 
	int j=mid+1;
#pragma omp parallel
	{
		 
		while(i<=mid && j<=right){
			if(arr[i] < arr[j]){
				temp[k] = arr[i]; 
				i++ ;
			}
			else{
				temp[k] = arr[j] ;
				j++; 
			}
			k++ ;
		}	
		//#pragma omp 
		while(i<=mid){
			temp[k] = arr[i] ;
			i++; 
			k++; 
		}

		while(j<=right){
			temp[k] = arr[j]; 
			j++; 
			k++ ;
		}
	}
	//now add to the same loop ;
	for(int i=0; i<k ; i++){
		arr[left+i] = temp[i] ;
	}
	free(temp);
	return ;
}


void merge_sort(int *arr, int left, int right){	
	if(left>=right){
		return ; 
	}	
	int mid = (left+right)/2; 
	#pragma omp sections
	{
	#pragma omp section 
	merge_sort(arr, left, mid);
	
	#pragma omp section
	merge_sort(arr, mid+1, right);
	}
	merge(arr, left, mid, right);
		
}


int main(int argc, char *argv[]){
//	int n;
//	std:: cout << "Enter the total number of the elements : " << std::endl; 
//	std:: cin >> n ;

	int *arr = (int *)malloc(MAX_INPUT*sizeof(int));

	FILE *read_int ;
	read_int = fopen(argv[1],"r") ;

	int count=0 ;
	char buff[50] ;

	while(fgets(buff, sizeof(buff), read_int)){
		int num;
		sscanf(buff, "%d", &num);
		arr[count++] = num ;
		if(count >= MAX_INPUT-1) break ;
	}
	fclose(read_int);
	
	merge_sort(arr, 0, count-1);
	
	for(int i=0;i<count;i++){
		std::cout<<arr[i]<<" " ; 
	}
	std::cout<<"\n" ;
	
	free(arr);

	return 0 ;
}


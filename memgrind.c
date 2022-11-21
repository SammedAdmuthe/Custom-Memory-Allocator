#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "umalloc.c"

int maximal_allocation(){
    int last_allocation = 1;
    char* f = (char*)malloc(last_allocation*1);
    int g = 1;
    int count = 0;
    
    if(f!=NULL){
        free(f);
        while(g == 1){
            last_allocation = last_allocation*2;
            f = (char*)malloc(last_allocation);
            if(f!= NULL){
                free(f);
            }else{
                break;
            }
        }
        last_allocation = last_allocation/2;
        count = last_allocation;
        while(count>0){
            f = (char*)malloc(last_allocation+count);
            if(f!=NULL){
                free(f);
                last_allocation = last_allocation+count;
            }else{
                count = count/2;
            }
        }
    }else{
        printf("This should never happen in this test case\n");
    }
    return last_allocation;
}

void basicCoalescence(int last_allocation){
    //Basic Coalescence
   int last_allocation_ref = last_allocation/2;
   char* test_2 = (char*)malloc(last_allocation_ref);
   if(test_2!=NULL){
   	char* test_2_q = (char*)malloc(last_allocation/4);
   	if(test_2_q!=NULL){   		
   		free(test_2);
   		free(test_2_q);
   		char* test_2_f = (char*)malloc(last_allocation);
   		if(test_2_f!=NULL){
   			free(test_2_f);
   			printf("Basic Coalescence test success\n");
   		}else{
   			printf("Basic Coalescence test Failure\n");   		
   		}
   	}else{
   		printf("Failure allocating quarter of maximal allocation\n");   	
   	}
   }else{
   	printf("Failure allocating half of the maximal allocation!\n");
   }
}

int saturation(int* arr[]){
    struct timespec beginTimer, endTimer;
    int k = 0;
    for(k = 0 ; k < 9216 ; k++){
        arr[k]= (int*)malloc(1024*sizeof(char));
    }
    while((arr[k] = (int*)malloc(sizeof(char))) != NULL) {
        k++;
    }
    return k;
}

void timeOverhead(int* arr[],int k){
    //Time Overhead
    struct timespec beginTimer, endTimer;
    free(arr[k-1]);
    clock_gettime(CLOCK_MONOTONIC, &beginTimer);
    arr[k-1] = (int*)malloc(sizeof(char));
    clock_gettime(CLOCK_MONOTONIC, &endTimer);
    printf("\nTime for 1B allocation in saturated mem : %ld \n", endTimer.tv_nsec - beginTimer.tv_nsec);
}

void intermediateCoalescence(int* arr[],int k,int maximalAllocation){
    //Intermediate Coalescence
    for(int e = 0; e < k ; e++){
        free(arr[e]);
    }
    char* final_allocation = (char*)malloc(maximalAllocation);
    if(final_allocation!=NULL){
        printf("Intermediate Coalescence Test Success!\n");   
        free(final_allocation);
    }else{
        printf("Intermediate Coalescence Test Failure!\n");
    }
    return ;
}

void consistency(){
    char* first_allocation = (char*)malloc(1);
    first_allocation[0] = 'a';
    free(first_allocation);
    char* second_allocation = (char*)malloc(1);
    free(second_allocation);
    if(first_allocation!=second_allocation){
        printf("Consistency test FAIL!\n");
    }else{
        printf("Consistency test PASS!\n");
    }
    return;
}
int main(){
    // char* a = (char*)malloc('a');
    //     printMetadata();

    // // printf("Allocation = %p", a);
    // free(a);
    // free(a);
    // consistency();
    int maxAllocation = maximal_allocation();
    printf("Maximal allocation is %d\n",maxAllocation);
    // basicCoalescence(maxAllocation);
    // int* arr[118000];
    // int k = saturation(arr);
    
    // timeOverhead(arr,k);
    // intermediateCoalescence(arr,k,maxAllocation);
}
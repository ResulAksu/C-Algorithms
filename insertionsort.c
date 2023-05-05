#include <stdio.h>

void insertion_sort(int A[], int n){

 for (int i = 1; i < n; i++) {
     int j = i;
     while(j>0 && A[j-1] > A[j]){
         int temp = A[j-1];
         A[j-1] = A[j];
         A[j] = temp;
         j = j-1;
     }
 }
}

int main(void) {
  int n;
  scanf("%d",&n);
  
  int input[n];
  for(int i=0; i<n; ++i){
      scanf("%d", &input[i]);
  }
  
  insertion_sort(input,n);
  
  //Print Array
  for (int i = 0; i < n; i++) {
      printf("%d ", input[i]);
  }
  printf("\n");
 
  return 0;
}

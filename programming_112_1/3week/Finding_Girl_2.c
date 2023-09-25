#include<stdio.h>
#include<stdlib.h>
#define MAX 100009


int arr[MAX][2] = { 0 };


signed main(){
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    int num;
    scanf("%d", &num);
    arr[num % MAX][0]++;
    arr[num % MAX][1] = num / MAX;
  }
  for(int i = 0; i < MAX; i++){
    if(arr[i][0] == 1){
      printf("%d\n", arr[i][1] * MAX + i);
      return 0;
    }
  }
  return 0;
}
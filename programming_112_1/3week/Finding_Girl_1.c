#include<stdio.h>
#include<stdlib.h>
#define int long long

signed main(){
  int *arr = (int*)malloc(sizeof(int) * 1000005);
  int n, count = 0, index;
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    scanf("%d", &arr[i]);
  }
  for(int i = 1; i < n; i++){
    if(arr[i] != arr[i - 1]){
      count++;
      index = i - 1;
    }
  }

  if(count == 1 && index == n - 2) printf("%d\n", arr[n - 1]);
  else printf("%d\n", arr[index]);

  return 0;
}
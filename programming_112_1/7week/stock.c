#include<stdio.h>
#include<stdlib.h>
#define int long long

signed main(){
  int n, count;
  int arr[12];
  scanf("%lld", &n);
  int t = n;
  for(int i = 0; i < 12; i++){
    scanf("%lld", &arr[i]);
  }
  for(int i = 1; i < 12; i++){
    if(arr[i] > arr[i - 1]){
      n = n * arr[i] / arr[i - 1];
    }
  }
  printf("%lld\n", n - t);
  return 0;
}
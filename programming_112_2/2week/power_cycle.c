#include<stdio.h>
#define int long long

int arr[32][100005];

int max(int a, int b){
  if(a > b) return a;
  return b;
}

int min(int a, int b){
  if(a < b) return a;
  return b;
}

signed main(){
  int n, idx = 1, temp;
  scanf("%lld", &n);
  temp = n;
  for(int i = 0; i < n; i++) scanf("%lld", &arr[0][i]);

  while(1){
    if(n == 1) break;
    for(int i = 1; i < n; i += 2){
      if(idx % 2 == 1) arr[idx][i / 2] = max(arr[idx - 1][i], arr[idx - 1][i - 1]);
      else arr[idx][i / 2] = min(arr[idx - 1][i], arr[idx - 1][i - 1]);
    }
    if(n % 2 == 1) arr[idx][n / 2] = arr[idx - 1][n - 1];
    n = (n + 1) / 2;
    idx++;
  }
  
  if(idx % 2 == 0) printf("%lld\n", arr[idx - 1][0]);
  else{
    n = temp, idx = 1;
    while(1){
      if(n == 1) break;
      for(int i = 1; i < n; i += 2){
        if(idx % 2 == 1) arr[idx][i / 2] = min(arr[idx - 1][i], arr[idx - 1][i - 1]);
        else arr[idx][i / 2] = max(arr[idx - 1][i], arr[idx - 1][i - 1]);
      }
      if(n % 2 == 1) arr[idx][n / 2] = arr[idx - 1][n - 1];
      n = (n + 1) / 2;
      idx++;
    }
    printf("%lld\n", arr[idx - 1][0]);
  }
}
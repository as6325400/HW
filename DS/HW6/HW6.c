#include<stdio.h>
#include<stdlib.h>
#define int long long

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

signed main(){

  int p1, p2, p3, p4;
  scanf("%lld %lld %lld %lld", &p1, &p2, &p3, &p4);

  int n = p1 / 10;

  int index[10] = {0};

  int arr[10][n];

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < n; j++){
      scanf("%lld", &arr[i][j]);
    }
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n - j - 1; k++){
        if(arr[i][k] > arr[i][k + 1]) swap(&arr[i][k], &arr[i][k + 1]);
      }
    }
    printf("%lld", arr[i][p2 - 1]);
    if(i != 9) printf(", ");
  }
  printf("\n");

  int end;
  scanf("%lld", &end);

  for(int i = 0; i < p1; i++){

    int mm = (int)1e18, idx;

    for(int j = 0; j < 10; j++){
      if(index[j] != n && arr[j][index[j]] < mm){
        mm = arr[j][index[j]];
        idx = j;
      }
    }

    index[idx]++;
    
    if(i >= p3 - 1 && i < p4){
      printf("%lld", mm);
      if(i != p4 - 1) printf(", ");
      else printf("\n");
    }

  }

  return 0;
}
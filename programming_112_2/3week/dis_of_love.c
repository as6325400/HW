#include<stdio.h>
#include <stdbool.h>
#define int long long

int ans = 0, n, k;

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void permutation(int arr[11], int begin, int end) {
    int i;
    if(begin == end) {
      int count = 0;
      for(i = 1; i <= end; ++i) {
          if(arr[i - 1] > arr[i]) count++;
      }
      if(count <= k) ans++;
    }
    else {
        for(i = begin; i <= end; ++i) {
            swap(&arr[i], &arr[begin]);
            permutation(arr, begin + 1, end);
            swap(&arr[i], &arr[begin]);
        }
    }
}

signed main(){
  
  scanf("%lld %lld", &n, &k);
  int arr[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  permutation(arr, 0, n - 1);
  printf("%lld\n", ans);
}
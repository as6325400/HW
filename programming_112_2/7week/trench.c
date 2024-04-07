/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

long long height[100005];
long long length[100005];

int compare(const void *a, const void *b){
  long long va = *((long long*)a);
  long long vb = *((long long*)b);
  return (int)(va - vb);
}

signed main(){
  
  long long n, m, step;
  scanf("%lld %lld", &n, &m);
  
  // 先讀入所有的高度
  for(long long i = 0; i < n; i++){
    scanf("%lld", &height[i]);
  }
  
  // 然後計算相鄰高度的差異
  for(long long i = 0; i < n - 1; i++){
    height[i] = -(height[i + 1] - height[i]);
  }
  
  // printf("-------------------\n");
  // for(long longi = 0; i < n - 1; i++)
  // {
  //   printf("%d ", height[i]);
  // }
  // printf("\n");
  // printf("-------------------\n");
  for(long long i = 0; i < m; i++){
    scanf("%lld", &length[i]);
  }
  
  qsort((void *)length, m, sizeof(long long), compare);
  // printf("-------------------\n");
  // for(long longi = 0; i < m; i++)
  // {
  //   printf("%d ", length[i]);
  // }
  // printf("\n");
  // printf("-------------------\n");
  long long i = 0, j = 0, ans = 0;
  while(i < n - 1 && j < m){
    if(length[j] >= height[i]){
      j++;
      i++;
      ans++;
    }
    else j++;
  }
  printf("%lld\n", ans + 1);
}
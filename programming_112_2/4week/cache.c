#include<stdio.h>

int cache[2000050];

int main(){
  int n;
  scanf("%d", &n);
  int num, start = 0, end = -1;
  while(scanf("%d", &num) != EOF){
    int len = end - start + 1;
    cache[++end] = num;
    if(len >= n) start++;
  }
  for(int i = start; i <= end; i++){
    printf("%d ", cache[i]);
  }
  printf("\n");
}
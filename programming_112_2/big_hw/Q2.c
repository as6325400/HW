#include<stdio.h>
#include<stdlib.h>

unsigned int MurmurOAAT32(char *key){
  unsigned int h = 3323198485u;
  for (; *key; ++key){
  h ^= *key;
  h *= 0x5bd1e995;
  h ^= h >> 15;
  }
  return h;
}

unsigned int arr[50][100005];
int height[50];

signed main(){
  int n, start;
  char *str = (char*)malloc(sizeof(char) * 105);
  scanf("%d", &n);
  height[49] = n;
  for(int i = 0; i < n; i++){
    scanf("%s", str);
    arr[49][i] = MurmurOAAT32(str);
  }
  if(height[49] % 2 == 1) arr[49][height[49]] = arr[49][height[49] - 1];
  for(int i = 48; i >= 0; i--){
    height[i] = (height[i + 1] + 1) / 2;
    for(int j = 0; j < height[i]; j++){
      char *a = (char*)malloc(sizeof(char) * 105);
      char *b = (char*)malloc(sizeof(char) * 105);
      sprintf(a, "%u", arr[i + 1][j * 2] + arr[i + 1][(j * 2) + 1]);
      arr[i][j] = MurmurOAAT32(a);
    }
    if(height[i] == 1){
      start = i;
      break;
    }
    if(height[i] % 2 == 1) arr[i][height[i]] = arr[i][height[i] - 1];
  }
  for(int i = start; i < 50; i++){
    for(int j = 0; j < height[i]; j++){
      printf ("%15lu" , arr[i][j]);
    }
    printf("\n");
  }
}
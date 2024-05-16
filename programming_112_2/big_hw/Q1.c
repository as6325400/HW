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

signed main(){
  char *a = (char*)malloc(sizeof(char) * 105);
  char *b = (char*)malloc(sizeof(char) * 105);
  scanf("%s %s", a, b);
  char *ans = (char*)malloc(sizeof(char) * 105);
  sprintf(ans, "%u", MurmurOAAT32(a) + MurmurOAAT32(b));
  printf("%u", MurmurOAAT32(ans));
}
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

static int myCompare(const void* a, const void* b) 
{ 
  return strcmp(*(const char**)a, *(const char**)b); 
} 

void sort(char** arr, int n) 
{ 
  qsort(arr, n, sizeof(const char*), myCompare); 
} 

int main() 
{ 
  char **name = (char**)malloc(sizeof(char*) * 1005);
  for(int i = 0; i < 1004; i++){
    name[i] = (char*)malloc(sizeof(char) * 25);
  }

  int index = 0;

  while(scanf("%s", name[index++]) != EOF) {}

  sort(name, index);

  for(int i = 0; i < index; i++){
    printf("%s\n", name[i]);
  }
} 
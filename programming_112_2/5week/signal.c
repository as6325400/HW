/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<stdio.h>
#include<string.h>
#define int long long

int t = 0;

char arr[100000];

void push(char c){
  arr[t++] = c;
}

void pop(){
  t--;
}

int size(){
  return t;
}

char top(){
  return arr[t - 1];
}


signed main(){
  char s[1000];
  scanf("%s", s);
  int len = strlen(s);
  for(int i = 0; i < len; i++){
    if(size() != 0 && s[i] == top()) pop();
    else push(s[i]);
  }
  len = size();
  while(size() != 0)
  {
    s[size() - 1] = top(); 
    pop();
  }
  for(int i = 0; i < len; i++){
    printf("%c", s[i]);
  }
  printf("\n");
  
}
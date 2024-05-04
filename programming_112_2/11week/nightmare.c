#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long

struct stack{
  char *arr;
  int size;
  int back;
}typedef stack;

stack* init(){
  stack* s = (stack*)malloc(sizeof(stack));
  s->arr = (char*)malloc(sizeof(char)*10005);
  s->size = 0;
  s->back = 0;
  return s;
}

void push(stack* s, char val){
  s->arr[s->size++] = val;
}

void pop(stack* s){
  s->size--;
}

char top(stack* s){
  return s->arr[s->size - 1];
}

signed main(){
  char *s = (char*)malloc(sizeof(char)*10005);
  scanf("%s", s);
  int len = strlen(s);
  stack* st = init();
  for(int i = 0; i < len; i++){
    if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
      push(st, s[i]);
    }
    else{
      if(st -> size == 0){
        printf("%c", s[i]);
      }
      else{
        printf("%c", s[i]);
        printf("%c", top(st));
        pop(st);
      }
    }
  }
}
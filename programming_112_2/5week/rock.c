/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define int long long

struct stack {
  int val;
  struct stack *nxt;
} typedef stack;   

bool empty(stack *ptr){
  if(ptr -> nxt == NULL) return 1;
  return 0;
}

void push(stack **ptr, int c){
  stack *tmp = (stack*)malloc(sizeof(stack));
  tmp -> nxt = (*ptr) -> nxt;
  tmp -> val = c;
  (*ptr) -> nxt = tmp;
}

void pop(stack **ptr){
  if(empty(*ptr)) return;
  stack *tmp = (*ptr) -> nxt;
  (*ptr) -> nxt = tmp -> nxt;
  free(tmp);
}

int top(stack *ptr){
  return ptr -> nxt -> val;
}

stack **arr;

void insert_number(int num, int index){
  while(!empty(arr[index]) && top(arr[index]) < num)
  {
    int temp = top(arr[index]);
    pop(&arr[index]);
    insert_number(temp, index + 1);
  }
  push(&arr[index], num);
}

signed main(){
  int n;
  scanf("%lld", &n);
  arr = (stack**)malloc(sizeof(stack*) * (n + 5));
  for(int i = 0; i <= n; i++) arr[i] = (stack*)malloc(sizeof(stack));
  for(int i = 0; i < n; i++)
  { 
    int num;
    scanf("%lld", &num);
    insert_number(num, 0);
  }
  for(int i = 0; i < n + 5; i++)
  {
    if(empty(arr[i])){
      printf("%lld\n", i);
      break;
    }
  }
}
#include<stdio.h>
#include<stdlib.h>
#define int long long

typedef struct stack{
  int *arr;
  int len;
  int capicity;
}stack;

int max(int a, int b){
  return a > b ? a : b;
}

void stackInit(stack *ptr){
  ptr -> arr = (int*)malloc(sizeof(int) * 4);
  ptr -> len = 0;
  ptr -> capicity = 4;
}

void push(stack *ptr, int num){
  if(ptr -> len * 2 > ptr -> capicity){
    ptr -> capicity *= 2;
    int *arr = (int*)malloc(sizeof(int) * ptr -> capicity);
    for(int i = 0; i < ptr -> len; i++){
      arr[i] = ptr -> arr[i];
    }
    free(ptr -> arr);
    ptr -> arr = arr;
  }
  ptr -> arr[ptr -> len++] = num;
}

void pop(stack *ptr){
  if(ptr -> len <= 0) return;
  ptr -> len--;
  return;
}

int back(stack *ptr){
  return ptr -> arr[ptr -> len - 1];
}

void clear(stack *ptr){
  stackInit(ptr);
}

signed main(){

  int n;
  int arr[1005];
  int dp[1005];
  int dpr[1005];
  stack s;

  stackInit(&s);

  scanf("%lld", &n);

  for(int i = 0; i < n; i++){

    scanf("%lld", &arr[i]);

    while(s.len != 0 && arr[back(&s)] >= arr[i]) pop(&s);

    if(s.len == 0) dp[i] = arr[i] * (i + 1);
    else dp[i] = arr[i] * (i - back(&s));

    push(&s, i);
  }

  clear(&s);

  for(int i = n - 1; i >= 0; i--){

    while(s.len != 0 && arr[back(&s)] >= arr[i]) pop(&s);

    if(s.len == 0) dpr[i] = arr[i] * (n - i);
    else dpr[i] = arr[i] * (back(&s) - i);

    push(&s, i);
  }

  int ans = -1e9;
  
  for(int i = 0; i < n; i++) ans = max(ans, dp[i] + dpr[i] - arr[i]);

  printf("%lld\n", ans);

  return 0;
}
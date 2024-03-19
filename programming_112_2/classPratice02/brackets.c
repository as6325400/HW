#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define int long long

struct stack {
  char val;
  struct stack *nxt;
} typedef stack;   

bool empty(stack *ptr){
  if(ptr -> nxt == NULL) return 1;
  return 0;
}

void push(stack **ptr, char c){
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

char top(stack *ptr){
  return ptr -> nxt -> val;
}

char rv(char a){
  if(a == '}') return '{';
  if(a == ']') return '[';
  if(a == ')') return '(';
  if(a == '>') return '<';
  return '#';
}

bool is_signal(char a){
  if(a == '{' || a == '[' || a == '(' || a == '<') return 1;
  if(a == '}' || a == ']' || a == ')' || a == '>') return 1;
  return 0;
}


bool isValid(char * s){
  int num = strlen(s);
  stack *ss = (stack*)malloc(sizeof(stack));
  ss -> nxt = NULL;
  for(int i = 0; i < num; i++){
    if(!is_signal(s[i])) continue;
    if(!empty(ss) && rv(s[i]) == top(ss)) pop(&ss);
    else push(&ss, s[i]);
  }
  return empty(ss);
}


void solve(){
  char *s = (char*)malloc(sizeof(char) * 100000);
  fgets(s, 100000, stdin);
  s[strcspn(s, "\n")] = '\0'; // remove '\n' from s[strlen(s) - 1
  printf("%s\n", isValid(s) == 1 ? "T" : "F");
}


signed main(){
  int t;
  scanf("%lld", &t);
  getchar();
  while(t--){
    solve(); 
  }
}
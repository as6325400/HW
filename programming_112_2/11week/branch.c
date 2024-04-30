#include<stdio.h>
#include<stdlib.h>
#define int long long

int max_depth = -1e9;
int leaf_node;

struct vector{
  int *arr;
  int size;
  int cap;
}typedef vector;

vector* init(){
  vector* v = (vector*)malloc(sizeof(vector));
  v->arr = (int*)malloc(sizeof(int)*2);
  v->size = 0;
  v->cap = 2;
  return v;
}

void push_back(vector* v, int val){
  if(v->size == v->cap){
    v->cap *= 2;
    v->arr = (int*)realloc(v->arr, sizeof(int)*v->cap);
  }
  v->arr[v->size++] = val;
}

void dfs(vector** v, int* visited, int cur, int depth){
  if(depth > max_depth){
    max_depth = depth;
    leaf_node = cur;
  }
  visited[cur] = 1;
  for(int i = 0; i < v[cur]->size; i++){
    if(!visited[v[cur]->arr[i]]){
      dfs(v, visited, v[cur]->arr[i], depth + 1);
    }
  }
}

signed main(){
  int n;
  scanf("%lld", &n);
  vector** v = (vector**)malloc(sizeof(vector*)*n);
  for(int i = 0; i < n; i++){
    v[i] = init();
  }
  for(int i = 0; i < n - 1; i++){
    int a, b;
    scanf("%lld %lld", &a, &b);
    push_back(v[a], b);
    push_back(v[b], a);
  }
  dfs(v, (int*)calloc(n, sizeof(int)), 0, 0);
  max_depth = -1e9;
  dfs(v, (int*)calloc(n, sizeof(int)), leaf_node, 0);
  printf("%lld", max_depth);
}
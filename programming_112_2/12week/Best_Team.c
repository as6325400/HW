#include<stdio.h>
#include<stdlib.h>
#define int long long

int nums[10005];

struct vector{
  int *arr;
  int size;
  int capacity;
}typedef vector;

vector *new_vector(){
  vector *v = (vector*)malloc(sizeof(vector));
  v->size = 0;
  v->capacity = 32;
  v->arr = (int*)malloc(sizeof(int) * v->capacity);
  return v;
}

void push_back(vector *v, int val){
  if(v->size == v->capacity){
    v->capacity *= 2;
    v->arr = (int*)realloc(v->arr, sizeof(int) * v->capacity);
  }
  v->arr[v->size++] = val;
}

int size(vector *v){
  return v->size;
}

void dfs(vector **tree, int *visited, int u){
  visited[u] = 1;
  nums[u] = 1;
  if(size(tree[u]) == 0){
    return;
  }
  for(int i = 0; i < size(tree[u]); i++){
    int v = tree[u]->arr[i];
    if(visited[v] == 0){
      dfs(tree, visited, v);
    }
    nums[u] += nums[v];
  }
}

signed main(){
  int n, q;
  scanf("%lld %lld", &n, &q);
  vector **tree = (vector**)malloc(sizeof(vector*) * (n + 1));
  for(int i = 0; i < n; i++){
    tree[i] = new_vector();
  }
  for(int i = 0; i < n - 1; i++){
    int u, v;
    scanf("%lld %lld", &u, &v);
    push_back(tree[u], v);
  }
  int *visited = (int*)malloc(sizeof(int) * (n + 1));
  for(int i = 0; i <= n; i++){
    visited[i] = 0;
  }
  dfs(tree, visited, 0);
  // printf("---------------------\n");
  // for(int i = 0; i < n; i++){
  //   printf("%lld ", nums[i]);
  // }
  // printf("\n---------------------\n");
  for(int i = 0; i < q; i++){
    int x;
    scanf("%lld", &x);
    printf("%lld\n", nums[x]);
  }
}
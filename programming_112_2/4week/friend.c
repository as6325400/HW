#include<stdio.h>
#define int long long

int n;
int arr[200005];

int find(int num){
  for(int i = 0; i < n; i++){
    if(arr[i] == num) return i;
  }
  return 1e9;
}

void remove_left(int idx, int dis){
  int count = 0;
  for(int i = idx - 1; i >= 0; i--){
    if(arr[i] != (int)2e18) count++;
    if(count == dis){
      arr[i] = (int)2e18;
      break;
    }
  }
  arr[idx] = (int)2e18;
}

void remove_right(int idx, int dis){
  int count = 0;
  for(int i = idx + 1; i < n; i++){
    if(arr[i] != (int)2e18) count++;
    if(count == dis){
      arr[i] = (int)2e18;
      break;
    }
  }
  arr[idx] = (int)2e18;
}

int left(int idx, int dis, int id, int ran){
  int count = 0;
  int oi = idx;
  while(idx >= 0 && count < dis + 1){
    if(arr[idx] <= id + ran && arr[idx] >= id - ran && idx != oi){
      return count;
    }
    if(arr[idx] == (int)2e18) count--;
    idx--;
    count++;
  }
  return 1e9;
}

int right(int idx, int dis, int id, int ran){
  int count = 0;
  int oi = idx;
  while(idx < n && count < dis + 1){
    if(arr[idx] <= id + ran && arr[idx] >= id - ran && idx != oi){
      return count;
    } 
    if(arr[idx] == (int)2e18) count--;
    idx++;
    count++;
  }
  return 1e9;
}

signed main(){
  scanf("%lld", &n);
  for(int i = 0; i < n; i++) scanf("%lld", &arr[i]);
  int id, dis, range;
  while(scanf("%lld %lld %lld", &id, &dis, &range) != EOF){
    int idx = find(id);
    if(idx == (int)1e9) continue;
    int l = left(idx, dis, id, range);
    int r = right(idx, dis, id, range);
    if(l == (int)1e9 && r == (int)1e9) continue;
    if(l <= r) remove_left(idx, l);
    else remove_right(idx, r);
  }
  int count = 0;
  for(int i = 0; i < n; i++){
    if(arr[i] == (int)2e18) continue;
    else{
      printf("%lld ", arr[i]);
      count++;
    }
  }
  printf("\n");
  if(count == 0) printf("Wonderful\n");
}
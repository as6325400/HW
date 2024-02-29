#include<stdio.h>
#include<stdlib.h>
#include <time.h>   

int arr1[100000];
int arr2[100000];

signed main(){
  int n, m, idx = 0;
  int ans[2];
  scanf("%d %d", &n, &m);
  for(int i = 0; i < n; i++) scanf("%d", &arr1[i]);
  for(int i = 0; i < m; i++) scanf("%d", &arr2[i]);

  for(int i = 0; i < n; i++){
    int target = arr1[i], left = 0, right = m - 1;

    while(left <= right)
    {
      int mid = (left + right) / 2;
      if(arr2[mid] < target) left = mid + 1;
      else if(arr2[mid] > target) right = mid - 1;
      else if(arr2[mid] == target){
        // printf("mid: %d target: %d\n", mid, target);
        ans[idx++] = arr2[mid];
        break;
      }
    }

  }
  // printf("idx: %d\n", idx);
  if(idx != 2) printf("-1\n");
  else{
    if(ans[1] % ans[0] == 0) printf("%d %d\n", ans[0], ans[1]);
    else printf("-1\n");
  }
  

}
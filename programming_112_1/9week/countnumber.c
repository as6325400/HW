#include<stdio.h>
#define int long long

int arr[100005];

signed main(){
  int n, q;
  scanf("%lld%lld", &n, &q);
  for(int i = 0; i < n; i++){
    scanf("%lld", &arr[i]);
  }
  for(int i = 0; i < q; i++){
    int num;
    scanf("%lld", &num);
    int left = 0, right = n - 1;
    while(left <= right){
      int mid = left + right >> 1;
      if(arr[mid] >= num) right = mid - 1;
      else left = mid + 1;
    }
    if(arr[left] == num) printf("%lld\n", left);
    else printf("-1\n");
  }
}
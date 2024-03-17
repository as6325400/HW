#include<stdio.h>
#define int long long

int dp[100005];

signed main(){
  int n;
  scanf("%lld", &n);
  for(int i = 1; i <= n; i++)
  {
    int num;
    scanf("%lld", &num);
    dp[i] = dp[i - 1] + num;
  }
  int q;
  scanf("%lld", &q);

  for(int i = 0; i < q; i++){
    int t, m, ans = 0;
    scanf("%lld %lld", &t, &m);
    int left = t, right = n - 1;
    while(left <= right){
      int mid = (left + right) / 2;
      if(dp[mid + 1] - dp[t] <= m){
        ans = mid + 1 - t;
        left = mid + 1;
      }
      else right = mid - 1;
    }
    printf("%lld\n", ans);
  }
}
#include <stdio.h>
#define int long long


signed main()
{
  int n, x, y;
  scanf("%d%d%d", &n, &x, &y);
  int month = (n - x) / y;
  if((n - x) % y != 0) month++;
  if(month <= 12) printf("%d\n", month);
  else printf("-1\n");
}
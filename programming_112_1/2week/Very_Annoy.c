#include<stdio.h>
#define int long long

signed main()
{
  double price = 400;
  int g, s, y, j;
  scanf("%d%d%d%d", &g, &s, &y, &j);
  if(s == 0)
  {
    printf("100\n");
    return 0;
  }
  price -= ((g - 1) * 100 + j * 50);
  if(y == 1)
  {
    price *= (1.0 - g * 0.1);
  }
  printf("%ld\n", (int)price);
}
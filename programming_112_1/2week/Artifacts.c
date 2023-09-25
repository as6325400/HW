#include<stdio.h>
#define int long long

signed main(){
  double a, r, d;
  scanf("%lf%lf%lf", &a, &r, &d);
  double score = a * 1.3 + r * 2 + d;
  printf("%.1lf ", score);
  if(score < 20.0)
  {
    printf("Failed\n");
  }
  else if(score >= 20.0 && score < 30)
  {
    printf("Good\n");
  }
  else if(score >= 30.0 && score < 40)
  {
    printf("Wonderful\n");
  }
  else
  {
    printf("Be careful when going out\n");
  }
}
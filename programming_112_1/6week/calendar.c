#include<stdio.h>
#include<stdlib.h>
#define int long long

int judge(int year){
  if(year % 4 == 0 && year % 100 != 0) return 1;
  if(year % 400 == 0) return 1;
  return 0;
}

signed main(){
  int y1, y2, m1, m2, d1, d2;
  int month1[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int month2[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  while(scanf("%lld%lld%lld%lld%lld%lld", &y1, &m1, &d1, &y2, &m2, &d2) != EOF){
    int day1 = 0, day2 = 0;
    for(int i = 1; i < y1; i++) day1 += judge(i) ? 366 : 365;
    for(int i = 1; i < y2; i++) day2 += judge(i) ? 366 : 365;
    if(!judge(y1)) for(int i = 1; i < m1; i++) day1 += month1[i];
    if(!judge(y2)) for(int i = 1; i < m2; i++) day2 += month1[i];
    if(judge(y1)) for(int i = 1; i < m1; i++) day1 += month2[i];
    if(judge(y2)) for(int i = 1; i < m2; i++) day2 += month2[i];
    day1 += d1;
    day2 += d2;
    printf("%lld\n", day2 - day1);
  }
  return 0;
}
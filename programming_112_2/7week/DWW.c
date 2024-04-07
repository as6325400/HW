/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define int long long


int times[100005];
int nums[1000005][2];

signed main()
{
  int n, m;
  scanf("%lld %lld", &n, &m);
  for(int i = 0; i < n; i++){
    int id;
    scanf("%lld", &id);
    times[id]++;
  }
  for(int i = 1; i <= 100000; i++){
    if(nums[times[i]][0] == 0) nums[times[i]][0] = i;
    else nums[times[i]][1] = i;
  }
  for(int i = 0; i < m; i++){
    int q;
    scanf("%lld", &q);
    if(nums[q][0] == 0) printf("-1\n");
    else if(nums[q][0] != 0 && nums[q][1] == 0) printf("%lld %lld\n", nums[q][0], nums[q][0]);
    else printf("%lld %lld\n", nums[q][0], nums[q][1]);
  }
}

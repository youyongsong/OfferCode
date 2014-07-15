#include <stdio.h>
 
long long countNum(int);
 
int main(int argc, char** argv)
{
    int num;
 
    while(scanf("%d", &num) != EOF)
        printf("%lld\n", countNum(num));
}
 
long long countNum(int n)
{
    long long count[51] = {0, 1, 2};
 
    for(int i = 3; i <= n; i++){
      for(int j = 1; j < i; j++){
        count[i] += count[j];
      }
      count[i] ++;
    }
 
    return count[n];
}
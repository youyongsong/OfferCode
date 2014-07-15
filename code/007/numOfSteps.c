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
    if(n <= 2)
        return n;
 
    long long countNMinusOne = 2;
    long long countNMinusTwo = 1;
    long long countN = 0;
    for(int i = 3; i <= n; i++){
      countN = countNMinusOne + countNMinusTwo;
      countNMinusTwo = countNMinusOne;
      countNMinusOne = countN;
    }
 
    return countN;
}
#include <stdio.h>
 
long long fabonacci(int);
 
int main(int argc, char** argv)
{
    int num;
 
    while(scanf("%d", &num) != EOF)
        printf("%lld\n", fabonacci(num));
}
 
long long fabonacci(int n)
{
    if(n <= 1)
        return n;
 
    long long fibNMinusOne = 1;
    long long fibNMinusTwo = 0;
    long long fibN = 0;
    for(int i = 2; i <= n; i++){
      fibN = fibNMinusOne + fibNMinusTwo;
      fibNMinusTwo = fibNMinusOne;
      fibNMinusOne = fibN;
    }
 
    return fibN;
}
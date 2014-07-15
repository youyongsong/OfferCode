#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double Power(double base, int exponent);
double PowerWithUnsignedExponent(double base, int exponent);
double PowerWithUnsignedExponent2(double base, int exponent);
bool equal(double num1, double num2);

bool g_InvalidInput;

int main()
{
  int t(0);
  double base;
  int exponent;
  double result;
  scanf("%d", &t);

  for(int i = 0; i < t; i++){
    scanf("%lf%d", &base, &exponent);    //double类型需要用%lf输入
    result = Power(base, exponent);
    if(g_InvalidInput)
      printf("INF\n");
    else
      printf("%.2ef\n", result);         //%.2e保留2位精度的浮点数
  }
}

double Power(double base, int exponent)
{
  g_InvalidInput = false;
  double result = 1.0;

  if(equal(base, 0.0) && (exponent < 0)){
    g_InvalidInput = true;
    return 0.0;
  }

  unsigned int absExponent = (unsigned int) exponent;
  if(exponent < 0)
    absExponent = (unsigned int) -exponent;

  //result = PowerWithUnsignedExponent(base, absExponent);
  result = PowerWithUnsignedExponent2(base, absExponent);

  if(exponent < 0)
    result = 1.0/result;

  return result;
}

//循环的方法，时间复杂度O(n)
double PowerWithUnsignedExponent(double base, int exponent)
{
  double result = 1.0;

  for(int i = 0; i < exponent; i++)
    result *= base;

  return result;
}

//递归的方法，时间复杂度O(logn)
/*
 * a^n = a^(n/2) * a^(n/2)  n为偶数
 *     = a^((n-1）/2) * a^((n-1)/2) * a n为奇数
 * */
double PowerWithUnsignedExponent2(double base, int exponent)
{
  double result = 1.0;

  if(exponent == 0)
    return 1.0;
  if(exponent == 1)
    return base;

  result = PowerWithUnsignedExponent2(base, exponent >> 1);  //exponent左移1，相当于整除2
  result *= result;
  if(exponent & 0x1 == 1)  //exponent为奇数
    result *= base;

  return result;
}

bool equal(double num1, double num2)
{
  if((num1 - num2 < 0.0000001)
      && (num1 - num2 > -0.0000001))
    return true;
  else
    return false;
}

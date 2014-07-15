#include <stdio.h>
#include <stdlib.h>

int numOf1(int num);
int numOf1_2(int num);
int numOf1_3(int num);

int main()
{
  int t, n;
  scanf("%d", &t);

  while(t--){
    scanf("%d", &n);
    printf("%d\n", numOf1_3(n));
  }
}


/*
 * 解法一： 如果是是负数，则把其最高位拉低并使计数+1*/
int numOf1(int num)
{
  int count = 0;
  if(num < 0){
    //把num的最高位拉低
    unsigned int temp = 1<<(sizeof(num)*8 - 1);
    temp = ~temp;
    num &= temp;

    count++;
  }

  while(num){
    if(num & 1)
      count++;
    num = num >> 1;
  }

  return count;
}

/*
 * 解法二： 不右移输入数字，左移掩码*/
int numOf1_2(int num)
{
  int count = 0;
  unsigned int mask = 1;

  while(mask){
    if(num & mask)
      count++;
    mask = mask << 1;
  }

  return count;
}

/*
 * 解法三： 有数学规律推导出的算法*/
int numOf1_3(int num)
{
  int count = 0;

  while(num){
    count ++;
    num = (num - 1) & num;
  }

  return count;
}
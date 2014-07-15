#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Print1ToMaxOfNDigits(int);
bool Increase(char*);
void PrintCharNum(char*);
void PrintCharRecursively(int);
void PrintRecursivelyCore(char*, int, int);


int main()
{
  int n;
  scanf("%d", &n);

  //方法一：字符串模拟加法
  Print1ToMaxOfNDigits(n);
  //方法二：递归全排列数字
  //由于最后多出一个回车，所以不能通过九度的onlineJudge
  //PrintCharRecursively(n);

  return 0;
}

void Print1ToMaxOfNDigits(int n)
{
  if(n <= 0)
    return;

  char *number = (char*)malloc(n+1);
  memset(number, 0, n+1);
  memset(number, '0', n);

  while(!Increase(number)){
    PrintCharNum(number);
    printf("\n");
  }

  free((void*) number);
}

bool Increase(char *number)
{
  bool isOverFlow = false;
  int nTakeOver = 0;  //进位
  int nlen = strlen(number);

  for(int i = nlen-1; i >= 0; i--){
    int nSum = number[i] - '0' + nTakeOver;

    if(i == nlen-1)
      nSum++;

    if(nSum >= 10){
      if(i == 0)
        isOverFlow = true;

      nSum -= 10;
      nTakeOver = 1;
      number[i] = '0' + nSum;
    }
    else{
      number[i] = '0' + nSum;
      break;
    }
  }

  return isOverFlow;
}

void PrintCharNum(char *number)
{
  bool isBeginning0 = true;
  int nlen = strlen(number);

  for(int i = 0; i < nlen; i++){
    if(number[i] != '0' && isBeginning0)
      isBeginning0 = false;

    if(!isBeginning0)
      printf("%c", number[i]);
  }
}

void PrintCharRecursively(int n)
{
  if(n <= 0)
    return;

  char *number = (char*)malloc(n+1);
  memset(number, 0, n+1);
  memset(number, '0', n);

  PrintRecursivelyCore(number, strlen(number), 0);

  free((void*)number);
}

void PrintRecursivelyCore(char *number, int nlen, int index)
{
  if(index == nlen-1){
    for(int i = 0; i < 10; i++){
      number[index] = '0' + i;
      PrintCharNum(number);
      printf("\n");
    }
    return;
  }
  else{
    for(int i = 0; i < 10; i++){
      number[index] = '0' + i;
      PrintRecursivelyCore(number, nlen, index + 1);
    }
  }
}
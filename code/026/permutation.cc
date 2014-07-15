#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

void Permutation(char *str);
void Permutation(char *str, char *begin);
void PermutationByOrder(char *str, char *begin);

char str[10];

int main()
{
  while(scanf("%s", str) != EOF){
    Permutation(str);
  }
}

//不保证输出顺序，不能去重
void Permutation(char *str)
{
  if(str == NULL || *str == '\0')
    return;

  char *begin = str;
  PermutationByOrder(str, begin);
}

void Permutation(char *str, char *begin)
{
  if(*begin == '\0'){
    printf("%s\n", str);
    return;
  }

  for(char *pCh = begin; *pCh != '\0'; pCh++){
    char temp = *begin;
    *begin = *pCh;
    *pCh = temp;

    Permutation(str, begin+1);

    temp = *begin;
    *begin = *pCh;
    *pCh = temp;
  }
}

//以字典序输出，同时去重
void PermutationByOrder(char *str, char *begin)
{
  if(*begin == '\0'){
    printf("%s\n", str);
    return;
  }

  for(char *pCh = begin; *pCh != '\0'; pCh++){
    //保证以字典序输出,必须在for循环里面，？？
    std :: sort(begin, str + strlen(str));
   
    //去重1
    if((pCh - 1 >= begin) && (*pCh == *(pCh - 1)))
      continue;

    //去重2
    if(*pCh == *begin && pCh != begin)
      continue;

    char temp = *begin;
    *begin = *pCh;
    *pCh = temp;

    PermutationByOrder(str, begin+1);

    temp = *begin;
    *begin = *pCh;
    *pCh = temp;
  }
}

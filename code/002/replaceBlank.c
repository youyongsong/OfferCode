#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int replaceBlank(char[], int);

int main()
{
  char str[4000000];
  memset(str, 0, sizeof(str));

  while(gets(str) != NULL){
    replaceBlank(str, 4000000);
    printf("%s\n", str);
  }

  return 0;
}


//length为字符串数组str的容量
int replaceBlank(char str[], int length)
{
  if(str == NULL || length <= 0)
    return -1;

  int count = 0;
  int indexOfOrigin = 0;
  int indexOfNew = 0;

  /*计算字符串中的空格个数和字符串的实际长度*/
  for(int i = 0; str[i] != '\0'; i++){
    ++ indexOfOrigin;
    if(str[i] == ' ')
      count ++;
  }

  //计算将空格替换后的字符串实际长度，如果无空格或容量不足以存放替换后的字符串则返回-1
  indexOfNew = indexOfOrigin + 2*count;
  if((indexOfNew + 1 > length) || (count == 0))
    return -1;

  while((indexOfNew > indexOfOrigin) && (indexOfOrigin >= 0)){
    if(str[indexOfOrigin] == ' '){
      str[indexOfNew--] = '0';
      str[indexOfNew--] = '2';
      str[indexOfNew--] = '%';
    }
    else{
      str[indexOfNew--] = str[indexOfOrigin];
    }
    indexOfOrigin --;
  }

  return 0;
}

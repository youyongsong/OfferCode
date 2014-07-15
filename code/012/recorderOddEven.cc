#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReorderOddEven(int *, int);
void ReorderOddEvenByOrder(int *, int);
void ReorderOddEvenByOrder2(int *, int);

int main()
{
  int test, *pData;

  if(scanf("%d", &test) < 1)
    perror("input wrong");
  pData = (int*) malloc(test*sizeof(int));
  for(int i = 0; i < test; i++){
    if(scanf("%d", &pData[i]) < 1)
      perror("input wrong");
  }

  //ReorderOddEven(pData, test);
  //ReorderOddEvenByOrder(pData, test);
  ReorderOddEvenByOrder2(pData, test);

  for(int i = 0; i < test; i++){
    printf("%d", pData[i]);
    if(i < test - 1)
      printf(" ");
  }

  free((void*)pData);
}

//不保证奇偶数的相对顺序，时间和空间复杂度都最优
void ReorderOddEven(int *pData, int len)
{
  if(len <= 0 || pData == NULL)
    return;

  int indexBegin = 0;
  int indexEnd = len - 1;

  while(indexBegin < indexEnd){
    if(((pData[indexBegin] & 0x1) == 0) && ((pData[indexEnd] & 0x1) != 0)){ //pData[indexBegin] is even and pData[indexEnd] is odd
          int temp = pData[indexBegin];
          pData[indexBegin] = pData[indexEnd];
          pData[indexEnd] = temp;
    }
    if((pData[indexBegin] & 0x1) != 0){  //pData[indexBegin] is odd
      indexBegin++;
    }
    if((pData[indexEnd] & 0x1) == 0){  //pData[indexEnd] is even
      indexEnd--;
    }
  }
}

//时间换空间
//保证奇偶数的相对顺序，不需额外空间，时间复杂度O(n^2)
void ReorderOddEvenByOrder(int *pData, int len)
{
  if(len < 0 || pData == NULL)
    return;

  int countEven = 0;
  for(int i = 0; i < len - countEven;){
    if((pData[i] & 0x1) != 0){  //pData[i] is odd
      i++;
    }
    else{  //pData[i] is Even
      countEven ++;
      int currentEven = pData[i];
      for(int j = i; j < len - 1; j++)
        pData[j] = pData[j+1];
      pData[len-1] = currentEven;
    }
  }
}

//空间换时间
//保证奇数和偶数的相对顺序，需要额外空间，时间复杂度O(n)
void ReorderOddEvenByOrder2(int *pData, int len)
{
  if(len <= 0 || pData == NULL)
    return;

  int countEven = 0;
  int countOdd = 0;
  int *pEven = (int*)malloc(len*sizeof(int));
  int *pOdd = (int*)malloc(len*sizeof(int));

  for(int i = 0; i < len; i++){
    if((pData[i] & 0x1) != 0){  //pData[i] is odd
      pOdd[countOdd] = pData[i];
      countOdd++;
    }
    else{  //pData[i] is Even
      pEven[countEven] = pData[i];
      countEven++;
    }
  }

  for(int i = 0; i < countOdd; i++)
    pData[i] = pOdd[i];
  for(int i = 0; i < countEven; i++)
    pData[i+countOdd] = pEven[i];

  free((void*)pEven);
  free((void*)pOdd);
}

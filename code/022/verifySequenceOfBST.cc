#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool VerifySequenceOfBST(unsigned long sequence[], int length);

unsigned long sequence[10000];
int main()
{
  int number;

  while(scanf("%d", &number) != EOF){
    for(int i = 0; i < number; i++)
      if(scanf("%ld", &sequence[i]) < 1)
        perror("input error");

    if(VerifySequenceOfBST(sequence, number))
      printf("Yes\n");
    else
      printf("No\n");
  }
}

bool VerifySequenceOfBST(unsigned long sequence[], int length)
{
  if(sequence == NULL || length <= 0)
    return false;

  unsigned long root = sequence[length - 1];
  int countLeft = 0;
  int countRight = 0;

  //统计左子树节点
  for(int i = 0; i < length - 1; i++){
    if(sequence[i] >= root)
      break;
    countLeft++;
  }

  //统计右子树节点
  for(int i = countLeft; i < length - 1; i++){
    if(sequence[i] < root)
      return false;
    countRight++;
  }

  //判断左子树是否为搜索二叉树
  bool left = true;
  if(countLeft > 1)
    left = VerifySequenceOfBST(sequence, countLeft);

  //判断右子树是否为搜索二叉树
  bool right = true;
  if(countRight > 1)
    right = VerifySequenceOfBST(sequence + countLeft, countRight);

  return (left && right);
}
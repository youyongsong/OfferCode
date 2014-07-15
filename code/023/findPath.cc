#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode
{
  int nValue;
  struct BinaryTreeNode *pLeft;
  struct BinaryTreeNode *pRight;
  int index;
} BinaryTreeNode;

void swap(int &a, int &b);
void DestroyTree(BinaryTreeNode *pRoot);
void FindPath(BinaryTreeNode *pRoot, int sum);
void FindPath
(
    BinaryTreeNode *pRoot,
    int *path,
    int pathLength,
    int expectedSum,
    int currentSum
);

int main()
{
  int number, sum;

  while(scanf("%d%d", &number, &sum) != EOF){
    //创建树节点数组，即一颗树
    BinaryTreeNode **pTree = (BinaryTreeNode**) malloc(number * sizeof(BinaryTreeNode*));

    //为树节点分配空间并初始化
    for(int i = 0; i < number; i++){
      pTree[i] = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
      pTree[i]->nValue = 0;
      pTree[i]->index = i + 1;
      pTree[i]->pLeft = NULL;
      pTree[i]->pRight = NULL;
    }

    //为树节点赋值，并连接树
    int value, indexL, indexR;
    for(int i = 0; i < number; i++){
      //输入树节点i的值和左右节点的编号
      if(scanf("%d%d%d", &value, &indexL, &indexR) < 3)
        perror("input error");

      //保证以字典顺序输出
      if(indexL > indexR)
        swap(indexL, indexR);

      pTree[i]->nValue = value;
      if(indexL > 0)
        pTree[i]->pLeft = pTree[indexL - 1];
      if(indexR > 0)
        pTree[i]->pRight = pTree[indexR - 1];
    }

    BinaryTreeNode *pRoot = pTree[0];

    printf("result:\n");
    FindPath(pRoot, sum);

    DestroyTree(pRoot);
  }
}

void FindPath(BinaryTreeNode *pRoot, int sum)
{
  if(pRoot == NULL || sum <= 0)
    return;

  int *path = (int*) malloc(10000 * sizeof(int));
  int pathLength = 0;
  int currentSum = 0;

  FindPath(pRoot, path, pathLength, sum, currentSum);

  free((void*)path);
}

void FindPath
(
    BinaryTreeNode *pRoot,
    int *path,
    int pathLength,
    int expectedSum,
    int currentSum
)
{
  if(pRoot == NULL)
    return;

  //添加当前节点到path中
  path[pathLength] = pRoot->index;
  pathLength++;
  currentSum += pRoot->nValue;

  //如果是页节点输出路径
  bool isLeaf = (pRoot->pLeft == NULL && pRoot->pRight == NULL);
  if(currentSum == expectedSum && isLeaf){
    printf("A path is found: ");
    for(int i = 0; i < pathLength; i++){
      printf("%d", path[i]);
      if(i < pathLength - 1)
        printf(" ");
    }
    printf("\n");
  }

  //非叶节点，则遍历其子节点
  if(pRoot->pLeft != NULL)
    FindPath(pRoot->pLeft, path, pathLength, expectedSum, currentSum);
  if(pRoot->pRight != NULL)
    FindPath(pRoot->pRight, path, pathLength, expectedSum, currentSum);

  //回溯
  pathLength --;
  currentSum -= pRoot->nValue;
}

void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void DestroyTree(BinaryTreeNode *pRoot)
{
  if(pRoot != NULL){
    BinaryTreeNode *pLeft = pRoot->pLeft;
    BinaryTreeNode *pRight = pRoot->pRight;

    free((void*)pRoot);
    pRoot = NULL;

    DestroyTree(pLeft);
    DestroyTree(pRight);
  }
}
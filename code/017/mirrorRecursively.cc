#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode
{
  int nValue;
  struct BinaryTreeNode *pLeft;
  struct BinaryTreeNode *pRight;
} BinaryTreeNode;

BinaryTreeNode* CreateTreeNode(int value);
void ConnectTreeNode(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
void DestroyTree(BinaryTreeNode *pRoot);
void PrintTree(BinaryTreeNode *pRoot);

void MirrorRecursively(BinaryTreeNode *pRoot);

int preNodes[1000];  //存储树的前序遍历，以方便以特定格式输出
int count;

int main()
{
  int number;

  while(scanf("%d", &number) != EOF){
    if(number == 0){
      printf("NULL\n");
      continue;
    }

    BinaryTreeNode **pTree = (BinaryTreeNode**) malloc(number * sizeof(BinaryTreeNode*));
    int value;

    //输入并创建所有的树节点
    for(int i = 0; i < number; i++){
      if(scanf("%d", &value) < 1)
        perror("input error");

      pTree[i] = CreateTreeNode(value);
    }

    //将树节点连接成树
    char position[2];
    int indexL, indexR;
    for(int i = 0; i < number; i++){
      if(scanf("%s", position) < 0)
        perror("input error");

      switch(position[0]){
      case 'd':
        if(scanf("%d%d", &indexL, &indexR) < 2)
          perror("input error");
        ConnectTreeNode(pTree[i], pTree[indexL-1], pTree[indexR-1]);
        break;
      case 'l':
        if(scanf("%d", &indexL) < 1)
          perror("input error");
        ConnectTreeNode(pTree[i], pTree[indexL-1], NULL);
        break;
      case 'r':
        if(scanf("%d", &indexR) < 1)
          perror("input error");
        ConnectTreeNode(pTree[i], NULL, pTree[indexR-1]);
        break;
      case 'z':
        break;
      default:
        printf("invalid input\n");
        i--;
        break;
      }
    }

    //镜像翻转树
    BinaryTreeNode *pRoot = pTree[0];
    MirrorRecursively(pRoot);

    //以要求的格式输出树的前序遍历
    count = 0;
    PrintTree(pRoot);
    for(int i = 0; i < number; i++){
      printf("%d", preNodes[i]);
      if(i < number-1)
        printf(" ");
    }
    printf("\n");

    //释放树节点所占空间
    DestroyTree(pRoot);
    //释放树所占空间
    free((void*) pTree);
    pTree = NULL;
  }
}

void MirrorRecursively(BinaryTreeNode *pNode)
{
  if(pNode == NULL)
    return;
  if(pNode->pLeft == NULL && pNode->pRight == NULL)
    return;

  BinaryTreeNode *pTempNode = pNode->pLeft;
  pNode->pLeft = pNode->pRight;
  pNode->pRight = pTempNode;

  MirrorRecursively(pNode->pLeft);
  MirrorRecursively(pNode->pRight);
}


BinaryTreeNode* CreateTreeNode(int value)
{
  BinaryTreeNode *pTreeNode = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));

  pTreeNode->nValue = value;
  pTreeNode->pLeft = NULL;
  pTreeNode->pRight = NULL;

  return pTreeNode;
}

void ConnectTreeNode(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
  if(pParent == NULL)
    return;

  pParent->pLeft = pLeft;
  pParent->pRight = pRight;
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

void PrintTree(BinaryTreeNode *pRoot)
{
  if(pRoot != NULL){
    preNodes[count++] = pRoot->nValue;
    //printf("%d ", pRoot->nValue);
    PrintTree(pRoot->pLeft);
    PrintTree(pRoot->pRight);
  }
}

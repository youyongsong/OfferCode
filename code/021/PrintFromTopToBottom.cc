#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>

using namespace  std;

typedef struct BinaryTreeNode
{
  int nValue;
  struct BinaryTreeNode *pLeft;
  struct BinaryTreeNode *pRight;
} BinaryTreeNode;

void PrintFromTopToBottom(BinaryTreeNode *pRoot);
BinaryTreeNode* CreateTreeNode(int value);
void ConnectTreeNode(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
void DestroyTree(BinaryTreeNode *pRoot);

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

    //按层遍历输出
    BinaryTreeNode *pRoot = pTree[0];
    PrintFromTopToBottom(pRoot);
    printf("\n");

    //释放树节点所占空间
    DestroyTree(pRoot);
    //释放树所占空间
    free((void*) pTree);
    pTree = NULL;
  }
}

void PrintFromTopToBottom(BinaryTreeNode *pRoot)
{
  if(pRoot == NULL){
    printf("\n");
    return;
  }

  deque<BinaryTreeNode*> dequeTreeNode;
  dequeTreeNode.push_back(pRoot);

  while(dequeTreeNode.size() != 0){
    BinaryTreeNode *pNode = dequeTreeNode.front();

    printf("%d", pNode->nValue);
    dequeTreeNode.pop_front();

    if(pNode->pLeft != NULL)
      dequeTreeNode.push_back(pNode->pLeft);
    if(pNode->pRight != NULL)
      dequeTreeNode.push_back(pNode->pRight);
    
    //格式要求，最后一个数字后面不输出空格
    if(dequeTreeNode.size() != 0)
      printf(" ");
  }
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
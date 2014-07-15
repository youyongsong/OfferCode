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

bool HasSubTree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2);
bool DoesTree1HasTree2(BinaryTreeNode *pTree1, BinaryTreeNode *pTree2);

int main()
{
  int m, n;

  while(scanf("%d%d", &m, &n) != EOF){
    //创建树节点的数组，数组的每个元素是一个树指针
    BinaryTreeNode **pTree1 = (BinaryTreeNode**) malloc(m * sizeof(unsigned long));
    BinaryTreeNode **pTree2 = (BinaryTreeNode**) malloc(n * sizeof(unsigned long));

    int tValue;
    //创建二叉树A
    //输入二叉树节点值
    for(int i = 0; i < m; i++){
      if(scanf("%d", &tValue) < 1)
        perror("input error");
      pTree1[i] = CreateTreeNode(tValue);
    }
    //将节点连接成特定结构的二叉树
    int tNum, leftNodeIndex, rightNodeIndex;
    for(int i = 0; i < m; i++){
      if(scanf("%d", &tNum) < 1)
        perror("input error");

      if(tNum == 1){
        if(scanf("%d", &leftNodeIndex) < 1)
          perror("input error");

        ConnectTreeNode(pTree1[i], pTree1[leftNodeIndex-1], NULL);
      }
      else if(tNum == 2){
        if(scanf("%d%d", &leftNodeIndex, &rightNodeIndex) < 2)
          perror("input error");

        ConnectTreeNode(pTree1[i], pTree1[leftNodeIndex-1], pTree1[rightNodeIndex-1]);
      }
    }

    //创建二叉树B
    //输入二叉树节点值
    for(int i = 0; i < n; i++){
      if(scanf("%d", &tValue) < 1)
        perror("input error");
      pTree2[i] = CreateTreeNode(tValue);
    }
    //将节点连接成特定结构的二叉树
    for(int i = 0; i < n; i++){
      if(scanf("%d", &tNum) < 1)
        perror("input error");

      if(tNum == 1){
        if(scanf("%d", &leftNodeIndex) < 1)
          perror("input error");

        ConnectTreeNode(pTree2[i], pTree2[leftNodeIndex-1], NULL);
      }
      else if(tNum == 2){
        if(scanf("%d%d", &leftNodeIndex, &rightNodeIndex) < 2)
          perror("input error");

        ConnectTreeNode(pTree2[i], pTree2[leftNodeIndex-1], pTree2[rightNodeIndex-1]);
      }
    }

    //确定树的根节点
    /*
     * 注意:如果树为空，则pTree=NULL,此时并未pTree[0]分配空间
     * 此时在任何地方引用pTree[0]都会出现错误
     * 所以不要直接把pTree[0]直接当做根节点来用，因为树为空时，pTree[0]不等于NULL，而是不存在
     */
    BinaryTreeNode *pRoot1 = NULL;
    BinaryTreeNode *pRoot2 = NULL;
    if(m > 0)
      pRoot1 = pTree1[0];
    if(n > 0)
      pRoot2 = pTree2[0];

    //判断树A是否包含数B
    if(HasSubTree(pRoot1, pRoot2))
      printf("YES\n");
    else
      printf("NO\n");

    //释放树节点所占空间
    DestroyTree(pRoot1);
    DestroyTree(pRoot2);
    pRoot1 = NULL;
    pRoot2 = NULL;
    //释放树所占空间
    free(pTree1);
    free(pTree2);
    pTree1 = NULL;
    pTree2 = NULL;
  }
}

bool HasSubTree(BinaryTreeNode *pRoot1, BinaryTreeNode *pRoot2)
{
  bool result = false;

  if(pRoot1 == NULL || pRoot2 == NULL)
    return result;

  if(pRoot1->nValue == pRoot2->nValue)
    result = DoesTree1HasTree2(pRoot1, pRoot2);
  if(!result)
    result = HasSubTree(pRoot1->pLeft, pRoot2);
  if(!result)
    result = HasSubTree(pRoot1->pRight, pRoot2);

  return result;
}

bool DoesTree1HasTree2(BinaryTreeNode *pTree1, BinaryTreeNode *pTree2)
{
  if(pTree2 == NULL)
    return true;
  if(pTree1 == NULL)
    return false;

  if(pTree1->nValue != pTree2->nValue)
    return false;

  return DoesTree1HasTree2(pTree1->pLeft, pTree2->pLeft) &&
         DoesTree1HasTree2(pTree1->pRight, pTree2->pRight);
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

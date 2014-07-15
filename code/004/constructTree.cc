#include<stdio.h>

typedef struct BTreeNode
{
  int key;
  struct BTreeNode* leftChild;
  struct BTreeNode* rightChild;
} BTreeNode;
bool buildFlag = true;  //是否可重建二叉树标志位

BTreeNode* construct(int*, int*, int);
BTreeNode* constructCore(int*, int*, int*, int*);
void backPrint(BTreeNode*);
void clearTree(BTreeNode*);

int main()
{
  int num;
  int *arrayPre, *arrayIn;
  BTreeNode* root;

  while(scanf("%d", &num) != EOF){
    buildFlag = true;
    arrayPre = new int[num];
    arrayIn = new int[num];

    for(int i = 0; i < num; i++)
      scanf("%d", &arrayPre[i]);
    for(int i = 0; i < num; i++)
      scanf("%d", &arrayIn[i]);

    root = construct(arrayPre, arrayIn, num);

    if(buildFlag){
      backPrint(root);
      printf("\n");
    }
    else
      printf("No\n");

    //注意要回收内存
    clearTree(root);
    delete arrayPre;
    delete arrayIn;
  }
}

BTreeNode* construct(int* preOrder, int* inOrder, int length)
{
  if(preOrder == NULL || inOrder == NULL || length <= 0){
    buildFlag = false;
    return NULL;
  }

  return constructCore(preOrder, preOrder + length -1, inOrder, inOrder + length -1);
}

BTreeNode* constructCore(int *startPreOrder, int *endPreOrder, int *startInOrder, int *endInOrder)
{
  /*
   * 首先找到当前的根节点
   * 前序遍历的第一个数字就是根节点
   */
  BTreeNode *root = new BTreeNode();
  root->key = startPreOrder[0];
  root->leftChild = NULL;
  root->rightChild = NULL;

  if(startPreOrder == endPreOrder){
    if(startInOrder == endInOrder && *startInOrder == root->key)
      return root;
    else{
      buildFlag = false;
      return NULL;
      //throw std::exception("Invalid input!");
    }
  }

  /*
   * 在中序遍历中需找根节点
   */
  int* rootInOrder = startInOrder;
  while(*rootInOrder != root->key && rootInOrder < endInOrder){
    rootInOrder++;
  }

  if(rootInOrder == endInOrder && *rootInOrder != root->key){
    buildFlag = false;
    return NULL;
    //throw std::exception("Invalid input!");
  }

  //将当前的数组分为左子树和右子树两部分
  int leftChildNum = rootInOrder - startInOrder;
  int rightChildNum = endInOrder - rootInOrder;

  if(leftChildNum > 0){
    //构建左子树
    root->leftChild = constructCore(startPreOrder+1, startPreOrder+leftChildNum,
        startInOrder, rootInOrder-1);
  }
  if(rightChildNum > 0){
    //构建右子树
    root->rightChild = constructCore(startPreOrder+leftChildNum+1, endPreOrder,
        rootInOrder+1, endInOrder);
  }

  return root;
}

/*
 * 后续遍历打印
 */
void backPrint(BTreeNode* root)
{
  if(root == NULL)
    return;
  backPrint(root->leftChild);
  backPrint(root->rightChild);
  printf("%d ", root->key);

  return;
}

/*
 * 后续遍历释放树
 */
void clearTree(BTreeNode* root)
{
  if(root){
    clearTree(root->leftChild);
    clearTree(root->rightChild);
    delete root;
    root = NULL;
  }
  return;
}
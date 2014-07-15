#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
  int nValue;
  struct ListNode *pNext;
} ListNode;

ListNode* MergeList(ListNode *pHead1, ListNode *pHead2);
ListNode* MergeList2(ListNode *pHead1, ListNode *pHead2);
void FreeList(ListNode *pHead);

int main()
{
  int num1, num2;

  while(scanf("%d%d", &num1, &num2) != EOF){
    ListNode *pHead1 = NULL;
    ListNode *pHead2 = NULL;

    //初始化第一条链表
    ListNode *pTail1;
    for(int i = 0; i < num1; i++){
      if(pHead1 == NULL){
        pHead1 = (ListNode*) malloc(sizeof(ListNode));
        if(scanf("%d", &(pHead1->nValue)) < 1)
          perror("input error");
        pHead1->pNext = NULL;
        pTail1 = pHead1;
        continue;
      }

      pTail1->pNext = (ListNode*)malloc(sizeof(ListNode));
      pTail1 = pTail1->pNext;
      pTail1->pNext = NULL;
      if(scanf("%d", &(pTail1->nValue)) < 1)
        perror("input error");
    }

    //初始化第二条链表
    ListNode *pTail2;
    for(int i = 0; i < num2; i++){
      if(pHead2 == NULL){
        pHead2 = (ListNode*)malloc(sizeof(ListNode));
        if(scanf("%d", &(pHead2->nValue)) < 1)
          perror("input error");
        pHead2->pNext = NULL;
        pTail2 = pHead2;
        continue;
      }

      pTail2->pNext = (ListNode*)malloc(sizeof(ListNode));
      pTail2 = pTail2->pNext;
      pTail2->pNext = NULL;
      if(scanf("%d", &(pTail2->nValue)) < 1)
        perror("input error");
    }

    //合并链表
    ListNode* pMergedList = MergeList2(pHead1, pHead2);

    //打印合并后的链表
    if(pMergedList == NULL){
      printf("NULL\n");
      continue;
    }
    ListNode* pNode = pMergedList;
    while(pNode != NULL){
      printf("%d", pNode->nValue);
      if(pNode->pNext != NULL)
        printf(" ");
      pNode = pNode->pNext;
    }
    printf("\n");

    //释放链表空间
    FreeList(pMergedList);
  }
}


void FreeList(ListNode *pHead)
{
  ListNode *pNode = pHead;

  while(pHead){
    pNode = pHead->pNext;
    free((void*)pHead);
    pHead = pNode;
  }
}

/*
 * 这种做法是存在安全隐患的做法：
 * pMergedHead自己分配了空间，可以不改变pHead1和pHead2的结构，
 * 但是pMergedHead同时又参杂了pHead1和pHead2的元素
 * 这样会导致无法释放pMergedList占用的空间，例如：
 * free(pHead1);
 * free(pHead2);
 * free(pMergedHead);
 * 这样在释放pMergedHead所占空间的时候，有可能重复释放pHead1或pHead2中
 * 已经释放过的空间，引发Runtime Error
 */
ListNode* MergeList(ListNode *pHead1, ListNode *pHead2)
{
  if(pHead1 == NULL)
      return pHead2;
    else if(pHead2 == NULL)
      return pHead1;

    ListNode *pMergedHead = (ListNode*)malloc(sizeof(ListNode));

    if(pHead1->nValue <= pHead2->nValue){
      pMergedHead->nValue = pHead1->nValue;
      pMergedHead->pNext = MergeList(pHead1->pNext, pHead2);
    }
    else{
      pMergedHead->nValue = pHead2->nValue;
      pMergedHead->pNext = MergeList(pHead1, pHead2->pNext);
    }

    return pMergedHead;
}

/*
 * 不为pMergedHead分配新空间的方法，
 * 这样只需释放pMergedHead占的空间即相当于同时释放了pHead1和pHead2所占的空间;
 * 但是这样会改变pHead1和pHead2的链表结构
 */
ListNode* MergeList2(ListNode *pHead1, ListNode *pHead2)
{
  if(pHead1 == NULL)
    return pHead2;
  else if(pHead2 == NULL)
    return pHead1;

  ListNode *pMergedHead = NULL;

  if(pHead1->nValue <= pHead2->nValue){
    pMergedHead = pHead1;
    pMergedHead->pNext = MergeList2(pHead1->pNext, pHead2);
  }
  else{
    pMergedHead = pHead2;
    pMergedHead->pNext = MergeList2(pHead1, pHead2->pNext);
  }

  return pMergedHead;
}

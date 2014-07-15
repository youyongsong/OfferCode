#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
  int nValue;
  struct ListNode *pNext;
} ListNode;

ListNode* FindKthToTail(ListNode *pHead, int k);

int main()
{
  int number, k;
  while(scanf("%d%d", &number, &k) != EOF){
    ListNode *pHead = NULL;

    if(number <=0){
      printf("NULL\n");
      continue;
    }

    //initialize the list
    ListNode *pTail;
    for(int i = 0; i < number; i++){
      if(pHead == NULL){
        pHead = (ListNode*)malloc(sizeof(ListNode));
        if(scanf("%d", &(pHead->nValue)) < 1)
          perror("input wrong");
        pHead->pNext = NULL;
        pTail =pHead;
        continue;
      }

      pTail->pNext = (ListNode*)malloc(sizeof(ListNode));
      pTail = pTail->pNext;
      pTail->pNext = NULL;
      if(scanf("%d", &(pTail->nValue)) < 1)
        perror("input wrong");
    }

    //find the Kth to tail
    ListNode *pKthToTail = FindKthToTail(pHead, k);

    //print the result
    if(pKthToTail == NULL)
      printf("NULL\n");
    else
      printf("%d\n", pKthToTail->nValue);

    free((void*)pHead);
  }
}


ListNode* FindKthToTail(ListNode *pHead, int k)
{
  if(pHead == NULL || k <= 0)
    return NULL;

  ListNode* pAhead = pHead;
  ListNode* pBehind = pHead;

  //头指针向前移动k-1步
  int distance = k - 1;
  while(distance--){
    if(pAhead->pNext != NULL)
      pAhead = pAhead->pNext;
    else
      return NULL;
  }

  //头尾指针同时向前移动直到头指针移动到尾部
  while(pAhead->pNext != NULL){
    pAhead = pAhead->pNext;
    pBehind = pBehind->pNext;
  }

  return pBehind;
}

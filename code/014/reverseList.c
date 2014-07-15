#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode
{
  int key;
  struct ListNode* next;
} ListNode;

ListNode* reverseList(ListNode *pHead);

int main()
{
  int num;
  ListNode *list = NULL;
  ListNode *pNode;
  ListNode *tail;

  while(scanf("%d", &num) != EOF){
    // input list
    while(num--){
      if(list == NULL){
        list = (ListNode*) malloc(sizeof(ListNode));
        tail = list;
        scanf("%d", &tail->key);
        tail->next = NULL;
      }
      else{
        tail->next = (ListNode*) malloc(sizeof(ListNode));
        tail = tail->next;
        scanf("%d", &tail->key);
        tail->next = NULL;
      }
    }

    // reverse list
    list = reverseList(list);

    // output list
    pNode = list;
    if(pNode == NULL)
      printf("NULL\n");
    else{
      while(pNode != NULL){
        /*最后一个元素后无空格，否则会出现格式错误(Presentation Error)*/
        if(pNode->next != NULL)
          printf("%d ", pNode->key);
        else
          printf("%d", pNode->key);
        pNode = pNode->next;
      };
      printf("\n");
    }

    // free list
    pNode = list;
    while(pNode != NULL){
      list = pNode->next;
      free((void*) pNode);
      pNode = list;
    }
  }
}

ListNode* reverseList(ListNode *pHead)
{
  ListNode *pReverseHead = NULL;
  ListNode *pPrev = NULL;
  ListNode *pNode = pHead;
  ListNode *pNext;

  while(pNode != NULL){
    pNext = pNode->next;
    if(pNext == NULL)
      pReverseHead = pNode;

    pNode->next = pPrev;
    pPrev = pNode;
    pNode = pNext;
  }

  return pReverseHead;
}
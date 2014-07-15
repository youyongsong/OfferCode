#include<stdio.h>
#include<stack>

typedef struct ListNode
{
  int key;
  struct ListNode* pNext;
} ListNode;

void printListByRecursion(ListNode*);
void printListByStack(ListNode *phead);

int main()
{
  int elements;
  ListNode *head = NULL, *tail = NULL;

  //建立链表
  scanf("%d", &elements);
  while(elements >= 0){
    if(head == NULL){
      head = new ListNode();
      head->key = elements;
      tail = head;
    }
    else{
      tail->pNext = new ListNode();
      tail = tail->pNext;
      tail->key = elements;
    }

    scanf("%d", &elements);
  }
  
  //两种方法从尾到头打印链表
  printf("--------print by recursion-----------\n");
  printListByRecursion(head);
  printf("--------print by stack-----------\n");
  printListByStack(head);

  //删除链表，释放链表所占空间
  ListNode* pNode = head;
  while(head != NULL){
    pNode = head;
    head = head->pNext;
    delete pNode;
  }

  return 0;
}

// 用递归的方式从尾到头打印链表
void printListByRecursion(ListNode *phead)
{
  if(phead != NULL){
    printListByRecursion(phead->pNext);
    printf("%d\n", phead->key);
  }
  return;
}

// 用堆栈的方式从尾到头打印链表
void printListByStack(ListNode *phead)
{
  std::stack<ListNode*> nodes;
  ListNode* pnode = phead;
  while(pnode != NULL){
    nodes.push(pnode);
    pnode = pnode->pNext;
  }

  while(!nodes.empty()){
    pnode = nodes.top();
    printf("%d\n", pnode->key);
    nodes.pop();
  }
}
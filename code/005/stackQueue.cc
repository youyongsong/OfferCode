#include<stdio.h>
#include<stack>

using namespace std;

template <typename T> class CQueue
{
public:
  CQueue(void);
  ~CQueue(void);
  void appendTail(const T& node);
  T deleteHead();

private:
  stack<T> stack1;
  stack<T> stack2;
};

int main()
{
  CQueue<int> queue;
  int count,element,ret;
  char cmd[10];

  scanf("%d", &count);
  while(count--){
    scanf("%s", cmd);
    if(cmd[1] == 'U'){
      scanf("%d", &element);
      queue.appendTail(element);
    }
    else if(cmd[1] == 'O'){
      ret = queue.deleteHead();
      printf("%d\n", ret);
    }
  }
}


template<typename T>
CQueue<T> :: CQueue(void)
{
}

template<typename T>
CQueue<T> :: ~CQueue(void)
{
  while(stack1.size() > 0){
    stack1.pop();
  }
  while(stack2.size() > 0){
    stack2.pop();
  }
}

template<typename T>
void CQueue<T> :: appendTail(const T& element)
{
  stack1.push(element);
}

template<typename T>
T CQueue<T> :: deleteHead()
{
  if(stack2.size() <= 0){
    while(stack1.size() > 0){
      T& data = stack1.top();
      stack1.pop();
      stack2.push(data);
    }
  }

  if(stack2.size() == 0){
    //throw new exception("queue is empty");
    return -1;
  }

  T head = stack2.top();
  stack2.pop();

  return head;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <assert.h>

using namespace std;

template <typename T>
class StackWithMin
{
public:
  StackWithMin(void);
  ~StackWithMin(void);
  void push(const T& element);
  void pop();
  const T& min() const;
  bool isEmpty();
private:
  stack<T> dataStack;
  stack<T> minStack;
};

int main()
{
  int num, element;
  char command[5];
  
  while(scanf("%d", &num) != EOF){
    StackWithMin<int> stack;

    for(int i = 0; i < num; i++){
      if(scanf("%s", command) < 1)
        perror("input error");

      switch(command[0]){
      case 's':
        if(scanf("%d", &element) < 1)
          perror("input error");
        stack.push(element);
        break;
      case 'o':
        stack.pop();
        break;
      default:
        printf("invalid command, input again\n");
        i--;
        break;
      }

      if(stack.isEmpty())
        printf("NULL\n");
      else
        printf("%d\n", stack.min());
    }
  }
}


template <typename T>
StackWithMin<T> :: StackWithMin(void)
{
}

template <typename T>
StackWithMin<T> :: ~StackWithMin(void)
{
}

template <typename T>
void StackWithMin<T> :: push(const T& element)
{
  dataStack.push(element);

  if(minStack.size() == 0 || element <= minStack.top())
    minStack.push(element);
  else
    minStack.push(minStack.top());
}

template <typename T>
void StackWithMin<T> :: pop()
{
  assert(dataStack.size() > 0 && minStack.size() > 0);

  dataStack.pop();
  minStack.pop();
}

template <typename T>
const T& StackWithMin<T> :: min() const
{
  assert(dataStack.size() > 0 && minStack.size() > 0);

  return minStack.top();
}

template <typename T>
bool StackWithMin<T> :: isEmpty()
{
  if(dataStack.size() == 0 || minStack.size() == 0)
    return true;
  else
    return false;
}
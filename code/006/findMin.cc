#include<stdio.h>
#include<stdlib.h>

int minBinary(int*, int);
int minInOrder(int*, int);

int main()
{
  int count,ret;
  while(scanf("%d", &count) != EOF)
  {
    int *array = (int*) malloc(count*sizeof(int));
    for(int i = 0; i < count; i++)
      scanf("%d", &array[i]);

    ret = minBinary(array, count);
    printf("%d\n", ret);

    free((void*)array);
  }
}

int minBinary(int *array, int length)
{
  if(array == NULL || length <= 0){
    printf("invalid parameters\n");
    return -1;
    //throw new exception("invalid parameters");
  }

  int start, end, mid;

  start = 0;
  end = length -1;
  mid = start;

  while(array[start] >= array[end]){
    if(end - start == 1){
      mid = end;
      break;
    }

    mid = (start + end) / 2;

    /*三个数都相同时，无法确定缩小范围的方向，只能顺序查找*/
    if(array[start] == array[end] && array[start] == array[mid])
      return minInOrder(array, length);

    /*array[mid]在第一个数组中*/
    else if(array[mid] >= array[start])
      start = mid;
    /*array[mid]在第二个数组中*/
    else if(array[mid] <= array[end])
      end = mid;
  }
  return array[mid];
}

int minInOrder(int *array, int length)
{
  if(array == NULL || length <= 0){
    printf("invalid array\n");
    return -1;
    //throw new exception("invalid parameters");
  }

  int target = array[0];
  for(int i = 0; i < length; i++){
    if(array[i] < target)
      target = array[i];
  }

  return target;
}

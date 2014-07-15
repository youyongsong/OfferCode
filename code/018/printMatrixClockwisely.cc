#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintMatrixClockwisely(int**, int, int);
void PrintMatrixInCircle(int**, int, int, int);

int main()
{
  int m, n;

  while(scanf("%d%d", &m, &n) != EOF){
    //创建矩阵
    int **numbers = (int**) malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++)
      numbers[i] = (int*) malloc(n * sizeof(int));

    //输入矩阵
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
        if(scanf("%d", &numbers[i][j]) < 1)
          perror("input wrong");
      }
    }

    //顺时针打印矩阵
    PrintMatrixClockwisely(numbers, n, m);
    printf("\n");

    //释放数组
    for(int i = 0; i < m; i++){
      free((void*) numbers[i]);
      numbers[i] = NULL;
    }
    free((void*) numbers);
    numbers = NULL;
  }
}

void PrintMatrixClockwisely(int **matrix, int columns, int rows)
{
  if(matrix == NULL || columns <= 0 || rows <= 0)
    return;

  int start = 0;
  while(columns > 2 * start && rows > 2 * start){
    PrintMatrixInCircle(matrix, columns, rows, start);
    start++;
  }
}

void PrintMatrixInCircle(int **matrix, int columns, int rows, int start)
{
  int endColumn = columns - 1 - start;
  int endRow = rows - 1 - start;

  //从左向右打印一行
  for(int i = start; i <= endColumn; i++){
    printf("%d ", matrix[start][i]);
  }

  //从上到下打印一列
  if(endRow > start){
    for(int i = start + 1; i <= endRow; i++){
      printf("%d ", matrix[i][endColumn]);
    }

    //从右到左打印一行
    if(endColumn > start){
      for(int i = endColumn - 1; i >= start; i--){
        printf("%d ", matrix[endRow][i]);
      }

      //从下到上打印一列
      if(endRow - 1 > start){
        for(int i = endRow - 1; i > start; i--){
          printf("%d ", matrix[i][start]);
        }
      }
    }
  }
}
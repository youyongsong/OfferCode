#include<stdio.h>
#include<stdlib.h>

bool find(int**, int, int, int);

int main()
{
  int row, col;

  while(scanf("%d%d", &row, &col) != EOF){
    int obj;
    scanf("%d", &obj);

    int **mat = (int **) malloc(row * sizeof(void*));
    for(int i = 0; i < row; i++)
      mat[i] = (int *) malloc(col * sizeof(int));

    for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
        scanf("%d", &mat[i][j]);
      }
    }

    if(find(mat, row, col, obj))
      printf("Yes\n");
    else
      printf("No\n");

    for(int i = 0; i < row; i++)
      free((void*) mat[i]);
    free((void*) mat);
  }

  return 0;
}

/*
 * 从矩阵的右上角的元素开始查找：
 * 0、如果该元素小于obj，则返回true
 * 1、如果该元素大于obj，则该元素所在列都大于该元素，删除该列
 * 2、如果该元素小于obj，则该元素所在行都小于该元素，删除改行
 * 反复上述的步骤不断缩小矩阵范围，直至矩阵为空，则返回false
 */
bool find(int **mat, int rows, int cols, int obj)
{
  bool found = false;
  int row = 0;
  int col = cols -1;

  while((col >= 0) && (row < rows)){
    if(mat[row][col] == obj)
      return true;

    else if(mat[row][col] > obj)
      --col;

    else
      ++row;
  }

  return false;
}


> 题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。     

在线测试平台：http://ac.jobdu.com/problem.php?pid=1384

----------------

解题思路，不断缩小矩阵的大小 ，直至矩阵为空。例如：    
从矩阵的右上角的元素开始查找：        
 
- 如果该元素等于obj，则返回true
- 如果该元素大于obj，则该元素所在列都大于该元素，删除该列
- 如果该元素小于obj，则该元素所在行都小于该元素，删除该行         

反复上述步骤不断缩小矩阵范围直至矩阵为空，返回false。

```
def findInMatrix(matrix, obj):

	row = 0
	col = len(matrix[0]) - 1

	while row < len(matrix) and col >= 0:
		current = matrix[row][col]

		if current == obj:
			return True
		elif current > obj:
			col -= 1
		else:
			row += 1

	return False
```
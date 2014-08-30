#!/usr/bin/env python
# -*- coding: utf-8 -*-

def findInMatrix(matrix, obj):
	"""
	matrix是一个二维列表，如果matrix中包含目标obj则返回true，
	否则返回false
	"""

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

matrix = ((1, 2, 3, 4),
	      (5, 6, 7, 8),
	      (9, 10, 11, 12),
	      (13, 14, 15, 16))

print findInMatrix(matrix, 18)

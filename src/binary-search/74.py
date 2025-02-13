class Solution:
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        
        for row in matrix:
            if row[-1] < target:
                continue
            else:
                left, right = 0, len(row) - 1
                while left <= right:
                    mid = (right + left) // 2
                    if row[mid] == target:
                        return True
                    elif row[mid] < target:
                        left = mid + 1
                    else:
                        right = mid - 1
                return False
        return False
    
    # 2nd solution treat the 2d matrix like array
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        if not matrix or not matrix[0]:
            return False
        
        rows, cols = len(matrix), len(matrix[0])
        left, right = 0, rows * cols - 1  # Treat the 2D matrix as a 1D array
        
        while left <= right:
            mid = left + (right - left) // 2
            row, col = divmod(mid, cols)  # Convert 1D index to 2D
            mid_value = matrix[row][col]
            
            if mid_value == target:
                return True
            elif mid_value < target:
                left = mid + 1
            else:
                right = mid - 1
        
        return False
    
s = Solution()
assert s.searchMatrix([[1,3,5,7],[10,11,16,20],[23,30,34,60]], 3) == True
assert s.searchMatrix([[1,3,5,7],[10,11,16,20],[23,30,34,60]], 13) == False
assert s.searchMatrix([[1,3]], 3) == True
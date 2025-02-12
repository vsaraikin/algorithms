class Solution:
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        
        def binary_search(arr, target):
            low = 0
            high = len(arr) - 1

            while low <= high:
                mid = (low + high) // 2
                if arr[mid] == target:
                    return mid
                elif arr[mid] < target:
                    low = mid + 1
                else:
                    high = mid - 1

            return -1


        for row in range(len(matrix)):
            if matrix[row][-1] < target:
                continue
            else:
                if matrix[row][0] <= target:
                    res = binary_search(matrix[row], target)
                    if res != -1:
                        return True
                    else:
                        break
                
        

        return False
    
s = Solution()
assert s.searchMatrix([[1,3,5,7],[10,11,16,20],[23,30,34,60]], 3) == True
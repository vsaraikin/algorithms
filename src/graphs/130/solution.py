class Solution:
    def solve(self, board: list[list[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        if not board:
            return board

        n = len(board)
        m = len(board[0])
    
        def dfs(row, col):
            if row < 0 or row >= n or col < 0 or col >= m or board[row][col] != 'O':
                return
            
            board[row][col] = 'V' # Temporarily mark as visited
            dfs(row+1, col)
            dfs(row-1, col)
            dfs(row, col+1)
            dfs(row, col-1)
            
        for i in range(n):
            dfs(i, 0)
            dfs(i, m-1)
            
        for j in range(m):
            dfs(0, j)
            dfs(n-1, j)
            
        for i in range(n):
            for j in range(m):
                if board[i][j] == 'O':
                    board[i][j] = 'X'
                elif board[i][j] == 'V':
                    board[i][j] = 'O'
            
        
s = Solution()
        
board1 = [["X","X","X","X"], ["X","O","O","X"], ["X","X","O","X"], ["X","O","X","X"]]
board1_result = [["X","X","X","X"], ["X","X","X","X"], ["X","X","X","X"], ["X","O","X","X"]]
s.solve(board1)

assert board1 == board1_result


board2 = [["X","O","X"],["X","O","X"],["X","O","X"]]
board2_result = [["X","O","X"],["X","O","X"],["X","O","X"]]
s.solve(board2)

assert board2 == board2_result

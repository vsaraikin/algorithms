from itertools import permutations, product

class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        for l in board:
            tmp_set = set()
            for x in l:
                if x != ".":
                    if x in tmp_set:
                        return False
                    else:
                        tmp_set.add(x)
                    
                    
        new_board = [[0] * len(board) for _ in range(len(board))] 
        for z in range(len(board)):
            for q in range(len(board)):
                new_board[z][q] = board[q][z]
        
                    
        for l in new_board:
            tmp_set = set()
            for x in l:
                if x != ".":
                    if x in tmp_set:
                        return False
                    else:
                        tmp_set.add(x)
        
        a = range(0, 3)
        b = range(3, 6)
        c = range(6, 9)
        
        def func(q, w):
            tmp_set = set()
            for i in q:
                for j in w:
                    if board[i][j] != ".":
                    
                        if board[i][j] in tmp_set:
                            return False
                        else:
                            tmp_set.add(board[i][j])   
            return True
            

        l = product([a, b, c], repeat=2)
        for p in l:
            res = func(p[0], p[1]) 
            if not res:
                return False
        
        return True
            
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        rows = [set() for _ in range(9)]
        cols = [set() for _ in range(9)]
        boxes = [set() for _ in range(9)]

        for i in range(9):
            for j in range(9):
                num = board[i][j]
                if num == '.':
                    continue

                # Check rows
                if num in rows[i]:
                    return False
                rows[i].add(num)

                # Check columns
                if num in cols[j]:
                    return False
                cols[j].add(num)

                # Check boxes
                box_index = (i // 3) * 3 + j // 3
                if num in boxes[box_index]:
                    return False
                boxes[box_index].add(num)

        return True
      
s = Solution()
assert s.isValidSudoku(
    [["5","3",".",".","7",".",".",".","."]
    ,["6",".",".","1","9","5",".",".","."]
    ,[".","9","8",".",".",".",".","6","."]
    ,["8",".",".",".","6",".",".",".","3"]
    ,["4",".",".","8",".","3",".",".","1"]
    ,["7",".",".",".","2",".",".",".","6"]
    ,[".","6",".",".",".",".","2","8","."]
    ,[".",".",".","4","1","9",".",".","5"]
    ,[".",".",".",".","8",".",".","7","9"]]
) == True

assert s.isValidSudoku(
    [["8","3",".",".","7",".",".",".","."]
    ,["6",".",".","1","9","5",".",".","."]
    ,[".","9","8",".",".",".",".","6","."]
    ,["8",".",".",".","6",".",".",".","3"]
    ,["4",".",".","8",".","3",".",".","1"]
    ,["7",".",".",".","2",".",".",".","6"]
    ,[".","6",".",".",".",".","2","8","."]
    ,[".",".",".","4","1","9",".",".","5"]
    ,[".",".",".",".","8",".",".","7","9"]]
) == False

assert s.isValidSudoku(
    [[".",".",".",".","5",".",".","1","."],
     [".","4",".","3",".",".",".",".","."],
     [".",".",".",".",".","3",".",".","1"],
     ["8",".",".",".",".",".",".","2","."],
     [".",".","2",".","7",".",".",".","."],
     [".","1","5",".",".",".",".",".","."],
     [".",".",".",".",".","2",".",".","."],
     [".","2",".","9",".",".",".",".","."],
     [".",".","4",".",".",".",".",".","."]]
) == False

assert s.isValidSudoku(
    [[".","4",".",".",".",".",".",".","."],
     [".",".","4",".",".",".",".",".","."],
     [".",".",".","1",".",".","7",".","."],
     [".",".",".",".",".",".",".",".","."],
     [".",".",".","3",".",".",".","6","."],
     [".",".",".",".",".","6",".","9","."],
     [".",".",".",".","1",".",".",".","."],
     [".",".",".",".",".",".","2",".","."],
     [".",".",".","8",".",".",".",".","."]]
    ) == False
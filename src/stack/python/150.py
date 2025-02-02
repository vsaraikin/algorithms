class Solution:
    def evalRPN(self, tokens: list[str]) -> int:
        if not tokens:
            return 0  
        elif len(tokens) == 1:
            return int(tokens[0]) 

        digits = []
        ops = {'*', '/', '-', '+'}

        for tok in tokens:
            if tok not in ops:
                digits.append(int(tok))
            else:
                b = digits.pop()
                a = digits.pop()
                if tok == '*':
                    digits.append(a * b)
                elif tok == '/':
                    digits.append(int(a / b))
                elif tok == '-':
                    digits.append(a - b)
                else:
                    digits.append(a + b)

        return digits[0] 

                    
            
        
s = Solution()
assert s.evalRPN(["2","1","+","3","*"]) == 9
assert s.evalRPN(["4","13","5","/","+"]) == 6
assert s.evalRPN(["10","6","9","3","+","-11","*","/","*","17","+","5","+"]) == 22
assert s.evalRPN(["3","11","+","5","-"]) == 9
class Solution:
    def evalRPN(self, tokens: list[str]) -> int:
        stack = []
        operators = {
            '*': lambda a, b : a * b, 
            '/': lambda a, b : int(a / b), 
            '-': lambda a, b : a - b, 
            '+': lambda a, b : a + b
        }
        for t in tokens:
            if t in operators:
                b, a = stack.pop(), stack.pop()
                result = operators[t](a, b)
                stack.append(result)
            else:
                stack.append(int(t))
        return stack[0]
                    
            
        
s = Solution()
assert s.evalRPN(["2","1","+","3","*"]) == 9
assert s.evalRPN(["4","13","5","/","+"]) == 6
assert s.evalRPN(["10","6","9","3","+","-11","*","/","*","17","+","5","+"]) == 22
assert s.evalRPN(["3","11","+","5","-"]) == 9
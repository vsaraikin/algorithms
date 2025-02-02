class MinStack:

    def __init__(self):
        self.stack = []
        self.min_values = []

    def push(self, val: int) -> None:
        self.stack.append(val)

        if len(self.min_values) >= 1:
            if self.min_values[-1] >= self.stack[-1]:
                self.min_values.append(val)
        else:
            self.min_values.append(val)
  

    def pop(self) -> None:
        if self.stack[-1] == self.min_values[-1]:
            self.min_values.pop()
            
        return self.stack.pop()

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return self.min_values[-1]
    
    
obj = MinStack()
obj.push(0)
obj.push(1)
obj.push(0)
obj.pop()
assert obj.top() == 1
assert obj.getMin() == 0

import math

def validParantheses(s: str):
    stack = []
    for i, c in enumerate(s):
        if c == '(' or c == '[' or c == '{':
            stack.append(c)
        if c == ')':
            if not stack or stack.pop() != "(":
                return False
        if c == ']':
            if not stack or stack.pop() != "[":
                return False
        if c == '}':
            if not stack or stack.pop() != "{":
                return False
    if stack:
        return False
    return True

class MinStack:
    def __init__(self):
        self.stack = []
        self.minStack = []
    def push(self, val: int) -> None:
        self.stack.append(val)
        if not self.minStack or val <= self.minStack[-1]:
            self.minStack.append(val)
    def pop(self) -> None:
        if self.minStack[-1] == self.stack[-1]:
            self.minStack.pop()
        self.stack.pop()
    def top(self) -> int:
        return self.stack[-1]
    def getMin(self) -> int:
        return self.minStack[-1]

def evalRPN(tokens: list[str]):
    stack = []
    for token in tokens:
        if (token[0] == '-' and token[1:].isnumeric()) or token.isnumeric():
            stack.append(int(token))
            continue
        a = stack.pop()
        b = stack.pop()
        if token == '+':
            stack.append(b+a)
        elif token == '-':
            stack.append(b-a)
        elif token == '*':
            stack.append(b*a)
        elif token == '/':
            stack.append(int(b/a))
    return stack[0]

def generateParentheses(n: int):
    result = []
    def genParanHelper(open, close, current):
        if (open == close and open == n):
            result.append(current)
            return
        if (open < n):
            genParanHelper(open+1, close, current + "(")
        if (close < open):
            genParanHelper(open, close+1, current + ")")
    
    genParanHelper(0, 0, "")
    return result

def dailyTemperatures(temperatures: list[int]):
    answer = [0] * len(temperatures)
    currentStack = []
    i = 0
    for temp in temperatures:
        while (currentStack and currentStack[-1][0] < temp):
            oldTemp, index = currentStack.pop()
            answer[index] = i-index
        currentStack.append((temp, i))
        i += 1
    return answer

def carFleet(target: int, position: list[int], speed: list[int]):
    fleets = 0
    currentFleetTime = -1
    posiSpeeds = sorted(zip(position, speed), key=lambda x: -x[0])
    for pos, s in posiSpeeds:
        t = (target-pos) / s
        if t > currentFleetTime:
            currentFleetTime = t
            fleets += 1
    return fleets

def largestRectangleHistogram(heights: list[int]):
    maxArea = 0
    stack = []
    for i, h in enumerate(heights):
        thisStart = i
        while stack and h < stack[-1][1]:
            start, lastH = stack.pop()
            area = (i - start) * lastH
            maxArea = max(area, maxArea)
            thisStart = start
        stack.append((thisStart, h))
    
    while stack:
        start, lastH = stack.pop()
        area = (len(heights) - start) * lastH
        maxArea = max(area, maxArea)
    
    return maxArea

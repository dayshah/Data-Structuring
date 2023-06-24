
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

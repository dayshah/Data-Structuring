import collections

def numIslands(grid: list[list[int]]):
    visited = set()
    islands = 0

    def getNeighbors(i: int, j: int) -> list[int]:
        return [(i+1,j), (i-1,j), (i,j+1), (i,j-1)]
    def isValidNeighbor(i: int, j: int) -> bool:
        return (i, j) not in visited and i >= 0 and i < len(grid) and j >= 0 and j < len(grid[i]) and grid[i][j] == "1"
    
    def dfs(i: int, j: int):
        stack = [(i, j)]
        while stack:
            current = stack.pop()
            visited.add(current)
            neighbors = getNeighbors(current[0], current[1])
            for x, y in neighbors:
                if isValidNeighbor(x, y):
                    stack.append((x,y))

    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == "0":
                continue
            if (i,j) not in visited:
                islands += 1
                dfs(i, j)
    return islands

class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

def cloneGraph(self, node: Node) -> Node:
    if not node:
        return None
    newRoot = Node(node.val)
    newDeck = {node.val: newRoot}
    oldDeck = collections.deque([node])
    while oldDeck:
        oldN = oldDeck.popleft()
        newN = newDeck[oldN.val]
        for next in oldN.neighbors:
            if next.val not in newDeck:
                oldDeck.append(next)
                newDeck[next.val] = Node(next.val)
            newN.neighbors.append(newDeck[next.val])
    return newRoot

def maxArea(grid: list[list[int]]):
    visited = set()
    maxArea = 0
    def getNeighbors(i: int, j: int) -> list[int]:
        return [(i+1,j), (i-1,j), (i,j+1), (i,j-1)]
    def isValidNeighbor(i: int, j: int) -> bool:
        return (i, j) not in visited and i >= 0 and i < len(grid) and j >= 0 and j < len(grid[i]) and grid[i][j] == 1
    
    def dfs(i: int, j: int):
        area = 1
        stack = [(i, j)]
        visited.add((i, j))
        while stack:
            current = stack.pop()
            neighbors = getNeighbors(current[0], current[1])
            for x, y in neighbors:
                if isValidNeighbor(x, y):
                    stack.append((x,y))
                    visited.add((x,y))
                    area += 1
        return area

    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if grid[i][j] == 1 and (i,j) not in visited:
                maxArea = max(maxArea, dfs(i, j))
    return maxArea

grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
print(maxArea(grid))
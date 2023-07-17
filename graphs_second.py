
import collections

# can finish all courses
# is it a DAG
def canFinish(numCourses: int, prerequisites: list[list[int]]) -> bool:
    #creating adjList
    adjList = collections.defaultdict(list)
    for before, after in prerequisites:
        adjList[after].append(before)
    
    visiting = set()
    def dfs(course):
        visiting.add(course)
        # if the list of prereqs becomes empty we can complete all of them
        while adjList[course]:
            before = adjList[course].pop()
            # if it's in the current visiting set it's a cycle
            if before in visiting:
                return False
            if not dfs(before):
                return False
        visiting.remove(course)
        return True
    
    for course in range(numCourses):
        if not dfs(course):
            return False
    return True

# topological sort
def findOrder(numCourses: int, prerequisites: list[list[int]]) -> list[int]:
    ordering = []
    adjList = collections.defaultdict(list)
    #create adj list
    for after, before in prerequisites:
        adjList[after].append(before)
    
    visiting = set()
    completed = set()
    def dfs(course):
        # if we've already gone through and added to ordering
        if course in completed:
            return True
        # if it's a cycle
        if course in visiting:
            return False
        visiting.add(course)
        while adjList[course]:
            before = adjList[course].pop()
            if not dfs(before):
                return False
        ordering.append(course)
        completed.add(course)
        visiting.remove(course)
        return True
    for course in range(numCourses):
        if not dfs(course):
            return []
    return ordering

def findRedundantConnection(edges: list[list[int]]):
    parents = {}
    def findParent(x):
        par = parents[x]
        while par != parents[par]:
            par = parents[par]
        return par
    def union(x, y):
        parX = findParent(x)
        parY = findParent(y)
        if parX == parY:
            return False

    for x, y in edges:
        if not union(x, y):
            return [x,y]

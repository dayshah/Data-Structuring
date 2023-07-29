import collections

# number of unique paths from (0,0) to (n, m)
def uniquePaths(n, m):
    numPathsFrom = collections.defaultdict(int)
    numPathsFrom[(m-1, n-1)] = 1
    for i in range(m-1, -1, -1):
        for j in range(n-1, -1, -1):
            if i == m-1 and j == n-1: continue
            down = numPathsFrom[(i+1, j)]
            right = numPathsFrom[(i, j+1)]
            numPathsFrom[(i, j)] = down + right
    return numPathsFrom[(0,0)]

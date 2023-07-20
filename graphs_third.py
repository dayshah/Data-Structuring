import collections

def findItinerary(tickets: list[list[str]]):
    adjList = collections.defaultdict(list)
    for x, y in tickets:
        adjList[x].append(y)

    itinerary = []
    def dfs(x):
        adjList[x].sort(reverse=True)
        while adjList[x]:
            y = adjList.pop()
            dfs(y)
        itinerary.append(x)
    dfs("JFK")
    return reversed(itinerary)

import heapq
# Prim's algorithm
def minCostConnectPoints(points: list[list[int]]):
    connected = set()
    x, y = points[0]
    distances = [(0, x, y)]
    minCost = 0
    while len(connected) < len(points):
        dist, x, y = heapq.heappop(distances)
        if (x,y) in connected:
            continue
        minCost += dist
        connected.add((x,y))
        for x1, y1 in points:
            if (x1,y1) == (x,y) or (x1,y1) in connected:
                continue
            dist = abs(x1-x) + abs(y1-y)
            heapq.heappush(distances, (dist, x1, y1))
    return minCost

# Dijkstra's for every dest
def networkDelayTime(times: list[list[int]], n: int, k: int):
    adjList = collections.defaultdict(list)
    for src, dest, time in times:
        adjList[src].append((time, dest))
    costs = [(0, k)]
    visited = set()
    path = 0
    while len(visited) < n:
        if not costs:
            return -1
        cost, src = heapq.heappop(costs)
        if src in visited:
            continue
        visited.add(src)
        path = cost
        while adjList[src]:
            time, dest = adjList[src].pop()
            heapq.heappush(costs, (time+path, dest))
    return path

# Bellman-Ford
def findCheapestPrice(n: int, flights: list[list[int]], src: int, dst: int, k: int):
    #for cost, start, end in flights:
    costs = [float("infinity") for i in range(n)]
    costs[src] = 0
    stops = 0
    while stops <= k:
        currentCosts = costs.copy()
        for fr, to, price in flights:
            costs[to] = min(currentCosts[fr]+price, costs[to])
        stops += 1
    if costs[dst] == float("infinity"):
        return -1
    else:
        return costs[dst]

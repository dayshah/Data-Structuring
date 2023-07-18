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
        print(minCost)
        print(connected)
        for x1, y1 in points:
            if (x1,y1) == (x,y) or (x1,y1) in connected:
                continue
            dist = abs(x1-x) + abs(y1-y)
            heapq.heappush(distances, (dist, x1, y1))
    return minCost

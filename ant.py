from random import randint

# Stworzenie macierzy 

INF = 1e18 + 10

N = 10  # size of the graph

adjMatrix = []
pheromoneMatrix = []

edges = []

for i in range(N):
    for j in range(i + 1, N):
        weight = randint(1, 30)
        edges.append([i, j, weight])


for i in range(N):
    adjMatrix.append([])
    pheromoneMatrix.append([])
    for j in range(N):
        adjMatrix[i].append(0)
        pheromoneMatrix[i].append(1)

for v, u, weight in edges:
    adjMatrix[v][u] = weight
    adjMatrix[u][v] = weight

for i in range(N):
    adjMatrix[i][i] = INF
    


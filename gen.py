import random


n = int(input())
m = n * (n - 1) // 2

print(n, m)

for i in range(1, n + 1):
    for j in range(i + 1, n + 1):
        c = random.uniform(1, 10000)
        print(i, j, c)

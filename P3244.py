mod = 10**9 + 7

n, m, x, y = map(int, input().split())

g = {}
in_degree = {}
dp = {}
ans = 1

def dfs(v):
    if dp[v] != 0:
        return dp[v]
    for i in g[v]:
        dfs(i)
        dp[v] += dp[i]
    dp[v] = dp[v] // in_degree[v]
    return dp[v] % mod

for i in range(n + 1):
    g[i] = []
    in_degree[i] = 0
    dp[i] = 0

for i in range(m):
    a, b = map(int, input().split())
    g[a].append(b)
    in_degree[b] += 1

dp[x] = 1

for i in range(2, n):
    if i == y:
        ans = ans * (in_degree[i] + 1)
    else:
        ans = ans * in_degree[i]
    dp[x] = dp[x] * in_degree[i]

if y == 1:
    print(ans)
else:
    dp[x] = dp[x] // in_degree[x]
    dp[x] = dp[x] % mod
    ans = ans - dfs(y)
    print(int(ans % (10**9 + 7)))
print(2 ** (mod - 2) % mod)
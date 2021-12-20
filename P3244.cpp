#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mod = 1e9 + 7;

struct Edge {
    int to, next;
}e[100005];

int vis[100005], head[100005], 
    cnt = 1, ans = 1, sum = 1, in[100005];

ll dp[100005];

void addArc(int x, int y) {
    e[cnt].to = y;
    e[cnt].next = head[x];
    head[x] = cnt++;
    in[y] ++;
}

ll ksm(ll a, int b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

ll inv(int a) {
    return ksm(a, mod - 2) % mod;
}

void dfs(int u, int y) {
    if (dp[u]) return;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        dfs(v, y);
        dp[u] += (dp[u] + dp[v]) % mod;
        dp[u] = dp[u] % mod;
    }
    dp[u] = dp[u] * inv(in[u]);
    return;
}

main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    for(int i = 1;i <= m;i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addArc(a, b);
    }
    ans = 1; cnt = 1; in[1] = 1;
    for(int i = 1;i <= n;i++) {
        ans = (ans * in[i]) % mod;
        if(i == y) {
            cnt = (cnt * (in[i] + 1)) % mod;
        }
        else {
            cnt = (cnt * in[i]) % mod;
        }
    }
    dp[x] = (ans * inv(in[x])) % mod;
    dp[x] %= mod;
    dfs(y, y);
    cnt = (cnt - dp[y] + mod) % mod;
    if(y == 1 || x == y) printf("%d\n", ans);
    else printf("%d\n", cnt);
    return 0;
}
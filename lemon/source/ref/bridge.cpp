#include <cstdio>
#include <cstring>
static const int MAXN = 64;
static const int INF = 0x3fffffff;
template <typename T> inline T min(T a, T b) { return a < b ? a : b; }

int n, a1, a2, an, b1, b2, bn;
char graph[MAXN][MAXN];
int a[MAXN][MAXN] = {{ 0 }};
int source, sink;

int dist[MAXN];
int cur[MAXN];

bool dinic_lvlgraph()
{
    memset(dist, -1, sizeof dist);
    static int q[MAXN], qhead, qtail;
    dist[source] = 0;
    q[0] = source; qhead = 1; qtail = 0;
  
    while (qhead != qtail) {
        int u = q[qtail++];
        for (int v = 0; v < n; ++v) if (a[u][v] > 0 && dist[v] == -1) {
            dist[v] = dist[u] + 1;
            q[qhead++] = v;
        }
    }

    return (dist[sink] > 0);
}

int dinic_augment(int u, int cap = INF)
{
    if (u == sink) return cap;
    int new_cap;
    for (int v = cur[u]; v < n; ++v, ++cur[u])
        if (a[u][v] > 0 && dist[v] == dist[u] + 1
            && (new_cap = dinic_augment(v, min(cap, a[u][v]))) > 0)
        {
            a[u][v] -= new_cap;
            a[v][u] += new_cap;
            return new_cap;
        }
    return 0;
}

int dinic()
{
    int ans = 0, aug;
    while (dinic_lvlgraph()) {
        memset(cur, 0, sizeof cur);
        while ((aug = dinic_augment(source)) > 0) ans += aug;
    }
    return ans;
}

bool work()
{
    if (scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) != 7) return false;
    getchar();
    memset(graph, 0, sizeof graph);
    for (int i = 0; i < n; ++i) gets(graph[i]);

    n += 2;
    source = n - 2; sink = n - 1;

    memset(a, 0, sizeof a);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) switch (graph[i][j]) {
            case 'X': break;
            case 'O': a[i][j] = 1; break;
            case 'N': a[i][j] = INF; break;
            default: break;
        }
    a[source][a1] = a[a2][sink] = an;
    a[source][b1] = a[b2][sink] = bn;
    int flow_1 = dinic();

    memset(a, 0, sizeof a);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) switch (graph[i][j]) {
            case 'X': break;
            case 'O': a[i][j] = 1; break;
            case 'N': a[i][j] = INF; break;
            default: break;
        }
    a[source][a1] = a[a2][sink] = an;
    a[source][b2] = a[b1][sink] = bn;
    int flow_2 = dinic();

    puts((flow_1 == an + bn && flow_2 == an + bn) ? "Yes" : "No");

    return true;
}

int main()
{
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);

    while (work());

    fclose(stdin); fclose(stdout);
    return 0;
}

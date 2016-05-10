#include <cstdio>
#include <vector>
static const int MAXN = 500008;
static const int MAXD = 22;
typedef std::vector<int> edgelist;
template <typename T> inline void update_min(T &a, T b) { if (a > b) a = b; }

int n, d, m;
int w[MAXN];
bool marked[MAXN][MAXD] = {{ false }};
edgelist e[MAXN];

int f[MAXN][MAXD] = {{ 0 }}, g[MAXN][MAXD] = {{ 0 }};

void dfs_calc(int u = 0, int p = MAXN - 1)
{
    // Build tree
    int v;
#define each_child(__var) \
    /*for*/ (edgelist::iterator __ch = e[u].begin(); __ch != e[u].end(); ++__ch) \
        if ((__var = *__ch) != p)

    for each_child(v) {
        dfs_calc(v, u);
        for (int i = 0; i < d; ++i)
            marked[u][i + 1] |= marked[v][i];
    }

    // DP calculations
    if (e[u].size() == 1 && u != 0) {
        f[u][0] = g[u][0] = (marked[u][0] ? w[u] : 0);
        for (int i = 1; i <= d; ++i) {
            f[u][i] = 0; g[u][i] = w[u];
        }
        return;
    }

    g[u][d] = w[u];
    for each_child(v) {
        for (int i = 1; i <= d; ++i) f[u][i] += f[v][i - 1];
        g[u][d] += f[v][d];
    }

    for (int i = d - 1; i >= 0; --i) {
        int sum = 0; for each_child(v) sum += f[v][i];
        g[u][i] = g[u][i + 1];
        for each_child(v)
            update_min(g[u][i], sum - f[v][i] + g[v][i + 1]);
    }

    f[u][0] = g[u][0];
    for (int i = 1; i <= d; ++i) update_min(f[u][i], f[u][i - 1]);
    for (int i = d - 1; i >= 0; --i)
        if (!marked[u][i]) update_min(f[u][i], f[u][i + 1]);
    g[u][0] = f[u][0];

#undef each_child
}

int main()
{
    freopen("observer.in", "r", stdin);
    freopen("observer.out", "w", stdout);

    int u, v;
    scanf("%d%d", &n, &d);
    for (int i = 0; i < n; ++i) scanf("%d", &w[i]);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &u);
        marked[u - 1][0] = true;
    }
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d%d", &u, &v);
        e[u - 1].push_back(v - 1);
        e[v - 1].push_back(u - 1);
    }

    dfs_calc();
    /*for (int i = 0; i < n; ++i)
        for (int j = 0; j <= d; ++j)
            printf("%d%c", f[i][j], j == d ? '\n' : ' ');
    puts("====");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= d; ++j)
            printf("%d%c", g[i][j], j == d ? '\n' : ' ');*/
    printf("%d\n", f[0][0]);

    fclose(stdin); fclose(stdout);
    return 0;
}


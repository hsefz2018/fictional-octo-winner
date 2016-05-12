#include <cstdio>
#include <algorithm>
static const int MAXN = 512;
template <typename T> inline T abs(T x) { return x < 0 ? -x : x; }

template <typename T> double *gaussian_elimination(int n, T a[MAXN][MAXN])
{
    for (int i = 0; i < n - 1; ++i) {
        // Partial pivoting
        double maxval = abs(a[i][i]);
        int maxidx = i;
        for (int j = i + 1; j < n; ++j) if (abs(a[j][i]) > maxval) {
            maxval = abs(a[j][i]);
            maxidx = j;
        }
        if (maxidx != i) {
            // Swap lines #i and #maxidx
            for (int j = 0; j <= n; ++j)
                std::swap(a[i][j], a[maxidx][j]);
        }
        // Elimination
        for (int j = i + 1; j < n; ++j) {
            for (int k = i + 1; k <= n; ++k)
                a[j][k] -= a[i][k] * a[j][i] / a[i][i];
            a[j][i] = 0;
        }
    }

    double *x = new double[MAXN]();
    for (int i = n - 1; i >= 0; --i) {
        x[i] = a[i][n] / a[i][i];
        for (int j = i - 1; j >= 0; --j)
            a[j][n] -= a[j][i] * x[i];
    }
    return x;
}

int n, m;
bool a[MAXN][MAXN];
int deg[MAXN];
double g[MAXN][MAXN] = {{ 0 }};

int main()
{
    freopen("desired.in", "r", stdin);
    freopen("desired.out", "w", stdout);

    scanf("%d%d", &n, &m);
    int u, v;
    do {
        scanf("%d%d", &u, &v); --u, --v;
        a[u][v] = a[v][u] = true;
        ++deg[u]; ++deg[v];
    } while (--m);

    for (u = 0; u < n; ++u) {
        for (v = 0; v < n - 1; ++v)
            if (a[u][v]) g[u][v] = 1.0 / deg[v];
    }
    for (int i = 0; i < n; ++i)
        g[i][i] -= 1.0;
    g[0][n] = -1.0;
    double *c_vert = gaussian_elimination(n, g);

    double c_edge[MAXN * MAXN];
    m = 0;
    for (u = 0; u < n - 1; ++u)
        for (v = u + 1; v < n; ++v) if (a[u][v])
            c_edge[m++] = c_vert[u] / deg[u] + (v == n - 1 ? 0 : c_vert[v] / deg[v]);
    std::sort(c_edge, c_edge + m);

    double ans = 0;
    for (int i = 0; i < m; ++i)
        ans += (m - i) * c_edge[i];
    printf("%.3lf\n", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}


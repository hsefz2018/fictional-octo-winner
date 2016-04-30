#include <cstdio>
#include <cstring>
#include <algorithm>
static const int MAXN = 1024;
static const int MAXM = MAXN * MAXN / 2;
typedef double mat[MAXN][MAXN];
int mat_size = 1;
mat MAT_IDENTITY = {{ 1.0 }};

int n, m;
bool a[MAXN][MAXN];
int out[MAXN] = { 0 };
double edge_w[MAXM];
mat g;

inline void mat_init(int sz)
{
	mat_size = sz;
	for (int i = 0; i < sz; ++i)
		MAT_IDENTITY[i][i] = 1.0;
}
inline void mat_assign(mat a, mat b)
{
	for (register int i = 0; i < mat_size; ++i)
		memcpy(a[i], b[i], mat_size * sizeof(a[0][0]));
}
inline void mat_mul(mat a, mat b)
{
	static mat ans;
	for (int i = 0; i < mat_size; ++i) {
		for (int j = 0; j < mat_size / 2; ++j) {
			ans[i][j] = 0.0;
			for (register int k = 0; k < mat_size; ++k)
				ans[i][j] += a[i][k] * b[k][j];
		}
		for (register int j = mat_size / 2; j < mat_size; ++j)
			ans[i][j] = a[i][j];
	}
	mat_assign(a, ans);
}

int main()
{
	freopen("desired.in", "r", stdin);
	freopen("desired.out", "w", stdout);

	scanf("%d%d", &n, &m);
	mat_init(n + n);
	int u, v;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v); --u, --v;
		a[u][v] = a[v][u] = true;
		++out[u]; ++out[v];
	}
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < n; ++j)
			g[i][j] = a[i][j] ? (1.0 / out[i]) : 0.0;
	for (int i = 0; i < n; ++i)
		g[i + n][i] = g[i + n][i + n] = 1.0;
	for (int i = 0; i < 16; ++i) mat_mul(g, g);

	int edge_ct = 0;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < n; ++j) if (a[i][j]) {
			edge_w[edge_ct++] = g[n][i] / out[i] + (j == n - 1 ? 0 : g[n][j] / out[j]);
		}
	std::sort(edge_w, edge_w + m);
	double ans = 0.0;
	for (int i = 0; i < m; ++i)
		ans += (m - i) * edge_w[i];
	printf("%.3lf\n", ans);

	fclose(stdin); fclose(stdout);
	return 0;
}


#include <cstdio>
#include <cstring>
static const int MAXN = 18;
static const int MODULUS = 1e9 + 7;
typedef long long int64;
#define _ % MODULUS
inline int64 __(int64 x) { return (x _ + MODULUS)_; }
inline int64 fpow(int64 base, int exp) {
    int64 ans = 1;
    while (exp) {
        if (exp & 1) ans = ans * base _;
        base = base * base _;
        exp >>= 1;
    }
    return ans;
}
inline int64 inv(int64 x) { return fpow(x, MODULUS - 2); }

int n, m[MAXN], e[MAXN][MAXN * MAXN][2];
int a[MAXN][MAXN];

int64 det(int n, int64 a[][MAXN])
{
    int64 ans, mul = 1;
    // Gaussian elimination
    int64 inv_aii;
    for (int i = 0; i < n; ++i) {
        inv_aii = inv(a[i][i]);
        for (int j = i + 1; j < n; ++j) {
            for (int k = i + 1; k < n; ++k)
                a[j][k] = (a[j][k] - a[i][k] * a[j][i]_ * inv_aii _)_;
            a[j][i] = 0;
        }
    }

    ans = 1;
    for (int i = 0; i < n; ++i)
        ans = ans * a[i][i]_;
    return __(ans);
}

int64 spanning_tree_count(int n, int a[][MAXN])
{
    static int64 d[MAXN][MAXN];
    memset(d, 0, sizeof d);
    for (int i = 1; i < n; ++i) if (a[0][i]) d[i - 1][i - 1] += a[0][i];
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < n; ++j) if (a[i][j]) {
            d[i - 1][j - 1] = -a[i][j];
            d[i - 1][i - 1] += a[i][j];
        }
    /*for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1; ++j)
            printf("%lld%c", d[i][j], j + 2 == n ? '\n' : ' ');
    puts("===");*/
    return det(n - 1, d);
}

int main()
{
    freopen("ptree.in", "r", stdin);
    freopen("ptree.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d", &m[i]);
        for (int j = 0; j < m[i]; ++j) {
            scanf("%d%d", &e[i][j][0], &e[i][j][1]);
            --e[i][j][0], --e[i][j][1];
        }
    }
    int64 ans = 0;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        memset(a, false, sizeof a);
        for (int i = 0; i < n - 1; ++i) if (mask & (1 << i)) {
            for (int j = 0; j < m[i]; ++j)
                ++a[e[i][j][0]][e[i][j][1]], ++a[e[i][j][1]][e[i][j][0]];
        }
        ans += spanning_tree_count(n, a) * (((__builtin_popcount(mask) ^ n) & 1) ? 1 : -1);
    }
    printf("%lld\n", __(ans));

    fclose(stdin); fclose(stdout);
    return 0;
}


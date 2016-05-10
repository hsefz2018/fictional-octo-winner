#include <cstdio>
#include <cstring>
#include <algorithm>
static const int MAXN = 105;
static const int MAXM = 105;
typedef long long int64;
template <typename T> inline T abs(T x) { return x < 0 ? -x : x; }

static const int64 MODULUS = 1000000007;
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

int64 fact[MAXN], inv_fact[MAXN];
void cbnation_init()
{
    fact[0] = fact[1] = inv_fact[0] = inv_fact[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i _;
        inv_fact[i] = inv(fact[i]);
    }
}
inline int64 cbnation(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fact[n] * inv_fact[m]_ * inv_fact[n - m]_;
}
inline int64 pmtation(int n, int m) {
    return fact[n] * inv_fact[n - m]_;
}

static const int MAXPOW = 212;
int64 *gaussian_elimination(int n, int64 a[][MAXPOW])
{
    for (int i = 0; i < n - 1; ++i) {
        int64 inv_aii = inv(a[i][i]);
        for (int j = i + 1; j < n; ++j) {
            for (int k = i + 1; k <= n; ++k)
                a[j][k] = (a[j][k] - a[i][k] * a[j][i]_ * inv_aii _)_;
            a[j][i] = 0;
        }
    }

    int64 *x = new int64[MAXPOW]();
    for (int i = n - 1; i >= 0; --i) {
        x[i] = __(a[i][n]_ * inv(a[i][i])_);
        for (int j = i - 1; j >= 0; --j)
            a[j][n] -= a[j][i] * x[i]_;
    }
    return x;
}
int64 *pow_sum_coef[MAXPOW] = { NULL };
int64 pow_sum(int pow, int64 x)
{
    static int64 a[MAXPOW][MAXPOW];
    int64 *coef;
    if ((coef = pow_sum_coef[pow]) == NULL) {
        int n = pow + 2;
        for (int i = 0; i < n; ++i) {
            a[i][n] = (i ? (a[i - 1][n] + fpow(i, pow))_ : 0);
            a[i][0] = 1;
            for (int j = 1; j < n; ++j) a[i][j] = a[i][j - 1] * i _;
        }
        coef = pow_sum_coef[pow] = gaussian_elimination(n, a);
    }
    int64 ans = 0, x_pow = 1;
    for (int i = 0; i <= pow + 1; ++i) {
        ans = (ans + x_pow * coef[i])_;
        x_pow = (x_pow * x)_;
    }
    return ans;
}

int n, m, k;
int u[MAXM], r[MAXM];

int64 nyanya_item[MAXN];
void nyanpasu()
{
    int64 item;
    for (int i = 0; i < m; ++i) {
        /*for (int score = 1; score <= u[i]; ++score) {
            item += fpow(score, n - r[i]) * fpow(u[i] - score, r[i] - 1)_;
        }*/
        item = 0;
        for (int j = 0; j <= r[i] - 1; ++j)
            item += cbnation(r[i] - 1, j) * fpow(u[i], r[i] - 1 - j)_ * /*fpow(-1, j)_*/((j & 1) ? -1 : 1) * pow_sum(j + n - r[i], u[i])_;
        nyanya_item[i] = __(item);
    }
}
int64 nyanya(int k)
{
    int64 prod = 1;
    for (int i = 0; i < m; ++i) {
        if (r[i] + k > n) return 0;
        prod = prod * nyanya_item[i]_ * cbnation(n - k - 1, r[i] - 1)_;
    }
    prod = prod * cbnation(n - 1 - ::k, k - ::k)_;
    return prod;
}

int main()
{
    freopen("mark.in", "r", stdin);
    freopen("mark.out", "w", stdout);

    cbnation_init();
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i) scanf("%d", &u[i]);
    for (int i = 0; i < m; ++i) scanf("%d", &r[i]);

    int64 ans = 0;
    nyanpasu();
    for (int i = k; i < n; ++i)
        ans += nyanya(i) * (((i ^ k) & 1) ? -1 : 1);
    ans = __(ans) * cbnation(n - 1, k)_;
    printf("%lld\n", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}


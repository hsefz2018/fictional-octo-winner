#include <cstdio>
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

int n, m, k;
int u[MAXM], r[MAXM];

int64 nyanya(int k)
{
    int64 prod = 1, item;
    for (int i = 0; i < m; ++i) {
        item = 0;
        for (int score = 1; score <= u[i]; ++score) {
            item += fpow(score, n - r[i]) * fpow(u[i] - score, r[i] - 1)_;
        }
        if (r[i] + k > n) item = 0;
        else item = item * cbnation(n - k - 1, r[i] - 1)_;
        prod = prod * item _;
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
    for (int i = k; i < n; ++i)
        ans += nyanya(i) * (((i ^ k) & 1) ? -1 : 1);
    ans = __(ans) * cbnation(n - 1, k)_;
    printf("%lld\n", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}

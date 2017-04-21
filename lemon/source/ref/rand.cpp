#include <cstdio>
#include <set>
typedef long long int64;
static const int MAXN = 100004;
static const int MODULUS = 1e9 + 7;
#define _  %  MODULUS
#define __ %= MODULUS

int n, q, a[MAXN];
int pow3[MAXN], seq[MAXN];

namespace sgt {

static const int MAXN = ::MAXN * 2;
int sz;
int l[MAXN], r[MAXN], lch[MAXN], rch[MAXN];
int sum[MAXN], tag[MAXN];

inline void apply(int idx, int val) {
    sum[idx] = (int64)sum[idx] * val _;
    tag[idx] = (int64)tag[idx] * val _;
}
inline void push(int idx) {
    if (lch[idx] == -1 || tag[idx] == 1) return;
    apply(lch[idx], tag[idx]);
    apply(rch[idx], tag[idx]);
    tag[idx] = 1;
}
inline void update(int idx) {
    push(idx);
    sum[idx] = (sum[lch[idx]] + sum[rch[idx]])_;
}

int build(int L, int R) {
    int idx = sz++;
    l[idx] = L, r[idx] = R; tag[idx] = 1;
    if (L == R) {
        lch[idx] = rch[idx] = -1;
        sum[idx] = ::seq[L];
    } else {
        int M = (L + R) >> 1;
        lch[idx] = build(L, M);
        rch[idx] = build(M + 1, R);
        update(idx);
    }
    return idx;
}
inline void build(int N) { sz = 0, build(0, N - 1); }

int QL, QR, QV;

inline int query_sum(int idx) {
    push(idx);
    if (l[idx] >= QL && r[idx] <= QR) return sum[idx];
    int ans = 0;
    if (r[lch[idx]] >= QL) ans += query_sum(lch[idx]);
    if (l[rch[idx]] <= QR) ans += query_sum(rch[idx]);
    return ans _;
}
inline int query_sum(int L, int R) { if (L > R) return 0; QL = L, QR = R; return query_sum(0); }

inline void modify_mul(int idx) {
    push(idx);
    if (l[idx] >= QL && r[idx] <= QR) { apply(idx, QV); return; }
    if (r[lch[idx]] >= QL) modify_mul(lch[idx]);
    if (l[rch[idx]] <= QR) modify_mul(rch[idx]);
    update(idx);
}
inline void modify_mul(int L, int R, int V) { QL = L, QR = R, QV = V; modify_mul(0); }

}

inline int64 fpow(int64 base, int exp) {
    int64 ans = 1;
    for (; exp; exp >>= 1) { if (exp & 1) (ans *= base)__; (base *= base)__; }
    return ans;
}
inline int inv(int x) { return fpow(x, MODULUS - 2); }

int main()
{
    freopen("rand.in", "r", stdin);
    freopen("rand.out", "w", stdout);

    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    pow3[0] = 1; for (int i = 1; i < n; ++i) pow3[i] = ((int64)pow3[i - 1] * 3)_;

    std::set<int> zeroes;
    zeroes.insert(n);
    int64 prod = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) a[i] = 1, zeroes.insert(i);
        (prod *= a[i])__;
        seq[i] = prod * (i == n - 1 ? 1 : 2 * pow3[n - i - 2])_;
    }
    sgt::build(n);

    int t, v;
    std::set<int>::iterator p;
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &t, &v); --t;
        if (a[t] != v) {
            if (v == 0) {
                zeroes.insert(t);
            } else {
                if ((p = zeroes.find(t)) != zeroes.end()) zeroes.erase(p);
                int mul = (int64)v * inv(a[t])_;
                sgt::modify_mul(t, n - 1, mul);
                a[t] = v;
            }
        }
        printf("%d\n", sgt::query_sum(0, *zeroes.begin() - 1));
    }

    fclose(stdin); fclose(stdout);
    return 0;
}

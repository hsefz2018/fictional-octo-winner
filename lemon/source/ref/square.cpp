#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
typedef long long int64;
static const int MAXN = 1000004;
static const int MAXK = 2006;
static const int64 MODULUS = 100000007;
#define _ % MODULUS
#define __(__x) (((__x) % MODULUS + MODULUS) % MODULUS)

int n, m, k;
typedef std::pair<int, int> banned_pt;
banned_pt b[MAXK];
std::set<banned_pt> bset;

inline int64 fpow(int64 base, int exp) {
    int64 ans = 1;
    while (exp) {
        if (exp & 1) ans = (ans * base)_;
        base = (base * base)_;
        exp >>= 1;
    }
    return ans;
}
inline int64 inv(int64 x) { return fpow(x, MODULUS - 2); }
const int64 inv2 = inv(2);
const int64 inv4 = inv(4);
const int64 inv6 = inv(6);
const int64 inv8 = inv(8);
inline int64 sigma_cubic(int64 x) {
    return inv4 * x _ * x _ * (x + 1)_ * (x + 1)_;
}
inline int64 sigma_square(int64 x) {
    return inv6 * x _ * (x + 1)_ * (x + x + 1)_;
}
inline int64 sigma_linear(int64 x) {
    return inv2 * x _ * (x + 1)_;
}
int64 full(int64 n, int64 m)
{
    if (m > n) std::swap(n, m);
    int64 ans = sigma_cubic(m)
        - sigma_square(m) * (m + n + 2)_
        + sigma_linear(m) * (m * n _ + m + n + 1)_;
    return __(ans);
}

inline int64 single_aff(int64 n, int64 m, int64 c) {
    if (n == 0) return 0;
    int64 ans = 0;
    /*for (int i = 0; i <= std::min(c, n); ++i)
        ans += std::min(n - i + 1, m - c + 1);
    return __(ans - 1);*/
    int type_max = std::min(c, n);
    if (n <= m - c) ans += n * (type_max + 1)_ - sigma_linear(type_max);
    else if (n - type_max >= m - c) ans += (m - c) * (type_max + 1)_;
    else {
        int turnpoint = n - m + c;  // satisfying n - turnpoint + 1 == m - c + 1
        ans += (m - c) * (type_max + 1)_;
        ans -= sigma_linear(type_max - turnpoint)_;
    }
    return __(ans + type_max);
}
int64 single_aff(int64 r, int64 c) {
    int64 ans = 0;
    if (c > m / 2) c = m - c;
    if (r > n / 2) r = n - r;
    ans += (single_aff(r, m, c) + single_aff(n - r, m, c))_;
    ans += (single_aff(c, n, r) + single_aff(m - c, n, r))_;
    ans -= std::min(r, c);
    ans -= std::min(r, m - c);
    ans -= std::min(n - r, c);
    ans -= std::min(n - r, m - c);
    return __(ans);
}

inline int ban_state(int row, int col) {
    if (row < 0 || row > n || col < 0 || col > m) return 23333;
    return (bset.find(std::make_pair(row, col)) != bset.end());
}
inline bool try_diagonal(const banned_pt &p, const banned_pt &q, int &r, int &c) {
    if (((q.first - p.first) & 1) ^ ((q.second - p.second) & 1)) return false;
    int dr = q.first - p.first, dc = q.second - p.second;
    r = p.first + (dc + dr) / 2;
    c = p.second + (dc - dr) / 2;
    return true;
}

int main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);

    scanf("%d%d%d", &n, &m, &k);
    int row, col;
    for (int i = 0; i < k; ++i) {
        scanf("%d%d", &b[i].first, &b[i].second);
        bset.insert(b[i]);
    }

    int64 ans = full(n, m);
    for (int i = 0; i < k; ++i)
        ans -= single_aff(b[i].first, b[i].second);
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < k; ++j) if (i != j) {
            int extra =
                ban_state(b[i].first + b[j].second - b[i].second,
                          b[i].second - b[j].first + b[i].first) +
                ban_state(b[j].first + b[j].second - b[i].second,
                          b[j].second - b[j].first + b[i].first);
            switch (extra) {
                case 2: ans += inv8 * 3; break;
                case 1: ans += inv4 * 2; break;
                case 0: ans += 1; break;
                default: break;
            }
            // Check for diagonals
            extra = 0;
            if (try_diagonal(b[i], b[j], row, col)) {
                extra += ban_state(row, col);
                try_diagonal(b[j], b[i], row, col);
                extra += ban_state(row, col);
                switch (extra) {
                    case 2: ans += inv8 * 3; break;
                    case 1: ans += inv4 * 2; break;
                    case 0: ans += inv2; break;
                    default: break;
                }
            }
        }

    printf("%lld\n", __(ans));
    fclose(stdin); fclose(stdout);
    return 0;
}


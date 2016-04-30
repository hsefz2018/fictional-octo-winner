#include <cstdio>
#include <cstdlib>
#include <algorithm>
static const int MAXN = 400007;
static const long long INF = 0x7ffffffffffLL;
using std::min;
using std::max;

struct __sgt_node {
	int l, r, lch, rch;
	long long max;
} t[MAXN * 2];

int sgt_size = 0;
int sgt_build(int l, int r)
{
	int idx = sgt_size++;
	t[idx].l = l; t[idx].r = r;
	t[idx].max = -INF;
	if (l == r) {
		t[idx].lch = t[idx].rch = -1;
	} else {
		int m = (l + r) >> 1;
		t[idx].lch = sgt_build(l, m);
		t[idx].rch = sgt_build(m + 1, r);
	}
	return idx;
}
long long sgt_querymax(int l, int r, int idx = 0)
{
	if (t[idx].l >= l && t[idx].r <= r) return t[idx].max;
	long long ans = -INF;
	if (t[t[idx].lch].r >= l) ans = max(ans, sgt_querymax(l, r, t[idx].lch));
	if (t[t[idx].rch].l <= r) ans = max(ans, sgt_querymax(l, r, t[idx].rch));
	return ans;
}
void sgt_assign(int pos, long long val, int idx = 0)
{
	if (t[idx].l == t[idx].r) {
		t[idx].max = val;
	} else {
		if (t[t[idx].lch].r >= pos) sgt_assign(pos, val, t[idx].lch);
		else sgt_assign(pos, val, t[idx].rch);
		t[idx].max = max(t[t[idx].lch].max, t[t[idx].rch].max);
	}
}

int n, l, r;
int a[MAXN];
int main()
{
	freopen("ice.in", "r", stdin);
	freopen("ice.out", "w", stdout);

	scanf("%d%d%d", &n, &l, &r);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	sgt_build(0, n + n);
	sgt_assign(0, a[0]);
	for (int i = l; i <= n; ++i)
		sgt_assign(i, sgt_querymax(std::max(i - r, 0), i - l) + a[i]);
	printf("%lld\n", sgt_querymax(n - r + 1, n));

	fclose(stdin); fclose(stdout);
	return 0;
}


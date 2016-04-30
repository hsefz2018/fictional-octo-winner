#include <cstdio>
#include <cstring>
static const int MAXN = 1024;
static const int MODULUS = 999983;
typedef long long int64;
#define int int64

bool s[10] = { false };

inline int sqr(int x)
{
	return ((int64)x * x) % MODULUS;
}
int calc2(int n)
{
	int *a = new int[10 * n + 12];
	int64 ans = 0;
	//memset(a, 0, sizeof a);
    memset(a, 0, sizeof(int) * (10 * n + 12));
	a[0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 10 * n; j >= 0; --j) {
			for (register int k = 1; k <= 9; ++k)
				if (s[k]) a[j + k] = (a[j + k] + a[j]) % MODULUS;
			if (!s[0]) a[j] = 0;
		}
	}
	for (int i = 0; i <= 10 * n; ++i)
		ans = (ans + (int64)a[i] * a[i]) % MODULUS;
	return (ans % MODULUS + MODULUS) % MODULUS;
}
int calc(int n)
{
	int *a = new int[10 * n + 12];
	int64 ans = 0;
	//memset(a, 0, sizeof a);
    memset(a, 0, sizeof(int) * (10 * n + 12));
	a[0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 10 * n; j >= 0; --j) {
			for (register int k = 1; k <= 9; ++k)
				if (s[k]) a[j + k] = (a[j + k] + a[j]) % MODULUS;
			if (!s[0]) a[j] = 0;
		}
	}
	for (int i = 0; i <= 10 * n; ++i)
		ans = (ans + (int64)a[i] * a[i]) % MODULUS;
	if (n & 1) {
		ans += ans;
		ans -= (calc2(n / 2) * calc2(n / 2 + 1));
	} else {
		ans += ans;
		ans -= sqr(calc2(n / 2));
		ans += MODULUS;
	}
	delete[] a;
	return (ans % MODULUS + MODULUS) % MODULUS;
}

#undef int
int main()
#define int int64
{
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);

	int n;
	scanf("%lld", &n);
	char ch;
	while ((ch = getchar()) < '0' || ch > '9');
	do {
        //printf("%d [%c]\n", ch, ch);
		s[ch - '0'] = true;
		ch = getchar();
	} while (ch >= '0' && ch <= '9');
    //printf("%d\n", n);
    //for (int i = 0; i < 10; ++i) printf("%d", s[i]); putchar('\n');

	printf("%lld\n", calc(n));
	fclose(stdin); fclose(stdout);
	return 0;
}


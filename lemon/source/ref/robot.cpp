#include <cstdio>
static const int MAXN = 5008;

int n, t;
char s[MAXN];
int x[MAXN], y[MAXN];

inline void move(char op, int x0, int y0, int &x1, int &y1)
{
	switch (op) {
		case 'N': x1 = x0; y1 = y0 + 1; break;
		case 'S': x1 = x0; y1 = y0 - 1; break;
		case 'W': x1 = x0 - 1; y1 = y0; break;
		case 'E': x1 = x0 + 1; y1 = y0; break;
	}
}

int main()
{
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);

	n = 0;
	while ((s[n] = getchar()) != '\r' && s[n] != '\n') ++n;
	move(s[0], 0, 0, x[0], y[0]);
	for (int i = 1; i < n; ++i)
		move(s[i], x[i - 1], y[i - 1], x[i], y[i]);

	scanf("%d", &t);
	int cx = 0, cy = 0;
	cx += (t / n) * x[n - 1];
	cy += (t / n) * y[n - 1];
	if (t % n) {
		cx += x[t % n - 1];
		cy += y[t % n - 1];
	}
	printf("%d %d\n", cx, cy);

	fclose(stdin); fclose(stdout);
	return 0;
}


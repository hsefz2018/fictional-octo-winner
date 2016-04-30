#include <cstdio>
#include <algorithm>
#include <list>
static const int MAXN = 100005;
static const int MAXCOLOURS = 1000005;
typedef std::list<int> chain;

int n, m, cur_ans;
int a[MAXN];
chain ch[MAXCOLOURS];
int mapped[MAXCOLOURS];

inline void merge_and_update(int petite, int grande)
{
    //printf("Merging: %d -> %d\n", petite, grande);
    for (chain::iterator i = ch[petite].begin(); i != ch[petite].end(); ++i) {
        if (a[*i + 1] == grande) --cur_ans;
        if (*i && a[*i - 1] == grande) --cur_ans;
    }
    for (chain::iterator i = ch[petite].begin(); i != ch[petite].end(); ++i) {
        a[*i] = grande;
    }
    ch[grande].merge(ch[petite]);
}

int main()
{
    freopen("pudding.in", "r", stdin);
    freopen("pudding.out", "w", stdout);
    scanf("%d%d", &n, &m);
    cur_ans = 0;
    for (int i = 0; i < MAXCOLOURS; ++i) mapped[i] = i;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        ch[a[i]].push_back(i);
        if (!i || a[i] != a[i - 1]) ++cur_ans;
    }
    int op, x, y;
    do {
        scanf("%d", &op);
        switch (op) {
            case 1:
                scanf("%d%d", &x, &y);
                if (x != y) {
                    if (ch[x].size() > ch[y].size())
                        std::swap(mapped[x], mapped[y]);
                    // Merge lists and update # of segments
                    merge_and_update(mapped[x], mapped[y]);
                }
                break;
            case 2:
                printf("%d\n", cur_ans);
                break;
            default: break;
        }
    } while (--m);
    fclose(stdin); fclose(stdout);
    return 0;
}


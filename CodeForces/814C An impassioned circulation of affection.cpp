#include <cstdio>
#include <algorithm>

const int maxn = 1500 + 10;

int n;
char s[maxn];
int q;
int m;
char c;

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%d", &q);
    while (q--) {
        scanf("%d %c", &m, &c);
        int sum = 0;
        int ans = 0;
        for (int i = 0, j = i; i < n; i++) {
            for ( ; j < n && sum < m; j++) {
                if (s[j] != c) sum++;
            }
            while (s[j] == c) j++;
            ans = std::max(ans, j - i);
            if (s[i] != c) sum--;
        }
        printf("%d\n", ans);
    }
    return 0;
}
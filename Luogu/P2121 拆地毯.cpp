#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int maxM = 2e5 + 10;

int n, m, K;
int u, v, w;
int ans;
int cnt;

namespace Graph {
	struct Vertex {
		int fa;
	} vertex[maxN];

	struct Edge {
		int tail;
		int head;
		int weight;

		bool operator<(Edge other) const {
			return weight > other.weight;
		}
	} edge[maxM];

	int ecnt;

	void AddEdge(int tail, int head, int weight) {
		ecnt++;
		edge[ecnt].tail = tail;
		edge[ecnt].head = head;
		edge[ecnt].weight = weight;
		return;
	}

	int Get(int u) {
		if (vertex[u].fa == u) return u;
		return vertex[u].fa = Get(vertex[u].fa);
	}

	void Union(int u, int v) {
		u = Get(u);
		v = Get(v);
		vertex[u].fa = v;
		return;
	}

	void Kruscal() {
		for (int i = 1; i <= n; i++) vertex[i].fa = i;
		std::sort(edge + 1, edge + m + 1);
		for (int e = 1; e <= m; e++) {
			int u = Get(edge[e].tail);
			int v = Get(edge[e].head);
			if (u == v) continue;
			Union(u, v);
			ans += edge[e].weight;
			cnt++;
			if (cnt == K) break;
		}
		return;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &u, &v, &w), Graph::AddEdge(u, v, w);
	Graph::Kruscal();
	printf("%d\n", ans);
	return 0;
}
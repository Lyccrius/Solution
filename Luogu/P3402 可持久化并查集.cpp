#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int maxM = 2e5 + 10;

int n, m;

namespace PDS {
	struct Node {
		int l, r;
		int lNode;
		int rNode;
		int value;
		int depth;
	};

	int root[maxM];
	Node node[maxN * 30];
	int cnt;

	void Build(int &xNode, int l, int r) {
		cnt++;
		xNode = cnt;
		node[xNode].l = l;
		node[xNode].r = r;
		if (l == r) {
			node[xNode].value = l;
			node[xNode].depth = 1;
			return;
		}
		int mid = (l + r) >> 1;
		Build(node[xNode].lNode, l, mid);
		Build(node[xNode].rNode, mid + 1, r);
		return;
	}

	int Clone(int xNode) {
		cnt++;
		node[cnt] = node[xNode];
		return cnt;
	}

	int Query(int xNode, int x) {
		if (node[xNode].l == node[xNode].r) return xNode;
		int mid = (node[xNode].l + node[xNode].r) >> 1;
		if (mid >= x) return Query(node[xNode].lNode, x);
		else return Query(node[xNode].rNode, x);
	}

	int Find(int version, int x) {
		int pos = Query(root[version], x);
		if (node[pos].value == x) return pos;
		return Find(version, node[pos].value);
	}

	int Modify(int xNode, int x, int value) {
		int nNode = Clone(xNode);
		if (node[nNode].l == node[nNode].r) {
			node[nNode].value = value;
			return nNode;
		}
		int mid = (node[nNode].l + node[nNode].r) >> 1;
		if (mid >= x) node[nNode].lNode = Modify(node[xNode].lNode, x, value);
		else node[nNode].rNode = Modify(node[xNode].rNode, x, value);
		return nNode;
	}
	
	int Add(int xNode, int x) {
		int nNode = Clone(xNode); 
		if (node[nNode].l == node[nNode].r) {
			node[nNode].depth++;
			return nNode;
		}
		int mid = (node[nNode].l + node[nNode].r) >> 1;
		if (mid >= x) node[nNode].lNode = Add(node[xNode].lNode, x);
		else node[nNode].rNode = Add(node[xNode].rNode, x);
		return nNode;
	}

	void Union(int version, int x, int y) {
		root[version] = root[version - 1];
		x = Find(version, x);
		y = Find(version, y);
		if (node[x].value != node[y].value) {
			if (node[x].depth > node[y].depth) std::swap(x, y);
			root[version] = Modify(root[version - 1], node[x].value, node[y].value);
			if (node[x].depth == node[y].depth) root[version] = Add(root[version], node[y].value);
		}
		return;
	}

	bool Check(int version, int x, int y) {
		x = Find(version, x);
		y = Find(version, y);
		if (node[x].value == node[y].value) return true;
		else return false;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	PDS::Build(PDS::root[0], 1, n);
	for (int i = 1; i <= m; i++) {
		int opt;
		int a, b;
		int k;
		scanf("%d", &opt);
		switch(opt) {
			case 1: {
				scanf("%d%d", &a, &b);
				PDS::Union(i, a, b);
				break;
			}
			case 2: {
				scanf("%d", &k);
				PDS::root[i] = PDS::root[k];
				break;
			}
			case 3: {
				scanf("%d%d", &a, &b);
				if (PDS::Check(i - 1, a, b)) printf("1\n");
				else printf("0\n");
				PDS::root[i] = PDS::root[i - 1];
				break;
			}
		}
	}
	return 0;
}
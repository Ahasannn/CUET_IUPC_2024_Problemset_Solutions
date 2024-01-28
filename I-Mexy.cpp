#include<bits/stdc++.h>
// #define int long long
// #define endl '\n'
#define check(x) cout<< #x << " = " << x <<endl
#define vin(v) for(auto &x: v) cin >> x
#define all(v) v.begin(), v.end()
#define F first
#define S second
#define pb push_back

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int N = 1e5 + 5;
const int mod = 1000000007;
int bit[2][N];
void upd(int v, int i, int c) {
	if (i == 0) {
		bit[v][i] += c;
		return;
	}
	while (i < N) {
		bit[v][i] += c;
		i += i & -i;
	}
}
int qur(int v, int i) {
	int ret = 0;
	while (i) {
		ret += bit[v][i];
		i -= i & -i;
	}
	ret += bit[v][0];
	return ret;
}
vector<int> g[N];
bool big[N];
long long cur, ans[N];
int n, a[N], ansv[N], ansp[N], col[N], sz[N], cnt0[N], cnt1[N];
void dfs(int u, int p) {
	sz[u] = 1;
	for (auto v: g[u]) {
		if (v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}
void add(int u, int p, int x) {
	cnt0[a[u]] -= x;
	cnt1[a[u]] += x;
	if (cnt0[a[u]] == 0) upd(0, a[u], -1);
	if (cnt0[a[u]] == 1 && x < 0) upd(0, a[u], 1);
	if (cnt1[a[u]] == 0) upd(1, a[u], -1);
	if (cnt1[a[u]] == 1 && x > 0) upd(1, a[u], 1); 
	for (auto v: g[u]) {
		if (v == p || big[v] == 1) continue;
		add(v, u, x);
	}
}
int get(int v) {
	int l = 0, r = n + 1, ret = -1;
	while (l <= r) {
		int m = (l + r) >> 1;
		if (qur(v, m) <= m) ret = m, r = m - 1;
		else l = m + 1;
	}
	return ret;
}
void dsu(int u, int p, bool keep) {
	int bigchild = -1, mx = -1;
	for (auto v: g[u]) {
		if (v == p) continue;
		if (sz[v] > mx) mx = sz[v], bigchild = v;
	}
	for (auto v: g[u]) {
		if (v == p || v == bigchild) continue;
		dsu(v, u, 0);
	}
	if (bigchild != -1) dsu(bigchild, u, 1), big[bigchild] = 1;
	add(u, p, 1);
	
	ansv[u] = get(1);
	ansp[u] = get(0);
	cur += ansv[u];

	if (bigchild != -1) big[bigchild] = 0;
	if (keep == 0) add(u, p, -1);
}
void reroot(int u, int p) {
	ans[u] = cur;
	for (auto v: g[u]) {
		if (v == p) continue;
		cur += ansp[v] - ansv[v];
		reroot(v, u);
		cur -= ansp[v] - ansv[v];
	}
}
void solve(int tc) {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cnt0[a[i]]++;
		if (cnt0[a[i]] == 1) upd(0, a[i], 1);
	}
	dfs(0, -1);
	dsu(0, -1, 1);
	reroot(0, -1);
	for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
}

int32_t main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int T = 1;
	for(int t=1; t<=T; t++) {
		solve(t);
	}

	return 0;
}
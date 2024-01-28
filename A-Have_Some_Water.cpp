#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 3e5 + 9;
const ll inf = 1e12;
int a[N];
ll dp[N];
ll get_lcm(ll x, ll y) {
	ll g = __gcd(x, y);
	x /= g;
	if (x <= inf / y) return x * y;
	return inf;
}
int32_t main() {
	ios_base::sync_with_stdio(false);
	cout.tie(NULL);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		map<ll, int> mp;
		for (int i = 1; i <= n; i++) {
			int x; cin >> x;
			map<ll, int> cur;
			cur[x] = i;
			for (auto [y, j]: mp) {
				ll lc = get_lcm(x, y);
				if (lc >= inf) break;
				if (cur.find(lc) != cur.end()) {
					cur[lc] = min(cur[lc], j);
				}
				else {
					cur[lc] = j;
				}
			}
			mp = cur;
			dp[i] = dp[i - 1] + x;
			for (auto [y, j]: mp) {
				dp[i] = min(dp[i], dp[j - 1] + y);
			}
		}
		cout << dp[n] << '\n';
	}
	return 0;
}
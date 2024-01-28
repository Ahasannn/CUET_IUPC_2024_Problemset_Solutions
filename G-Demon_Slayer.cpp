#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define vi vector<int>
#define pii pair<int,int>
#define endl '\n'

void solve(){
    
    int n,m;
    cin>>n>>m;
    pii pp[m];

    for(int i=0;i<m;i++){
        cin>>pp[i].first>>pp[i].second;
    }
    map< pii, int > mp[m];
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if( i == j ) continue;
            int dx = pp[i].first - pp[j].first;
            int dy = pp[i].second - pp[j].second;

            int gg = __gcd( dx,dy);
            dx/=gg;
            dy/=gg;
            

            mp[i][{dy, dx}]++;
        }
    }
    
    vector<int> ans(n + 1);
    for (int i=0; i<m; i++) {
        for (int j=0; j<m; j++) {
            if (i == j) continue;
            if(pp[i].second == pp[j].second) continue;
            
            int dx = pp[i].first - pp[j].first;
            int dy = pp[i].second - pp[j].second;

            int gg = __gcd( dx,dy);
            dx/=gg;
            dy/=gg;
            int val = dx * pp[i].second;
         
            if (dx == 0) {
                val = pp[i].first;
                if (val > 0 and val <= n) ans[val] = max(ans[val], mp[i][{dy, dx}]); 
            }
            else if (val % dy == 0) {
                val /= dy;
                val = pp[i].first - val;
                if (val > 0 and val <= n) ans[val] = max(ans[val], mp[i][{dy, dx}]); 
            }
        }
     
    }

    for (int i=1; i<=n; i++) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;


}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tc=1;
    //cin>>tc;
    while(tc--) solve();
}
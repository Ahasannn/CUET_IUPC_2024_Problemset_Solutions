#include<bits/stdc++.h>
using namespace std;

int n,p,x,a,z;

void solve() {
    
    cin>>n>>p>>x>>a;

    int hit = p + x,ans = 0,flag=0;

    priority_queue<int>pq;

    for(int i=1;i<=n;i++) {
        cin>>z;
        if (flag) continue;
        if (i<=a) {
            pq.push(-z);
            ans = i;
        } else {
            pq.push(-z);
            int mn = -pq.top();
            pq.pop();
            if(mn<=hit) {
                hit -= mn;
                ans = i;
            } else {
                flag = 1;
            }
        }

    }
    cout<<ans<<"\n";
    return ;
}

int32_t main() {
    int t;
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>t;
    while(t--) {
        solve();
    }
}
///Bismillahir Rahmanir Rahim
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll solve(ll n,ll m,ll p) {
    ll total = n*m;
    ll remaining = total - p;
    
    // Maintaining n <= m
    if (n > m) {
        swap(n,m);
    }
    
    // Check impossible Case
    if (p > total) {
       return -1;
    }
    
    // Check when answer is p - 1
    if (p == total) {
        return p-1;
    }
    
    // Check when it's a strip 
    if (n == 1 || m == 1) {
        return p;
    }
    
    //Check when both n & m exceeds p
    if (n > p) {
        return p+1;
    }
    
    // Check if the remaining part could be kept as a single unbroken grid
    for(ll i=1;i<=n;i++){
       if (remaining % i == 0) {
           int ll j = remaining/i;
             if (j <= m) {
                return p;
             }
       }
    }

    // Assuming answer would be P - 1 or P or P + 1
    return p + 1;
}

int32_t main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--) {
        ll n,m,p;
        cin>>n>>m>>p;
        cout<<solve(n,m,p)<<"\n";
    }
    return 0;
}
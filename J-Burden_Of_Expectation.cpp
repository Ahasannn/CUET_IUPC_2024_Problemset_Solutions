#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#ifdef LOKAL
#include "DEBUG_TEMPLATE.h"
#else
#define HERE
#define debug(args...)
#endif
const int N = 300 + 5;
const int mod = 998244353;
typedef pair<int,int> pii;

int bigmod(int a, int b)
{
    int ans =1;
    while(b>0)
    {
        if(b&1)
        {
            ans = (ans*1ll*a)%mod;
        }
        a= (a*1ll*a)%mod;
        b>>=1;
    }
    return ans;
}

inline int add(int x, int y)
{
    return (x+y>=mod ? x+y-mod : x+y);
}

inline int sub(int x, int y)
{
    return (x-y<0 ? x-y+mod : x-y);
}

inline int gun(int x, int y)
{
    return ((x*1ll*y)%mod);
}

inline int vag(int x, int y)
{
    return (x*1ll* bigmod(y,mod - 2))%mod;
}


int fact[N];
int invfact[N];
int inv[N];

void init()
{
    fact[0]=1;
    invfact[0] = 1;
    inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = inv[mod % i] *1ll* (mod - mod / i) % mod;
    for(int i=1; i<N; i++)
    {
        fact[i]= gun(fact[i-1],i);
        invfact[i] = invfact[i - 1] *1ll* inv[i] % mod;
    }
}

int getncr(int n, int r)
{
    if(n<r || n<0 || r<0)
    {
        return 0;
    }
    return gun(fact[n] , gun(invfact[r] , invfact[n-r]));
}

int n,m,k,q;
int a[N];
int isDanger[N];
int dp[N][N][2];
int prob[N][N];
vector<int>adj[N];
int pw[N];

int solve(int op, int u, bool needDanger)
{
    if(op==0)
    {
        return (isDanger[u] == needDanger ? 1 : 0);
    }
    int &ret = dp[op][u][needDanger];
    if(ret!=-1)
        return ret;
    int ans = 0;
    int tot = adj[u].size();
    if(tot==0 || isDanger[u])
    {
        ans = add(ans, solve(op-1, u, needDanger));
    }
    else
    {
        for(int i:adj[u])
        {
            int tmp = gun(inv[tot], solve(op-1, i, needDanger));
            ans = add(ans , tmp);
        }
    }
    return ret = ans;
}


int32_t main()
{
#ifndef LOKAL
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    init();
    cin>>n>>m>>k>>q;
    for(int i=0; i<n; i++)
    {
        cin>>isDanger[i];
    }
    for(int i=0; i<k; i++)
    {
        cin>>a[i];
        a[i]--;
    }
    for(int i=0; i<m; i++)
    {
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if(k==1)
    {
        cout<<"0\n";
        return 0;
    }
    memset(dp,-1,sizeof dp);

    pw[0] = 1;
    for(int i=1;i<N;i++)
    {
        pw[i] = gun(pw[i-1], k-2);
    }

    for(int op=0;op<=q;op++)
    {
        for(int u=0;u<n;u++)
        {
            int ans = 0;
            for(int z=0;z<=op;z++)
            {
                int x = op - z;
                int tmp = gun(solve(z, u, 1),invfact[z]);
                tmp = gun(tmp, gun(pw[x] , invfact[x]));
                ans = add(ans, tmp);
            }
            prob[op][u] = ans;
        }
    }

    int pcal = vag(fact[q],bigmod(k,q));
    int ans = 0;
    for(int i=0; i<k; i++)
    {
        for(int j=0; j<k; j++)
        {
            if(i==j)
                continue;
            for(int y=0;y<=q;y++)
            {
                int tmp = pcal;
                tmp = gun(tmp , gun(solve(y,a[i],0) , invfact[y]));
                tmp = gun(tmp, prob[q-y][a[j]]);
                ans = add(ans, tmp);
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}

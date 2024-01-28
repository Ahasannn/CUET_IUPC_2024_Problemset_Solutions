///Bismillahir Rahmanir Rahim
#include<bits/stdc++.h>
using namespace std;

#define ll long long 

const int mx = 200005;

ll n,q;
ll tre[4*mx][2],lz[4*mx];

// tre[pos][0] = total number of 1
// tre[pos][1] = sum of positions of 1 

ll pre_sum(ll x) {
    if (x%2==0) {
        return (x/2)*(x+1);
    }
    else {
        return x*((x+1)/2);
    }
}

void propagate(ll pos,ll l,ll r) {
    if (lz[pos]== -1) return;
    else if (lz[pos]) {
       tre[pos][0] = (r-l+1);
       tre[pos][1] = pre_sum(r) - pre_sum(l-1);
    } else {
        tre[pos][0] = 0;
        tre[pos][1] = 0;
    }
    if (l!=r) {
        lz[2*pos] = lz[pos];
        lz[2*pos+1] = lz[pos];
    }
    lz[pos] = -1;
    return ;
}

void update(ll pos,ll l,ll r,ll I,ll J,ll x) {
    propagate(pos,l,r);
    if (l > J || r < I) return ;
    if (I<=l && J>=r) {
        lz[pos] = x;
        propagate(pos,l,r);
        return ;
    }
    int mid = (l+r)>>1LL;
    update(2*pos,l,mid,I,J,x);
    update(2*pos+1,mid+1,r,I,J,x);
    tre[pos][0] = tre[2*pos][0] + tre[2*pos+1][0];
    tre[pos][1] = tre[2*pos][1] + tre[2*pos+1][1];
}

int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

    memset(lz,-1,sizeof lz);
    
    cin>>n>>q;
    for(int i=1;i<=q;i++) {
        ll type,lft,rgt,ans;
        cin>>type;
         if(type == 1) {
             cin>>lft>>rgt;
             assert(1<=lft && lft<=rgt && rgt<=n);
             update(1,1,n,lft,rgt,0);
         } else if (type ==2) {
             cin>>lft>>rgt;
             assert(1<=lft && lft<=rgt && rgt<=n);
             update(1,1,n,lft,rgt,1);
         } else {
            propagate(1,1,n);
            ans = (2LL*tre[1][1]) - (tre[1][0]*tre[1][0]);
            cout<<ans<<"\n";
         }
    }

}
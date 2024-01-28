#include <bits/stdc++.h>
using namespace std;
#define hlw ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

string s;
int n, i, j, k,t,p,f,it;
int freq[100005][27], freq2[100005][27], cnt[100005][27];
int mex[100005];
vector<int> v[26];
vector<int> vv;
int vvst,vst[26];

int main()
{
    hlw;
    cin>>t;
    while(t--)
    {
        f=2;
        cin>>s;
        n=s.size();
        vvst=0;
        for(i=0; i<26; i++)
        {
            vst[i]=0;
            v[i].clear();
        }
        for (i = 0; i < n; i++)
        {
            v[s[i] - 'a'].push_back(i);
            mex[i]=0;
            for (j = 0; j < 26; j++)
            {
                freq[i][j] = -1;
                freq2[i][j] = 0;
                if (j == s[i] - 'a')
                    cnt[i][j] = 1;
                else
                    cnt[i][j] = 0;
                if (i)
                    cnt[i][j] += cnt[i - 1][j];
            }
        }
        vv.clear();
        for (i = 0; i < 26; i++)
        {
            for (j = 0; j < 25 && j < v[i].size(); j++)
            {
                //pushToVV(v[i][j]);
                p=v[i][j];
                for(int i=vvst; i<vv.size(); i++)
                {
                    if(vv[i]>p)swap(p,vv[i]);
                }
                vv.push_back(p);


                int idx = v[i][j];
                for (k = 0; k < 26; k++)
                {
                    freq[idx][k] = cnt[idx][k];
                    if(freq[idx][k]<26)
                        freq2[idx][freq[idx][k]]++;
                }
                for(k=0; k<27; k++)
                {
                    if(freq2[idx][k]==0)
                    {
                        mex[idx]=k;
                        break;
                    }
                }
                f = max(f, mex[idx]);
            }
        }
        for (i = 0; i < n; i++)
        {
            vvst++;
            int ch = s[i] - 'a';
            vst[ch]++;
            for (int ii=vvst; ii<vv.size(); ii++)
            {
                it=vv[ii];
                int cc=cnt[it][ch]-cnt[i][ch];
                if(cc<26)
                {
                    if(freq[it][ch]<26)
                    {
                        freq2[it][freq[it][ch]]--;
                        if (freq2[it][freq[it][ch]] == 0&&freq[it][ch]<mex[it])
                        {
                            mex[it]=freq[it][ch];
                        }
                    }
                    freq[it][ch]=cc;
                    freq2[it][freq[it][ch]]++;
                    if(cc==mex[it])
                    {
                        while(freq2[it][mex[it]]!=0)mex[it]++;
                    }

                }
                else
                {
                    if(freq[it][ch]<26)
                    {
                        freq2[it][freq[it][ch]]--;
                        if (freq2[it][freq[it][ch]] == 0&&freq[it][ch]<mex[it])
                        {
                            mex[it]=freq[it][ch];
                        }
                    }
                }
                freq[it][ch]=cc;
                f=max(f,mex[it]);
            }
            for (j = vst[ch]; j < 25+vst[ch] && j < v[ch].size(); j++)
            {
                int idx = v[ch][j];
                if (freq[idx][ch] == -1)
                {
                    for (k = 0; k < 26; k++)
                    {
                        freq[idx][k] = cnt[idx][k] - cnt[i][k];
                        if(freq[idx][k]<26)
                            freq2[idx][freq[idx][k]]++;
                    }
                    for(k=0; k<27; k++)
                    {
                        if(freq2[idx][k]==0)
                        {
                            mex[idx]=k;
                            break;
                        }
                    }
                    f = max(f, mex[idx]);
                    //pushToVV(idx);
                    p=idx;
                    for(int i=vvst; i<vv.size(); i++)
                    {
                        if(vv[i]>p)swap(p,vv[i]);
                    }
                    vv.push_back(p);
                    break;
                }
            }
        }

        cout << f << '\n';
    }
    return 0;
}
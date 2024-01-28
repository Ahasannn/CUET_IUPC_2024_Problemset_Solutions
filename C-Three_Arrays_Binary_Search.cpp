#include <bits/stdc++.h>
using namespace std;
#define hlw                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class Solve
{
    vector<int> A, B, C;
    int n, nd;

public:
    void solveMe(int testCase)
    {
        cin >> n;
        assert(n > 0 && n <= 100000);
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            assert(a > 0 && a <= 100000);
            A.push_back(a);
            B.push_back(a);
            C.push_back(a);
        }
        B[n - 1] = 1;
        nd = 1;
        for (int i = n - 2; i >= 0; i--)
        {
            int lo = 1, hi = A[i], mid;
            while (lo <= hi)
            {
                mid = (lo + hi) / 2;
                if (A[i] / mid <= C[i + 1])
                {
                    B[i] = mid;
                    hi = mid - 1;
                }
                else
                    lo = mid + 1;
            }
            C[i] = A[i] / B[i];
            nd &= B[i];
        }
        if (nd)
        {
            for (int i = n - 1; i > 0; i--)
            {
                if (B[i] < A[i] && A[i] / (B[i] + 1) >= C[i - 1])
                {
                    B[i]++;
                    nd = 0;
                    break;
                }
            }
            if (nd && B[0] < A[0])
            {
                B[0]++;
                nd = 0;
            }
        }
        for (int i = 0; i < n; i++)
            cout << B[i] << ' ';
        cout << '\n';
    }
};

int main()
{
    hlw;
    int testCases = 1;
    cin >> testCases;
    assert(testCases > 0 && testCases <= 10000);

    for (int cas = 1; cas <= testCases; cas++)
    {
        Solve solve;
        solve.solveMe(cas);
    }
    return 0;
}
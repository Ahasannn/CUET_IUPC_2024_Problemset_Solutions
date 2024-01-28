#include <bits/stdc++.h>
using namespace std;

class Solve
{
    int bit = 0;
    string s;
    bool verify(int A)
    {
        cout << "VERIFY " << A << '\n';
        cin >> s;
        return s == "AC";
    }
    bool multiply(int X)
    {
        cout << "MUL " << X << '\n'
             << flush;
        cin >> s;
        return s != "WA";
    }
    bool divide(int Y)
    {
        cout << "DIV " << Y << '\n'
             << flush;
        cin >> s;
        return s != "WA";
    }

public:
    void solveMe(int testCase)
    {
		bit = 0;
        for (int i = 29; i > 0; i--)
        {
            multiply((1 << i) + 1);
            divide(1 << i);
            if (s == ">")
            {
                bit = i;
                break;
            }
        }
        if (bit == 0)
        {
            verify(1);
            return;
        }
        multiply(999999999);
        divide(1000000000);
        if (s != "=")
        {
            verify(1000000000);
            return;
        }
        divide(1 << bit);
        long long lo = 1 << bit;
        long long hi = (1 << (bit + 1)) - 1;
        if (hi > 1e9)
            hi = 1e9;
        long long ans = 0, mid;
        while (lo <= hi)
        {
            mid = (lo + hi) / 2;
            multiply(mid);
            if (s == "=")
            {
                ans = mid;
                break;
            }
            else if (s == ">")
            {
                hi = mid - 1;
            }
            else
            {
                lo = mid + 1;
            }
            divide(mid);
        }
        if (ans == 0)
            ans = lo;
        verify(ans);
        return;
    }
};

int main()
{
    int testCases = 1;
    cin >> testCases;
    Solve solve;
    for (int cas = 1; cas <= testCases; cas++)
    {
        solve.solveMe(cas);
    }
    return 0;
}
#include "bits/stdc++.h"

using namespace std;

int mod = 10 * 1000 * 1000;
int cache[101][101];

int poly(int n, int first)
{
    // n = first 이면 리턴
    if (n == first)
        return 1;

    // n = fisrt , first = second
    int &ret = cache[n][first];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int second = 1; second <= n - first; second++)
    {
        int add = first + second - 1;
        add *= poly(n - first, second);
        add %= mod;
        ret += add;
        ret %= mod;
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("../inputs/poly.txt", "r", stdin);
    memset(cache, -1, sizeof(cache));

    int cases;
    cin >> cases;
    for (int cc = 0; cc < cases; ++cc)
    {
        int n;
        cin >> n;
        int ret = 0;
        for (int i = 0; i < n; i++)
            (ret += poly(n, i + 1)) %= mod;
        cout << ret << endl;
    }

    return 0;
}

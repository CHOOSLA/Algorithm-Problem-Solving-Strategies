#include "bits/stdc++.h"

using namespace std;

// 현재 문제인 점
// 사각형은 가로 * 세로 를 생각을 안함
// 울타리를 만드는데 느슨하게 만들어짐

int func(vector<int> &seq, int now)
{
    int half = now / 2;
    if (half == 0)
    {
        return seq[now];
    }

    int left = func(seq, half);
    int right = func(seq, now - half);

    int ret = max(left, right);
    ret = min(left + right, ret);
    return ret;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("../inputs/fence.txt", "r", stdin);
    int c;
    cin >> c;
    for (int i = 0; i < c; i++)
    {
        int n;
        cin >> n;
        vector<int> seq;
        for (int j = 0; j < n; j++)
        {

            int tmp;
            cin >> tmp;
            seq.push_back(tmp);
        }

        cout << func(seq, n) << endl;
    }

    return 0;
}

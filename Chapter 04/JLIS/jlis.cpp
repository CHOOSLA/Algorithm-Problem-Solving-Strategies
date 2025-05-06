#include "bits/stdc++.h"

using namespace std;

// long long의 최소값
const long long LOWEST = numeric_limits<long long>::min();
// a, b의 길이 n, m
int n, m;
// 수열
long long A[100], B[100];
// memoiztion
int cache[101][101];

int func(int indexA, int indexB)
{
    // -1로 시작하는 것을 고려한 인덱스값
    int &ret = cache[indexA + 1][indexB + 1];
    // 저장이 되어 있는 값이라면 return
    if (ret != -1)
        return ret;
    // 선택할 수 있는 것의 최소값
    ret = 2;
    // 처음 시작했는가를 판단
    long long a = (indexA == -1 ? LOWEST : A[indexA]);
    long long b = (indexB == -1 ? LOWEST : B[indexB]);
    // 둘중 최대값을 선택한다
    long long maxElement = max(a, b);

    // 다음 증가하는 부분 수열을 찾기 위한 과정
    for (int nextA = indexA + 1; nextA < n; nextA++)
    {
        if (maxElement < A[nextA])
        {
            ret = max(ret, 1 + func(nextA, indexB));
        }
    }

    for (int nextB = indexB + 1; nextB < m; nextB++)
    {
        if (maxElement < B[nextB])
        {
            ret = max(ret, 1 + func(indexA, nextB));
        }
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    freopen("../inputs/jlis.txt", "r", stdin);

    int c;
    cin >> c;
    for (int i = 0; i < c; i++)
    {
        // cache 초기화
        memset(cache, -1, sizeof(cache));
        cin >>
            n >> m;
        for (int j = 0; j < n; j++)
        {
            cin >> A[j];
        }

        for (int k = 0; k < m; k++)
        {
            cin >> B[k];
        }

        int ret = func(-1, -1);
        cout << ret - 2 << endl;
    }

    return 0;
}

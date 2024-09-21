#include "bits/stdc++.h"

using namespace std;

const int M = 1 * 1000 * 1000 * 1000 + 100;
int k;
int bino[201][201]; // 이항계수를 저장하기 위한 공간

void calcBino()
{
    memset(bino, 0, sizeof(bino)); // 초기화
    for (int i = 0; i <= 200; i++) // n
    {
        bino[i][0] = bino[i][i] = 1;
        for (int j = 1; j < i; j++) // k
        {
            // 오버플로우 방지
            bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
        }
    }
}

string morse(int n, int m, int skip)
{
    // 기저 사례
    // n : (-)를 뽑을 개수
    // n =0 이란건 나머지 m개가 o라는 뜻
    if (n == 0)
        return string(m, 'o');
    if (skip < bino[n + m - 1][n - 1])
    {
        return '-' + morse(n - 1, m, skip);
    }
    return 'o' + morse(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main(int argc, char const *argv[])
{
    calcBino();
    cout << morse(100, 100, 2147483647);
    return 0;
}

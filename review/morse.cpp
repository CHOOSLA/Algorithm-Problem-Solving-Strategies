#include "bits/stdc++.h"

using namespace std;
// k 번째를 구하는 레시피
// 1. 숫자를 구하는 함수를 작성
// 2. 전체 숫자를 구한다.
// 3. k-1 번째 숫자를 구한다.

// k 번째에 올 수 있는 모스부호
// skip을 이용해야 한다.
// 일단 완전 탐색 알고리즘을 구상한다
// n,m 의 개수로 - - 해서 뽑아내야한다
// i 번째에 뽑은 경우와 뽑지 않는 경우를 따져서 생각

// morse의 완전 탐색
void generate(int n, int m, string morseCode)
{
    // 기저사례 : 문자열이 완성되었을 때
    // n과 m이 모두 없을때
    if (n == 0 && m == 0)
    {
        cout << morseCode << endl;
        return;
    }

    if (n > 0)
    {
        generate(n - 1, m, morseCode + "-");
    }
    if (m > 0)
    {
        generate(n, m - 1, morseCode + "*");
    }
}

// 1. 숫자를 구하는 함수를 작성
// 2. 전체 숫자를 구한다.
// 이항 계수로 개수를 미리 다 세어놓는다.
// n, m <= 100
// k <= 1000 * 1000 * 1000
// ( n + m / n ) 의 이항계수를 저장한다.
int MAX = 1000 * 1000 * 1000;
int bino[201][201];
void calcBino()
{
    // 캐시 초기화
    memset(bino, -1, sizeof(bino));

    for (int i = 0; i < 201; i++)
    {
        // 모두 뽑았을 때와 모두 뽑지 않았을 때의 경우의 수는 1
        bino[i][0] = bino[i][i] = 1;

        // bottom-up 방식으로 채워나감
        for (int j = 1; j < i; j++)
        {
            // ( n / k ) = (n - 1 / k - 1 ) + ( n - 1 / k )
            // 이항계수의 점화식
            bino[i][j] = min(MAX, bino[i - 1][j - 1] + bino[i - 1][j]);
        }
    }
}

// - : n * : m
// n == k
// 이것이 전부 뽑혔을 때,
string morse(int n, int m, int skip)
{
    // n이 전부 뽑혔을 때, 나머지는 전부 * 이다.
    if (n == 0)
        return string(m, '*');

    if (skip < bino[n + m - 1][n - 1])
    {
        return "-" + morse(n - 1, m, skip);
    }
    return "*" + morse(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main(int argc, char const *argv[])
{
    calcBino();
    cout << morse(6, 6, 2) << endl;
    return 0;
}

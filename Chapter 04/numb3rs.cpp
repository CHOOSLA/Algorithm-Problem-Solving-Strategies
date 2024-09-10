#include "bits/stdc++.h"

using namespace std;

int n;
int p;
int vil[50][50];
int cache[50][101];

// 현재 마을에서 몇개가 연결되어 있는 지 계산
int connection[50];

// 역참조를 해보자
// 현재 위치에서 days에 따른 모든 경우의 수

int moveVil(int here, int day)
{
    // 마지막 날이 교도소가 아닌 경우
    if (day == 0 && here != p)
    {
        return -1;
    }

    // 기저 사례
    if (day == 0)
    {
        return 0;
    }

    int &ret = cache[here][day];
    if (ret != -1)
        return ret;

    ret = 0;
    // day = 0 일때, 교도소에 있는 경우만 계산한다.
    for (int there = 0; there < n; there++)
    {
        // 연결되어 있다면
        if (vil[here][there] == 1)
        {
            int cases = moveVil(there, day - 1);

            if (cases == -1)
            {
                ret = -1;
            }
            else
            {
                ret += connection[here] + cases;
            }
        }
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    freopen("../inputs/numb3rs.txt", "r", stdin);

    int cases;
    cin >> cases;
    for (int cc = 0; cc < cases; cc++)
    {
        memset(cache, -1, sizeof(cache));
        // 마을의 수
        cin >> n;

        // 날짜
        int d;

        cin >> d >> p;

        for (int i = 0; i < n; i++)
        {
            int count_connection = 0;
            for (int j = 0; j < n; j++)
            {
                int isConnected = 0;
                cin >> isConnected;
                vil[i][j] = isConnected;
                if (isConnected)
                {
                    count_connection++;
                }
            }
            // 연결되어 있는 마을의 수 저장
            connection[i] = count_connection;
        }

        int test_num;
        int tests[50];

        cin >> test_num;
        for (int i = 0; i < test_num; i++)
        {
            int vil_num;
            cin >> vil_num;
            cout << 1.0 / moveVil(vil_num, d) << endl;
        }

        cout << endl
             << endl;
    }

    return 0;
}

#include <iostream>

using namespace std;

int n;
bool areFriends[10][10];

int countPairing(bool taken[10]);
int fixedCountPairing(bool taken[10]);

int main(int argc, char **argv)
{
    int test_case;
    int T;

    freopen("../inputs/picnic.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int m = 0;
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            cout << a << ',' << b << ' ';
            areFriends[a][b] = true;
            areFriends[b][a] = true;
        }

        bool taken[10] = {
            false,
        };
        printf("\n 정답 : %d\n", fixedCountPairing(taken));
    }
    return 0;
}

int countPairing(bool taken[10])
{
    // 기저 사례 : 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    bool finished = true;
    for (int i = 0; i < n; ++i)
    {
        if (!taken[i])
            finished = false;
    }
    if (finished)
        return 1;
    int ret = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (!taken[i] && !taken[j] && areFriends[i][j])
            {
                taken[i] = taken[j] = true;
                ret += countPairing(taken);
                taken[i] = taken[j] = false;
            }
        }
    }
    return ret;
}

int fixedCountPairing(bool taken[10])
{
    int firstFree = -1;
    for (int i = 0; i < n; ++i)
    {
        if (!taken[i])
        {
            firstFree = i;
            break;
        }
    }

    // 기저 사례 : 모든 학생이 짝을 찾았으면 한 가지 방법을 찾았으니 종료한다.
    if (firstFree == -1)
    {
        return 1;
    }
    int ret = 0;
    for (int pairwith = firstFree + 1; pairwith < n; ++pairwith)
    {
        if (!taken[pairwith] && areFriends[firstFree][pairwith])
        {
            taken[firstFree] = taken[pairwith] = true;
            ret += fixedCountPairing(taken);
            taken[firstFree] = taken[pairwith] = false;
        }
    }
    return ret;
}
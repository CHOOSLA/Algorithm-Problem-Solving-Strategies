#include "bits/stdc++.h"

using namespace std;

string e, digit; // e : 현재 계란 값 , 정렬된 계란값 (후보들)
int n;           // e의 길이
int m;           // 옛날 사탕 값

int cache[1 << 15][21][2];
int count(int idx, int taken, int mod, int less)
{
    // 기저 사례 : n에 도달했을 때, less = true이고 mod = 0 이면 count
    if (idx == n)
    {
        return (less && mod == 0) ? 1 : 0;
    }

    // cache를 불러옴
    int &ret = cache[taken][mod][less];
    if (ret != -1)
    {
        return ret;
    }

    // 저장된 값이 없을 경우 0으로 초기화
    ret = 0;

    // 다음에 올 수 있는 모든 후보군을 선택
    for (int next = 0; next < n; next++)
    {
        // 1. 현재 후보가 뽑힌적이 없어야함
        // next를 기준으로 taken확인
        if ((taken & (1 << next)) == 0)
        {
            // 2. 후보가 현재 자리에서 e를 넘어버리는가?
            if (!less && e[idx] < digit[next])
            {
                continue;
            }

            // 3. 후보가 놓아질 수 없는 자린가?
            // 1) 첫번째도 아니면서
            // 2) 현재 후보 전과 같으면서
            // 3) 전의 후보가 뽑혀있지 않으면
            // 중복으로 세지므로 안된다.
            if (next > 0 && digit[next - 1] == digit[next] && (taken & (1 << (next - 1))) == 0)
            {
                continue;
            }

            int next_taken = taken | (1 << next);
            int next_mod = (mod * 10 + digit[next] - '0') % m;
            int next_less = less || e[idx] > digit[next];
            ret += count(idx + 1, next_taken, next_mod, next_less);
            ret %= 1000 * 1000 * 1000 + 7;
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("../inputs/zimbabwe.txt", "r", stdin);
    int c;
    cin >> c;
    for (int cc = 0; cc < c; cc++)
    {
        memset(cache, -1, sizeof(cache));
        cin >> e >> m;
        digit = e;
        sort(digit.begin(), digit.end());
        n = e.size();
        cout << count(0, 0, 0, 0) << endl;
    }

    return 0;
}

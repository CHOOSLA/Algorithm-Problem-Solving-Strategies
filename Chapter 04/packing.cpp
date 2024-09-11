#include "bits/stdc++.h"

using namespace std;

int n, w;

vector<string> things;
int volumes[100], needs[100];

int cache[101];
vector<string> choices;

// 왜 나는 헷갈리는가,,,,
// LIS와 PACKING의 차이는 무엇인가,,,
// 절박도를 max로 하는 값
int packing(int idx, int weight)
{
    // 기저 사례
    if (idx == n)
        return 0;

    int &ret = cache[idx + 1];
    if (ret != -1)
        return ret;

    ret = 0;
    int best_next = 0;
    for (int next = idx + 1; next < n; next++)
    {
        // 무게를 초과하지 않는 것들을 불러옴
        // 이건 무게를 최대화 하는 방향,,,
        // 무게 >> 절박도
        int space = weight - volumes[next];
        if (space >= 0)
        {
            int cand = needs[idx] + packing(next, space);
            if (ret <= cand)
            {
                ret = cand;
                best_next = next;
            }
        }
    }

    choices.push_back(things[best_next]);
    return ret;
}

int main(int argc, char const *argv[])
{
    freopen("../inputs/packing.txt", "r", stdin);
    int cases;
    cin >> cases;
    for (int cc = 0; cc < cases; cc++)
    {
        memset(cache, -1, sizeof(cache));
        cin >> n >> w;
        // cout << n << w << endl;
        for (int dd = 0; dd < n; dd++)
        {
            string thing;
            cin >> thing;
            things.push_back(thing);
            cin >> volumes[dd] >> needs[dd];
            // cout << volumes[dd] << " " << needs[dd] << endl;
        }
        cout << packing(-1, w) << " ";
        cout << choices.size() << endl;
        for (string s : choices)
        {
            cout << s << endl;
        }
    }

    return 0;
}

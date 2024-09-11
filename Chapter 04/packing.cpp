#include "bits/stdc++.h"

using namespace std;

int n, w;

vector<string> things;
int volumes[100], needs[100];

int cache[101];
vector<string> choices;

// 왜 나는 헷갈리는가,,,,
// LIS와 PACKING의 차이는 무엇인가,,,

// ❌❌❌❌문제점❌❌❌❌
// 첫 번째,
// cache 사용도가 틀림 --> cache는 매개변수에 따른 저장이다
// fibo(1) , fibo(2) ... fibo(n) 에 대한 cache는 cache[n] 이다.
// fibo(i)일 때의 함수 값을 저장하기 때문에
// 두 번째,
// packing문제에서 해당 값을 포함하지 않는 것을 고려하지 않음
// 모든 문제를 LIS 범위에서 생각할려고함
// LIS는 PACKING과 뭐가 다를까?
// LIS는 현재 인덱스를 '무조건' 포함된다고하고
// PACKING은 넣다 말다 할까?
// 우리는 연속된 값을 찾는게 아닌 포함했을 대와 포함하지 않았을 때를 생각하기 때문이다.
// ❌❌❌❌❌❌❌❌❌❌❌

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

int answer_cache[101][1000];
vector<int> answer_choices;
int AnswerPacking(int item, int capacity)
{
    // 기저 사례
    if (item == n)
        return 0;

    // 캐쉬확인
    int &ret = answer_cache[item][capacity];
    if (ret != -1)
        return ret;

    // 현재 item을 뽑지 않았을 경우
    ret = AnswerPacking(item + 1, capacity);

    // 뽑았을 경우
    if (capacity >= volumes[item])
    {
        ret = max(ret, AnswerPacking(item + 1, capacity - volumes[item]) + needs[item]);
    }

    return ret;
}

// 역추적하는 알고리즘
// pack를 시켜서 둘의 값이 같다면 그것을 안뽑아도 되고
// 다르다면 뽑아야한다.
void reconstruct(int item, int capacity, vector<string> &picked)
{
    if (item == n)
        return;
    if (AnswerPacking(item, capacity) == AnswerPacking(item + 1, capacity))
    {
        reconstruct(item + 1, capacity, picked);
    }
    else
    {
        picked.push_back(things[item]);
        reconstruct(item + 1, capacity - volumes[item], picked);
    }
}

int main(int argc, char const *argv[])
{
    freopen("../inputs/packing.txt", "r", stdin);
    int cases;
    cin >> cases;
    for (int cc = 0; cc < cases; cc++)
    {
        memset(cache, -1, sizeof(cache));
        memset(answer_cache, -1, sizeof(answer_cache));
        answer_choices.clear();
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
        cout << AnswerPacking(0, w) << " ";
        vector<string> picked;
        reconstruct(0, w, picked);
        cout << picked.size() << endl;
        for (auto &&i : picked)
        {
            cout << i << endl;
        }
        }

    return 0;
}

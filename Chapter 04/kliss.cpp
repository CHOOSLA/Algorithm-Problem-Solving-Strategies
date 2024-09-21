#include "bits/stdc++.h"

using namespace std;

int seq[500];
int n;
int k;

int cache[501];
// 여기까진 기본 lis 파트
int lis(int idx)
{
    if (idx == n)
        return 0;

    int &ret = cache[idx + 1];
    if (ret != -1)
        return ret;

    ret = 1;
    for (int next = idx + 1; next < n; next++)
    {
        if (idx == -1 || seq[idx] < seq[next])
        {
            ret = max(ret, 1 + lis(next));
        }
    }

    return ret;
}

// 해당 idx를 기준으로 lis의 개수를 count해주는 함수
int cacheCnt[501];
// int 형 MAX값을 표현
int MAX = 2000 * 1000 * 1000 + 1;
int count(int idx)
{
    if (lis(idx) == 1)
        return 1;

    int &ret = cacheCnt[idx + 1];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int next = idx + 1; next < n; next++)
    {
        // 증가하는 수열이면서 그 부분 구조인 것들만 확인
        if ((idx == -1 || seq[idx] < seq[next]) && lis(idx) == lis(next) + 1)
        {
            ret = min<long long>(MAX, (long long)ret + count(next));
        }
    }
    return ret;
}

// lis 와 count를 이용해서 lis가 같을 때, k번째를 찾는 함수 구현
void reconstruct(int start, int skip, vector<int> &list)
{
    // k 번째 수열 구성을 위한 구문
    if (start != -1)
    {
        list.push_back(seq[start]);
    }

    // k 번째가 될 수 있는 후보군을 저장한다
    // pair을 하는 것은 같은 숫자끼리는 idx가 먼저 인 것을 뽑기 위해서
    vector<pair<int, int>> candidate;
    for (int next = start + 1; next < n; next++)
    {
        if ((start == -1 || seq[start] < seq[next]) && lis(start) == 1 + lis(next))
        {
            candidate.push_back(make_pair(seq[next], next));
        }
    }

    // 해당 배열을 정렬
    sort(candidate.begin(), candidate.end());

    // 후보순으로 k-1 번째를 맞춰나감
    for (int i = 0; i < candidate.size(); i++)
    {
        int idx = candidate[i].second;
        int cnt = count(idx);
        // skip 보다 작을경우 빼고
        // skip 보다 크다면 그 사이에 있는 수열을 찾아내는 과정
        if (cnt <= skip)
        {
            skip -= cnt;
        }
        else
        {
            reconstruct(idx, skip, list);
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("../inputs/klis.txt", "r", stdin);

    int cases = 0;
    cin >> cases;
    for (int cc = 0; cc < cases; cc++)
    {
        memset(cache, -1, sizeof(cache));
        memset(cacheCnt, -1, sizeof(cacheCnt));
        cin >> n >> k;
        for (int i = 0; i < n; i++)
        {
            cin >> seq[i];
        }

        vector<int> result;
        reconstruct(-1, k - 1, result);
        cout << result.size() << endl;
        for (auto &num : result)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}

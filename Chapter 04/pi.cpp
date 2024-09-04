#include "bits/stdc++.h"

using namespace std;

string num;
int n;
const int INF = 987654321;
int cache[10002];

// 등차수열 및 규칙을 판단해주는 함수
int classify(int idx, int size)
{
    // 등차수열을 확인
    bool arithmetic = true;
    int diff = num[idx + 1] - num[idx];

    for (int i = idx + 1; i < idx + size - 1; i++)
    {
        if (diff != (num[i + 1] - num[i]))
        {
            arithmetic = false;
            break;
        }
    }

    // 등차수열이라면
    if (arithmetic)
    {
        // 같은 숫자일 때
        if (diff == 0)
        {
            return 1;
        }
        else if (diff == 1 || diff == -1) // 단조 증가 혹은 단조 감소
        {
            return 2;
        }
        else // 그 외 등차수열
        {
            return 5;
        }
    }

    // 두 개의 숫자가 번갈아서 나오는지 확인
    bool alternate = true;
    for (int i = idx + 2; i < idx + size; i++)
    {
        if (num[i] != num[i - 2])
        {
            alternate = false;
            break;
        }
    }

    if (alternate)
    {
        return 4;
    }

    return 10;
}

// 최적 부분 구조를 찾는 함수 (메모이제이션 적용)
int optimalSubstructure(int idx)
{
    // 기저 사례: 문자열의 끝에 도달하면 0을 반환
    if (idx == n)
        return 0;

    // 메모이제이션: 이미 계산된 값이면 바로 반환
    int &ret = cache[idx];
    if (ret != -1)
        return ret;

    ret = INF;

    // 길이가 3부터 5까지의 부분 수열을 확인
    for (int size = 3; size <= 5; size++)
    {
        if (idx + size <= n)
        {
            ret = min(ret, classify(idx, size) + optimalSubstructure(idx + size));
        }
    }

    return ret;
}

int main(int argc, char const *argv[])
{
    // 입력 파일 처리
    freopen("../inputs/pi.txt", "r", stdin);
    int c;
    cin >> c;
    for (int i = 0; i < c; i++)
    {
        // 캐시 초기화
        // ❌ 메모리 초기화를 잘 못해서 틀림
        memset(cache, -1, sizeof(cache));
        cin >> num;
        n = num.size();
        cout << optimalSubstructure(0) << endl;
    }

    return 0;
}
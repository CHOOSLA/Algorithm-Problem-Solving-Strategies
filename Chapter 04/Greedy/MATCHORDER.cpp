#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

// 상대팀을 최대한 많이 이기는 경우의 수를 구하는 문제

// 최대화를 위한 기준
// 1) 우리팀에서 이기는 수가 없을 경우: 제일 점수가 낮은 사람 출전
// 2) 우리팀이 이기는 수가 있는 경우: 상대 팀을 이기는 최소한의 점수인 사람 출전

int order(const vector<int>& russian, const vector<int>& korean) {
    int n = russian.size(), wins = 0;

    // 중복된 값을 허용하는 multiset을 사용하여 오름차순으로 정렬됩니다.
    multiset<int> ratings(korean.begin(), korean.end());

    for (int rus = 0; rus < n; ++rus) {
        // 한국 팀에서 가장 높은 점수가 러시아 선수보다 낮은 경우
        if (*ratings.rbegin() < russian[rus]) {
            // 가장 낮은 점수의 선수로 매칭 (패배 처리)
            ratings.erase(ratings.begin());
        } else {
            // 러시아 선수를 이길 수 있는 한국 선수 중 가장 낮은 점수의 선수로 매칭 (승리 처리)
            ratings.erase(ratings.lower_bound(russian[rus]));
            ++wins;
        }
    }

    return wins;
}

int main() {
    // 임의의 값을 입력합니다.
    // 예제:
    // 러시아 팀 점수: 3000, 2700, 2800, 2200, 2500
    // 한국 팀 점수: 2800, 2750, 2995, 1800, 2600
    vector<int> russian = {3000, 2700, 2800, 2200, 2500};
    vector<int> korean = {2800, 2750, 2995, 1800, 2600};

    int wins = order(russian, korean);

    cout << "한국 팀의 최대 승리 수: " << wins << endl;

    return 0;
}
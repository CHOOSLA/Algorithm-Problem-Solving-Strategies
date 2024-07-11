#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// 여행하는 외판원 문제
// 각 점과 가중치가 있는 간선이 있을 때, 모든 점을 방문한 후
// 시작지점으로 오는 비용이 가장 적은 경로를 정하는 문제
double shortestPath(vector<int> &path, vector<bool> &visited, double currentLength);

int n;             // 도시의 수
double dist[8][8]; // 두 도시 간의 거리를 저장하는 배열

int main(int argc, char const *argv[])
{
    int T;
    // freopen("inputs/traveling-sales-man.txt", "r", stdin);
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++)
    {
        // 도시의 갯수 n
        cin >> n;
        // 각 도시간의 거리 가중치
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                double tmp;
                cin >> tmp;
                dist[i][j] = tmp;
            }
        }

        double result = INFINITY;
        for (int i = 0; i < n; i++)
        {
            vector<int> path;
            vector<bool> visited;
            for (int j = 0; j < n; j++)
            {
                visited.push_back(false);
            }
            path.push_back(i);
            visited[i] = true;
            double currentLength = 0.0;
            double tmp = shortestPath(path, visited, currentLength);
            result = min(result, tmp);
        }
        cout << fixed;
        cout.precision(10);
        cout << result << endl;
    }

    return 0;
}

// 필요한 매개변수
// 경로를 저장할 path
// 방문한 점을 저장한 배열 visited
// 현재 경로의 가중치 currentLength
double shortestPath(vector<int> &path, vector<bool> &visited, double currentLength)
{
    // 기저 사례 : 모든 지점을 방문했을 경우
    // 모든 지점을 방문했을 경우 다시 시작 지점으로 돌아온 후 return
    if (path.size() == n)
    {
        return currentLength; // + dist[path[0]][path.back()];
    }

    // 방문되지 않은 모든 점을 방문하며
    // 재귀 호출로 거리 계산을 시킴
    double ret = INFINITY;
    for (int next = 0; next < n; ++next)
    {
        // 이미 방문한 노드라면 넘어감
        if (visited[next])
            continue;

        // 방문되지 않은 노드라면
        int now = path.back();
        visited[next] = true;
        path.push_back(next);
        double cand = shortestPath(path, visited, currentLength + dist[now][next]);

        ret = min(ret, cand);
        visited[next] = false;
        path.pop_back();
    }

    return ret;
}

#include <iostream>
#include <vector>

using namespace std;

bool canPlace(vector<vector<int>> &board, int y, int x, int type, int delta);
int countCover(vector<vector<int>> &board);

int main(int argc, char **argv)
{
    int T;

    freopen("../inputs/boardcover.txt", "r", stdin);
    cin >> T;
    for (int test_case = 1; test_case <= T; ++test_case)
    {
        int H, W;
        vector<vector<int>> board;
        cin >> H >> W;
        for (int i = 0; i < H; i++)
        {
            vector<int> tmp;
            for (int j = 0; j < W; j++)
            {
                char tile;
                cin >> tile;
                if (tile == '#')
                {
                    tmp.push_back(1);
                }
                else
                {
                    tmp.push_back(0);
                }
            }
            board.push_back(tmp);
        }

        cout << countCover(board) << endl;
    }
    return 0;
}

// 4가지 모션을 저장한 배열 = 4
// 3개의 칸을 차지함 = 3
// x,y의 좌표 = 2
int moving[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}},
};

// 중간에 종료하지 않는 게 포인트다..
// 다시 빼야하는 상황을 생각해서 코딩하자... ( 이해하는 데 2시간 걸림 )
bool canPlace(vector<vector<int>> &board, int y, int x, int type, int delta)
{
    bool ok = true;

    // 해당하는 모양의 블럭을 채운다.
    for (int i = 0; i < 3; i++)
    {
        const int ny = y + moving[type][i][0];
        const int nx = x + moving[type][i][1];

        // 경기장 밖으로 나갈경우
        if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
        {
            ok = false;
        }
        else if ((board[ny][nx] += delta) > 1)
        {
            ok = false;
        }
    }

    return ok;
}

int countCover(vector<vector<int>> &board)
{
    // 왼쪽 위부터 블럭을 채워 나간다.
    // 겹치는 건 고려하지 않고 모든 형태의 L자를 채우는 코드
    int y = -1, x = -1;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 0)
            {
                y = i;
                x = j;
                break;
            }
        }

        // 찾았으므로 반복문을 종료시킨다
        if (y != -1)
            break;
    }

    // 기저 사례1 : 모든 블럭을 넣었을 경우 종료한다
    // 이것은 서로 겹치는 경우를 고려하지 않고 일단 모든 칸에 모든 형태의 블럭을 채운다.
    if (y == -1)
        return 1;
    int ret = 0;
    for (int type = 0; type < 4; type++)
    {
        if (canPlace(board, y, x, type, 1))
            ret += countCover(board);

        canPlace(board, y, x, type, -1);
    }

    return ret;
}
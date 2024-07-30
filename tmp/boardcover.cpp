#include "iostream"

using namespace std;

// 1 <= H , W <= 20
// int board[20][20]; --> ❌ 부분 재귀호출마다 각 상태가 저장되어야 하기 때문
int H, W;
// 4가지 모션을 저장한 배열 = 4
// 3개의 칸을 차지함 = 3
// x,y의 좌표 = 2
int moving[4][3][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}},
};

int countSet(int board[20][20]);
bool checkSet(int board[20][20], int y, int x, int sel, int delta);
int main(int argc, char const *argv[])
{
    int T;
    int test_case;
    freopen("../inputs/boardcover.txt", "r", stdin);
    cin >> T;
    for (int test_case = 0; test_case < T; test_case++)
    {
        // 보드 불러오기
        cin >> H >> W;
        int board[20][20];
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                char tile;
                cin >> tile;
                if (tile == '#')
                {
                    board[i][j] = 1;
                }
                else
                {
                    board[i][j] = 0;
                }
            }
        }

        // L 모양의 블럭을 해당 블럭에 겹치지 않게 채워야한다.
        // 무식한 방법을 이용해서 한번 만들어보자
        // 기저 사례 : 내부의 .이 없을 때 count
        // L의 4가지 모양으로 모두 검사한다.
        // 만약에 겹치는 부분이 있다면 트리 구조 가지치기
        // 겹치는 곳을 확인하긴 위한 변수 checkBoard[][]
        // 가능한 L의 움직임이 담긴 move
        cout << countSet(board) << endl;
    }
}

int countSet(int board[20][20])
{
    int result = 0;
    // base case
    // 흰색칸인 x,y를 찾는다
    // ❌ 흰색칸을 찾으면 break 해줘야하는 데 안함
    int y = -1, x = -1;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (board[i][j] < 1)
            {
                y = i;
                x = j;
                break;
            }
        }
        if (y != -1)
            break;
    }

    if (y == -1)
    {
        return 1;
    }

    // 4가지 행동을 재귀해서 확인한다.
    // 겹치지 않은 경우만 재귀호출 --> 어차피 겹쳐버리면 모두 무의미
    for (int i = 0; i < 4; i++)
    {
        if (checkSet(board, y, x, i, 1))
        {
            result += countSet(board);
        }
        checkSet(board, y, x, i, -1);
    }
    return result;
}

// 선택된 행동이 겹치냐 안 겹치냐 판단

bool checkSet(int board[20][20], int y, int x, int sel, int delta)
{
    // 일단 블럭을 둔다
    // 재귀호출 나중에 알아서 빼줌 ( pop 작업 )
    bool clear = true;
    for (int i = 0; i < 3; i++)
    {
        const int dy = y + moving[sel][i][0];
        const int dx = x + moving[sel][i][1];

        // 경기장 밖으로 나갔을 경우
        if (dx < 0 || dx >= W || dy < 0 || dy >= H)
        {
            clear = false;
        }
        else if ((board[dy][dx] += delta) > 1)
            clear = false;
    }

    return clear;
}

#include "iostream"

using namespace std;

// 1 <= H , W <= 20
int board[20][20];

int main(int argc, char const *argv[])
{
    int T;
    int test_case;
    freopen("../inputs/boardcover.txt", "r", stdin);
    cin >> T;
    for (int test_case = 0; test_case < T; test_case++)
    {
        int H, W;
        cin >> H >> W;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                cin >> board[i][j];
                cout << board[i][j];
            }
            cout << endl;
        }
    }
}
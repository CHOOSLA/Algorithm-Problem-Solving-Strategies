#include <cstdio>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// 정방 행렬 클래스
class SquareMatrix{
    public:
    int size;
    vector<vector<double>>mat;
    
    SquareMatrix(int n) : size(n), mat(n, vector<double>(n,0.0)){}
    
    SquareMatrix operator*(const SquareMatrix& other) const {
        SquareMatrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    result.mat[i][j] = result.mat[i][j] + mat[i][j] * other.mat[i][j];
                }
                
            }
            
        }
        return result;
    }
};


// 거듭제곱의 분할정복
SquareMatrix pow(const SquareMatrix& mat, int k){
    if(k == 1) return mat;
    if(k%2==0){
        SquareMatrix half = pow(mat,k/2);
        return half * half;
    }else{
        return mat * pow(mat,k-1);
    }
}


// 지니어스
int n, k, m;
int length[50], pref[10];
double T[50][50];

int	main(int argc, char **argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("../inputs/genius.txt", "r", stdin);

    int cc;
    cin >> cc;;
    for (int c = 0; c < cc; c++)
    {
        cin >> n >> k >> m;
        cout << k;
        for (int i = 0; i < n; i++)
        {
            cin >> length[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> T[i][j];
            }
        }
        
        for (int i = 0; i < m; i++)
        {
            cin >> pref[i];
        }
        
    }
    

    system("pause");
    return 0;
}

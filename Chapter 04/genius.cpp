#include "bits/stdc++.h"
#include <algorithm>
#include <vector>

using namespace std;

// 행렬에 대한 클래스
class SquareMatrix{
    public:
    int size;
    vector<vector<double> > mat;
    
    SquareMatrix(int n) : size(n), mat(n, vector<double>(n,0.0)){}

    SquareMatrix operator*(SquareMatrix& other){
        SquareMatrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    result.mat[i][j] = result.mat[i][j] + mat[i][k] * other.mat[k][j];
                }
                
            }
            
        }
        return result;
    }
};

// 행렬 거듭제곱의 분할 정복
SquareMatrix pow(SquareMatrix& mat, int k){
    if(k==1) return mat;
    if(k % 2 == 0){
        SquareMatrix half = pow(mat, k /2);
        return half * half;
    }else{
        SquareMatrix tmp = pow(mat, k -1);
        return mat * tmp;
    }
}

int n,k,m;
int length[50];
double T[50][50];
int prefer[10];



int	main(int argc, char **argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("../inputs/genius.txt","r",stdin);
    int cc;
    cin >> cc;
    for (int c = 0; c < cc; c++)
    {        
        cin >> n >> k >> m;
        cout << n << endl;
        for (int i = 0; i < k; i++)
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
            cin >> prefer[i];
        }
        
        cout << T[3][3] << endl;;
        
    }
    
    return 0;
}

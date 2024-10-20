#include "bits/stdc++.h"
#include <valarray>
#include <vector>

using namespace std;

const int MOD = 10 * 1000 * 1000;
// 행렬 곱을 하는 클래스를 정방행렬 정의
class SquareMatrix{
    public:
    int size;
    vector<vector<int> > mat;
    
    // 초기화
    SquareMatrix(int n) : size(n), mat(n, vector<int>(n,0)){}

    // 행렬을 곱하기 위한 연산자 오버라이딩
    SquareMatrix operator*(SquareMatrix& other){
        SquareMatrix result(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                for (int k = 0; k < size; k++)
                {
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
                
            }
            
        }
        return result;
    }
};

// 행렬거듭제곱 분할정복
SquareMatrix pow(SquareMatrix mat,int n){
    if(n==0) return 0;
    if(n==1) return mat;
    if(n % 2 == 0){
        SquareMatrix half = pow(mat, n /2);
        return half * half;
    }else{
        SquareMatrix tmp = pow(mat , n-1);
        return mat * tmp;
    }
}

int fibo(int n){
    if(n == 0) return 0;
    SquareMatrix W(2);
    W.mat[0][0] = 1; W.mat[0][1] = 1;
    W.mat[1][0] = 1; W.mat[1][1] = 0;
    SquareMatrix result = pow(W,n);
    return result.mat[1][1];
}


int	main(int argc, char **argv)
{
    
    int n;
    std::cout << "피보나치 수열에서 구할 n번째 값을 입력하세요: ";
    std::cin >> n;

    int result = fibo(n);
    std::cout << n << "번째 피보나치 수: " << result << std::endl;

    return 0;

    system("pause");
    return 0;
}

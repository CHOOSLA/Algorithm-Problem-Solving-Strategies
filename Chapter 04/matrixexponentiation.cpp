#include "bits/stdc++.h"
#include <vector>

using namespace std;

// 행렬 거듭제곱을 이용한 피보나치
const int MOD = 10 * 1000 * 1000;

// 정사각행렬
class SquareMatrix{
public:
    int size;
    vector<vector<int> > mat;
    
    SquareMatrix(int n) : size(n), mat(n, vector<int>(n,0)){}

    SquareMatrix operator*(const SquareMatrix& other){
        SquareMatrix result(size);
        for(int i=0; i < size; i++){
            for (int j=0; j < size; j++) {
                for (int k = 0; k < size; k++)
                {
                    result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
            }
        }
        return result;
    }
};

// 행렬 제곱함수
SquareMatrix pow(SquareMatrix& A, int n){
    if(n == 1) return A;
    // 짝수면
    if( n % 2 == 0){
        SquareMatrix half = pow( A  , n /2 );
        return half * half;
    }else{
        // 홀수면
        return A * pow(A , n-1);
    }
}

int fibo(int n){
    if(n==0) return 0;
    SquareMatrix W(2);
    W.mat[0][0] = 1 , W.mat[0][1] = 1;
    W.mat[1][0] = 1 , W.mat[1][1] = 0;

    SquareMatrix result = pow(W,n);
    return result.mat[1][1];
}

int main(int argc, const char** argv) {
int n;
    std::cout << "피보나치 수열에서 구할 n번째 값을 입력하세요: ";
    std::cin >> n;

    int result = fibo(n);
    std::cout << n << "번째 피보나치 수: " << result << std::endl;

    return 0;
}
#include "bits/stdc++.h"
#include <algorithm>
#include <cstdint>
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
double T[50][50] = {0.0,};
int prefer[10];


// 행렬벡터 거듭제곱을 이용한 풀이
vector<double> getprob(){
    // 4n * 4n 크기의 행렬 W 생성
    SquareMatrix W(4* n);
    
    // C_time 에서 C_time+1 으로 그대로 전이 되는
    // time - 3 ~ time -1  >> time - 2 ~ time
    // 를 그대로 복사
    for(int i = 0; i < 3 * n; ++i)
    {
        W.mat[i][i + n] = 1.0;
    }
    
    // 0 ~ 3n - 1 까지 복사후 time + 1 에 대한 것
    // 이것은 아직 일어난 일이 아니기 때문에 전이 확률을 채워넣음
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            // 0번째 곡부터
            // 이전 곡(j)에서 i 번째 곡으로 전이될 확률
            W.mat[ 3 * n + i ][(4 - length[j]) * n + j] = T[j][i];
        }
    }
    
    // Wk를 만드는 작업
    SquareMatrix Wk = pow(W,k);
    
    vector<double> ret(n,0.0);
    // 각 곡마다 최종적인 전이확률 저장
    for(int song = 0; song < n; ++song)
    {
        for(int start = 0; start < length[song]; ++start)
        {
            // 해당 곡이 재생되는 모든 확률을 더함
            // 현재 곡이 어느 지점까지 재생됐는지 모르니
            // 곡이 재생될 수 있는 모든 시점에서 확률을 더함
            ret[song] += Wk.mat[(3-start) * n + song][3 * n];
        }
        
        
    }
    return ret;
}


int	main(int argc, char **argv)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    if(!freopen("../inputs/genius.txt","r",stdin)){
        cerr << "입력 파일을 찾을 수 없습니다." << endl;
        return 1;
    };

    int cc;
    cin >> cc;
    for (int c = 0; c < cc; c++)
    {   
        // n : 곡의 개수 , k : 분 , m : 좋아하는 노래 개수     
        cin >> n >> k >> m;

        // 노래의 길이 입력
        for (int i = 0; i < n; i++)
        {
            cin >> length[i];
        }

        // 전이 확률 T 입력
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> T[i][j];
            }
        }
        
        // 좋아하는  노래의 번호 입력
        for (int i = 0; i < m; i++)
        {
             cin >> prefer[i];
        }
        
        vector<double> result = getprob();

        for(int i = 0; i < m; ++i)
        {
            printf("%.8f ",result[prefer[i]]);
        }
        cout << endl;
    }
    
    return 0;
}
 
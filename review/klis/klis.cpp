#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, k;
int arr[501];
int cacheLis[501];
long long cacheCnt[501];

long long MAX = 1000000000L;

int lis(int idx){
    int& ret = cacheLis[idx + 1];
    if(ret != -1) return ret;

    ret = 1;
    for(int next = idx +1; next < n; next++){
        if(idx ==-1 || arr[idx] < arr[next]){
            ret = max(ret, lis(next) + 1);
        }
    }

    return ret;
}

// 각 idx마다 lis의 크기를 세는 함수
int count(int idx){
    if(lis(idx) == 1) return 1;
    long long& ret = cacheCnt[idx + 1];
    if(ret != -1) return ret;
    ret = 0;
    for(int next = idx + 1; next < n; ++next){
        // 부분 lis가 같은 것들만 취급
        if((idx==-1 || arr[idx] < arr[next]) && lis(idx) == 1 + lis(next)){
            ret = min<long long>(MAX, ret + count(next));
        }
    }

    return ret;
}

void klis(int idx, int k, vector<int>& result){
    // 해당 인덱스를 저장
    if(idx!=-1) result.push_back(arr[idx]);

    // k번째를 탐색해 가면서 부분 lis를 만듦
    vector<pair<int,int>> follwers;
    for(int next = idx +1; next < n; ++next){
        if((idx==-1 || arr[idx] < arr[next]) && lis(idx) == 1 + lis(next)){
            // klis의 후보군을 모두 저장
            follwers.push_back(make_pair(arr[next], next));
        }
    }

    // 숫자를 오름 차순으로 정렬
    sort(follwers.begin(), follwers.end());

    for(int i=0; i < follwers.size(); ++i){
        int index = follwers[i].second;
        int cnt = count(index);

        if(cnt <= k){
            // k -1 번째 까지 구함
            k -= cnt;
        }else{
            // 부분 lis로 진입
            klis(index,k,result);
            break;
        }
    }
}


int main(void){
    int c;
    

    cin >> c;
    for(int cc=0; cc < c; cc++){
        cin >> n >> k;
        memset(cacheLis,-1,sizeof(cacheLis));
        memset(cacheCnt,-1,sizeof(cacheCnt));
        for(int i=0; i<n; i++){
            cin >> arr[i];
        }
        vector<int> result;

        klis(-1,k-1,result);

        for(int i=0; i < result.size(); ++i){
            printf("%d ", result[i]);
        }
        printf("\n");
    }
    return 0;
}
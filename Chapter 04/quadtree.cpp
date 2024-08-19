#include "bits/stdc++.h"

using namespace std;
// 애초에 뒤집어 버리는 생각
// 기존 분할 처리법에는 1/2의 생각을 가지고 접근하지만
// 그것은 보드의 크기의 문제로 구현하기 까다로우며
// 해당 그래프를 디코딩-뒤집기-인코딩을 실행하게 되면 실행시간 공간 모두 초과하게 된다.

// 기저 사례 : 해당 블럭이 w 이거나 b인 경우
// 매개 변수 해당 문자열을 가르키는 iterator포인터
string func(string::iterator &it)
{
    char head = *it; // 해당 포인터가 가르키는 문자열 추출
    ++it;            // 포인터 증가
    if (head == 'b' || head == 'w')
    {
        return string(1, head); //
    }
    string upperLeft = func(it);
    string upperRight = func(it);
    string lowerLeft = func(it);
    string lowerRight = func(it);

    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main(int argc, char const *argv[])
{
    freopen("../inputs/quadtree.txt", "r", stdin);
    int c;
    cin >> c;

    for (int i = 0; i < c; i++)
    {
        string tmp;
        cin >> tmp;
        string::iterator it = tmp.begin();
        cout << func(it) << endl;
    }

    return 0;
}

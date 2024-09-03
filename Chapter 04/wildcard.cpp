#include "bits/stdc++.h"

using namespace std;

// 와일드카드 패턴 w가 문자열 s에 대응되는지 여부를 반환한다.
bool match(const string &w, const string &s)
{
    // w[pos]와 s[pos]를 맞춰나간다.
    int pos = 0;
    while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
    {
        ++pos;
    }
    // 더이상 대응할 수 없으며 왜 while문이 끝났는지 확인한다.
    // 2. 패턴 끝에 도달해서 끝난 경우 : 문자열도 끝났어야 대응됨
    if (pos == w.size())
        return pos == s.size();

    // 4. *를 만나서 끝난 경우 : *에 몇 글자를 대응해야 할지 재귀 호출하면서 확인한다.
    if (w[pos] == '*')
    {
        for (int skip = 0; pos + skip < s.size(); skip++)
        {
            if (match(w.substr(pos + 1), s.substr(pos + skip)))
                return true;
        }
    }

    // 이 외에 경우에는 모두 대응하지 않는다.
    return false;
}

int main(int argc, char const *argv[])
{

    return 0;
}

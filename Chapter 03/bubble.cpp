#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

void pick(int n, vector<int> &picked, int toPick);
void printPicked(vector<int> &picked);

int main()
{
    vector<int> picked = {};
    pick(10, picked, 2);
    return 0;
};

void pick(int n, vector<int> &picked, int toPick)
{
    if (toPick == 0)
    {
        printPicked(picked);
        return;
    }
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for (int next = smallest; next < n; ++next)
    {
        picked.push_back(next);
        pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}

void printPicked(vector<int> &picked)
{
    for (auto &i : picked)
    {
        cout << i << ' ';
    }
    cout << endl;
}

#ifdef picnic

// taken[i] = i
#endif

#include "bits/stdc++.h"

using namespace std;

void makeCurve(const string &seed, int generation)
{
    if (generation == 0)
    {
        cout << seed;
        return;
    }

    for (int i = 0; i < seed.size(); i++)
    {
        if (seed[i] == 'X')
        {
            makeCurve("X+YF", generation - 1);
        }
        else if (seed[i] == 'Y')
        {
            makeCurve("FX-Y", generation - 1);
        }
        else
        {
            cout << seed[i];
        }
    }
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string seed = "FX";
    makeCurve(seed, 2);
    return 0;
}

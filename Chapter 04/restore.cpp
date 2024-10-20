#include "bits/stdc++.h"

using namespace std;

vector<string> seq;
int k;

int getOverlap(const string& a, const string& b) {
	for(int len = min(a.size(), b.size()); len > 0; --len) {
		if(a.substr(a.size()-len) == b.substr(0, len))
			return len;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    freopen("../inputs/restore.txt", "r", stdin);

    int c;
    cin >> c;
    for (int cc = 0; cc < c; cc++)
    {
        //memset(cache, -1, sizeof(cache));
        cin >> k;
        for (int i = 0; i < k; i++)
        {
            string tmp;

            cin >> tmp;
            seq.push_back(tmp);
        }
    }

    cout << getOverlap("cadabra", "dabrㅈ") << endl;

    return 0;
}

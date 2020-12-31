#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

int main()
{
    string input;
    int n, m;

    getline(cin, input);

    size_t pos = input.find(' ');
    size_t initialPos = 0;

    n = atoi(input.substr(0, pos).c_str());
    m = atoi(input.substr(pos, input.length()).c_str());

    vector<int> b;
    b.resize(n);

    for (int i = 0; i < n; ++i)
        cin >> b[i];

    unordered_set<int> forFind;
    list<int> result;

    int index = -1;
    int type = -1;
    bool crack = false;

    for (int i = 0; i < n; ++i)
    {
        if (forFind.find(i) != forFind.end())
            continue;

        if (b[i] != type)
        {
            type = b[i];
            forFind.insert(i);
            cout << i << ' ';

            if (crack)
            {
                i = index - 1;
                crack = false;
            }

            continue;
        }

        if (crack == false)
        {
            index = i;
            crack = true;
        }
    }

}
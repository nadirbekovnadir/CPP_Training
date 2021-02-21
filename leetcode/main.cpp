#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>
#include <queue>
#include <unordered_map>

using namespace std;

int comp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

int arrayPairSum(vector<int> &nums)
{
    qsort(&nums[0], nums.size(), sizeof(int), comp);

    int result = 0;
    for (int i = 0; i < nums.size(); i += 2)
        result += nums[i];

    return result;
}

int maximumWealth(vector<vector<int>> &accounts)
{
    int max = 0;
    int current = 0;

    vector<int> *link;

    for (int i = 0; i < accounts.size(); ++i)
    {
        link = &accounts[i];
        for (int j = 0; j < link->size(); ++j)
        {
            current += link->at(j);
        }
        if (current > max)
            max = current;

        current = 0;
    }

    return max;
}

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> result;
    result.resize(numRows);

    for (int i = 0; i < numRows; ++i)
    {
        result[i].resize(i + 1);
    }

    if (numRows < 1)
    {
        return result;
    }

    result[0][0] = 1;

    if (numRows < 2)
    {
        return result;
    }

    vector<int> *link0;
    vector<int> *link1 = &result[1];
    link1->at(0) = 1;
    link1->at(1) = 1;

    int i, j;
    for (i = 2; i < numRows; ++i)
    {
        link0 = link1;
        link1 = &result[i];

        link1->at(0) = 1;
        for (j = 0; j < link0->size() - 1; ++j)
        {
            link1->at(j + 1) = link0->at(j) + link0->at(j + 1);
        }
        link1->at(j + 1) = 1;
    }

    return result;
}

vector<int> getRow(int rowIndex)
{
    vector<int> result;
    result.resize(rowIndex + 1);

    result[0] = 1;

    if (rowIndex == 0)
    {
        return result;
    }

    result[0] = 1;
    result[1] = 1;

    if (rowIndex == 1)
    {
        return result;
    }

    int i, j;
    int crV = 1;
    int oldR;

    for (i = 2; i <= rowIndex; ++i)
    {
        for (j = 1; j < i; ++j)
        {
            oldR = result[j];
            result[j] = crV + result[j];
            crV = oldR;
        }
        result[j] = 1;
    }

    return result;
}

int subarraysDivByK(vector<int> &A, int K)
{
    int cnt = 0;
    int *C = new int[K];

    int i;
    int lastV = 0;

    for (i = 0; i < K; ++i)
        C[i] = 0;

    C[0] = 1;
    int aSizeMinusOne = A.size() - 1;
    for (i = 0; i < aSizeMinusOne; ++i)
    {
        A[i + 1] += A[i];
        C[(A[i] % K + K) % K]++;
    }
    C[(A[aSizeMinusOne] % K + K) % K]++;

    for (i = 0; i < K; ++i)
        cnt += C[i] * (C[i] - 1) / 2;

    return cnt;
}

int minSubarray(vector<int> &nums, int p)
{
    uint64_t cur_r = 0;

    const int n = nums.size();
    int i;
    for (i = 0; i < n; ++i)
        cur_r += nums[i];
    cur_r %= p;

    if (cur_r == 0)
        return 0;

    unordered_map<int, int> m = {{0, -1}};

    int sum = 0;
    int temp;
    int res = n;
    unordered_map<int, int>::iterator iter;
    for (i = 0; i < n; ++i)
    {
        sum = (sum + nums[i]) % p;
        iter = m.find((sum - cur_r + p) % p);

        if (iter != m.end())
        {
            if ((temp = i - iter->second) < res)
                res = temp;
        }

        m[sum] = i;
    }

    return res == n ? -1 : res;
}

int main(int, char **)
{
    vector<int> test1;

    test1.push_back(26);
    test1.push_back(19);
    test1.push_back(11);
    test1.push_back(14);

    test1.push_back(18);
    test1.push_back(4);
    test1.push_back(7);
    test1.push_back(1);

    test1.push_back(30);
    test1.push_back(23);
    test1.push_back(19);
    test1.push_back(8);

    test1.push_back(10);
    test1.push_back(6);
    test1.push_back(26);
    test1.push_back(3);

    //[ 26, 19, 11, 14, 18, 4, 7, 1, 30, 23, 19, 8, 10, 6, 26, 3 ]

    vector<int> test2;

    test2.push_back(3);
    test2.push_back(1);
    test2.push_back(4);
    test2.push_back(2);

    int v1 = 26;
    int v2 = 6;

    for (auto item : test2)
        cout << item << ' ';

    cout << endl;

    cout << minSubarray(test2, v2) << endl;
}

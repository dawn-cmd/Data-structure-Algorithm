//
// Created by LightString on 1/25/2023.
//
#include "bits/stdc++.h"
using namespace std;
using LL = long long;
class BIT {
private:
    vector<LL> tree;
    LL lowbit(const int &x) {
        return x & (-x);
    }
public:
    BIT (const LL &n) {
        tree = vector<LL>(n + 1);
        for (auto &num: tree)
            num = 0;
    }
    void update(int id, const int &val) {
        while (id < tree.size())
        {
            tree[id] += val;
            id += lowbit(id);
        }
    }
    LL query(int id) {
        LL ans = 0;
        while (id)
        {
            ans += tree[id];
            id -= lowbit(id);
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int m;
    cin >> n >> m;
    BIT bit(n);
    for (int i = 1, tmp; i <= n; ++i)
    {
        cin >> tmp;
        bit.update(i, tmp);
    }
    int opt;
    while (m--)
    {
        cin >> opt;
        switch (opt) {
            case 1 :
            {
                int id;
                int val;
                cin >> id >> val;
                bit.update(id, val);
                break;
            }
            case 2 :
            {
                int l;
                int r;
                cin >> l >> r;
                cout << bit.query(r) - bit.query(l - 1) << '\n';
                break;
            }
        }
    }
}
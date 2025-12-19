#include <bits/stdc++.h>

using namespace std;
struct edge
{
    int from, to;
    double dist;
};
vector<vector<pair<int, double>>> MST;
vector<int> R;
inline bool sorto(const edge &lhs, const edge &rhs)
{
    return lhs.dist < rhs.dist;
}

double lowerBound = 0;

inline int fint(int v) { return R[v] == v ? v : R[v] = fint(R[v]); }

inline void onion(int a, int b, double w)
{

    if (fint(a) == fint(b))
        return;
    R[fint(b)] = fint(a);
    MST[a].push_back({b, w});
    MST[b].push_back({a, w});
    lowerBound += w;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;

    cin >> n >> m;
    vector<edge> Edges(m);
    MST.resize(n + 1);
    R.resize(n + 1);
    int offNode = 1;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        double c;
        cin >> a >> b >> c;

        Edges[i] = {a, b, c};
    }
    for (int i = 1; i <= n; i++)
        R[i] = i;

    sort(Edges.begin(), Edges.end(), sorto);

    for (auto &e : Edges)
    {
        if (e.from == offNode || e.to == offNode)
            continue;
        onion(e.from, e.to, e.dist);
    }

    int cnt = 2;
    for (auto &e : Edges)
    {

        if (e.from == offNode || e.to == offNode)
        {
            lowerBound += e.dist;
            cnt--;
        }
        if (cnt == 0)
            break;
    }

    cout << "Lower Bound = " << lowerBound << "\n";
    return 0;
}
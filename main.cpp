#include <bits/stdc++.h>

using namespace std;

// creating graph
constexpr double Q = 1;
constexpr int inf = 1e9 + 7;
int iterations = 1000;
struct edge
{
    int to;
    double weight;
};

struct pathUpdate
{
    double cost;
    vector<int> path;
};
struct bestPath
{
    int to;
    double weight;
    double probability;
};

struct cmp
{
    bool operator()(const bestPath &lhs, const bestPath &rhs) const
    {
        return lhs.probability >= rhs.probability;
    }
};

vector<vector<edge>> Graph;
vector<vector<double>> Pheromone;
vector<set<bestPath, cmp>> BestPath;

// update Pheromone
void updatePheromone(vector<pathUpdate> &pUpdate, int n)
{
    // map<pair<int, int>, double> pheromoneUpt;
    vector<vector<double>> pheromoneUpt(n + 1, vector<double>(n + 1, 0));

    for (auto &path : pUpdate)
        for (int i = 0; i < path.path.size() - 1; i++)
            pheromoneUpt[path.path[i]][path.path[i + 1]] += (Q / path.cost);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;

            Pheromone[i][j] = (1 - Q) * Pheromone[i][j] + pheromoneUpt[i][j];
        }
}

// updating attractiveness of every edge for every node
void updateBestPath(int n)
{
    for (int i = 1; i <= n; i++)
    {
        BestPath[i].clear();
        double sumOfProbability = 0;
        for (auto e : Graph[i])
            sumOfProbability += (double(Q / e.weight)) * Pheromone[i][e.to];

        for (auto e : Graph[i])
        {
            double currentPathAttractiveness = (double(Q / e.weight)) * Pheromone[i][e.to];
            currentPathAttractiveness /= sumOfProbability;
            BestPath[i].insert({e.to, e.weight, currentPathAttractiveness});
        }
    }
}

// searching for best next node
void inline nextVertex(vector<int> &path, int v, set<int> &vis, double &cost, const int n)
{
    path.push_back(v);
    vis.insert(v);
    if (path.size() == n + 1)
        return;

    for (auto w : BestPath[v])
    {
        if (vis.count(w.to) && (path.size() != n || (path.size() == n && w.to != path[0])))
            continue;
        cost += w.weight;
        nextVertex(path, w.to, vis, cost, n);
        break;
    }
}
// simulate ant
pathUpdate simulateAnt(int currentStart, const int n)
{
    vector<int> path;
    set<int> vis;
    double cost = 0;
    nextVertex(path, currentStart, vis, cost, n);

    return {cost, path};
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;

    cin >> n >> m;

    Graph.resize(n + 1);
    Pheromone.resize(n + 1);
    BestPath.resize(n + 1);

    int a, b;
    double c;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        Graph[a].push_back({b, c});
        Graph[b].push_back({a, c});
    }

    for (int i = 1; i <= n; i++)
        Pheromone[i].resize(n + 1, 1);

    pathUpdate bestAns = {inf, {}};
    while (iterations--)
    {

        updateBestPath(n);
        vector<pathUpdate> pUpdate;
        for (int i = 1; i <= n; i++)
            pUpdate.push_back(simulateAnt(i, n));

        // update Pheromone
        updatePheromone(pUpdate, n);

        for (auto &el : pUpdate)
            if (el.cost < bestAns.cost)
                bestAns = el;
    }

    cout << "Best cost = " << bestAns.cost << "\n";
    cout << "Path: " << bestAns.path.size() << "\n";
    for (int w : bestAns.path)
        cout << w << ' ';

    cout << "\n";

    return 0;
}
// to do wielowątkowość
// zamień map na hash map

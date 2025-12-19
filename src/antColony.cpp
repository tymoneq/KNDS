#include "../include/antColony.h"
#include <iostream>

void AntColony::run()
{
    readData();
    findBestScore();
}

void inline AntColony::readData()
{
    cin >> n >> m;
    prepare();

    int a, b;
    double c;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        Graph[a].push_back({b, c});
        Graph[b].push_back({a, c});
    }
}

void inline AntColony::prepare()
{
    dim = n + 1;
    Graph.resize(n + 1);
    Pheromone.resize(n + 1);
    BestPath.resize(n + 1);
    pheromoneUpt.resize(dim * dim + 5, 0);

    for (int i = 1; i <= n; i++)
        Pheromone[i].resize(n + 1, 1);
}
void inline AntColony::updatePheromone(vector<pathUpdate> &pUpdate)
{

    for (auto &path : pUpdate)
        for (int i = 0; i < path.path.size() - 1; i++)
            pheromoneUpt[path.path[i] * dim + path.path[i + 1]] += (Q / path.cost);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;

            Pheromone[i][j] = (1 - Q) * Pheromone[i][j] + pheromoneUpt[i * dim + j];
        }

    fill(pheromoneUpt.begin(), pheromoneUpt.end(), 0.0);
}

// updating attractiveness of every edge for every node
void inline AntColony::updateBestPath()
{
    for (int i = 1; i <= n; i++)
    {
        BestPath[i].clear();
        double sumOfProbability = 0;
        for (const auto &e : Graph[i])
            sumOfProbability += (double(Q / e.weight)) * Pheromone[i][e.to];

        for (const auto &e : Graph[i])
        {
            double currentPathAttractiveness = (double(Q / e.weight)) * Pheromone[i][e.to];
            currentPathAttractiveness /= sumOfProbability;
            BestPath[i].insert({e.to, e.weight, currentPathAttractiveness});
        }
    }
}

// searching for best next node
void inline AntColony::nextVertex(vector<int> &path, int v, set<int> &vis, double &cost)
{
    path.push_back(v);
    vis.insert(v);
    if (path.size() == n + 1)
        return;

    for (const auto &w : BestPath[v])
    {
        if (vis.count(w.to) && (path.size() != n || (path.size() == n && w.to != path[0])))
            continue;
        cost += w.weight;
        nextVertex(path, w.to, vis, cost);
        break;
    }
}
// simulate ant
pathUpdate inline AntColony::simulateAnt(int currentStart)
{
    vector<int> path;
    set<int> vis;
    double cost = 0;
    nextVertex(path, currentStart, vis, cost);

    return {cost, path};
}

void inline AntColony::findBestScore()
{
    pathUpdate bestAns = {inf, {}};
    while (iterations--)
    {
        updateBestPath();
        vector<pathUpdate> pUpdate;
        for (int i = 1; i <= n; i++)
            pUpdate.push_back(simulateAnt(i));

        // update Pheromone
        updatePheromone(pUpdate);

        for (const auto &el : pUpdate)
            if (el.cost < bestAns.cost)
                bestAns = el;
    }

    cout << "Best cost = " << bestAns.cost << "\n";
    cout << "Path: " << bestAns.path.size() << "\n";
    for (int &w : bestAns.path)
        cout << w << ' ';

    cout << "\n";
}
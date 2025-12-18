#ifndef ANT_COLONY
#define ANT_COLONY

#include <vector>
#include <set>
using namespace std;
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

class AntColony
{
private:
    const double Q = 1;
    const double inf = 1e9 + 7;
    int iterations = 100;
    int dim;
    int n, m;

    vector<vector<edge>> Graph;
    vector<vector<double>> Pheromone;
    vector<set<bestPath, cmp>> BestPath;
    vector<double> pheromoneUpt;

public:
    void run();
    void updatePheromone(vector<pathUpdate> &pUpdate);
    void updateBestPath();
    void inline nextVertex(vector<int> &path, int v, set<int> &vis, double &cost);
    pathUpdate simulateAnt(int currentStart);
    void prepare();
    void readData();
    void findBestScore();
};

#endif

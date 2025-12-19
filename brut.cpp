#include <bits/stdc++.h>

using namespace std;

constexpr int N = 24;

double MATRIX[N][N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;

    cin >> n >> m;

    vector<int> Permutations;

    for (int i = 1; i <= n; i++)
        Permutations.push_back(i);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        double c;
        cin >> a >> b >> c;

        MATRIX[a][b] = c;
        MATRIX[b][a] = c;
    }
    double best_ans = numeric_limits<double>::max();

    do
    {

        double dist = 0;

        for (int i = 0; i < n - 1; i++)
            dist += MATRIX[Permutations[i]][Permutations[i + 1]];

        dist += MATRIX[Permutations[n - 1]][Permutations[0]];

        best_ans = min(best_ans, dist);

    } while (next_permutation(Permutations.begin(), Permutations.end()));

    cout << "Brutal = " << best_ans << "\n";

    return 0;
}
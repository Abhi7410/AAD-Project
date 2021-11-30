#include "headers.h"

int randNum(long int lower, long int upper)
{
    return (int)(random() % (upper - lower + 1) + lower);
}



bool DFS(int raph[maxN][maxN], int *parent, bool *visited, int n, int x, int t)
{

    // cout << x << " ";
    if (x == t)
        return true;
    visited[x] = true;

    for (int i = 0; i < n; ++i)
    {
        if (raph[x][i] > 0 && !visited[i])
        {
            parent[i] = x;
            if (DFS(raph, parent, visited, n, i, t))
                return true;
        }
    }
    return false;
}

int FordFulkerson(int graph[maxN][maxN], int n, int s, int t)
{

    int rGraph[maxN][maxN];
    int parent[maxN];
    bool visited[maxN];

    // Replicate the graph for residual one
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            rGraph[i][j] = graph[i][j];

    int max_flow = 0;

    while (DFS(rGraph, parent, visited, n, s, t))
    {
      
        memset(visited, false, sizeof(visited));
        int path_flow = 0xfffffff; // Current flow to add on the max flow later

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // cout << path_flow << endl;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
    // cout << max_flow << " ";
    return max_flow;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    srand(time(NULL));
    int graph[maxN][maxN];

    int n, m;
    cin >> n >> m;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            graph[i][j] = 0;
        }
    }

    for (int j = 0, a, b, k; j < m; ++j)
    {
        cin >> a >> b >> k;
        graph[a][b] = k;
    }
    int s, t;
    cin >> s >> t; // s -> starting point, t -> ending point

    //edmand
    // printf("%d %d %d\n", FordFulkerson(graph1,n1,souce,sink), EdmandKarp(graph1,n1,souce,sink),FordFulkerson(graph2,n2,souce,sink));
    
    int ans2 = FordFulkerson(graph, n, s, t);
    cout << "Maximum flow (Ford-fulkerson): ";
    cout << ans2 << endl;
}
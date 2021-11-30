#include "headers.h"

bool BFS(int ways[maxN][maxN], int *parent, bool *visited, int n, int s, int t)
{

    queue<int> q;

    parent[s] = -1;
    q.push(s);

    while (!q.empty())
    {

        int u = q.front();
        q.pop();

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i] && ways[u][i] > 0)
            {
                q.push(i);
                parent[i] = u;
                visited[i] = true;
            }
        }
    }

    return visited[t];
}

int EdmandKarp(int graph[maxN][maxN], int n, int s, int t)
{

    int rrGraph[maxN][maxN];
    int parent[maxN];
    bool visited[maxN];

    // Replicate the graph for residual one
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            rrGraph[i][j] = graph[i][j];

    int max_flow = 0;

    while (BFS(rrGraph, parent, visited, n, s, t))
    {
        // while(DFS(rGraph, parent, visited, n, s, t)){
        memset(visited, false, sizeof(visited));
        int path_flow = 0xfffffff; // Current flow to add on the max flow later

        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, rrGraph[u][v]);
        }
        // cout << path_flow << endl;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rrGraph[u][v] -= path_flow;
            rrGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
 
    return max_flow;
}

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    srand(time(NULL));
    int graph1[maxN][maxN];
   
    int n, m;
    cin >> n >> m;
  
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            graph1[i][j] = 0;
         
        }
    }

    for (int j = 0, a, b, k; j < m; ++j)
    {
        cin >> a >> b >> k;
        graph1[a][b] = k;
     
    }
    int s, t;
    cin >> s >> t; // s -> starting point, t -> ending point
  
    cout << "Maximum flow (Edmand-Karp): ";
    int ans2 = EdmandKarp(graph1, n,s,t);
    cout << ans2 << " ";
  
   
}
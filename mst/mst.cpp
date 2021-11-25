#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

//Prim algorithm
const int MAX = 1e4 + 5;
typedef pair<ll, int> PII;
bool marked[MAX];
vector<PII> adj[MAX];

int randNum(long int lower, long int upper)
{
    return (int)(random() % (upper - lower + 1) + lower);
}


ll prim(int x)
{
    priority_queue<PII, vector<PII>, greater<PII>> Q;
    int y;
    ll minimumCost = 0;
    PII pp;
    Q.push(make_pair(0, x));
    while (!Q.empty())
    {
       
        pp = Q.top();
        Q.pop();
        x = pp.second;
        
        if (marked[x] == true)
            continue;
        minimumCost += pp.first;
        marked[x] = true;
        for (int i = 0; i < adj[x].size(); ++i)
        {
            y = adj[x][i].second;
            if (marked[y] == false)
                Q.push(adj[x][i]);
        }
    }
    return minimumCost;
}


//kruskal algorithm

int id[MAX], nodes, edges;
pair<ll, pair<int, int>> p[MAX];

void initialize() //making parent of their own
{
    for (int i = 0; i < MAX; ++i)
        id[i] = i;
}

int root(int x)  //finding the parent or root
{
    while (id[x] != x)
    {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void union1(int x, int y)   //joining two separate subsets
{
    int a = root(x);
    int b = root(y);
    id[a] = id[b];
}

ll kruskal(pair<ll, pair<int, int>> p[])
{
    int x, y;
   ll cost, minimumCost = 0;
    for (int i = 0; i < edges; ++i)
    {
       
        x = p[i].second.first;
        y = p[i].second.second;
       
        cost = p[i].first;

        if (root(x) != root(y))
        {
            minimumCost += cost;
            union1(x, y);
        }
    }
    return minimumCost;
}

int main()
{

    cin.sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    srand(time(NULL));
    cout << "Enter number of nodes" << endl;
    cin >> nodes;

    initialize();
    edges = (nodes * (nodes + 1)) / 2;
    int k = 0;
    for (int i = 1; i < nodes; i++)
    {
        for (int j = i + 1; j <= nodes;j++)
        {
            int w = randNum(1,200);
            adj[i].push_back({w, j});
            adj[j].push_back({w, i});
            // cout << i << " " << j << " " << w << endl;
            p[k] = make_pair(w, make_pair(i, j));
            k++;
        }
     }

    clock_t s1 = clock();
    ll ans2 = prim(1);
    cout << "Prim: ";
    cout << ans2 << endl;
    cout.precision(10);
    cout << fixed << float(clock() - s1) / CLOCKS_PER_SEC << endl;

    // fflush(stdout);
    
    clock_t s2 = clock();
    sort(p, p + edges);
    ll ans1 = kruskal(p);
    cout << "Kruskal: ";
    cout << ans1 << endl;

    cout.precision(10);
    cout << fixed << float(clock() - s2) / CLOCKS_PER_SEC << endl;

 



    return 0;
}

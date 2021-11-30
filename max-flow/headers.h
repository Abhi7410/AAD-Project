#ifndef _header
#define _header


#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int randNum(long int lower, long int upper);

/*ford-fulkerson*/

#define maxN 101
// int graph[maxN][maxN];
bool DFS(int ways[maxN][maxN], int *parent, bool *visited, int n, int x, int t);
int FordFulkerson(int graph[maxN][maxN], int n, int s, int t);

/*edmand-karp*/
bool BFS(int ways[maxN][maxN], int *parent, bool *visited, int n, int x, int t);
int EdmandKarp(int graph[maxN][maxN], int n, int s, int t);

/*dinic*/
struct edge
{
    int a, b, f, c;
};
const int inf = 1000 * 1000 * 1000;
const int MAXN = 1050;

int n, m;
vector<edge> e;
int pt[MAXN]; // very important performance trick
vector<int> g[MAXN];
long long flow = 0;
queue<int> q;
int d[MAXN];
int lim;
void insert_edge(int a, int b, int c);
bool bfs();
bool dfs();
void dinic();


#endif
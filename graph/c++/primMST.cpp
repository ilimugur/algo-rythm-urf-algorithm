#include<bits/stdc++.h>

using namespace std;


class UndirectedGraph
{
    typedef vector< vector < pair<int, long long> > > AdjList;

    int V;    // Number of vertices
  
    AdjList adjList;
public:
    UndirectedGraph(int V);

    void addEdge(int u, int v, long long w);

    // Finds the shortest path from source to destination
    UndirectedGraph primMinimumSpanningTree();
};

UndirectedGraph::UndirectedGraph(int n) : adjList(n), V(n)
{
}
 
void UndirectedGraph::addEdge(int u, int v, long long w)
{
    adjList[u].emplace_back(v, w);
    adjList[v].emplace_back(u, w);
}
  
UndirectedGraph UndirectedGraph::primMinimumSpanningTree()
{
    set<int> included;
    set< pair<long long, pair<int, int> > > pq;

    int startIndex = 0; // Can be any valid vertex index
    included.insert(startIndex);
    for(int i=0; i < adjList[startIndex].size(); ++i)
    {
        int v = adjList[startIndex][i].first;
        long long vWeight = adjList[startIndex][i].second;
        pq.insert( make_pair(vWeight, make_pair(startIndex, v)) );
    }

    UndirectedGraph result(V);

    int leftToConnect = V - 1;
    while(!pq.empty() && leftToConnect > 0)
    {
        set< pair<long long, pair<int, int> > >::iterator it = pq.begin();
        long long vWeight = it->first;
        int u = it->second.first;
        int v = it->second.second;
        pq.erase(it);

        if(included.find(v) == included.end())
        {
            result.addEdge(u, v, vWeight);
            cout << "Added edge (" << u << ", " << v << ") with weight: " << vWeight << endl;

            for(int i=0; i < adjList[v].size(); ++i)
            {
                int w = adjList[v][i].first;
                long long wWeight = adjList[v][i].second;

                pq.insert( make_pair(wWeight, make_pair(v, w)) );
            }

            --leftToConnect;
            included.insert(v);
        }
    }

    return result;
}

// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    UndirectedGraph g(5);
    g.addEdge(0, 1, 3LL);
    g.addEdge(1, 3, 6LL);
    g.addEdge(3, 4, 2LL);
    g.addEdge(1, 2, 4LL);
    g.addEdge(2, 3, 1LL);

    UndirectedGraph mst = g.primMinimumSpanningTree();

    return 0;
}

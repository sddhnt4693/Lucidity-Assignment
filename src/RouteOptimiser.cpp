#include <bits/stdc++.h>

using namespace std;

class RouteOptimise {
public:
    vector<string> getOptimalPath(int nodes, vector<vector<pair<int, double>>> deliveryGraph,
                                  map<int, int> orderMap, map<int, string> reverseMap) {

        vector<vector<double>> distMatrix = getDistanceMatrix(nodes, deliveryGraph);
        initCache(nodes);
        vector<int> optimalPathNodes = getOptimalPathNodes(nodes, distMatrix, orderMap);
        vector<string> optimalPath = getOptimalPathFromNodes(optimalPathNodes,reverseMap);
        return optimalPath;
    }
private:
    vector<vector<double>>best;
    vector<vector<int>>lastEdge;
    vector<vector<int>> vis;
    void initCache(int n)
    {
        best.assign(1<<n, vector<double>(n, 1e6));
        vis.assign(1<<n, vector<int>(n ,0));
        lastEdge.assign(1 << n, vector<int>(n, -1));
    }

    static bool checkBitSet(int val, int bit)
    {
        return ( ((1<<bit)&val) > 0 );
    }

    vector<int> getOptimalPathNodes(int nodes, vector<vector<double>> distMatrix,
                                    map<int, int> orderMap) {
        best[1][0] = 0;
        map<int,int>revOrderMap;
        for ( auto it : orderMap )
        {
            revOrderMap[it.second] = it.first;
        }
        for (int i = 0; i < (1 << nodes); i++) {
            if ((i & (i - 1)) == 0)
                continue;
            for (int j = 0; j < nodes; j++) {
                //check if j is a pre-req of something
                if ( checkBitSet(i,j) ) {
                    if ( revOrderMap[j] )
                    {
                        if ( checkBitSet(i,revOrderMap[j]) )
                            continue;
                    }

                    int withoutJ = i - (1 << j);
                    for ( int k = 0; k < nodes; k++ ) {
                        if ( j == k || !checkBitSet(i,k) )
                            continue;
                        if (best[i][j] > best[withoutJ][k] + distMatrix[k][j])
                        {
                            best[i][j] = best[withoutJ][k] + distMatrix[k][j];
                            lastEdge[i][j] = k;
                        }
                    }
                }
            }

        }

        double ans = 1e6;
        int currentVertex = -1;
        for ( int i = 0; i < nodes; i++ )
        {
            if ( ans > best[(1 << nodes) - 1][i] )
            {
                ans = best[(1 << nodes) - 1][i];
                currentVertex = i;
            }
        }
        vector<int>path;
        int mask = (1 << nodes) - 1;
        while(currentVertex != -1)
        {
            path.push_back(currentVertex);
            int prevVertex = lastEdge[mask][currentVertex];
            mask -= (1 << currentVertex);
            currentVertex = prevVertex;
        }
        reverse(path.begin(), path.end());
        return path;
    }
    vector<string> getOptimalPathFromNodes(vector<int>path, map<int, string> reverseMap) {
        vector<string> result;

        for ( int i = 1; i < path.size(); i++ )
            result.push_back(reverseMap[path[i]]);
        return result;
    }
    vector<vector<double>> getDistanceMatrix(int nodes, vector<vector<pair<int, double>>> deliveryGraph) {
        vector<vector<double>> distMatrix(nodes, vector<double>(nodes,0));
        for(int i = 0; i< deliveryGraph.size(); i++){
            for(int j=0;j<deliveryGraph[i].size();j++) {
                int destination = deliveryGraph[i][j].first;
                double weight = deliveryGraph[i][j].second;
                distMatrix[i][destination] = weight;
            }
        }
        return distMatrix;
    }
};
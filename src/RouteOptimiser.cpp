#include <bits/stdc++.h>

#define debug1(a) cout<<#a<<" = "<<(a)<<endl;
#define debug2(a,b) cout<<#a<<" = "<<(a)<<", "<<#b<<" = "<<(b)<<endl;
#define debug3(a,b,c) cout<<#a<<" = "<<(a)<<", "<<#b<<" = "<<(b)<<", "<<#c<<" = "<<(c)<<endl;
#define debug4(a,b,c,d) cout<<#a<<" = "<<(a)<<", "<<#b<<" = "<<(b)<<", "<<#c<<" = "<<(c)<<", "<<#d<<" = "<<(d)<<endl;
#define debug5(a,b,c,d,e) cout<<#a<<" = "<<(a)<<", "<<#b<<" = "<<(b)<<", "<<#c<<" = "<<(c)<<", "<<#d<<" = "<<(d)<<", "<<#e<<" = "<<(e)<<endl;

using namespace std;

class RouteOptimise {
public:
    vector<string> OptimalPath(int nodes, vector<vector<pair<int, double>>> deliveryGraph,
                               map<int, int> orderMap, map<int, string> reverseMap) {

        vector<vector<double>> distMatrix = getDistanceMatrix(nodes, deliveryGraph);
        for(vector<double> v: distMatrix) {
            for(double i:v) {
                cout<<i<<" ";
            }
            cout<<endl;
        }
        vector<vector<int>> allValidOrderSubset = generateAllValidPaths(nodes, orderMap);

        for(auto v : allValidOrderSubset) {
            for(int i : v) {
                cout<<i<<" ";
            }
            cout<<endl;
        }

        vector<int> optimalPathNodes = getOptimalPathNodes(distMatrix, allValidOrderSubset);
        for(int i : optimalPathNodes) {
            cout<<i<<" ";
        }
        cout<<endl;
        vector<string> optimalPath = getOptimalPath(optimalPathNodes, reverseMap);
        for(string s : optimalPath) {
            cout<<s<<" ";
        }
        cout<<endl;
        return optimalPath;
    }
private:
    vector<string> getOptimalPath(vector<int> optimalPathNodes, map<int, string> reverseMap) {
        vector<string> optimalPath;
        for(int node : optimalPathNodes) {
            optimalPath.push_back(reverseMap[node]);
        }
        return optimalPath;
    }
    vector<int> getOptimalPathNodes(vector<vector<double>>& distMatrix, vector<vector<int>> allValidOrderSubset) {
        vector<int> ans;
        long time = INT_MAX;
        for(vector path : allValidOrderSubset) {
            long double curTime = distMatrix[0][path[0]];
            debug3(curTime, path[0], distMatrix[0][path[0]]);
            for(int i=0;i<path.size()-1;i++) {
                curTime += distMatrix[path[i]][path[i+1]];
                debug4(curTime, path[i], path[i+1], distMatrix[path[i]][path[i+1]]);
            }
            for(int i : path) {
                cout<<i<<" ";
            }
            cout<<curTime<<endl;
            if(curTime < time) {
                ans = path;
                time = curTime;
            }
        }
        return ans;
    }
    vector<vector<int>> generateAllValidPaths(int nodes, map<int, int> orderMap) {
        vector<vector<int>> ans;
        vector<int> subset;
        vector<bool> visited(nodes+1, 0);
        generatePathRecursively(ans, subset, nodes, visited, orderMap);
        return ans;
    }
    void generatePathRecursively(vector<vector<int>>& ans, vector<int> subset,
                                 int nodes, vector<bool>& visited, map<int, int> orderMap) {
        if(subset.size() == nodes-1) {
            ans.push_back(subset);
            return;
        }
        for(int i=1;i<nodes;i++) {
            if(visited[i] == true) continue;

            if(orderMap.count(i) != 0) {
                if(visited[orderMap[i]] == false)
                    continue;
            }

            subset.push_back(i);
            visited[i] = true;
            generatePathRecursively(ans, subset, nodes, visited, orderMap);
            visited[i] = false;
            subset.pop_back();
        }

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
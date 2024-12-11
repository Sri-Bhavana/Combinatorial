#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Function to check if two graphs are isomorphic
bool isIsomorphic(const vector<vector<int>>& graph1, const vector<vector<int>>& graph2, int v1, int v2, unordered_map<int, int>& mapping) {
    // Base case: If all vertices have been mapped, then the graphs are isomorphic
    if (v1 == graph1.size()) {
        return true;
    }

    // If the current vertex in graph2 has already been mapped, try another vertex
    if (mapping.find(v2) != mapping.end()) {
        return false;
    }

    // Mark the current mapping and recursively check for the rest of the vertices
    mapping[v2] = v1;

    // Check if the degrees of the current vertices are the same
    if (graph1[v1].size() != graph2[v2].size()) {
        mapping.erase(v2);
        return false;
    }

    // Check if the adjacent vertices are mapped correctly
    for (int u1 : graph1[v1]) {
        int u2 = graph2[v2].find(mapping[u1]);
        if (u2 == graph2[v2].end()) {
            mapping.erase(v2);
            return false;
        }
    }

    // If the recursive call is successful, the graphs are isomorphic
    if (isIsomorphic(graph1, graph2, v1 + 1, v2, mapping)) {
        return true;
    }

    // Backtrack: If the recursive call fails, remove the current mapping
    mapping.erase(v2);
    return false;
}

bool areGraphsIsomorphic(const vector<vector<int>>& graph1, const vector<vector<int>>& graph2) {
    // If the number of vertices is different, the graphs are not isomorphic
    if (graph1.size() != graph2.size()) {
        return false;
    }

    // Sort the adjacency lists of each vertex to handle isomorphic graphs with different edge orders
    for (int i = 0; i < graph1.size(); i++) {
        sort(graph1[i].begin(), graph1[i].end());
        sort(graph2[i].begin(), graph2[i].end());
    }

    // Use backtracking to find a vertex mapping that preserves edges
    for (int i = 0; i < graph1.size(); i++) {
        unordered_map<int, int> mapping;
        if (isIsomorphic(graph1, graph2, 0, i, mapping)) {
            return true;
        }
    }

    return false;
}


int main() {
    vector<vector<int>> graph1 = { {1, 2}, {0, 2}, {0, 1} };
    vector<vector<int>> graph2 = { {2, 1}, {0, 2}, {1, 0} };

    if (areGraphsIsomorphic(graph1, graph2)) {
        cout << "Graphs are isomorphic." << endl;
    }
    else {
        cout << "Graphs are not isomorphic." << endl;
    }

    return 0;
}
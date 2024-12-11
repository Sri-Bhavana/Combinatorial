#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "nauty.h"

using namespace std;

// function to load graph from text file
bool loadGraphFromFile(int n, int edges, char* filename, graph** g) {
    ifstream file(filename);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> (*g)[i][j];
        }
    }
    file.close();
    return true;
}

// Function to perform graph isomorphism using nauty library
bool isIsomorphicNauty(graph g1, graph g2) {
    int n = g1.nvertices;

    graph G1_copy = g1;
    graph G2_copy = g2;

    // Create a string for the arguments
    stringstream ss;
    ss << n << " " << n << " 1 1 ";

    char args[1000];
    strcpy(args, ss.str().c_str());

    // nauty's function to check isomorphism
    ISOMORPHISM* iso = isomorphic(&G1_copy, &G2_copy, args);

    if (iso == NULL) {
        cerr << "Error while using nauty" << endl;
        exit(EXIT_FAILURE);
    }

    bool is_isomorphic = (iso->f);
    free_ISOMORPHISM(iso);
    free_graph(&G1_copy);
    free_graph(&G2_copy);

    return is_isomorphic;
}


int main() {
    int n, m, edges1, edges2;

    cout << "Enter number of vertices in first graph: ";
    cin >> n;
    graph g1 = new_graph(n, 0);
    cout << "Enter number of edges in first graph: ";
    cin >> edges1;
    // Read edges of first graph from input or file
    // (Use the loadGraphFromFile function instead for file input)
    for (int i = 0; i < edges1; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(g1, u, v);
    }

    // Similarly, input data for the second graph 
    cout << "Enter number of vertices in second graph: ";
    cin >> m;
    graph g2 = new_graph(m, 0);
    cout << "Enter number of edges in second graph: ";
    cin >> edges2;
    for (int i = 0; i < edges2; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(g2, u, v);
    }

    // Check isomorphism
    bool isIsomorphic = isIsomorphicNauty(g1, g2);

    if (isIsomorphic) {
        cout << "Graphs are Isomorphic." << endl;
    }
    else {
        cout << "Graphs are not Isomorphic." << endl;
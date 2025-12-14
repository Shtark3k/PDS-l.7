#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

void buildAdjacencyMatrix(int** adj, int n, int m, ifstream& fin) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        adj[u - 1][v - 1] = 1; // орієнтоване ребро u → v
    }
}

void printAdjacencyMatrix(int** adj, int n) {
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << adj[i][j];
        }
        cout << "\n";
    }
}

void calculateDegrees(int** adj, int n, int* inDeg, int* outDeg) {
    for (int i = 0; i < n; i++) {
        inDeg[i] = 0;
        outDeg[i] = 0;
        for (int j = 0; j < n; j++) {
            outDeg[i] += adj[i][j];
            inDeg[i] += adj[j][i];
        }
    }
}

bool isHomogeneous(int* inDeg, int* outDeg, int n, int& degree) {
    degree = inDeg[0] + outDeg[0];
    for (int i = 1; i < n; i++) {
        if (inDeg[i] + outDeg[i] != degree) {
            return false;
        }
    }
    return true;
}

int main() {
    string inputFile, outputFile;

    cout << "Enter input file name: ";
    cin >> inputFile;

    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cerr << "Error: cannot open file!\n";
        return 1;
    }

    int n, m;
    fin >> n >> m;

    int** adj = new int* [n];
    for (int i = 0; i < n; i++) {
        adj[i] = new int[n] {0};
    }

    int* inDeg = new int[n] {0};
    int* outDeg = new int[n] {0};

    buildAdjacencyMatrix(adj, n, m, fin);
    fin.close();

    printAdjacencyMatrix(adj, n);
    calculateDegrees(adj, n, inDeg, outDeg);

    cout << "\nVertex degrees:\n";
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i + 1
            << ": in-degree = " << inDeg[i]
            << ", out-degree = " << outDeg[i]
            << ", total = " << inDeg[i] + outDeg[i] << endl;
    }

    int degree;
    if (isHomogeneous(inDeg, outDeg, n, degree)) {
        cout << "\nThe graph is homogeneous with degree " << degree << ".\n";
    }
    else {
        cout << "\nThe graph is not homogeneous.\n";
    }

    cout << "\nEnter output file name (or '-' to skip): ";
    cin >> outputFile;

    if (outputFile != "-") {
        ofstream fout(outputFile);
        if (!fout.is_open()) {
            cerr << "Error: cannot create output file!\n";
        }
        else {
            fout << "Adjacency Matrix:\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fout << setw(3) << adj[i][j];
                }
                fout << "\n";
            }

            fout << "\nVertex degrees:\n";
            for (int i = 0; i < n; i++) {
                fout << "Vertex " << i + 1
                    << ": in = " << inDeg[i]
                    << ", out = " << outDeg[i]
                    << ", total = " << inDeg[i] + outDeg[i] << "\n";
            }

            if (isHomogeneous(inDeg, outDeg, n, degree)) {
                fout << "\nGraph is homogeneous with degree " << degree << ".\n";
            }
            else {
                fout << "\nGraph is not homogeneous.\n";
            }

            fout.close();
            cout << "\nResults saved to: " << outputFile << endl;
        }
    }

    for (int i = 0; i < n; i++) {
        delete[] adj[i];
    }
    delete[] adj;
    delete[] inDeg;
    delete[] outDeg;

    return 0;
}
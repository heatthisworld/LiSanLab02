#pragma once
#include <vector>
#include "Graph.h"

using namespace std;

int valueOfMatrix(int n, vector<vector<int>> a);
int rankOfDeterminant(int n, vector<vector<int>> matrix);
Graph deleteEdge(const Graph& graph, int beg, int end);
Graph shrinkEdge(const Graph& graph, int beg, int end);

#ifndef __LISAN_LAB2_H
#define __LISAN_LAB2_H

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
using namespace std;

class Edge
{
public:
    int beg;
    int end;
    Edge(int b, int e) : beg(b), end(e) {}
};

class Graph
{
public:
    vector<vector<bool>> adj;
    vector<bool> vis;
    list<Edge> edge;
    int n, m; // nΪ������mΪ����

    Graph() { getGraph(); } // �Զ���ȡ�ļ�
    Graph(list<Edge> init);
    bool if_conn();
    void printGraph();
    Graph* tree;
    ~Graph();

private:
    Graph* dfs();
    void getGraph();
    void deleteInvaildEdge();
};

#endif
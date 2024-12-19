#include "Graph.h"

using namespace std;

void Graph::getGraph()
{
    ifstream file("Graph.txt");
    if (!file.is_open())
    {
        cerr << "can't open Graph.txt" << endl;
        return;
    }

    file >> n >> m;
    adj.resize(n, vector<bool>(n, false));

    for (int i = 0; i < m; i++)
    {
        int start, end;
        file >> start >> end;
        if (start > 0 && start <= n && end > 0 && end <= n)
        {
            adj[start - 1][end - 1] = adj[end - 1][start - 1] = true;
            edge.push_back(Edge(start, end));
        }
    }
    deleteInvaildEdge();
    file.close();
    tree = dfs();
}
// �����Ǳ��б��в��رߵ�����,�����Ǳ��漰���ĵ�����ֵ
Graph::Graph(list<Edge> init) : edge(init)
{
    deleteInvaildEdge();
    // n = m + 1;
    n = 0;
    for (Edge e : edge)
    {
        if (n < e.beg || n < e.end)
            n = (e.beg > e.end) ? e.beg : e.end;
    }
    adj.resize(n, vector<bool>(n, false));
    for (Edge e : edge)
    {
        adj[e.beg - 1][e.end - 1] = adj[e.end - 1][e.beg - 1] = true;
    }
    tree = dfs();
}

void Graph::printGraph()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

Graph* Graph::dfs()
{
    // ��ʼ����������
    vis.resize(n, false);
    // �������ı�
    list<Edge> init;

    int node = 0;
    for (int j = 0; j < n; j++)
    {
        vis[node] = true;
        for (int i = 0; i < n; i++)
        {
            if (adj[node][i] && !vis[i])
            {
                init.push_back(Edge(node + 1, i + 1));
                node = i;
                break;
            }
        }
    }
    if (n < m + 1)
        return new Graph(init);
    else
        return this;
}

bool Graph::if_conn()
{
    for (bool v : vis)
    {
        if (!v)
            return false;
    }
    return true;
}

void Graph::deleteInvaildEdge()
{
    vector<Edge> temp;
    for (auto it = edge.begin(); it != edge.end();)
    {
        bool isDuplicate = false;
        for (const Edge& tem : temp)
        {
            if ((it->beg == tem.beg && it->end == tem.end) || (it->beg == tem.end && it->end == tem.beg))
            {
                isDuplicate = true;
                it = edge.erase(it); // ɾ��Ԫ�أ�����ȡ��һ��Ԫ�صĵ�����
                break;               // �˳��ڲ�ѭ��
            }
        }
        if (it->beg == it->end)
        {
            isDuplicate = true;
            it = edge.erase(it); // ɾ��Ԫ�أ�����ȡ��һ��Ԫ�صĵ�����
        }
        if (!isDuplicate)
        {
            temp.push_back(*it);
            ++it; // ֻ����δɾ��Ԫ��ʱ�ŵ���������
        }
    }
    // ��������
    m = edge.size();
}

Graph::~Graph()
{
    if (tree != this)
        delete tree;
}
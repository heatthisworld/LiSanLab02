#include "tool.h"

// ����Ĳ�������Ϊ����ʽ�Ľ���������ʽ���飬����ֵΪ����ʽ��ֵ
int valueOfMatrix(int n, vector<vector<int>> a)
{
    // ʹ�õݹ��㷨��������ʽ��ֵ
    if (n == 1)
    {
        return a[0][0];
    }
    else if (n == 2)
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    else
    {
        int sum = 0;
        for (int k = 0; k < n; k++)
        {
            vector<vector<int>> b;
            for (int i = 1; i < n; i++)
            {
                vector<int> c;
                for (int j = 0; j < n; j++)
                {
                    if (j == k)
                        continue;
                    c.push_back(a[i][j]);
                }
                b.push_back(c);
            }
            sum = k % 2 == 0 ? sum + a[0][k] * valueOfMatrix(n - 1, b) : sum - a[0][k] * valueOfMatrix(n - 1, b);
        }
        return sum;
    }
}

// ����Ĳ���Ϊ����ʽ�Ľ���������ʽ���飬����ֵΪ�������
int rankOfDeterminant(int n, vector<vector<int>> matrix)
{
    // ������ƾ�����ȣ�����Ԫ�����б�Խ������м���1
    int row = 0;
    for (int col = 0; col < n && row < n; col++, row++) // ��ÿһ�п�ʼ����ÿһ������ֻ�� 1 �� 1 ����ȫ 0
    {
        int i = 0;
        for (i = row; i < n; ++i) // Ѱ����һ�е�һ���� 0 ����
        {
            if (matrix[i][col] != 0)
                break;
        }
        if (n == i)
            --row;
        else
        {
            swap(matrix[row], matrix[i]);
            for (int k = i + 1; k < n; k++)
            {
                if (0 != matrix[k][col])
                {
                    for (int j = col; j < n; j++)
                    {
                        matrix[k][j] ^= matrix[row][j]; // �õ� r �е� 1 ������һ��������ȫ���е� 1
                    }
                }
            }
        }
    }
    return row;
}
// ɾ����,û�ҵ������߾͸���һ��ԭͼ����
Graph deleteEdge(const Graph& graph, int beg, int end)
{
    // ǳ����һ��ԭͼ�ı�
    list<Edge> e_list = graph.edge;
    for (list<Edge>::iterator it = e_list.begin(); it != e_list.end(); it++)
    {
        if ((it->beg == beg && it->end == end) || (it->beg == end && it->end == beg))
        {
            e_list.erase(it);
            return Graph(e_list);
        }
    }
    return graph;
}

Graph shrinkEdge(const Graph& graph, int beg, int end)
{
    // ǳ����һ��ԭͼ�ı�
    list<Edge> e_list = graph.edge;
    int min = (beg > end) ? end : beg;
    int max = (beg < end) ? end : beg;
    for (list<Edge>::iterator it = e_list.begin(); it != e_list.end(); it++)
    {
        if (it->beg == max)
            it->beg = min;
        if (it->end == max)
            it->end = min;
        if (it->beg > max)
            it->beg--;
        if (it->end > max)
            it->end--;
    }
    return Graph(e_list);
}

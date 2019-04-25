
#ifndef MATTERSTATE_H
#define MATTERSTATE_H


#include "node.h"
#include <cstring>

using namespace std;

class CTask;

class CFieldOld {
public:

	CFieldOld();
	~CFieldOld();

	void	initData(CTask *task);
	void	clearData();
	double	loadData(string fName, int nCut);
	int getSize() { return nSize; }
	void	setSize(int nSizeNew) { nSize = nSizeNew; }

	void	setEdgeMode(bool edge_m) { bEdgeMode = edge_m; }
	bool	getEdgeMode() { return bEdgeMode; }

	inline Node &operator [] (const int i)
    {
        if(i < 0)		return bEdgeMode ? nodes[0]		  : left_edge;
		if(i > (int)nSize)   return bEdgeMode ? nodes[nSize-1] : right_edge;
        return nodes[i];
    }

	// ������� ������� ��� ������� ��������� � ����� �����

	Node* getnodes() { return nodes; }

	// �������, ������� ������ "����������" ��������� �������

	void setEdgeTransparent(void);

private:

	void	setEdge(Node &n, double x, double dm);

	Node	*nodes;		// ��������� �� ������ ����� �����
	int nSize;		// ������ �������

	Node	left_edge;	// ����� ��������� �������
	Node	right_edge;	// ������ ��������� �������
	bool	bEdgeMode;  // ����� ��������� ��������� �������
};


#endif
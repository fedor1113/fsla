
#ifndef MATTERSTATE_H
#define MATTERSTATE_H


#include "node.h"
#include <cstring>
using namespace std;

/*
   ���������� ������ CTask ������ ��������� task.h.
   ����� �������� �������������� ���� �� ����� �������.
*/

class CTask;


/*
   ����� MatterState �������� �� �������� � ������������� �������� 
   ������� (��������) ���� ���������� �������. �.�., ��  ������ �����:
   - �������� ���� �������������� �����;
   - ��������� � ������������ ������ ��� ���;
   - ���������� ��������� �������, ����������� �� �������� ����� ������� CTask.

   "�����" ������ � ��������� ��������� �������.
   ������������� ��� ������ �� ���������:
  
   1. setEdgeMode(false)  (�� ���������)
      ��� ��������� � ������ �������� �� ��������� �������� �������
	  ����� ���������� ����������� Node, ���������� ����� ��� ������
	  ��������� ��������.

	  ��������� Node'� ��� ����� ������ ����� ������ ������ ��������
	  �������� ��������� ms[-1] � ms[ms.getSize()]. ���� �������
	  �������� �� ��������� � private-������ setEdge(...).

   2. setEdgeMode(true)
      ��� ��������� � ������ �������� �� ��������� �������� �������
	  ����� ���������� ������ ��� ��������� Node �����.
*/

class MatterState
{
public:

	MatterState();
	~MatterState();

	void	initData(CTask *task);
	void	clearData();
	double	loadData(string fName, unsigned int nCut);
	unsigned int getSize() { return nSize; }
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
	unsigned int nSize;		// ������ �������

	Node	left_edge;	// ����� ��������� �������
	Node	right_edge;	// ������ ��������� �������
	bool	bEdgeMode;  // ����� ��������� ��������� �������
};


#endif
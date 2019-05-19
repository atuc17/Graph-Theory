#pragma once
#include <stack>
#include <queue>
#include <iostream>
#include <limits.h>
#include "Pair.h"
using namespace std;

class Graph
{
private:
	int soDinh, Count, inconnect, cnt;
	stack <int> LienThongManh;
	int Dinh[100][100];
	int CayKhung[100][100];
	int seen[1000];
	int trace[1000];
	int index[100];
	
public:
	int Low[100], Number[100];
	Pair pair[100];
	Graph();
	~Graph();
	void DFS(int s);
	void BFS(int s);
	void Visit(int u);
	void Nhap();
	void Xuat();
	void PrintPath(int, int);
	void AddEdge(int, int);
	void setDinh(int s) { soDinh = s; }
	int SoThanhPhanLienThong() { return inconnect; }
	void DemThanhPhanLienThong();
	void ThanhPhanLienThongManh();
	void XuatCayKhung();
	void SapXep(int, int);
	void ToMau();
};


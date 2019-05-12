#include "pch.h"
#include "Graph.h"


Graph::Graph()
{
	for (int i = 0; i < 100; i++)
	{
		memset(Dinh[i], 0, 100 * sizeof(int));
		memset(CayKhung[i], 0, 100 * sizeof(int));
		pair[i].Dinh = i;
		pair[i].Bac = 0;
		pair[i].DaToMau = 0;
	}
	memset(trace, -1, 1000 * sizeof(int));
	memset(seen, 0, 1000 * sizeof(int));
	memset(index, -1, 100 * sizeof(int));
	inconnect = 0;
}

Graph::~Graph()
{
}

void Graph::DFS(int u)
{
	/*
	seen[u] = 1;
	index[u] = inconnect;
	for (int v = 0; v < soDinh; v++)
	{
		if (Dinh[u][v] == 1 && seen[v] == 0)
		{
			trace[v] = u;
			DFS(v);
		}
	}
	*/
	
	stack <int> dinh;
	dinh.push(u); seen[u] = 1;
	index[u] = inconnect;
	while (!dinh.empty())
	{
		int s = dinh.top(); dinh.pop();
		index[s] = inconnect;
		for(int v = 0; v < soDinh; v++)
			if (Dinh[s][v] == 1 && seen[v] == 0)
			{
				trace[v] = s;
				CayKhung[s][v] = 1;
				seen[v] = 1;
				dinh.push(v);
			}
		
	}
	
}

void Graph::BFS(int s)
{
	queue <int> dinh;
	dinh.push(s);
	seen[s] = 1;
	index[s] = inconnect;
	do
	{
		int u = dinh.front(); dinh.pop();
		for(int v = 0; v < this->soDinh; v++)
			if (Dinh[u][v] == 1 && seen[v] == 0)
			{
				trace[v] = u;
				seen[v] = 1;
				dinh.push(v);
				CayKhung[u][v] = 1;
			}
	} while (!dinh.empty());
}
void Graph::Nhap()
{
	int u, v;
	cout << "Nhap so dinh: ";
	cin >> soDinh;
	cout << "Nhap canh, nhap -1 -1 de ket thuc\n";
	do
	{
		cin >> u >> v;
		if (u != -1 && v != -1)
		{
			Dinh[u][v] = 1;
			Dinh[v][u] = 1;
		}
	} while (u != -1 && v != -1);
}

void Graph::Xuat()
{
	for (int i = 0; i < soDinh; i++)
	{
		for (int j = 0; j < soDinh; j++)
			cout << Dinh[i][j] << " ";
		cout << "\n";
	}
}

void Graph::AddEdge(int u, int v)
{
	Dinh[u][v] = 1;
	Dinh[v][u] = 1;
	pair[u].Bac++;
	pair[v].Bac++;
}

void Graph::PrintPath(int s, int t)
{
	cout << "From " << s << " can visit: ";
	for (int v = 0; v < soDinh; v++)
		if (trace[v] >= 0)
			cout << v << " ";
	cout << "\n";
	if (trace[t] == -1)
		cout << "No path from " << t << "\n";
	else
	{
		while (t != s)
		{
			cout << t << "<-";
			t = trace[t];
		}
		cout << s << "\n";
	}
}

void Graph::DemThanhPhanLienThong()
{
	for(int v = 0; v < soDinh; v++)
		if (seen[v] == 0)
		{
			inconnect++;
			DFS(v);
		}
}

void Graph::XuatCayKhung()
{
	for (int i = 0; i < soDinh; i++)
	{
		for (int j = 0; j < soDinh; j++)
			cout << CayKhung[i][j] << " ";
		cout << endl;
	}
}

void Graph::SapXep(int l, int r)
{
	int i = l, j = r;
	int x = pair[(l + r) / 2].Bac;
	do
	{
		while (pair[i].Bac > x) i++;
		while (pair[j].Bac < x) j--;
		if (i <= j)
		{
			int tempDinh = pair[i].Dinh;
			int tempBac = pair[i].Bac;
			pair[i].Dinh = pair[j].Dinh;
			pair[i].Bac = pair[j].Bac;
			pair[j].Dinh = tempDinh;
			pair[j].Bac = tempBac;
			i++; j--;
		}
	} while (i <= j);
	if (i < r) SapXep(i, r);
	if (l < j) SapXep(l, j);
}

void Graph::ToMau()
{
	int i = 1;
	SapXep(0, this->soDinh - 1);
	for (int v = 0; v < this->soDinh; v++)
	{
		if (pair[v].DaToMau == 0)
		{
			pair[v].DaToMau = i;
			int u = pair[v].Dinh;
			for (int j = v + 1; j < soDinh; j++)
			{
				if (Dinh[pair[v].Dinh][pair[j].Dinh] == 0)
					pair[j].DaToMau = i;
			}
			i += 1;
		}
	}
}
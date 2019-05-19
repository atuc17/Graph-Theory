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
	memset(Low, 0, 100 * sizeof(int));
	memset(Number, 0, 100 * sizeof(int));
	inconnect = 0;
	Count = 0;
	cnt = 0;
}

Graph::~Graph()
{
}

void Graph::DFS(int u)
{
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
	/*
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
	*/
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
	if (Dinh[u][v] == 0)
	{
		pair[u].Bac++;
		Dinh[u][v] = 1;
	}
	
	if (Dinh[v][u] == 0)
	{
		pair[v].Bac++;
		Dinh[v][u] = 1;
	}
}

void Graph::Visit(int u)
{
	cnt += 1; Number[u] = cnt;
	Low[u] = Number[u];
	LienThongManh.push(u);
	seen[u] = 1;
	for (int v = 0; v < soDinh; v++)
	{
		if(Dinh[u][v] == 1)
			if (Number[v] && seen[v])
				Low[u] = std::min(Low[u], Number[v]);
			else
			{
				Visit(v);
				Low[u] = std::min(Low[u], Low[v]);
			}
	}
	if (Number[u] == Low[u])
	{
		Count += 1;
		int v;
		cout << "thanh phan lien thong " << Count << ": ";
		do
		{
			
			v = LienThongManh.top(); LienThongManh.pop();
			cout << v << " ";
			Number[v] = Low[v] = 123456789;
		} while (u != v);
		cout << endl;
	}
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
			for (int j = v + 1; j < this->soDinh; j++)
			{
				if (Dinh[pair[v].Dinh][pair[j].Dinh] == 0 && pair[j].DaToMau == 0)
				{
					int flag = 1;
					for (int k = 0; k < this->soDinh; k++)
					{
						if (Dinh[pair[j].Dinh][pair[k].Dinh] == 1 && pair[k].DaToMau == i)
							flag = 0;
					}
					if (flag)
						pair[j].DaToMau = i;
				}
					
			}
			i += 1;
		}
	}
}

void Graph::ThanhPhanLienThongManh()
{
	for (int i = 0; i < soDinh; i++)
		if (!Number[i])
			Visit(i);
	cout << Count;
}
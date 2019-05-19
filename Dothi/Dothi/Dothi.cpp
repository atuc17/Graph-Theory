// Dothi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "List.h"
#include "Graph.h"

int main()
{
	Graph g;
	/*
	g.setDinh(6);
	g.AddEdge(0, 1);
	g.AddEdge(1, 2);
	g.AddEdge(2, 0);
	g.AddEdge(3, 4);
	g.AddEdge(4, 5);
	g.AddEdge(5, 3);
	g.AddEdge(5, 1);
	g.Xuat();
	*/

	g.setDinh(81);
	int rows[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int cols[9] = { 0, 9, 18, 27, 36, 45, 54, 63, 72 };
	int rect[9] = { 0, 1, 2, 9, 10, 11, 18, 19, 20 };
	for (int r = 0; r < 9; r++)
	{
		for (int i = 0; i < 9; i++)
			for (int j = i + 1; j < 9; j++)
			{
				g.AddEdge(rows[i] + r, rows[j] + r);
				g.AddEdge(cols[i] + r, cols[j] + r);
				g.AddEdge(rect[i] + r, rect[j] + r);
			}
	}
	g.ToMau();
	for (int i = 0; i < 81; i++)
		cout << g.pair[i].Dinh << " " << g.pair[i].Bac << "\n";
	return 0;
}

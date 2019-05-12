// Dothi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "List.h"
#include "Graph.h"

int main()
{
	Graph g;
	g.setDinh(9);
	g.AddEdge(0, 1);
	g.AddEdge(1, 2);
	g.AddEdge(2, 4);
	g.AddEdge(0, 2);
	g.AddEdge(4, 3);
	g.AddEdge(1, 4);
	g.AddEdge(5, 6);
	g.AddEdge(6, 8);
	g.AddEdge(3, 6);
	g.AddEdge(4, 5);
	g.AddEdge(6, 7);
	g.ToMau();
	for (int i = 0; i < 9; i++)
		printf("Dinh %d Bac %d Mau %d\n", g.pair[i].Dinh, g.pair[i].Bac, g.pair[i].DaToMau);
	return 0;
}

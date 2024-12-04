#include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char** argv) {
	Graph G;
	Addr_Node P;

	CreateGraph(G);
	P=AlokasiNode('A');
	AddNewNode(G,P);
	P=AlokasiNode('B');
	AddNewNode(G,P);
	P=AlokasiNode('C');
	AddNewNode(G,P);
	P=AlokasiNode('D');
	AddNewNode(G,P);

	Connecting(G,'A','B');
	Connecting(G,'A','C');
	Connecting(G,'A','D');
	Connecting(G,'B','D');
	Connecting(G,'C','D');
	Show(G);

	cout<<"Disconnecting A D\n";
	Disconnecting(G,'A','D');
	Show(G);

	cout<<"Disconnecting A B\n";
	Disconnecting(G,'A','B');
	Show(G);

	cout<<"Disconnecting B D\n";
	Disconnecting(G,'B','D');
	Show(G);

	return 0;
}

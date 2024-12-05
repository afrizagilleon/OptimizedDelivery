    #include <iostream>

#include "graph.h"

using namespace std;

int main(int argc, char** argv) {
	Graph G;
	Addr_Kota P;

	CreateGraph(G);
	P=AlokasiKota("A");
	AddNewKota(G,P);
	P=AlokasiKota("B");
	AddNewKota(G,P);
	P=AlokasiKota("C");
	AddNewKota(G,P);
	P=AlokasiKota("D");
	AddNewKota(G,P);

	// Connecting(G,"A","B","Jl.Sisingamaharaja",30);
	// Connecting(G,"A","C","Jl.Katomos",20);
	// Connecting(G,"C","B","Jl.Setia Budi",30);
	// Connecting(G,"B","D","Jl.Jamin Ginting",200);
	// Connecting(G,"C","D","Jl.Littleindia",10);

	Connecting(G,"A","B","Jl.Sisingamaharaja",30);
	Connecting(G,"A","C","Jl.Katomos",20);
	Connecting(G,"C","B","Jl.Setia Budi",1);
	Connecting(G,"B","D","Jl.Jamin Ginting",1);
	Connecting(G,"C","D","Jl.Littleindia",10);
	Show(G);

	// cout<<"Disconnecting A D\n";
	// Disconnecting(G,"A","D");
	// Show(G);

	// cout<<"Disconnecting A B\n";
	// Disconnecting(G,"A","B");
	// Show(G);

	// cout<<"Disconnecting B D\n";
	// Disconnecting(G,"B","D");
	// Show(G);

    tempList L;
    CreateTempList(L);
	Dijkstra(G, L, "A", "D");

	return 0;
}

void menu(){

}

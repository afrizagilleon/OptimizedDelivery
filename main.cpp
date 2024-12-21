#include <iostream>
#include "graph.h"

using namespace std;

void menu(){
	cout<<"1. Add Kota\n";
	cout<<"2. Add Jalur\n";
	cout<<"3. Delete Kota\n";
	cout<<"4. Delete Jalur\n";
	cout<<"5. Show Graph\n";
	cout<<"6. Jalur Tercepat (Djikstra)\n";
	cout<<"7. Jalur Tercepat Alternatif (DFS)\n";
	cout<<"9. Exit\n";
	cout<<"Choose: ";
}

int main(int argc, char** argv) {
	Graph G;
	Addr_Kota P;

	CreateGraph(G);
	// P=AlokasiKota("A");
	// AddNewKota(G,P);
	// P=AlokasiKota("B");
	// AddNewKota(G,P);
	// P=AlokasiKota("C");
	// AddNewKota(G,P);
	// P=AlokasiKota("D");
	// AddNewKota(G,P);

	// Connecting(G,"A","B","Jl.Sisingamaharaja",30);
	// Connecting(G,"A","C","Jl.Katomos",20);
	// Connecting(G,"C","B","Jl.Setia Budi",30);
	// Connecting(G,"B","D","Jl.Jamin Ginting",200);
	// Connecting(G,"C","D","Jl.Littleindia",10);

	// Connecting(G,"A","B","Jl.Sisingamaharaja",30);
	// Connecting(G,"A","C","Jl.Katomos",20);
	// Connecting(G,"C","B","Jl.Setia Budi",1);
	// Connecting(G,"B","D","Jl.Jamin Ginting",1);
	// Connecting(G,"C","D","Jl.Littleindia",10);
	// Show(G);

	// cout<<"Disconnecting A D\n";
	// Disconnecting(G,"A","D");
	// Show(G);

	// cout<<"Disconnecting A B\n";
	// Disconnecting(G,"A","B");
	// Show(G);

	// cout<<"Disconnecting B D\n";
	// Disconnecting(G,"B","D");
	// Show(G);

	// Dijkstra(G, L, "A", "D");

	int inputMenu;
	while (inputMenu != 9) {
		menu();
		cin>>inputMenu;
		string kota1, kota2, jalan;
		string currentKota, destinationKota;
		string kota;
		string namaJalanTerblokir;
		int totalWaktu;
		switch(inputMenu){
			case 1:
				cout<<"Masukkan nama kota: ";
				cin>>kota;
				P=AlokasiKota(kota);
				AddNewKota(G,P);
				break;
			case 2:
				int waktu;
				cout<<"Masukkan nama kota 1: ";
				cin>>kota1;

				cout<<"Masukkan nama kota 2: ";
				cin>>kota2;

				cout<<"Masukkan nama jalan: ";
				cin>>jalan;

				cout<<"Masukkan waktu: ";
				cin>>waktu;
				Connecting(G,kota1,kota2,jalan,waktu);
				break;
			case 3:
				cout<<"Masukkan nama kota: ";
				cin>>kota;
				DeleteKota(G,kota);
				break;
			case 4:
				cout<<"Masukkan nama kota 1: ";
				cin>>kota1;

				cout<<"Masukkan nama kota 2: ";
				cin>>kota2;
				Disconnecting(G,kota1,kota2);
				break;
			case 5:
				Show(G);
				break;
			case 6:
				tempList L;
    			CreateTempList(L);
				totalWaktu = 0;
				cout<<"Masukkan kota asal: ";
				cin>>currentKota;
				cout<<"Masukkan kota tujuan: ";
				cin>>destinationKota;
				Dijkstra(G, L, currentKota, destinationKota,totalWaktu);
				break;
			case 7:
				cout<<"Masukkan kota asal: ";
				cin>>currentKota;
				cout<<"Masukkan kota tujuan: ";
				cin>>destinationKota;
				cout<<"Masukkan nama jalan terblokir: ";
				cin>>namaJalanTerblokir;
				DFSAlternative(G, currentKota, destinationKota, namaJalanTerblokir);
				break;
			case 9:
				break;
			default:
				cout<<"Input tidak valid\n";
				break;
		}
		cout<<"\n";
	}
	return 0;
}
